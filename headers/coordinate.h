#pragma once

// #include "level.h"

class coordinate {
    public:
        int row;
        int col;
        
        coordinate(int row, int col);
        void row_adjust(int offset, int row_max);
        void col_adjust(int offset, int col_max);
};