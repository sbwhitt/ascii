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
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, this->coord->row, this->coord->col, this->s.get_sprite());
    wattroff(win, COLOR_PAIR(2));
    // refresh();
}

bool player::collides(entity *e) {
    return e->get_pos()->row == this->coord->row && e->get_pos()->col == this->coord->col ? true : false;
}

void player::add_score(int amount) {
    this->score += amount;
}

void player::set_pos(coordinate* c) {
    this->coord->row = c->row;
    this->coord->col = c->col;
}

void player::add_life() {
    this->life += 1;
}

void player::lose_life() {
    this->life -= 1;
}

int player::get_score() {
    return this->score;
}

coordinate* player::get_pos() {
    return this->coord;
}

int player::get_life() {
    return this->life;
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
