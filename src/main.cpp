#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <ncurses.h>

#include "coordinate.h"
#include "player.h"
#include "level.h"
#include "entity.h"
#include "sprite.h"

bool is_level(char* arg) {
    std::regex r("([a-zA-Z]*.lvl)");
    std::string s = arg;
    if (std::regex_match(s, r)) return true;
    return false;
}

int main(int argc, char *argv[]) {
    initscr();
    if(has_colors() == FALSE) {
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    raw();
    noecho();
    start_color();

    // initialize level and accept cmd line input
    level l;
    if (argc > 1 && is_level(argv[1])) {
        std::string path = "./levels/";
        path += argv[1];
        l.load_file(path.c_str());
    }
    else l.load_file("./levels/one.lvl");

    // initialize windows
    WINDOW* game_win = newwin(l.get_rows()+1, l.get_cols()+1, 1, 1);
    WINDOW* game_bord = newwin(l.get_rows()+3, l.get_cols()+3, 0, 0);
    WINDOW* txt_win = newwin(3, 30, 0, l.get_cols()+4);
    
    refresh();
    wrefresh(game_win);
    wrefresh(game_bord);
    wrefresh(txt_win);

    // initialize player and entities
    player p;
    
    // main loop
    while (!(GetKeyState('X') & 0x8000)) {
        Sleep(50);
        l.render(game_win);

        auto entities = l.get_entities();
        for (size_t i = 0; i < entities.size(); i++) {
            if (entities[i]->status()) {
                entities[i]->render(game_win);
                if (p.collides(entities[i])) {
                    p.add_score(1);
                    // entities[i]->destroy();
                    entities[i]->set_pos(rand() % l.get_rows(), rand() % l.get_cols());
                }
                entities[i]->update(l.get_rows(), l.get_cols());
            }
        }
        p.render(game_win);

        wborder(game_bord, '|', '|', '-', '-', '+', '+', '+', '+');
        
        std::string p_score = "player score: " + std::to_string(p.get_score());
        mvwprintw(txt_win, 1, 1, p_score.c_str());
        mvwprintw(txt_win, 2, 1, p.log_pos().c_str());
        // mvwprintw(txt_win, 3, 1, e1.log_pos().c_str());
        // mvwprintw(txt_win, 4, 1, e2.log_pos().c_str());
        // mvwprintw(txt_win, 5, 1, e3.log_pos().c_str());
        wborder(txt_win, '|', '|', '-', '-', '+', '+', '+', '+');
        
        wrefresh(game_bord);
        wrefresh(game_win);
        wrefresh(txt_win);

        wgetch(game_win);

        if (GetKeyState('A') & 0x8000) {
            p.update_col(-1, l.get_cols());
        }
        if (GetKeyState('D') & 0x8000) {
            p.update_col(1, l.get_cols());
        }
        if (GetKeyState('W') & 0x8000) {
            p.update_row(-1, l.get_rows());
        }
        if (GetKeyState('S') & 0x8000) {
            p.update_row(1, l.get_rows());
        }

        wclear(game_win);
        wclear(txt_win);
        // clear();
    }
    wrefresh(game_win);
    delwin(game_win);

    wrefresh(game_bord);
    delwin(game_bord);

    wrefresh(txt_win);
	delwin(txt_win);

    clear();
    endwin();
    return 0;
}
