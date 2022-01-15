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

    int get_map_value(int, int);
    int get_height();
    int get_width();

    void load_map(const string&);
    void draw_map(RenderWindow &window);

    static const int TILE_SIZE = 32;
};

#endif
