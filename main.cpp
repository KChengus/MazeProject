#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "maze.cpp"

#define PAIRS 2


// forward declare functions
void maze_traverse(int r, int c);    
bool isPath(int r, int c);
void printState();
void turnLeft();
void turnRight();

// global variables
int r_index = 0;
int righthandAndFacing[PAIRS][PAIRS] = { {1, 0}, {0, 1} };
unsigned sleep_duration = 150000; // in microseconds

int main() {
    maze_main();
    maze_traverse(begin_r, begin_c);
    // for (size_t i = 0; i < DIRECTIONS; ++i) {
    //     turnLeft();
    //     printState();
    // }
    printf("You have escaped!!!\n");
    return 0;
}


bool isPath(int r, int c, int step[PAIRS]) {
    // adjecent cell
    r = r + step[0];
    c = c + step[1];
    assert (r >= 0 && r < DISPLAY_SIZE && c >= 0 && c < DISPLAY_SIZE) ;
    return not (maze_visual[r][c] == symbol::border);
}


void maze_traverse(int r, int c) {
    // check if escaped
    display_maze(r, c);
    if (r == end_r && c == end_c) return;
    usleep(sleep_duration);
    if (isPath(r, c, righthandAndFacing[0])) {
        // hand part is able to go
        // turnRight();
        int temp_r = r+righthandAndFacing[0][0];
        int temp_c = c+righthandAndFacing[0][1];
        turnRight();
        maze_traverse(temp_r, temp_c);
        return;
    }
    for (size_t i = 0; i < DIRECTIONS; ++i) {
        // test direction 
        if (isPath(r, c, righthandAndFacing[1])) {
            // direction is able to go
            maze_traverse(r+righthandAndFacing[1][0], c+righthandAndFacing[1][1]);
            return;
        }
        // change direction
        turnLeft();
    }
    std::cout << "Something went wrong\n";
    return;
}

void printState() {
    if (r_index == 0) {
        printf("Right hand is DOWN and is Facing RIGHT\n");
    } else if (r_index == 1) {
        printf("Right hand is RIGHT and is Facing UP\n");
    } else if (r_index == 2) {
        printf("Right hand is UP and is Facing LEFT\n");
    } else if (r_index == 3) {
        printf("Right hand is LEFT and is Facing DOWN\n");
    } else {
        printf("ERROROR");
    }
}

void turnLeft() {
    // turns counter clockwise
    r_index = (r_index+1) % DIRECTIONS;

    righthandAndFacing[0][0] = compass[r_index][0];
    righthandAndFacing[0][1] = compass[r_index][1];
        
    righthandAndFacing[1][0] = compass[(r_index+1) % DIRECTIONS][0];
    righthandAndFacing[1][1] = compass[(r_index+1) % DIRECTIONS][1];
    // printf("Turned Left\n");
    // printState();
}

void turnRight() {
    // turns clockwise
    righthandAndFacing[1][0] = compass[r_index][0];
    righthandAndFacing[1][1] = compass[r_index][1];

    r_index = ((r_index-1) == -1 ? 3 : (r_index-1));
    
    righthandAndFacing[0][0] = compass[r_index][0];
    righthandAndFacing[0][1] = compass[r_index][1];
    // printf("Turned Right\n");
}

