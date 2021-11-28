#pragma once

#include <string>
#include <vector>
#include <ncurses.h>

#include "coordinate.h"
#include "sprite.h"
// #include "level.h"
#include "entity.h"
#include "item.h"

class player {
    private:
        int score = 0;
        int life = 3;
        sprite s{"&"};
        coordinate * coord = new coordinate(0, 0);
        std::vector<item*> items;

    public:
        player();
        ~player();
        void update_row(int offset, int row_max);
        void update_col(int offset, int col_max);
        void render(WINDOW* win);
        bool collides(entity *e);
        void add_score(int amount);
        void add_life();
        void lose_life();
        void set_pos(coordinate* c);
        coordinate* get_pos();
        std::string log_pos();
        int get_score();
        int get_life();
        std::vector<item*> get_items();
};
