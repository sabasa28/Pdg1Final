#include "Game.h"

Game::Game()
{
	
}

Game ::~Game()
{
	
}

void Game::play()
{
	initBaseGame(1000, 500, "Puzzle Demo");
	engineLoop();
}

void Game::initGame(Renderer* renderer)
{
	timer = new Timer();
	timer->start();

	_camera = new Camera(renderer);
	_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	
	_lightA = new Lightning(renderer);
	_lightA->initializeDirectional(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f));
	_lightA->setActiveState(true);

	shapeA = new Shape(ShapeTypes::rectangle, renderer);
	shapeA->setPosition(vec3(0.0f, 1.5f, 0.0f));

	sprite1 = new Sprite(renderer, "res/roca.png",true);
	sprite1->setPosition(vec3(-2.0f, 0.0f, 0.0f));

	sprite2 = new Sprite(renderer, "res/brown.png", false);
	sprite2->setPosition(vec3(-3.5f, 0.0f, 0.0f));

	sprite3 = new Sprite(renderer, "res/peach.png", true);
	sprite3->setPosition(vec3(3.5f, 0.0f, 0.0f));
	sprite3->setScale(vec3(1.0f, 1.5f, 1.0f));

	for (int i = 0; i < 4; i++)
	{
		fuego[i] = new Sprite(renderer, "res/fuegoDibujo.png", true);
	}
	
	tileMap = new TileMap(renderer, 16, 16, "res/MasterSimple.png", 256, 256, 4.0f, 4.0f);

	vector<int> tilemapLayout = { 0,1,1,1,2,16,17,17,8 + 16 * 4,18,16,17,17,17,18,16,17,17,17,18,64,65,65,65,66,66 ,66 ,66 ,66 ,66 };

	vector<bool> tilemapWalkable = { true,true, true, true, true,
									true, true, true, false, true, 
									true,true, true, true, true, 
									true, true, true, true, true,
									true,true, true, true, true};
	tileMap->setTileMap(5,5,tilemapLayout,tilemapWalkable);
	
	
	animation2 = new Animation();

	animation2->addFrame(0.0f, 0.0f, 1600/6, 267, 1600, 267);
	animation2->addFrame((1600 / 6) * 1, 0.0f, 1600 / 6, 267, 1600, 267);
	animation2->addFrame((1600 / 6) * 2, 0.0f, 1600 / 6, 267, 1600, 267);
	animation2->addFrame((1600 / 6) * 3, 0.0f, 1600 / 6, 267, 1600, 267);
	animation2->addFrame((1600 / 6) * 4, 0.0f, 1600 / 6, 267, 1600, 267);
	animation2->addFrame((1600 / 6) * 5, 0.0f, 1600 / 6, 267, 1600, 267);
	animation2->addAnimation(1.0f);

	for (int i = 0; i < 4; i++)
	{
		fuego[i]->setAnimation(animation2);
	}
	fuego[0]->setPosition(vec3(1.5f, -1.5f, 0.0f));
	fuego[1]->setPosition(vec3(1.5f, -0.5f, 0.0f));
	fuego[2]->setPosition(vec3(1.5f, 0.5f, 0.0f));
	fuego[3]->setPosition(vec3(1.5f, 1.5f, 0.0f));

}

void Game::updateGame(CollisionManager collManager, Input* input)
{
	//input
	if (input->isKeyDown(GLFW_KEY_UP))
	{
		speedY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_DOWN))
	{
		speedY = -1;
	}
	else
	{
		speedY = 0;
	}

	if (input->isKeyDown(GLFW_KEY_RIGHT))
	{
		speedX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_LEFT))
	{
		speedX = -1;
	}
	else
	{
		speedX = 0;
	}

	if (input->isKeyDown(GLFW_KEY_L))
	{
		speedZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_O))
	{
		speedZ = -1;
	}
	else
	{
		speedZ = 0;
	}

	if (input->isKeyDown(GLFW_KEY_U))
	{
		growSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_J))
	{
		growSpeed = -1;
	}
	else
	{
		growSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_S))
	{
		rotXSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_W))
	{
		rotXSpeed = -1;
	}
	else
	{
		rotXSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_A))
	{
		rotYSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_D))
	{
		rotYSpeed = -1;
	}
	else
	{
		rotYSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_Q))
	{
		rotZSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_E))
	{
		rotZSpeed = -1;
	}
	else
	{
		rotZSpeed = 0;
	}
	if (input->isKeyDown(GLFW_KEY_KP_8))
	{
		camSpeedY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_KP_5))
	{
		camSpeedY = -1;
	}
	else
	{
		camSpeedY = 0;
	}
	if (input->isKeyDown(GLFW_KEY_KP_6))
	{
		camSpeedX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_KP_4))
	{
		camSpeedX = -1;
	}
	else
	{
		camSpeedX = 0;
	}
	if (input->isKeyDown(GLFW_KEY_KP_7))
	{
		camSpeedZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_KP_9))
	{
		camSpeedZ = -1;
	}
	else
	{
		camSpeedZ = 0;
	}
	//
	if (input->isKeyDown(GLFW_KEY_T))
	{
		camTargetY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_G))
	{
		camTargetY = -1;
	}
	else
	{
		camTargetY = 0;
	}
	if (input->isKeyDown(GLFW_KEY_H))
	{
		camTargetX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_F))
	{
		camTargetX = -1;
	}
	else
	{
		camTargetX = 0;
	}
	if (input->isKeyDown(GLFW_KEY_R)) //esta parte se puede remover
	{
		camTargetZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_Y))
	{
		camTargetZ = -1;
	}
	else
	{
		camTargetZ = 0;
	}

	if (input->isKeyPressed(GLFW_KEY_1, isPressed[1]))
	{
		_lightA->setActiveState(!_lightA->getActiveState());
	}

	vec3 cameraMovement = vec3(camSpeedX, camSpeedY, camSpeedZ) * 3.0f * timer->getDT();
	vec3 cameraRotation = vec3(camTargetX, camTargetY, camTargetZ) * camRotSpeed * timer->getDT();
	_camera->moveOnLocal(glm::vec3 (cameraMovement));
	_camera->rotate(glm::vec3(cameraRotation));
	
	vec3 playerMovement = vec3(speedX, speedY, speedZ) * timer->getDT();
	
	vec3 newPos = shapeA->getPosition() + playerMovement;
	shapeA->setPosition(newPos);
	
	vec3 newScale = shapeA->getScale() + vec3(growSpeed, growSpeed, growSpeed)*timer->getDT();
	shapeA->setScale(newScale);
	
	vec3 newRot = shapeA->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*timer->getDT();
	shapeA->setRotation(newRot);
	
	if (collManager.CheckCollision(sprite1, sprite2)) fireActive = false;
	if (collManager.CheckCollision(shapeA, sprite3)) cout << "YOU WIN" << endl;
	
	for (int i = 0; i < 4; i++)
	{
		if (fuego[i] && fireActive)
		{
			collManager.CheckCollisionAgainstStatic(shapeA, fuego[i], playerMovement);
		}
	}
	collManager.CheckCollisionAndPush(shapeA, sprite1, playerMovement);
	//
	tileMap->checkCollisionWithTileMap(shapeA, playerMovement);

	timer->updateTimer();

	//draw
	shapeA->draw();
	tileMap->drawTileMap();



	sprite1->draw();
	sprite2->draw();
	sprite3->draw();
	for (int i = 0; i < 4; i++)
	{
		if (fuego[i] && fireActive)
		{
			fuego[i]->updateSprite(*timer);
			fuego[i]->draw();
		}
	}
}
void Game::destroyGame()
{
	if (timer) delete timer;
	if (_camera) delete _camera;
	if (_lightA) delete _lightA;
	if (shapeA) delete shapeA;
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;
	if (sprite3) delete sprite3;
	for (int i = 0; i < 4; i++)
	{
		if (fuego[i]) delete fuego[i];
	}
	if (tileMap) delete tileMap;
	if (animation) delete animation;
	if (animation2) delete animation2;
}
