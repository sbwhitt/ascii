#include <string>

#include "item.h"

item::item(int type, int row, int col, std::string sprite) {
    this->type = type;
    this->set_pos(row, col);
    this->s = sprite;
}

int item::get_type() {
    return this->type;
}

int item::get_color() {
    return this->color;
}

std::string item::get_sprite() {
    return this->s.raw;
}
