#include "xppch.h"
#include "PlayerController.h"
#include "Xperrty/Input/InputManager.h"
#include "Xperrty/Input/KeyCodes.h"
#include "Xperrty/Loader/TextureManager.h"
#include "Xperrty/Rendering/Window.h"
#include "Xperrty/World/SceneManager.h"
#include "Xperrty/Math/Vector2.h"
#include "CombatManager.h"
#include <filesystem>
PlayerController::PlayerController() :speed(1000), followCam(nullptr), shotCooldown(0),currentAnimation(3) {
	object = std::make_shared<Xperrty::GameObject>();
	Xperrty::Texture* texture = Xperrty::TextureManager::getTexture(7);
	mat = new Xperrty::Material(Xperrty::Shader::getShader(std::filesystem::current_path().string() + "\\..\\XperrtyEngine\\src\\Xperrty\\Rendering\\Shaders\\MultiTextureShader.glsl"), texture, object.get());
	object->setMaterial(mat);
	Xperrty::SceneManager::instance()->addObject(object.get());
	followCam = new Xperrty::FollowCamera({ 0,0,(float)Xperrty::Window::instance->getWidth(), (float)Xperrty::Window::instance->getHeight() });
	followCam->addFollowTarget(object.get());
	followCam->setActive(true);
	object->setScaleX(2);
	object->setScaleY(2);
	animation = object->addComponent<AnimationPlayer>();
	animation->setAnimationData(4, 16, 256, 256, 30);
	animation->playAnimation(3);
	Xperrty::EventManager::addEventListener(Xperrty::UPDATE, this);
}

void PlayerController::onEngineEvent(Xperrty::EngineEventType eventNr, Xperrty::EventData* eventData)
{
	onUpdate(eventData);
}

void PlayerController::onUpdate(Xperrty::EventData* eventData) {
	Xperrty::FloatEventData* floatED = static_cast<Xperrty::FloatEventData*>(eventData);
	float dt = floatED->getValue();
	bool input = false;
	if (Xperrty::InputManager::isKeyDown(Xperrty::KEY_A)) {
		object->setX(object->getX() - dt * speed);
		object->setScaleX(-2);
		input = true;
		//APP_INFO("AAAAAAAAAAA {0}", object->getX());
	}
	if (Xperrty::InputManager::isKeyDown(Xperrty::KEY_D)) {
		object->setX(object->getX() + dt * speed);
		object->setScaleX(2);
		input = true;
	}
	if (Xperrty::InputManager::isKeyDown(Xperrty::KEY_W)) {
		object->setY(object->getY() - dt * speed);
		input = true;
	}
	if (Xperrty::InputManager::isKeyDown(Xperrty::KEY_S)) {
		object->setY(object->getY() + dt * speed);
		input = true;
	}
	
	if (!input && currentAnimation == 2) {
		animation->playAnimation(3);
		currentAnimation = 3;
	}
	if (input && currentAnimation != 2) {
		animation->playAnimation(2);
		currentAnimation = 2;
	}
	shotCooldown -= dt;
	if (shotCooldown < 0) {
		if (Xperrty::InputManager::isMouseDown(Xperrty::MOUSE_BUTTON_1)) {
			//Hardcode reset at 1s. Add it to account for the extra time after the moment the arrow cooldown was done.
			while (shotCooldown < 0)
			{
				//shotCooldown += 0.01;
				shotCooldown += 0.21;
				//shotCooldown += 1;
				onShootArrow();
				if(input) animation->playAnimation(1, 2, 1, 2);
				else animation->playAnimation(1, 2, 1, 3);

			}
		}
		else shotCooldown = 0;

	}

	object->updateTransform();
	followCam->update();
}

void PlayerController::onShootArrow() {
	CombatManager::getInstance()->spawnArrows(1);
}