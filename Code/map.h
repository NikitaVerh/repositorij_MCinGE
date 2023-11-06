#pragma once
#include "GlobalConnsts.h"
#include "Block.h"
#include <vector>
#include "player.h"


class Map {
private:
	Block* map[mapWidth][mapHeight];
	std::vector<Hitbox> staticHitboxes;
public:
	Map();
	void addStaticHitbox(Hitbox hitbox);
	void drawHitboxes(sf::RenderWindow& window);

	void setNewHitboxes();

	void generateLabyrinth();

	void draw(sf::RenderWindow& window);

	void setBlock(int i, int j, Block* block);

	bool collisionMap(Hitbox hitbox);
	
	Block& getMapBlock(int i, int j);
};
