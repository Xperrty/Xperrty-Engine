#pragma once
#include "Xperrty/World/GameObject.h"
#include "PlayerController.h"
#include "Xperrty/Events/IEventListener.h"
#include "Xperrty/Containers/Array.h"
#include "Xperrty/Performance/BatchedThreadPool.h"
#include "Xperrty/Performance/ObjectPool.h"
#include "Xperrty/Time/Timer.h"

#include "Components/AnimationPlayer.h"
#include "Components/Follower.h"
#include "Components/Arrow.h"


//Struct to hold data related to enemies.
struct EnemyData {
	EnemyData(Xperrty::GameObject* object, AnimationPlayer* player, Follower* follower) :enemy(object), animationPlayer(player), follower(follower) {};
	Xperrty::GameObject* enemy;
	AnimationPlayer* animationPlayer;
	Follower* follower;
	bool operator ==(const EnemyData& other) { return enemy == other.enemy; }
};
//Struct to hold data related to arrows.
struct ArrowData {
	ArrowData(Xperrty::GameObject* object, Arrow* arrowComp) :arrow(object), arrowComp(arrowComp) {};
	Xperrty::GameObject* arrow;
	Arrow* arrowComp;
	bool operator ==(const ArrowData& other) { return arrow == other.arrow; }

};


//Temp class to spawn enemies, update arrows and deal with things related to combat.
//Not necessary after switching to full component based.
//For now it's easy to use for quick prototyping.
class CombatManager : public Xperrty::IEngineEventListener
{
public:
	~CombatManager() {}

	//Returns the instance to the combat manager.
	inline static CombatManager* getInstance() { return CombatManager::_instance; };

	//Spawns count arrows towards the mouse pointer. They fan out by 10 degrees at max.
	void spawnArrows(int count);
private:
	//Update callback from engine.
	virtual void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override;
	CombatManager();
	//Player
	PlayerController playerController;
	Array<ArrowData> arrows;
	Array<EnemyData> enemies;
	Array<EnemyData> dyingEnemies;
	Array<ArrowData> arrowsToRemove;

	Xperrty::ObjectPool<Xperrty::GameObject> enemiesPool;
	Xperrty::ObjectPool<Xperrty::GameObject> arrowsPool;
	Xperrty::ObjectPool<Xperrty::Material> materialsPool;

	std::mutex removeMutex;

	//Main Update Loop
	void updateObjects();
	//Updates the arrows
	void updateArrows(float dt);
	//Updates the enemies
	void updateEnemies(float dt);
	//Spawns the enemies
	void generateObjects(float dt);
	//Checks collision between arrows and enemies.
	void checkCollisions();
	//Timer for the logging things to the console to avoid spamming every frame.
	void onLogTimerDone(float dt);
	//Checks user input for difficulty, multithread and kill all.
	void checkInput();
	//sets the spawn rate of enemies and arrows.
	void setDifficulty(unsigned int difficulty);
	//kills all the enemies and removes all the arrows.
	void clearEverything();

	void cleanupDeadObjects();

	//Helper function to loop through all arrows.
	void internalUpdateArrows(float dt,int start);
	//Helper function to loop through all enemies.
	void internalUpdateEnemies(float dt,int start);
	//Helper function to loop through all dying enemies.
	void internalUpdateDyingEnemies(float dt,int start);
	//Helper function to checkCollisions between an arrow and all the enemies.
	void internalCheckCollision(int ind, Array<int>& removedArrows, Array<int>& removedEnemies);
	static CombatManager* _instance;

	float enemySpawnTimer;
	float enemyTimer;

	int arrowSpawnMult;
	int kills;

	Xperrty::Texture* arrowTexture;
	Xperrty::Shader* mainShader;
	Xperrty::BatchedThreadPool threadPool;
	Xperrty::Timer<CombatManager> logTimer;
	friend class SandboxApp;
};
