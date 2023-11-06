#pragma once
#include "map.h"
#include "GlobalVariablesForResources.h"
#include "GlobalVariablesOfClasses.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int single_floor_walls = -1;
int numVertices = mapHeight * mapWidth;
int source = mapWidth * (mapHeight - 1);
int MinDoor = mapWidth / 7;


struct Edge {
public:
    int u, v, weight;
    Edge(int u_gvn, int v_gvn, int weight_gvn) {
        u = u_gvn;
        v = v_gvn;
        weight = weight_gvn;
    }
};

int fullRandom() {
    int random = (rand() % 100) + 2;
    return random;
}

vector<Edge> CreateLatticeGraph() {

    vector<Edge> edges;

    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            int currVrtex = i * mapWidth + j;
            int weight = 0;

            if (i > 0) {
                if (currVrtex == source) weight = 999;
                else weight = fullRandom();
                int upNghbr = currVrtex - mapWidth;
                edges.emplace_back(upNghbr, currVrtex, 2*weight);
            }

            if (j > 0) {
                if (currVrtex == source + 1) weight = 1;
                else weight = fullRandom();
                int leftNghbr = currVrtex - 1;
                edges.emplace_back(leftNghbr, currVrtex, weight);
            }
        }
    }

    return edges;
}


struct Subset {
    int parent;
    int rank;
    Subset(int par, int rnk) {
        parent = par;
        rank = rnk;
    }
};


class Kruskal {
private:
    vector<Subset> subsets;
public:

    int find(int v) {
        if (v != subsets[v].parent) subsets[v].parent = find(subsets[v].parent);
        return subsets[v].parent;
    }


    void unionSets(int a, int b) {
      if (subsets[a].rank < subsets[b].rank) {
          subsets[a].parent = b;
          if (subsets[a].rank == subsets[b].rank) subsets[b].rank++;
      }
      else {
          subsets[b].parent = a;
          if (subsets[a].rank == subsets[b].rank) subsets[a].rank++;
      }
    }


    vector<Edge> kruskal(vector<Edge>& edges) {
        vector<Edge> result;
        for (int v = 0; v < numVertices; ++v) subsets.emplace_back(Subset(v, 0));
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {return a.weight < b.weight;});
        for (const Edge& edge : edges) {
            int uRoot = find(edge.u);
            int vRoot = find(edge.v);

            if (uRoot != vRoot) {
                result.push_back(edge);
                unionSets(uRoot, vRoot);
            }
        }

        return result;
    }
};


int** Build_adjcncy_mtrix(vector<Edge> result) {
    int** adjcncy_mtrix = new int* [numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjcncy_mtrix[i] = new int[numVertices];
        for (int j = 0; j < numVertices; j++) {
            adjcncy_mtrix[i][j] = 0;
        }
    }
    for (const Edge& edge : result) {
        adjcncy_mtrix[edge.u][edge.v] = 1;
        adjcncy_mtrix[edge.v][edge.u] = 1;
    }
    return adjcncy_mtrix;
}


void Set_types(int** mtrx) {
    for (int i = 0; i < mapHeight; i++) {
        single_floor_walls = 0;
        for (int j = 0; j < mapWidth; j++) {
            int currVrtex = i * mapWidth + j;
            int weight = 0;
            bool set = false;

            if (i > 0) {
                if (mtrx[currVrtex][currVrtex - mapWidth] == 1) {
                    GameMap.setBlock(currVrtex%mapWidth, currVrtex/mapWidth, new BlockLadder());
                    set = true;
                }
            }

            if (set == false) GameMap.setBlock(currVrtex % mapWidth, currVrtex / mapWidth, new BlockWall());

            if (j > 0) {
                if (mtrx[currVrtex][currVrtex - 1] == 0) {
                    GameMap.getMapBlock(currVrtex % mapWidth, currVrtex / mapWidth).setWallLeft(true);
                    ++single_floor_walls;
                }
            }

            if (j < mapWidth - 1) {
                if (mtrx[currVrtex][currVrtex + 1] == 0) GameMap.getMapBlock(currVrtex % mapWidth, currVrtex / mapWidth).setWallRight(true);
            }
        }
        if (single_floor_walls > trunc(mapWidth / 2.4) || single_floor_walls < trunc(mapWidth/5.5)) break;
    }
}


void Base_Labyrinth_Generator(int cnt) {
    srand((unsigned int)(time(0)*cnt));
    vector<Edge> edges = CreateLatticeGraph();
    Kruskal kruskal;
    vector<Edge> result = kruskal.kruskal(edges);
    int** mtrx = Build_adjcncy_mtrix(result);
    Set_types(mtrx);
    for (int i = 0; i < numVertices; i++) delete[] mtrx[i];
    delete[] mtrx;
}


void fill_range(int i, int j) {
    int k;
    bool flag = true;
    int door_cnt = 0;
    while (door_cnt < MinDoor && flag == true) {
        k = j;
        flag = false;
        while (k < mapWidth) {
            if (GameMap.getMapBlock(k, i).getTypeBlock() == type_block_wall) {
                flag = true;
                bool right = GameMap.getMapBlock(k, i).getWallRight();
                bool left = GameMap.getMapBlock(k, i).getWallLeft();
                if (rand() % 100 > 70) GameMap.setBlock(k, i, new BlockDoor());
                if (GameMap.getMapBlock(k, i).getTypeBlock() == type_block_door) {
                    ++door_cnt;
                    if (right == true) GameMap.getMapBlock(k, i).setWallRight(true);
                    if (left == true) GameMap.getMapBlock(k, i).setWallLeft(true);
                }
            }
            if (GameMap.getMapBlock(k, i).getWallRight() == true) break;
            ++k;
        }
    }
    if (k != mapWidth) fill_range(i, k+1);
}

void Door_generation() {
    if (MinDoor == 0) MinDoor = 1;
    for (int i = 0; i < mapHeight; i++) {
        fill_range(i, 0);
    }
    GameMap.setBlock(0, source/mapWidth, new BlockWall());
}


void Map::setNewHitboxes() {
    staticHitboxes.clear();
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            if (map[i][j]->getWallRight() == true) addStaticHitbox(Hitbox(i+0.925,j,0.15,1));
        }
    }
    
}



void Map::generateLabyrinth() {
    int cnt = 1;
    Base_Labyrinth_Generator(cnt);
    while (single_floor_walls > trunc(mapWidth / 2.4) || single_floor_walls < trunc(mapWidth / 5.5)) {
        ++cnt;
        Base_Labyrinth_Generator(cnt);
    }
    Door_generation();
    setNewHitboxes();
}



void Map::draw(sf::RenderWindow& window) {
    sf::Sprite WallLeft;
    sf::Sprite WallRight;

    WallLeft.setTexture(texture_wall_left);
    WallRight.setTexture(texture_wall_right);
    WallLeft.setScale(sizeBlock / float(texture_wall_left.getSize().x), sizeBlock / float(texture_wall_left.getSize().y));
    WallRight.setScale(sizeBlock / float(texture_wall_right.getSize().x), sizeBlock / float(texture_wall_right.getSize().y));

	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
            
			sf::RectangleShape block = map[i][j]->getBlockForDraw();
			block.setPosition(sf::Vector2f(i*sizeBlock,j*sizeBlock));
			block.setSize(sf::Vector2f(sizeBlock, sizeBlock));
			window.draw(block);


            if (GameMap.getMapBlock(i, j).getWallLeft()) {
                WallLeft.setPosition(sf::Vector2f(i * sizeBlock, j * sizeBlock));
                window.draw(WallLeft);
            }
            if (GameMap.getMapBlock(i, j).getWallRight()) {
                WallRight.setPosition(sf::Vector2f(i * sizeBlock, j * sizeBlock));
                window.draw(WallRight);
            }

            
		}
	}
    drawHitboxes(window);
}

Map::Map() {
	for (int i = 0; i < mapWidth; i++) {
		for (int j = 0; j < mapHeight; j++) {
			map[i][j] = NULL;
		}
	}
}

void Map::addStaticHitbox(Hitbox hitbox){
    staticHitboxes.push_back(hitbox);
}

void Map::drawHitboxes(sf::RenderWindow& window){
    for (auto element : staticHitboxes) {
        element.draw(window);
    }
}

void Map::setBlock(int i, int j, Block* block) {
	if (map[i][j] != NULL) { delete(map[i][j]); }
	map[i][j] = block;
}

bool Map::collisionMap(Hitbox hitbox){
    for (auto element : staticHitboxes) {
        if (element.collision(hitbox)) {
            return true;
        }
    }
    return false;
}

Block& Map::getMapBlock(int i, int j) {
	if (i >= 0 && i < mapWidth && j >= 0 && j < mapHeight) {
		return *map[i][j];
	}
    BlockWall Blck;
    return Blck;
}