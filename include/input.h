#ifndef BLOB_DASH_INPUT_H
#define BLOB_DASH_INPUT_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Input {
private:
    int x, y;
    bool jump, dash;

public:
    Input();

    int get_x() const;
    int get_y() const;
    bool get_jump() const;
    bool get_dash() const;

    void set_jump(bool);
    void set_dash(bool);

    void input(RenderWindow &window, Event &event);
    void show_input() const;
};

#endif
