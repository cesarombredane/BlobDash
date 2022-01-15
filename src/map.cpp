#include "../include/map.h"
#include "iostream"
#include "fstream"
#include "sstream"

Map::Map() {
    if (!this->tileSet.loadFromFile("../assets/graphics/tile_set.png"))
        cerr << "error : tile-set not found" << endl;

    this->map = {};
}

void Map::load_map(const string& level) {
    fstream map_txt;
    string line_str, char_str;
    stringstream stream;
    vector<int> line;

    map_txt.open("../assets/map/map_" + level + ".txt");
    if (!map_txt.is_open())
        cerr << "error : map " << level << " not found" << endl;

    this->map.clear();
    while (!map_txt.eof()) {
        getline(map_txt, line_str);
        if (line_str.empty()) continue;

        stream.clear();
        stream.str(line_str);
        line.clear();

        do {
            getline(stream, char_str, ' ');
            line.push_back(stoi(char_str));
        } while (stream.good());

        this->map.push_back(line);
    }
}

void Map::draw_map(RenderWindow &window) {
    float y_window = 0;
    for (auto & y_map : this->map) {
        float x_window = 0;
        for (int tile_num : y_map) {
            Sprite tile;
            tile.setTexture(this->tileSet);
            tile.setTextureRect(IntRect(tile_num % 10 * 32, tile_num / 10 * 32, 32, 32));
            tile.setPosition(Vector2f(x_window, y_window));
            window.draw(tile);

            x_window += 32;
        }
        y_window += 32;
    }
}