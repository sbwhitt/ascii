#pragma once

#include <string>
#include <vector>
#include <ncurses.h>

#include "coordinate.h"
#include "entity.h"
#include "door.h"

class level {
    private:
        int rows;
        int cols;
        coordinate * p_start = new coordinate(0, 0);
        std::string terrain;
        std::vector<entity*> entities;
        std::vector<door*> doors;

        entity* create_entity(std::string spec);
        door* create_door(std::string spec);
        void destroy_entities();
        bool is_level(const char* path);
        coordinate* get_coord(std::string line);

    public:
        level();
        level(int rows, int cols, std::string terrain);
        ~level();
        int load_file(const char* fname);
        void set(int rows, int cols, std::string terrain);
        void render(WINDOW* win);
        std::vector<entity*> get_entities();
        std::vector<door*> get_doors();
        int get_rows();
        int get_cols();
        coordinate* get_p_start();
        void lock_doors();
        void unlock_doors();
        bool has_entities();
};