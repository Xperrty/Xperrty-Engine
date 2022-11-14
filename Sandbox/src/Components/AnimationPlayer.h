#pragma once
#include "Xperrty/World/Component.h"
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/World/GameObject.h"

class AnimationPlayer :public Xperrty::Component
{
public:
	~AnimationPlayer() = default;

	virtual void onAddedToObject()override;
	virtual void init()override;
	virtual void onUpdate(float dt)override;

	void setAnimationData(int animations, int spritesEachRow, int spriteWidth, int spriteHeight, float fps);
	void playAnimation(int animationNumber, float playbackSpeed= 1, int playTimes = -1,int animationOnComplete=-1,float animationOnCompleteSpeed = 1);

	AnimationPlayer();
	bool donePlaying;
private:
	int animations;
	int spritesEachRow;
	int spriteWidth;
	int spriteHeight;
	int spriteSheetWidth;
	int spriteSheetHeight;
	float durationPerFrame;


	float playbackMult;
	int animationNumber;
	int animationOnComplete;
	float animationOnCompleteSpeed;
	int playTimes;
	float cTime;
	float animationDuration;
	Xperrty::Texture* texture;
};