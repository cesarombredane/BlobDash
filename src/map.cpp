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
            tile.setTextureRect(IntRect(tile_num % 10 * TILE_SIZE, tile_num / 10 * TILE_SIZE, TILE_SIZE, TILE_SIZE));
            tile.setPosition(Vector2f(x_window, y_window));
            window.draw(tile);

            x_window += TILE_SIZE;
        }
        y_window += TILE_SIZE;
    }
}

int Map::get_map_value(int x, int y) {
    return this->map.at(y).at(x);
}

int Map::get_height() {
    return (int) this->map.size();
}

int Map::get_width() {
    return (int) this->map.at(0).size();
}
