#include "TileMap.h"
#include <algorithm>

TileMap::TileMap(Renderer* renderer, int rows, int columns, const char* path, int imageHeight, int imageWidth, float tileScaleX, float tileScaleY):Entity(renderer)
{
	correctlySet = false;
	_imageHeight = imageHeight;
	_imageWidth = imageWidth;
	tilemapRows = rows;
	tilemapColumns = columns;
	int tileProportionalWidth = _imageWidth/ columns;
	int tileProportionalHeight = _imageHeight / rows; 
	textureUsed = new Texture(path);
	textureUsed->Bind(0);
	texture = textureUsed->getTex();
	tiles.clear();
	float tileX = 0.0f;
	float tileY = imageHeight;
	int id = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			Tile* newTile = new Tile(renderer, texture, true, id, (float)rows/imageWidth * tileScaleX, (float)columns/imageHeight * tileScaleY);

			newTile->setTextureCoordinates(

			(tileX + tileProportionalWidth) / _imageWidth, tileY / _imageHeight,
			(tileX + tileProportionalWidth) / _imageWidth, (tileY - tileProportionalHeight) / _imageHeight,
			tileX / _imageWidth, (tileY - tileProportionalHeight) / _imageHeight,
			tileX / _imageWidth, tileY / _imageHeight

			);

			tileX += tileProportionalWidth;
			tiles.push_back(newTile);
			
			
			id++;
		}
		tileX = 0;
		tileY -= tileProportionalHeight;
	}
	_tileWidth = tiles[0]->width;
	_tileHeight = tiles[0]->height;
}
void TileMap::setTileMap(int column, int row, vector<int> tilesId)
{
	tilesLayout.clear();
	int tilesAmount = row * column;
	if (tilesId.size() >= tilesAmount)
	{
		correctlySet = true;
	}
	else
	{
		correctlySet = false;
		cout << "Tilemap not set correctly"<<endl;
		return;
	}
	vector<int>::iterator it = tilesId.begin();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (find(tilesId.begin(), it, tilesId[i * column + j]) == it)
				tilesLayout.push_back(tiles[tilesId[i * column + j]]);
			else
				tilesLayout.push_back(tiles[tilesId[i * column + j]]->clone());
			it++;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			tilesLayout[i*column + j]->setPosition(getPosition() + vec3(j*tilesLayout[i*column + j]->width + tilesLayout[i*column + j]->width / 2, i* -tilesLayout[i*column + j]->height - tilesLayout[i*column + j]->height / 2, 0) - vec3(column / 2.0f * tilesLayout[i*column + j]->width, -(row / 2.0f * tilesLayout[i*column + j]->height), 0));
		}
	}
	tilemapWidth = (tilesLayout[tilesLayout.size()-1]->getPosition().x + tilesLayout[tilesLayout.size() - 1]->width/2.0f) - (tilesLayout[0]->getPosition().x - tilesLayout[0]->width/2.0f);
	tilemapHeight = (tilesLayout[0]->getPosition().y + tilesLayout[0]->height / 2.0f) - (tilesLayout[tilesLayout.size() - 1]->getPosition().y - tilesLayout[tilesLayout.size() - 1]->height / 2.0f);
}

void TileMap::setTileMap(int column, int row, vector<vec2> tilesCoor)
{
	vector<int> tilesId;
	for (int i = 0; i < tilesCoor.size(); i++)
	{
		tilesId.push_back(tilesCoor[i].y * tilemapRows + tilesCoor[i].x);
	}
	setTileMap(column, row, tilesId);
}

void TileMap::setTileMap(int column, int row, vector<int> tilesId, vector<bool> tilesWalkable)
{
	tilesLayout.clear();
	int tilesAmount = row * column;
	if (tilesId.size() >= tilesAmount && tilesWalkable.size() >= tilesAmount)
	{
		correctlySet = true;
	}
	else
	{
		correctlySet = false;
		cout << "Tilemap not set correctly" << endl;
		return;
	}
	vector<int>::iterator it = tilesId.begin();
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (find(tilesId.begin(), it, tilesId[i * column + j]) == it)
				tilesLayout.push_back(tiles[tilesId[i * column + j]]);
			else
				tilesLayout.push_back(tiles[tilesId[i * column + j]]->clone());
			it++;
		}
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			tilesLayout[i*column + j]->setPosition(getPosition() + vec3(j*tilesLayout[i*column + j]->width + tilesLayout[i*column + j]->width / 2, i* -tilesLayout[i*column + j]->height - tilesLayout[i*column + j]->height / 2, 0) - vec3(column / 2.0f * tilesLayout[i*column + j]->width, -(row / 2.0f * tilesLayout[i*column + j]->height), 0));
			tilesLayout[i*column + j]->setWalkable(tilesWalkable[i*column + j]);
		}
	}
	tilemapWidth = (tilesLayout[tilesLayout.size() - 1]->getPosition().x + tilesLayout[tilesLayout.size() - 1]->width / 2.0f) - (tilesLayout[0]->getPosition().x - tilesLayout[0]->width / 2.0f);
	tilemapHeight = (tilesLayout[0]->getPosition().y + tilesLayout[0]->height / 2.0f) - (tilesLayout[tilesLayout.size() - 1]->getPosition().y - tilesLayout[tilesLayout.size() - 1]->height / 2.0f);
}

void TileMap::setTileMap(int column, int row, vector<vec2> tilesCoor, vector<bool> tilesWalkable)
{
	vector<int> tilesId;
	for (int i = 0; i < tilesCoor.size(); i++)
	{
		tilesId.push_back(tilesCoor[i].y * tilemapRows + tilesCoor[i].x);
	}
	setTileMap(column, row, tilesId, tilesWalkable);
}

TileMap::~TileMap()
{
	if (textureUsed) delete textureUsed;
	tiles.clear();
	tilesLayout.clear();
}

void TileMap::drawTileMap()
{
	if (!correctlySet)
	{
		cout << "Tilemap not set correctly" << endl;
		return;
	}

	for (int i = 0; i < tilesLayout.size(); i++)
	{
		tilesLayout[i]->draw();
	}
}

bool TileMap::checkCollisionWithTileMap(Shape* shape, vec3 movement)
{
	if (!collidesWithTileMap(shape))
		return false;

	bool collides = false;

	for (int i = 0; i < tilesLayout.size(); i++)
	{
		if (collMan.CheckCollision(tilesLayout[i], shape))
		{
			cout << "Colisiona con el tile " << i << endl;
			collides = true;
			if (!tilesLayout[i]->_isWalkable)
			{
				shape->setPosition(shape->getPosition() - movement);
			}
		}
	}
	return collides;
}

bool TileMap::collidesWithTileMap(Shape* shape)
{
	if (shape->getPosition().x + shape->width / 2.0f <	getPosition().x - tilemapWidth / 2.0f ||
		shape->getPosition().x - shape->width / 2.0f > getPosition().x  + tilemapWidth / 2.0f ||
		shape->getPosition().y + shape->height / 2.0f < getPosition().y - tilemapHeight / 2.0f ||
		shape->getPosition().y - shape->height / 2.0f > getPosition().y + tilemapHeight / 2.0f)
		return false;
	else return true;
}