#pragma once
#include "Tile.h"
#include "Exports.h"
#include <vector>
#include "Shape.h"
#include "CollisionManager.h"
class SABASAENGINE_API TileMap: public Entity
{
	Texture* textureUsed;
	unsigned int texture;
	vector<Tile*> tiles;
	vector<Tile*> tilesLayout;
	unsigned int tilemapRows;
	unsigned int tilemapColumns;
	float _tileWidth;
	float _tileHeight;
	int _imageHeight;
	int _imageWidth;
	bool correctlySet;
	CollisionManager collMan;
	bool collidesWithTileMap(Shape* shape);
public:
	float tilemapWidth;
	float tilemapHeight;
	TileMap(Renderer* renderer,int rows, int columns, const char* path, int imageHeight, int imageWidth, float tileWidth, float tileHeight);
	~TileMap();
	void setTileMap(int column, int row, vector<int> tilesId);
	void setTileMap(int column, int row, vector<vec2> tilesCoor);
	void setTileMap(int column, int row, vector<int> tilesId, vector<bool> tilesWalkable);
	void setTileMap(int column, int row, vector<vec2> tilesCoor, vector<bool> tilesWalkable);
	void drawTileMap();
	bool checkCollisionWithTileMap(Shape* sprite, vec3 movement);
};