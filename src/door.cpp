#include <string>

#include "door.h"
#include "coordinate.h"

door::door(std::string path, int row, int col) {
    this->lvl_path = path;
    this->coord->row = row;
    this->coord->col = col;
}

door::~door() {
    delete this->coord;
}

void door::set_path(std::string path) {
    this->lvl_path = path;
}

void door::set_pos(int row, int col) {
    this->coord->row = row;
    this->coord->col = col;
}

std::string door::get_path() {
    return this->lvl_path;
}

coordinate* door::get_pos() {
    return this->coord;
}
