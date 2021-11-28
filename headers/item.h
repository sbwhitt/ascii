#pragma once

#include <string>

#include "entity.h"
#include "sprite.h"

enum items {
    life = 1,
    armor = 2,
    sword = 3
};

class item: public entity {
    private:
        int type;
        int color = 7;

    public:
        item(int type, int row, int col, std::string sprite);
        int get_type();
        int get_color();
        std::string get_sprite();
        // ~item();
};