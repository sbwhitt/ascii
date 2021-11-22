#pragma once

#include <string>
#include <ncurses.h>

#include "coordinate.h"
#include "sprite.h"
// #include "level.h"

class entity {
    private:
        bool exists = true;
        sprite s{"!"};
        coordinate * coord = new coordinate(0, 0);

    public:
        entity();
        entity(int row, int col);
        entity(int row, int col, std::string s);
        ~entity();
        void update(int row_max, int col_max);
        void set_pos(int row, int col);
        void render(WINDOW* win);
        void destroy();
        bool status();
        coordinate* get_pos();
        std::string log_pos();
};
