#include "xppch.h"
#include "CombatManager.h"
#include "Xperrty/Input/InputManager.h"
#include "Xperrty/World/SceneManager.h"
#include "Xperrty/Loader/TextureManager.h"	

#include "Xperrty/Containers/Array.h"
#include <filesystem>
#include "Xperrty/Time/Stopwatch.h"
// temp random
#include <cstdlib>

CombatManager::CombatManager() :playerController(), enemiesPool(1000), arrowsPool(1000), materialsPool(2000), removeMutex(), mainShader(Xperrty::Shader::getShader(Xperrty::Shader::getDefaultShaderPath())), arrowTexture(Xperrty::TextureManager::getTexture(6)), enemySpawnTimer(1), enemyTimer(0), threadPool(std::thread::hardware_concurrency()-2), kills(0), arrowSpawnMult(1), logTimer(2000, -1, this, &CombatManager::onLogTimerDone) {
	_instance = this;
	Xperrty::EventManager::addEventListener(Xperrty::UPDATE, this);
	enemiesPool.debug = true;
	setDifficulty(0);
	//kills = 20000;
	//Xperrty
}

void CombatManager::onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) {
	updateObjects();
	checkInput();
}

void CombatManager::internalUpdateArrows(float dt, int start) {
	for (int i = start; i < arrows.size() && i < start + 256; i++)
	{
		arrows[i].arrowComp->onUpdate(dt);
		arrows[i].arrow->updateTransform();
		if (arrows[i].arrow->getAlpha() <= 0) {
			std::lock_guard<std::mutex> removeGuard(removeMutex);
			arrowsToRemove.push_back(arrows[i]);
		}
	}
}

void CombatManager::updateArrows(float dt) {
	//ToDo:add fixed updates;

	int start = 0;
	while (start <= arrows.size()) {

		if (Xperrty::SceneManager::instance()->multithreaded) {
			threadPool.queue([this, dt, start] {internalUpdateArrows(dt, start); });
		}
		else internalUpdateArrows(dt, start);
		start += 256;
	}
}

void CombatManager::cleanupDeadObjects() {
	//at the moment object pools are not thread safe so we have to do this single threaded...
	for (int i = 0; i < dyingEnemies.size(); i++)
	{
		AnimationPlayer* animation = dyingEnemies[i].animationPlayer;
		if (animation->donePlaying) {

			Xperrty::TextureManager::freeTexturePtr(dyingEnemies[i].enemy->getMaterial()->getTexture());
			materialsPool.deleteObject(dyingEnemies[i].enemy->getMaterial());
			Xperrty::SceneManager::instance()->removeObject(dyingEnemies[i].enemy);
			enemiesPool.deleteObject(dyingEnemies[i].enemy);
			//dyingEnemies[i]->setAlpha(0);
			dyingEnemies.removeAt(i);
			i--;
		}
	}

	//at the moment object pools are not thread safe so we have to do this single threaded...
	for (int i = 0; i < arrowsToRemove.size(); i++)
	{
		//All arrows have the same texture pointer, no need to free it here.
		materialsPool.deleteObject(arrowsToRemove[i].arrow->getMaterial());
		Xperrty::SceneManager::instance()->removeObject(arrowsToRemove[i].arrow);
		arrows.remove(arrowsToRemove[i]);
		arrowsPool.deleteObject(arrowsToRemove[i].arrow);
	}
	arrowsToRemove.clear();
}

void CombatManager::internalUpdateEnemies(float dt, int start) {
	for (int i = start; i < enemies.size() && i < start + 256; i++)
	{
		enemies[i].animationPlayer->onUpdate(dt);
		enemies[i].follower->onUpdate(dt);
		enemies[i].enemy->updateTransform();
	}
}
void CombatManager::internalUpdateDyingEnemies(float dt, int start) {
	for (int i = start; i < dyingEnemies.size() && i < start + 256; i++)
	{
		dyingEnemies[i].animationPlayer->onUpdate(dt);
	}
}

void CombatManager::updateEnemies(float dt) {
	int start = 0;
	while (start <= enemies.size()) {
		if (Xperrty::SceneManager::instance()->multithreaded) {
			threadPool.queue([this, dt, start] {internalUpdateEnemies(dt, start); });
		}
		else internalUpdateEnemies(dt, start);
		start += 256;
	}
	start = 0;
	while (start <= dyingEnemies.size()) {
		if (Xperrty::SceneManager::instance()->multithreaded) {
			threadPool.queue([this, dt, start] {internalUpdateDyingEnemies(dt, start); });
		}
		else internalUpdateDyingEnemies(dt, start);
		start += 256;
	}
}

void CombatManager::internalCheckCollision(int ind, Array<int>& removedArrows, Array<int>& removedEnemies) {
	for (int j = 0; j < enemies.size(); j++)
	{
		Xperrty::Vector2 distance(arrows[ind].arrow->getWorldPosition() - enemies[j].enemy->getWorldPosition());
		if (distance.magnitude() < 128) {
			//Check rect collision but for now...
			std::lock_guard<std::mutex> removeGuard(removeMutex);

			//To avoid locking without needing to, we lock it now and add the collisions.
			if (!removedArrows.contains(ind) && !removedEnemies.contains(j))removedArrows.push_back(ind);
			if (!removedEnemies.contains(j)) {
				enemies[j].follower->setSpeed(0);
				enemies[j].animationPlayer->playAnimation(0, 0.5, 1);
				removedEnemies.push_back(j);
				break;
			}
		}
	}
}

void CombatManager::checkCollisions() {

	Array<int> removedArrows;
	Array<int> removedEnemies;
	if (arrows.size() != 0) {
		for (int i = 0; i < arrows.size(); i++)
		{
			if (removedArrows.contains(i))continue;
			//Check each arrow with each zombie...
			//Really slow... but for now throw power at the problem and move on.
			if (Xperrty::SceneManager::instance()->multithreaded) {

				threadPool.queue([&, this, ind = i]() mutable {internalCheckCollision(ind, removedArrows, removedEnemies); });
			}
			else internalCheckCollision(i, removedArrows, removedEnemies);
		}
		threadPool.start();
		threadPool.waitAll();
	}
	std::sort(removedArrows.begin(), removedArrows.end());

	for (int i = removedArrows.size() - 1; i >= 0; i--)
	{
		//All arrows have the same texture pointer, no need to free it here.
		materialsPool.deleteObject(arrows[removedArrows[i]].arrow->getMaterial());
		Xperrty::SceneManager::instance()->removeObject(arrows[removedArrows[i]].arrow);
		arrowsPool.deleteObject(arrows[removedArrows[i]].arrow);
		arrows.removeAt(removedArrows[i]);
	}
	std::sort(removedEnemies.begin(), removedEnemies.end());
	for (int i = removedEnemies.size() - 1; i >= 0; i--)
	{
		dyingEnemies.push_back(enemies[removedEnemies[i]]);
		enemies.removeAt(removedEnemies[i]);
	}
	kills += removedEnemies.size();
}

void CombatManager::updateObjects() {
	float dt = Xperrty::Time::dt();
	generateObjects(dt);
	updateArrows(dt);

	updateEnemies(dt);
	threadPool.start();
	threadPool.waitAll();
	cleanupDeadObjects();

	checkCollisions();
	//ToDo:check for errors 
	playerController.getPlayer()->getComponent<AnimationPlayer>()->onUpdate(dt);
}

void CombatManager::generateObjects(float dt) {
	if (enemies.size() > 200000) return;
	enemyTimer -= dt;
	while (enemyTimer < 0) {
		enemyTimer += enemySpawnTimer;
		Xperrty::GameObject* enemy = enemiesPool.newObject();
		Xperrty::Texture* enemyTexture = Xperrty::TextureManager::getTexture(8);
		Xperrty::Material* mat = materialsPool.newObject(mainShader, enemyTexture, enemy);
		enemy->setMaterial(mat);
		Xperrty::SceneManager::instance()->addObject(enemy);
		AnimationPlayer* animation = enemy->addComponent<AnimationPlayer>();
		animation->setAnimationData(4, 16, 256, 256, 30);
		animation->playAnimation(2);
		Follower* follower = enemy->addComponent<Follower>();
		follower->setTarget(playerController.getPlayer().get(), 500);
		//enemy->addComponent<AnimationPlayer>()->playAnimation(2);
		enemies.push_back({ enemy ,animation,follower });
		float randX = (rand() % 2000 - 1000) / 2000.0f;
		float xSign = randX >= 0 ? 1 : -1;
		float randY = (rand() % 2000 - 1000) / 2000.0f;
		float ySign = randY >= 0 ? 1 : -1;
		Xperrty::Vector2 direction(randX, randY);
		direction.normalize();
		float distance = rand() % 5000;
		enemy->setX(playerController.getPlayer()->getX() + (2500 + distance) * direction.x);
		enemy->setY(playerController.getPlayer()->getY() + (2500 + distance) * direction.y);
		enemy->setWidth(256);
		enemy->setHeight(256);
	}
}

void CombatManager::spawnArrows(int count) {
	float mx = Xperrty::InputManager::getX();
	float my = Xperrty::InputManager::getY();
	Xperrty::Vector2 direction = Xperrty::Camera::getActiveCamera()->screenToWorldPoint(mx, my) - playerController.getPlayer()->getWorldPosition();
	direction.normalize();
	//int numberOfArrows = std::min(256, kills / 100 + 1);
	int numberOfArrows = arrowSpawnMult * count;
	float rotationDifference = std::min(toRadians(10), PI * 2 / numberOfArrows);

	float arrowSpeed = 1500;
	float directionToAngle = atan2(direction.y, direction.x);
	int halfArrows = numberOfArrows / 2;
	float startAngle = directionToAngle - rotationDifference * halfArrows + rotationDifference * ((numberOfArrows + 1) % 2) / 2;
	for (int i = 0; i < numberOfArrows; i++)
	{

		Xperrty::GameObject* arrow = arrowsPool.newObject();
		Xperrty::Material* mat = materialsPool.newObject(mainShader, arrowTexture, arrow);
		arrow->setMaterial(mat);
		arrow->resetToOriginalDimensions();
		arrow->setScaleY(0.2);
		arrow->setScaleX(0.2);
		float distance = 50;
		direction = Xperrty::Vector2(cos(startAngle), sin(startAngle));
		arrow->setX(playerController.getPlayer()->getWorldPosition().x + direction.x * distance);
		arrow->setY(playerController.getPlayer()->getWorldPosition().y + direction.y * distance);

		arrow->setRotation(startAngle + PI / 2);
		Arrow* arrowComp = arrow->addComponent<Arrow>();
		arrowComp->setDirection(direction, arrowSpeed);
		arrows.push_back({ arrow,arrowComp });
		Xperrty::SceneManager::instance()->addObject(arrow);
		startAngle += rotationDifference;
	}
}

void CombatManager::checkInput() {
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_1)) setDifficulty(0);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_2)) setDifficulty(1);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_3)) setDifficulty(2);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_4)) setDifficulty(3);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_5)) setDifficulty(4);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_6)) setDifficulty(5);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_6)) setDifficulty(6);
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_SPACE)) {
		Xperrty::SceneManager::instance()->multithreaded = !Xperrty::SceneManager::instance()->multithreaded;
		if(Xperrty::SceneManager::instance()->multithreaded)APP_INFO("Multithreading ON! Using {0} worker threads.",threadPool.getWorkerCount());
		else APP_INFO("Multithreading OFF!");
	}
	if (Xperrty::InputManager::isKeyUp(Xperrty::KEY_ESCAPE)) { clearEverything(); }
}

void CombatManager::setDifficulty(unsigned int difficulty) {
	if (difficulty == 0) {
		arrowSpawnMult = 1;
		enemySpawnTimer = 0.3f;
	}
	else if (difficulty == 1) {
		arrowSpawnMult = 6;
		enemySpawnTimer = 0.075f;
	}
	else if (difficulty == 2) {
		arrowSpawnMult = 24;
		enemySpawnTimer = 0.02f;
	}
	else if (difficulty == 3) {
		arrowSpawnMult = 64;
		enemySpawnTimer = 0.01f;
	}
	else if (difficulty == 4) {
		arrowSpawnMult = 128;
		enemySpawnTimer = 0.004f;
	}
	else if (difficulty == 5) {
		arrowSpawnMult = 256;
		enemySpawnTimer = 0.001f;
	}
	else if (difficulty == 6) {
		arrowSpawnMult = 512;
		enemySpawnTimer = 0.00055f;
	}
}
void CombatManager::clearEverything() {
	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemies[i].follower->setSpeed(0);
		enemies[i].animationPlayer->playAnimation(0, 0.5, 1);
		dyingEnemies.push_back(enemies[i]);
	}
	enemies.clear();
	for (int i = 0; i < arrows.size(); i++)
	{
		//to be removed next frame.
		arrows[i].arrow->setAlpha(0);
	}
}

void CombatManager::onLogTimerDone(float dt) {
	APP_INFO("Enemies:{0} Arrows:{1} DyingEnemies:{2} Kills{3}", enemies.size(), arrows.size(), dyingEnemies.size(), kills);
}

CombatManager* CombatManager::_instance = nullptr;