#include "xppch.h"
#include "AnimationPlayer.h"
#include <math.h>
#include "Xperrty/Math/Rect.h"
void AnimationPlayer::onAddedToObject() {

}
void AnimationPlayer::init() {

}
void AnimationPlayer::onUpdate(float dt) {
	if (playTimes == 0) {
		if (animationOnComplete != 1) playAnimation(animationOnComplete, animationOnCompleteSpeed);
		donePlaying = true;
		return;
	}
	cTime += dt * playbackMult;
	while (cTime >= animationDuration) {
		cTime -= animationDuration;
		playTimes--;
		if (playTimes == 0) break;
		if (playTimes < -1) playTimes = -1;
	}

	int frame = playTimes != 0 ? static_cast<int> (floor(cTime / durationPerFrame)) % spritesEachRow : spritesEachRow-1;
	float uvs[8];
	//ToDo: find a better way to deal with OpenGL bottom left texture origin + flipped...
	Xperrty::Rect bounds(frame * spriteWidth, (animationNumber + 1) * spriteHeight, spriteWidth, -spriteHeight);
	//bl
	uvs[0] = bounds.getX() / spriteSheetWidth;
	uvs[1] = bounds.getBot() / spriteSheetHeight;
	//br
	uvs[2] = bounds.getRight() / spriteSheetWidth;
	uvs[3] = bounds.getBot() / spriteSheetHeight;
	//tr
	uvs[4] = bounds.getRight() / spriteSheetWidth;
	uvs[5] = bounds.getY() / spriteSheetHeight;
	//tl
	uvs[6] = bounds.getX() / spriteSheetWidth;
	uvs[7] = bounds.getY() / spriteSheetHeight;
	texture->setUVs(uvs);
}

AnimationPlayer::AnimationPlayer() :donePlaying(false),animations(0), spritesEachRow(0), spriteWidth(0), spriteHeight(0), durationPerFrame(0), animationDuration(0), cTime(0), animationNumber(0), playTimes(0), playbackMult(0), spriteSheetHeight(0), spriteSheetWidth(0), texture(nullptr), animationOnComplete(-1), animationOnCompleteSpeed(1) {}

void AnimationPlayer::setAnimationData(int animations, int spritesEachRow, int spriteWidth, int spriteHeight, float fps) {
	this->animations = animations;
	this->spritesEachRow = spritesEachRow;
	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;
	durationPerFrame = 1.0f / fps;
	animationDuration = durationPerFrame * spritesEachRow;
	texture = gameObject->getMaterial()->getTexture();
	Xperrty::Material* mat = gameObject->getMaterial();
	spriteSheetWidth = spritesEachRow * spriteWidth;
	spriteSheetHeight = animations * spriteHeight;
	//APP_INFO("anim{0}, erachRow{1}, w{2}, h{3}, fps{4} ",animations,spritesEachRow,spriteWidth,spriteHeight,fps);
	//texture->setUVs();
	//texture = getGameObject()
}
void AnimationPlayer::playAnimation(int animationNumber, float playbackSpeed, int playTimes, int animationOnComplete, float animationOnCompleteSpeed) {
	this->animationNumber = animationNumber;
	this->playbackMult = playbackSpeed;
	this->playTimes = playTimes;
	this->animationOnComplete = animationOnComplete;
	this->animationOnCompleteSpeed = animationOnCompleteSpeed;
	cTime = 0;
}