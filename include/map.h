#ifndef BLOB_DASH_MAP_H
#define BLOB_DASH_MAP_H

#include "SFML/Graphics.hpp"
#include "vector"
#include "string"

using namespace std;
using namespace sf;

class Map {
private:
    Texture tileSet;

    vector<vector<int>> map;

public:
    Map();

    void load_map(const string&);
    void draw_map(RenderWindow &window);
};

#endif
