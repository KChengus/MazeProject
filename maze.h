#ifndef MAZE_H
#define MAZE_H

#define DIRECTIONS 4

#define SIZE 8
#define DISPLAY_SIZE (SIZE*2)+1
#define COORDS 2

char maze_visual[DISPLAY_SIZE][DISPLAY_SIZE]; 
int compass[DIRECTIONS][COORDS] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}}; // S E N W
unsigned int begin_r = 1;
unsigned int begin_c = 0;
unsigned int end_r = DISPLAY_SIZE - 2;
unsigned int end_c = DISPLAY_SIZE - 1;

int total_cells = SIZE * SIZE;

namespace symbol {
    char border = '#';
    char passageWay = ' ';
    char cell = '.';
    char current_pos = 'x';
}
#endif