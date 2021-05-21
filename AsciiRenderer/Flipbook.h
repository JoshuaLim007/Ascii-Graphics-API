#pragma once
#include "Sprite.h"
#include <string>
#include <map>

class Flipbook
{
private:
	struct SpriteSheet {
		Sprite sprite;
		int cellSize;
	};
	int layer = 0;
	float speed = 1;

	std::map<int, SpriteSheet> animations;
	int currentFramePosition = 0;


public:
	void SetActiveAnimationLayer(int);
	int GetActiveAnimationLayer();

	void SetAnimationSpeed(float);
	float GetAnimationSpeed();

	int GetCurrentFrameIndex();
	void SetFrameIndex(int);

	void SetAnimationSpriteSheet(int, Sprite, int, int);

	void Tick(float);
};

