#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <regex>

#include "level.h"
#include "coordinate.h"
#include "entity.h"
#include "door.h"

level::level() {}

level::level(int rows, int cols, std::string terrain) {
    this->rows = rows;
    this->cols = cols;
    this->terrain = terrain;
}

level::~level() {
    delete this->p_start;
    this->destroy_entities();
}

entity* level::create_entity(std::string spec, bool nme) {
    std::string info = spec.substr(spec.find('=')+1, spec.size()-1);
    int row, col, pos;
    row = -1;
    col = -1;
    std::string sprite;
    while ((pos = info.find(',')) != std::string::npos) {
        if (row == -1) {
            row = stoi(info.substr(0, pos));
        }
        else if (col == -1) {
            col = stoi(info.substr(0, pos));
        }
        info.erase(0, pos+1);
    }
    sprite = info;
    entity* e = new entity(row, col, sprite, nme);

    return e;
}

door* level::create_door(std::string spec) {
    std::string info = spec.substr(spec.find('=')+1, spec.size()-1);
    int row, col, pos;
    row = -1;
    col = -1;
    std::string path;
    std::string sprite = "";
    while ((pos = info.find(',')) != std::string::npos) {
        if (row == -1) row = stoi(info.substr(0, pos));
        else if (col == -1) col = stoi(info.substr(0, pos));
        // else if (sprite == "") sprite = info;
        info.erase(0, pos+1);
    }
    path = info;
    door* d = new door(row, col, path);

    return d;
}

void level::destroy_entities() {
    while (!this->entities.empty()) {
        delete this->entities.back();
        this->entities.pop_back();
    }
    while (!this->doors.empty()) {
        delete this->doors.back();
        this->doors.pop_back();
    }
}

coordinate* level::get_coord(std::string line) {
    std::string info = line.substr(line.find('=')+1, line.size()-1);
    int row, col;
    int pos = info.find(',');

    row = stoi(info.substr(0, pos));
    info.erase(0, pos+1);
    col = stoi(info);

    coordinate * c = new coordinate(row, col);

    return c;
}

int level::load_file(const char* fname) {
    destroy_entities();
    if (!this->is_level(fname)) return -1;
    std::ifstream fin(fname);
    for (std::string line; getline(fin, line);) {
        if (line[0] == 'r') {
            int rows = stoi(line.substr(line.find('=')+1, line.size()-1));
            this->rows = rows;
        }
        else if (line[0] == 'c') {
            int cols = stoi(line.substr(line.find('=')+1, line.size()-1));
            this->cols = cols;
        }
        else if (line[0] == 't') {
            std::string terrain = line.substr(line.find('=')+1, line.size()-1);
            this->terrain = terrain;
        }
        else if (line[0] == 'p') {
            coordinate * c = get_coord(line);
            this->p_start->row = c->row;
            this->p_start->col = c->col;
        }
        else if (line[0] == 'e') {
            this->entities.push_back(create_entity(line, false));
        }
        else if (line[0] == 'n') {
            this->entities.push_back(create_entity(line, true));
        }
        else if (line[0] == 'd') {
            this->doors.push_back(create_door(line));
        }
    }
    fin.close();
    return 0;
}

bool level::is_level(const char* path) {
    std::regex r("(\\W\\D\\S[a-zA-Z]*.*.lvl)");
    std::string s = path;
    if (std::regex_match(s, r)) return true;
    return false;
}

void level::set(int rows, int cols, std::string terrain) {
    this->rows = rows;
    this->cols = cols;
    this->terrain = terrain;
}

void level::lock_doors() {
    for (size_t i = 0; i < this->doors.size(); i++) {
        this->doors[i]->lock();
    }
}

void level::unlock_doors() {
    for (size_t i = 0; i < this->doors.size(); i++) {
        this->doors[i]->unlock();
    }
}

void level::render(WINDOW* win) {
    wattron(win, COLOR_PAIR(1));
    for (int i = 0; i <= this->rows; i++) {
        for (int j = 0; j <= this->cols; j++) {
            mvwprintw(win, i, j, this->terrain.c_str());
        }
    }
    wattroff(win, COLOR_PAIR(1));
}

void level::render_doors(WINDOW* win) {
    for (size_t i = 0; i < this->doors.size(); i++) {
        int color = this->doors[i]->is_locked() ? 5 : 6;
        wattron(win, COLOR_PAIR(color));
        this->doors[i]->render(win);
        wattroff(win, COLOR_PAIR(color));
    }
}

void level::render_entities(WINDOW* win) {
    for (size_t i = 0; i < this->entities.size(); i++) {
        if (this->entities[i]->alive()) {
            int color = this->entities[i]->is_enemy() ? 4 : 3;
            wattron(win, COLOR_PAIR(color));
            this->entities[i]->render(win);
            wattroff(win, COLOR_PAIR(color));
            this->entities[i]->update_rand(this->get_rows(), this->get_cols());
        }
    }   
}

std::vector<entity*> level::get_entities() {
    return this->entities;
}

bool level::has_entities() {
    for (size_t i = 0; i < this->entities.size(); i++) {
        if (this->entities[i]->alive() && !this->entities[i]->is_enemy()) return true;
    }
    return false;
}

std::vector<door*> level::get_doors() {
    return this->doors;
}

int level::get_rows() {
    return this->rows;
}

int level::get_cols() {
    return this->cols;
}

coordinate * level::get_p_start() {
    return this->p_start;
}
