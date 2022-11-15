#include "xppch.h"
#include "CombatManager.h"
#include "Xperrty/Input/InputManager.h"
#include "Xperrty/World/SceneManager.h"
#include "Xperrty/Loader/TextureManager.h"	
#include "Components/AnimationPlayer.h"
#include "Components/Follower.h"
#include "Components/Arrow.h"
#include "Xperrty/Containers/Array.h"
#include <filesystem>
#include "Xperrty/Time/Stopwatch.h"
// temp random
#include <cstdlib>

CombatManager::CombatManager() :playerController(), enemiesPool(1000), arrowsPool(1000), materialsPool(2000), removeMutex(), mainShader(Xperrty::Shader::getShader(Xperrty::Shader::getDefaultShaderPath())), arrowTexture(Xperrty::TextureManager::getTexture(6)), enemySpawnTimer(0.001), enemyTimer(0), threadPool(14), kills(0), logTimer(2000, -1, this, &CombatManager::onLogTimerDone) {
	_instance = this;
	Xperrty::EventManager::addEventListener(Xperrty::UPDATE, this);
	enemiesPool.debug = true;
	kills = 20000;
	//Xperrty
}

void CombatManager::onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) {
	updateObjects();
}

void CombatManager::updateArrows(float dt) {
	//ToDo:add fixed updates;

	int start = 0;
	while (start <= arrows.size()) {

		threadPool.queue([this, dt, start] {
			for (int i = start; i < arrows.size() && i < start + 256; i++)
			{
				arrows[i]->getComponent<Arrow>()->onUpdate(dt);
				arrows[i]->updateTransform();
				if (arrows[i]->getAlpha() <= 0) {
					std::lock_guard<std::mutex> removeGuard(removeMutex);
					arrowsToRemove.push_back(arrows[i]);
				}
				//if (arrowsDetails[i].cSpeed < 0) arrowsDetails[i].cSpeed = 0;
			}
			});
		start += 256;
	}
}

void CombatManager::updateEnemies(float dt) {
	for (int i = 0; i < dyingEnemies.size(); i++)
	{
		AnimationPlayer* animation = dyingEnemies[i]->getComponent<AnimationPlayer>();
		if (animation->donePlaying) {
			materialsPool.deleteObject(dyingEnemies[i]->getMaterial());
			Xperrty::SceneManager::instance()->removeObject(dyingEnemies[i]);
			enemiesPool.deleteObject(dyingEnemies[i]);
			//dyingEnemies[i]->setAlpha(0);
			dyingEnemies.removeAt(i);
			i--;
		}
		else animation->onUpdate(dt);
		//dyingEnemies[i]->getComponent<Follower>()->onUpdate(dt);
	}
	//APP_INFO("")
	int start = 0;
	while (start <= enemies.size()) {

		threadPool.queue([this, dt, start] {
			for (int i = start; i < enemies.size() && i < start + 256; i++)
			{
				//ToDo: remove this, it's slow.
				enemies[i]->getComponent<AnimationPlayer>()->onUpdate(dt);
				enemies[i]->getComponent<Follower>()->onUpdate(dt);
				enemies[i]->updateTransform();
			}
			});
		start += 256;
	}
}

void CombatManager::checkCollisions() {

	Array<int> removedArrows;
	Array<int> removedEnemies;
	if (arrows.size() != 0) {
		//Stopwatch sw;
		for (int i = 0; i < arrows.size(); i++)
		{
			if (removedArrows.contains(i))continue;
			//Check each arrow with each zombie...
			//Really slow... but for now throw power at the problem and move on.
			threadPool.queue([&, this, ind = i]() mutable {
				//int ind = i;
				for (int j = 0; j < enemies.size(); j++)
				{
					//if (removedEnemies.contains(j)) continue;
					Xperrty::Vector2 distance(arrows[ind]->getWorldPosition() - enemies[j]->getWorldPosition());
					if (distance.magnitude() < 156) {
						//XP_INFO("Mag {0} X {1} Y {2} AX{3} AY{4} EX{5} EY{6} ", distance.magnitude(),distance.x,distance.y, arrows[i]->getWorldPosition().x, arrows[i]->getWorldPosition().y, enemies[j]->getWorldPosition().x, enemies[j]->getWorldPosition().y);
						//Check rect collision but for now...
						std::lock_guard<std::mutex> removeGuard(removeMutex);
						//arrows[ind]->setAlpha(0);

						//int removed = 0;
						if (!removedArrows.contains(ind) && !removedEnemies.contains(j))removedArrows.push_back(ind);
						if (!removedEnemies.contains(j)) {
							enemies[j]->getComponent<Follower>()->setSpeed(0);
							enemies[j]->getComponent<AnimationPlayer>()->playAnimation(0, 0.5, 1);
							removedEnemies.push_back(j);
							break;
						}
					}
				}
				});
		}
		threadPool.start();
		threadPool.waitAll();
	}
	std::sort(removedArrows.begin(), removedArrows.end());
	
	for (int i = 1; i < removedArrows.size(); i++)
	{
		if (removedArrows[i] == removedArrows[i - 1])APP_ERROR("DUPLICATE ARROWS REMOVE!!!!");
	}
	for (int i = removedArrows.size() - 1; i >= 0; i--)
	{
		materialsPool.deleteObject(arrows[removedArrows[i]]->getMaterial());
		Xperrty::SceneManager::instance()->removeObject(arrows[removedArrows[i]]);
		arrowsPool.deleteObject(arrows[removedArrows[i]]);
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

	for (int i = 0; i < arrowsToRemove.size(); i++)
	{

		//materialsPool.deleteObject(arrowsToRemove[i]->getMaterial());
		Xperrty::SceneManager::instance()->removeObject(arrowsToRemove[i]);
		arrows.remove(arrowsToRemove[i]);
		arrowsPool.deleteObject(arrowsToRemove[i]);
	}
	arrowsToRemove.clear();

	checkCollisions();
	//ToDo:check for errors 
	playerController.getPlayer()->getComponent<AnimationPlayer>()->onUpdate(dt);
}

void CombatManager::generateObjects(float dt) {
	if (enemies.size() > 200000) return;
	enemyTimer -= dt;
	while (enemyTimer < 0) {
		if (kills < 1000) {
			enemyTimer += 0.5 * (1 - kills / 1000);
		}
		else enemyTimer += enemySpawnTimer;
		Xperrty::GameObject* enemy = enemiesPool.newObject();
		Xperrty::Texture* enemyTexture = Xperrty::TextureManager::getTexture(8);
		Xperrty::Material* mat = materialsPool.newObject(mainShader, enemyTexture, enemy);
		enemy->setMaterial(mat);
		Xperrty::SceneManager::instance()->addObject(enemy);
		AnimationPlayer* animation = enemy->addComponent<AnimationPlayer>();
		animation->setAnimationData(4, 16, 256, 256, 30);
		animation->playAnimation(2);
		enemy->addComponent<Follower>()->setTarget(playerController.getPlayer().get(), 500);
		//enemy->addComponent<AnimationPlayer>()->playAnimation(2);
		enemies.push_back(enemy);
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
		//APP_INFO("ENEMIES {0}", enemies.size());
		//arrow->resetToOriginalDimensions();
	}
}

void CombatManager::spawnArrows(int count) {
	//APP_INFO("SHOOT ARROW!");
	float mx = Xperrty::InputManager::getX();
	float my = Xperrty::InputManager::getY();
	//using namespace Xperrty;
	Xperrty::Vector2 direction = Xperrty::Camera::getActiveCamera()->screenToWorldPoint(mx, my) - playerController.getPlayer()->getWorldPosition();
	direction.normalize();
	//int numberOfArrows = std::min(16, kills / 100 + 1);
	int numberOfArrows =  kills / 100 + 1;
	float rotationDifference = std::min(toRadians(10), Pi * 2 / numberOfArrows);

	//APP_INFO("Raw Mx {0} Raw My{1} Cam Scale{2} camX{3} camY{4}", mx, my, Xperrty::Camera::getActiveCamera()->getScale(), Xperrty::Camera::getActiveCamera()->getBounds().x, Xperrty::Camera::getActiveCamera()->getBounds().y);
	//APP_INFO("MX{0} MY{1} PX{2} PY{3} DX{4} DY{5} DNX{6} DNY{7}", Xperrty::Camera::getActiveCamera()->screenToWorldPoint(mx, my).x, Xperrty::Camera::getActiveCamera()->screenToWorldPoint(mx, my).y,playerController.getPlayer()->getX(),playerController.getPlayer()->getY(),dir2.x, dir2.y, direction.x, direction.y);
	float arrowSpeed = 1500;
	float directionToAngle = atan2(direction.y, direction.x);
	int halfArrows = numberOfArrows / 2;
	float startAngle = directionToAngle - rotationDifference * halfArrows + rotationDifference * ((numberOfArrows + 1) % 2) / 2;
	//APP_INFO("DTA {0} StartAngle{1} Rot Dif {2}", toDegrees(directionToAngle), toDegrees(startAngle), toDegrees(rotationDifference));
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
		//direction.normalize();
		arrow->setRotation(startAngle + Pi / 2);
		arrow->addComponent<Arrow>()->setDirection(direction, arrowSpeed);
		arrows.push_back(arrow);
		Xperrty::SceneManager::instance()->addObject(arrow);
		startAngle += rotationDifference;
	}
}

void CombatManager::onLogTimerDone(float dt) {
	APP_INFO("Enemies:{0} Arrows:{1} DyingEnemies:{2} Kills{3}", enemies.size(), arrows.size(), dyingEnemies.size(), kills);
}

CombatManager* CombatManager::_instance = nullptr;