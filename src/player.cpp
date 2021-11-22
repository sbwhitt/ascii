#include <ncurses.h>

#include "player.h"
#include "coordinate.h"
#include "sprite.h"

player::player() {}

void player::update_row(int offset, int row_max) {
    this->coord->row_adjust(offset, row_max);
}

void player::update_col(int offset, int col_max) {
    this->coord->col_adjust(offset, col_max);
}

void player::render(WINDOW* win) {
    mvwprintw(win, this->coord->row, this->coord->col, this->s.get_sprite());
    // refresh();
}

bool player::collides(entity *e) {
    return e->get_pos()->row == this->coord->row && e->get_pos()->col == this->coord->col ? true : false;
}

void player::add_score(int amount) {
    this->score += amount;
}

int player::get_score() {
    return this->score;
}

coordinate* player::get_pos() {
    return this->coord;
}

std::string player::log_pos() {
    std::string ret;
    ret += "player pos: ";
    ret += std::to_string(this->coord->row);
    ret += ", ";
    ret += std::to_string(this->coord->col);

    return ret += "\n";
}

player::~player() {
    delete this->coord;
}
