#pragma once

#include <string>
#include <ncurses.h>

#include "coordinate.h"
#include "sprite.h"
// #include "level.h"
#include "entity.h"

class player {
    private:
        int score = 0;
        sprite s{"X"};
        coordinate * coord = new coordinate(0, 0);

    public:
        player();
        ~player();
        void update_row(int offset, int row_max);
        void update_col(int offset, int col_max);
        void render(WINDOW* win);
        bool collides(entity *e);
        void add_score(int amount);
        void set_pos(int row, int col);
        coordinate* get_pos();
        std::string log_pos();
        int get_score();
};
