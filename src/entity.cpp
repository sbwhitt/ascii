#include <string>
#include <math.h>
#include <ncurses.h>

#include "entity.h"
#include "coordinate.h"
#include "sprite.h"
#include "level.h"

entity::entity() {}

entity::entity(int row, int col) {
    this->coord->row = row;
    this->coord->col = col;
}

entity::entity(int row, int col, std::string sprite) {
    this->coord->row = row;
    this->coord->col = col;
    this->s.raw = sprite;
}

entity::entity(int row, int col, std::string sprite, bool nme) {
    this->coord->row = row;
    this->coord->col = col;
    this->s.raw = sprite;
    this->enemy = nme;
}

void entity::update_rand(int row_max, int col_max) {
    if ((rand() % 2 + 1) % 2 == 0) this->coord->row_adjust(rand() % 3 - 1, row_max);
    else this->coord->col_adjust(rand() % 3 - 1, col_max);
}

void entity::update_follow(int row_max, int col_max, coordinate* target) {
    int row_diff = 0;
    int col_diff = 0;
    
    if (target->row > this->coord->row) row_diff = 1;
    else if (target->row < this->coord->row) row_diff = -1;
    else if (target->col > this->coord->col) col_diff = 1;
    else if (target->col < this->coord->col) col_diff = -1;

    int choice = 1 + (rand() % 3);
    switch (choice) {
        case 1:
            this->coord->row_adjust(row_diff, row_max);
        case 2:
            this->coord->col_adjust(col_diff, col_max);
        case 3:
            break;
    }
}

void entity::set_pos(int row, int col) {
    this->coord->row = row;
    this->coord->col = col;
}

void entity::render(WINDOW* win) {
    mvwprintw(win, this->coord->row, this->coord->col, this->s.get_sprite());
    // refresh();
}

void entity::destroy() {
    this->exists = false;
}

bool entity::alive() {
    return this->exists;
}

bool entity::is_enemy() {
    return this->enemy;
}

coordinate* entity::get_pos() {
    return this->coord;
}

std::string entity::log_pos() {
    std::string ret;
    ret += "entity ";
    // ret += std::to_string(this->id);
    ret += " pos: ";
    ret += std::to_string(this->coord->row);
    ret += ", ";
    ret += std::to_string(this->coord->col);

    return ret += "\n";
}

entity::~entity() {
    // delete this->sprite;
    delete this->coord;
}
