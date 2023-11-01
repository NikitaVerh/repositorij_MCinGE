#pragma once
#include "map.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int numVertices = mapHeight * mapWidth;
int source = mapWidth * (mapHeight - 1);


struct Edge {
public:
    int u, v, weight;
    Edge(int u_gvn, int v_gvn, int weight_gvn) {
        u = u_gvn;
        v = v_gvn;
        weight = weight_gvn;
    }
};

struct Subset {
    int parent;
    int rank;
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
                edges.emplace_back(upNghbr, currVrtex, weight);
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

class Kruskal {
private:
    vector<Subset> subsets;
public:
    void makeSet(int v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }


    int find(int v) {
        if (v != subsets[v].parent)
            subsets[v].parent = find(subsets[v].parent);
        return subsets[v].parent;
    }


    void unionSets(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (subsets[a].rank < subsets[b].rank)
                swap(a, b);
            subsets[b].parent = a;
            if (subsets[a].rank == subsets[b].rank)
                subsets[a].rank++;
        }
    }


    vector<Edge> kruskal(vector<Edge>& edges) {
        vector<Edge> result;
        subsets.resize(numVertices);

        for (int v = 0; v < numVertices; ++v)
            makeSet(v);

        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
            });

        for (const Edge& edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int uRoot = find(u);
            int vRoot = find(v);

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
        for (int j = 0; j < mapWidth; j++) {
            int currVrtex = i * mapWidth + j;
            int weight = 0;
            bool set = false;

            if (i > 0) {
                if (mtrx[currVrtex][currVrtex - mapWidth] == 1) {
                    map [currVrtex/mapWidth][currVrtex%mapWidth] = new BlockLadder();
                    set = true;
                }
            }

            if (set == false) map [currVrtex/mapWidth][currVrtex % mapWidth] = new BlockWall();

            if (j > 0) {
                if (mtrx[currVrtex][currVrtex - 1] == 0) map [currVrtex / mapWidth][currVrtex % mapWidth] -> WallLeft = true;
            }

            if (j < mapWidth - 1) {
                if (mtrx[currVrtex][currVrtex + 1] == 0) map [currVrtex / mapWidth][currVrtex % mapWidth] -> WallRight = true;
            }
        }
    }
}


void Map::generateLabyrinth() {
    srand((unsigned int)time(0));
    vector<Edge> edges = CreateLatticeGraph();
    Kruskal kruskal;
    vector<Edge> result = kruskal.kruskal(edges);
    int** mtrx = Build_adjcncy_mtrix(result);
    Set_types(mtrx);
}