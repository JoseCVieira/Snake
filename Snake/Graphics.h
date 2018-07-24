#pragma once

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define HLINE '─'
#define VLINE '│'
#define NW '┌'
#define NE '┐'
#define SW '─'
#define SE '└'
#define SE  '┘'

#define WIDTH 22
#define LENGTH 15
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define PLAY 1
#define GAME_OVER 2
#define PAUSE 3

void print_playAgain(void);
void clear_game_area(void);
void print_gameOver(void);
void initial_play(void);
void print_board(void);
void print_score(void);
void print_logo(void);
void print_exit(void);