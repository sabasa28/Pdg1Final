#pragma once
#include "BaseGame.h"
class Game: BaseGame
{
private:
	Timer* timer;
	Shape* shapeA;
	Sprite* sprite1;
	Sprite* sprite2;
	Sprite* sprite3;
	Sprite* fuego[4];
	TileMap* tileMap;
	Animation* animation;
	Animation* animation2;
	Camera* _camera;
	Lightning* _lightA;

	bool fireActive = true;

	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;
	float growSpeed = 0;
	float rotXSpeed = 0;
	float rotYSpeed = 0;
	float rotZSpeed = 0;

	float camSpeedX = 0.0f;
	float camSpeedY = 0.0f;
	float camSpeedZ = 0.0f;

	float camTargetX = 0.0f;
	float camTargetY = 0.0f;
	float camTargetZ = 0.0f;
	float camRotSpeed = 50.0f;

	bool isPressed[9];

	double mouseLastX;
	double mouseLastY;
	double mouseCurrentX;
	double mouseCurrentY;
	double mousePitch;
	double mouseYaw;
public:
	Game();
	~Game();
	void play();
	void initGame(Renderer* renderer) override;
	void updateGame(CollisionManager collManager, Input* input) override;
	void destroyGame() override;
};