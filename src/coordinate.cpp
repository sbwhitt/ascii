#include "coordinate.h"
// #include "level.h"

coordinate::coordinate(int row, int col) {
    this->row = row;
    this->col = col;
}

void coordinate::row_adjust(int offset, int row_max) {
    if (this->row + offset < 0) return;
    else if (this->row + offset > row_max) return;
    else this->row += offset;
}

void coordinate::col_adjust(int offset, int col_max) {
    if (this->col + offset < 0) return;
    else if (this->col + offset > col_max) return;
    else this->col += offset;
}
