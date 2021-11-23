#pragma once

#include <string>

#include "entity.h"
#include "door.h"
#include "coordinate.h"
#include "sprite.h"

class door: public entity {
    private:
        std::string lvl_path;

    public:
        door(int row, int col, std::string path);
        void set_path(std::string path);
        void set_pos(int row, int col);
        std::string get_path();
        coordinate* get_pos();
};