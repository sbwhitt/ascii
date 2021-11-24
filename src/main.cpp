#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <ncurses.h>

#include "coordinate.h"
#include "player.h"
#include "level.h"
#include "entity.h"
#include "sprite.h"

void hard_clear() {
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            printw(" ");
        }
        printw("\n");
    }
}

void cleanup(std::vector<WINDOW*> wins) {
    for (size_t i = 0; i < wins.size(); i++) {
        wrefresh(wins[i]);
        delwin(wins[i]);
    }
    clear();
    printw("GAME OVER\n");
    printw("press any key to exit");
    getch();
    endwin();
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
    curs_set(0);
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, (COLOR_RED | COLOR_YELLOW), COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_CYAN);

    // initialize level and accept cmd line input
    level l;
    if (argc > 1) {
        if (l.load_file(argv[1]) != 0) return -1;
    }
    else l.load_file("./levels/one.lvl");

    // initialize windows
    std::vector<WINDOW*> wins;
    WINDOW* game_win = newwin(l.get_rows()+1, l.get_cols()+1, 1, 1);
    WINDOW* game_bord = newwin(l.get_rows()+3, l.get_cols()+3, 0, 0);
    WINDOW* txt_win = newwin(4, 30, 0, l.get_cols()+4);

    wins.push_back(game_win); wins.push_back(game_bord); wins.push_back(txt_win);
    
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

        if (!l.has_entities()) l.unlock_doors();
        for (size_t i = 0; i < l.get_doors().size(); i++) {
            if (p.collides(l.get_doors()[i]) && !l.get_doors()[i]->is_locked()) {
                l.load_file(l.get_doors()[i]->get_path().c_str());
                hard_clear();
                refresh();
                clear();                
                
                wresize(game_win, l.get_rows()+1, l.get_cols()+1);
                wresize(game_bord, l.get_rows()+3, l.get_cols()+3);
                mvwin(txt_win, 0, l.get_cols()+4);
                wrefresh(game_bord);
                wrefresh(game_win);
                wrefresh(txt_win);

                p.set_pos(l.get_p_start());
                l.render(game_win);
                break;
            }
        }

        for (size_t i = 0; i < l.get_entities().size(); i++) {
            if (l.get_entities()[i]->alive() && p.collides(l.get_entities()[i])) {
                if (l.get_entities()[i]->is_enemy()) {
                    cleanup(wins);
                    return 0;
                }
                p.add_score(1);
                l.get_entities()[i]->destroy();
                l.get_entities()[i]->set_pos(rand() % l.get_rows(), rand() % l.get_cols());
            }
        }

        p.render(game_win);
        l.render_doors(game_win);
        l.render_entities(game_win);

        wborder(game_bord, '|', '|', '-', '-', '+', '+', '+', '+');
        
        std::string p_score = "player score: " + std::to_string(p.get_score());
        mvwprintw(txt_win, 1, 1, p_score.c_str());
        mvwprintw(txt_win, 2, 1, p.log_pos().c_str());
        // mvwprintw(txt_win, 3, 1, e1.log_pos().c_str());
        // mvwprintw(txt_win, 4, 1, e2.log_pos().c_str());
        // mvwprintw(txt_win, 5, 1, e3.log_pos().c_str());
        wborder(txt_win, '|', '|', '-', '-', '+', '+', '+', '+');
        
        wrefresh(game_bord);
        // wrefresh(game_win);
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
    }

    cleanup(wins);
    return 0;
}
