#pragma once
#include "Xperrty/World/Component.h"
#include "Xperrty/Rendering/Texture.h"
#include "Xperrty/World/GameObject.h"

//Spritesheet based animation.
class AnimationPlayer :public Xperrty::Component
{
public:
	~AnimationPlayer() = default;

	//Called when component is added on the object.
	virtual void onAddedToObject()override;
	//NOT IMPLEMENTED
	virtual void init()override;
	//NOT IMPLEMENTED
	virtual void onUpdate(float dt)override;

	//Sets the animation data.
	void setAnimationData(int animations, int spritesEachRow, int spriteWidth, int spriteHeight, float fps);
	//Starts the animation playback.
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