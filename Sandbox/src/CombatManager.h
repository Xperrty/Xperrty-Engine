#pragma once
#include "Xperrty/World/GameObject.h"
#include "PlayerController.h"
#include "Xperrty/Events/IEventListener.h"
#include "Xperrty/Containers/Array.h"
#include "Xperrty/Performance/BatchedThreadPool.h"
#include "Xperrty/Performance/ObjectPool.h"
#include "Xperrty/Time/Timer.h"


//Temp class to spawn enemies, update arrows and deal with things related to combat.
class CombatManager : public Xperrty::IEngineEventListener
{
public:
	~CombatManager() {}

	inline static CombatManager* getInstance() { return CombatManager::_instance; };

	void spawnArrows(int count);
private:
	virtual void onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData) override;
	CombatManager();
	PlayerController playerController;
	Array<Xperrty::GameObject*> arrows;
	Array<Xperrty::GameObject*> enemies;
	Array<Xperrty::GameObject*> dyingEnemies;
	Array<Xperrty::GameObject*> arrowsToRemove;

	Xperrty::ObjectPool<Xperrty::GameObject> enemiesPool;
	Xperrty::ObjectPool<Xperrty::GameObject> arrowsPool;
	Xperrty::ObjectPool<Xperrty::Material> materialsPool;

	std::mutex removeMutex;


	void updateObjects();
	void updateArrows(float dt);
	void updateEnemies(float dt);
	void generateObjects(float dt);
	void checkCollisions();
	void onLogTimerDone(float dt);
	static CombatManager* _instance;

	float enemySpawnTimer;
	float enemyTimer;
	int kills;

	Xperrty::Texture* arrowTexture;
	Xperrty::Shader* mainShader;
	Xperrty::BatchedThreadPool threadPool;
	Xperrty::Timer<CombatManager> logTimer;
	friend class SandboxApp;
};
