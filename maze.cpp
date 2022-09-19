// libraries
#include <cassert>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#include <bitset>
#include "maze.h"

#define TUP 3
#define BITS 16

// bitset has 4 sets of 4 bits where 
// first set of bits is the backtrack direction
// second is the solution / path direction
// third is the border
// forth is the knocked down walls
// each sets of 4 bits means South East North West
std::bitset<BITS> maze[SIZE][SIZE];
std::bitset<BITS> WALL_BITS = 0b0000'0000'0000'1111;

std::bitset<BITS> WALL[DIRECTIONS] = {0b0100, 0b0010, 0b0001, 0b1000}; // S E N W
std::bitset<BITS> OPPOSITE_WALLS[DIRECTIONS] = {0b0001, 0b1000, 0b0100, 0b0010};

// get an adjecent neighbour
std::vector<int> get_random_cell_neighbour(int row, int col) {
    int adj_row, adj_col;
    std::vector<std::vector<int>> neighbours;
    for (size_t i = 0; i < 4; ++i) {
        adj_row = row + compass[i][0];
        adj_col = col + compass[i][1];
        if ((adj_row >= 0 && adj_row < SIZE) && (adj_col >= 0 && adj_col < SIZE) && ((maze[adj_row][adj_col] & WALL_BITS) == 0)) {
            std::vector<int> temp;
            temp.push_back(adj_row);
            temp.push_back(adj_col);
            temp.push_back(i);
            neighbours.push_back(temp);
        }
    }
    // if there are no neighbours return empty vector
    std::vector<int> empty;
    if (neighbours.size() <= 0) return empty; 
    // get random neighbour
    return neighbours.at(generate_randnum(neighbours.size()));
}

void connect_cells(int from_cell_r, int from_cell_c, int to_cell_r
, int to_cell_c, unsigned int compass_index) {
    // check if cells are adjecent to each other and compass points at the right direction
    assert(to_cell_r - from_cell_r == compass[compass_index][0] && to_cell_c - from_cell_c == compass[compass_index][1]);
    
    maze[from_cell_r][from_cell_c] |= WALL[compass_index];
    maze[to_cell_r][to_cell_c] |= OPPOSITE_WALLS[compass_index];
}

void create_maze() {
    // current cell

    int current_cell_r = generate_randnum(SIZE);
    int current_cell_c = generate_randnum(SIZE);
    std::vector<std::vector<int>> backtracks;
    std::vector<int> temp;
    temp[(current_cell_r)];
    temp[(current_cell_c)];
    backtracks.push_back(temp);
    unsigned int visited_cells = 1;
    while (visited_cells < total_cells) {
        std::vector<int> cell_neighbour = get_random_cell_neighbour(current_cell_r, current_cell_c);
        // divide index by x = cell_nei_index / 100 and y = cell_nei_ind / 10 and i = cell_nei_ind % 10
        if (cell_neighbour.size() > 0) {
            // if a neighbour exists => connect cells, add neighbour to backtrack and make current the new neighbour
            connect_cells(current_cell_r, current_cell_c, cell_neighbour[0], cell_neighbour[1], cell_neighbour[2]);
            current_cell_r = cell_neighbour[0];
            current_cell_c = cell_neighbour[1];
            temp = { };
            temp.push_back(current_cell_r);
            temp.push_back(current_cell_c);
            backtracks.push_back(temp);
            ++visited_cells;
        } else {
            // if no new neighbour exists => backtrack  
            std::vector<int> current_cell = backtracks.back();
            current_cell_r = current_cell[0];
            current_cell_c = current_cell[1];
            backtracks.pop_back();
        }
    }
}

int maze_main() {
    srand(time(NULL));
    // connect_cells(1, 1, 1, 0, 0);
    create_maze();
    store_maze();
   
    // create a beginning point and an end point
    maze_visual[begin_r][begin_c] = symbol::passageWay;
    maze_visual[end_r][end_c] = symbol::passageWay;
    display_maze(-1, -1);
    
    return 0;
}

char translateBoolToChar(bool flag) {
    return flag ? symbol::passageWay : symbol::border; 
}

void arrayAddAll(char displayRow[DISPLAY_SIZE], char row[DISPLAY_SIZE]) { 
    for (size_t i = 0; i < DISPLAY_SIZE; i++) {
        displayRow[i] = row[i];
    }
} 

// loop west and north position
void store_maze() {
    char north_connection[DISPLAY_SIZE] = {};
    char west_connection[DISPLAY_SIZE] = {};
    for (size_t i = 0; i < DISPLAY_SIZE - 1; i+=2) {
        north_connection[0] = symbol::border;
        for (size_t j = 1; j < DISPLAY_SIZE; j += 2) {
            // w s e n
            north_connection[j] =  translateBoolToChar(maze[i/2][j/2].test(0));
            north_connection[j+1] = symbol::border;
            west_connection[j-1] = translateBoolToChar(maze[i/2][j/2].test(3));
            west_connection[j] = symbol::cell;
        }

        // north[DISPLAY_SIZE-1] = symbol::border;
        west_connection[DISPLAY_SIZE-1] = symbol::border;
        arrayAddAll(maze_visual[i], north_connection);
        arrayAddAll(maze_visual[i+1], west_connection);
        // create a border all the way at the bottom
        maze_visual[DISPLAY_SIZE-1][i]   = symbol::border;
        maze_visual[DISPLAY_SIZE-1][i+1] = symbol::border; 
    }
    maze_visual[DISPLAY_SIZE-1][DISPLAY_SIZE-1] = symbol::border; 
    printf("\n");
}   

unsigned int generate_randnum(unsigned int limit) {
    return rand() % limit;
}

void display_maze(int current_r, int current_c) {
    printf("\n\n\n\n\n\n\n");
    for (int i = 0; i < DISPLAY_SIZE; ++i) {
        for (int j = 0; j < DISPLAY_SIZE; ++j) {
            if (current_r == i && current_c == j) {
                printf("%c", symbol::current_pos);
            } else {
                printf("%c", maze_visual[i][j]);
            }
        }
        printf("\n"); 
    }
}


int main() {
    maze_main();
    return 0;
}