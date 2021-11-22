#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

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
    while (!this->entities.empty()) {
        delete this->entities.back();
        this->entities.pop_back();
    }
    while (!this->doors.empty()) {
        delete this->doors.back();
        this->doors.pop_back();
    }
}

entity* level::create_entity(std::string spec) {
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
    entity* e = new entity(row, col, sprite);

    return e;
}

// entity* level::create_door(std::string spec) {
//     std::string info = spec.substr(spec.find('=')+1, spec.size()-1);
//     int row, col, pos;
//     row = -1;
//     col = -1;
//     std::string sprite;
//     while ((pos = info.find(',')) != std::string::npos) {
//         if (row == -1) {
//             row = stoi(info.substr(0, pos));
//         }
//         else if (col == -1) {
//             col = stoi(info.substr(0, pos));
//         }
//         info.erase(0, pos+1);
//     }
//     sprite = info;
//     entity* e = new entity(row, col, sprite);

//     return e;
// }

int level::load_file(const char* fname) {
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
        else if (line[0] == 'e') {
            this->entities.push_back(create_entity(line));
        }
        // else if (line[0] == 'd') {
        //     this->doors.push_back(create_door(line));
        // }
    }
    fin.close();
    return 0;
}

void level::set(int rows, int cols, std::string terrain) {
    this->rows = rows;
    this->cols = cols;
    this->terrain = terrain;
}

void level::render(WINDOW* win) {
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    wattron(win, COLOR_PAIR(1));
    for (int i = 0; i <= this->rows; i++) {
        for (int j = 0; j <= this->cols; j++) {
            mvwprintw(win, i, j, this->terrain.c_str());
        }
    }
    wattroff(win, COLOR_PAIR(1));
    // refresh();
}

std::vector<entity*> level::get_entities() {
    return this->entities;
}

int level::get_rows() {
    return this->rows;
}

int level::get_cols() {
    return this->cols;
}
