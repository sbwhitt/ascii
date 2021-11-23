#include <string>

#include "door.h"
#include "coordinate.h"

door::door(int row, int col, std::string path) {
    this->lvl_path = path;
    this->coord->row = row;
    this->coord->col = col;
    this->s = "@";
}

void door::set_path(std::string path) {
    this->lvl_path = path;
}

std::string door::get_path() {
    return this->lvl_path;
}

void door::lock() {
    this->locked = true;
}

void door::unlock() {
    this->locked = false;
}

bool door::is_locked() {
    return this->locked;
}
