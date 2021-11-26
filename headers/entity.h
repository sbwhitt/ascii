#pragma once

#include <string>
#include <ncurses.h>

#include "coordinate.h"
#include "sprite.h"
// #include "level.h"

class entity {
    protected:
        bool exists = true;
        bool enemy = false;
        sprite s{"!"};
        coordinate * coord = new coordinate(0, 0);

    public:
        entity();
        entity(int row, int col);
        entity(int row, int col, std::string sprite);
        entity(int row, int col, std::string sprite, bool nme);
        ~entity();
        void update_rand(int row_max, int col_max);
        void update_follow(int row_max, int col_max, coordinate* target);
        void set_pos(int row, int col);
        void render(WINDOW* win);
        void destroy();
        bool alive();
        bool is_enemy();
        coordinate* get_pos();
        std::string log_pos();
};
