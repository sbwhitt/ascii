#pragma once

#include <string>

#include "door.h"
#include "coordinate.h"
#include "sprite.h"

class door {
    private:
        std::string lvl_path;
        coordinate* coord = new coordinate(0, 0);
        sprite s{"@"};

    public:
        door(std::string path, int row, int col);
        ~door();
        void set_path(std::string path);
        void set_pos(int row, int col);
        std::string get_path();
        coordinate* get_pos();
};