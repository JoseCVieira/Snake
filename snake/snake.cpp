/***************************************\
*	 Author		-> José C. R. Vieira	*
*	 Program	-> Snake				*
\***************************************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

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

#define LARGURA 22
#define COMPRIMENTO 15
#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define PLAY 1
#define GAME_OVER 2
#define PAUSE 3

void display_game(void);
void SetPosition(int, int);
void input(void);
void play(void);
void clear_game_area(void);
void HideCursor(void);
void new_game(void);
void escolhe_tempo(void);

struct fruta_pos {
	char pos_x;
	char pos_y;
}fruta;
struct snake {
	char pos_x = -2;
	char pos_y = -2;
};
struct snake body[LARGURA*COMPRIMENTO];
char last_state = RIGHT;
char last_state_real = RIGHT;
char game_state = PLAY;
int body_length = 3;
char apanhou_fruta = 1;
char first_time = 1;
int trigger = 220;

int main() {
	int msec = 0;

	new_game();

	while (true) {
		// espera 200 ms e vai verificando se foi pressionado alguum botao
		clock_t before = clock();

		escolhe_tempo();

		msec = 0;
		do {
			clock_t difference = clock() - before;
			msec = difference * 1000 / CLOCKS_PER_SEC;
			input();
		} while (msec < trigger);

		play();
	}

    return 0;
}

void new_game(void) {
	last_state = RIGHT;
	last_state_real = RIGHT;
	game_state = PLAY;
	body_length = 3;
	apanhou_fruta = 1;
	trigger = 220;

	for (int i = 0; i < COMPRIMENTO*LARGURA; i++) {
		body[i].pos_x = -2;
		body[i].pos_y = -2;
	}

	system("cls");
	display_game();

	body[0].pos_x = LARGURA / 2;
	body[0].pos_y = COMPRIMENTO / 2;
	body[1].pos_x = LARGURA / 2 - 1;
	body[1].pos_y = COMPRIMENTO / 2;
	body[2].pos_x = LARGURA / 2 - 2;
	body[2].pos_y = COMPRIMENTO / 2;

	if (first_time) {
		first_time = 0;
		SetPosition(29, 15);
		printf(ANSI_COLOR_RED "+------+" ANSI_COLOR_RESET);
		SetPosition(29, 16);
		printf(ANSI_COLOR_RED "| " ANSI_COLOR_RESET "PLAY " ANSI_COLOR_RED "|" ANSI_COLOR_RESET);
		SetPosition(29, 17);
		printf(ANSI_COLOR_RED "+------+" ANSI_COLOR_RESET);

		HideCursor();

		while (_getch() != '\r');

		SetPosition(29, 15);
		printf("        ");
		SetPosition(29, 16);
		printf("        ");
		SetPosition(29, 17);
		printf("        ");
	}

	HideCursor();
}

void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void SetPosition(int X, int Y) {
	HANDLE Screen;
	Screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Position = {X, Y};
	SetConsoleCursorPosition(Screen, Position);
}

void display_game() {

	printf(ANSI_COLOR_RED "   _____ " ANSI_COLOR_RESET "            _        \n");
	printf(ANSI_COLOR_RED "  / ____|" ANSI_COLOR_RESET "           | |       \n");
	printf(ANSI_COLOR_RED " | (___  " ANSI_COLOR_RESET "_ __   __ _| | _____ \n");
	printf(ANSI_COLOR_RED "  \\___ \\" ANSI_COLOR_RESET "| '_ \\ / _` | |/ / _ \\\n");
	printf(ANSI_COLOR_RED "  ____) " ANSI_COLOR_RESET "| | | | (_| |   <  __/\n");
	printf(ANSI_COLOR_RED " |_____/" ANSI_COLOR_RESET "|_| |_|\\__,_|_|\\_\\___|\n");

	printf("\n  ");
	for (char i = 0; i < LARGURA + 3; i++)
		printf(ANSI_COLOR_CYAN "#" ANSI_COLOR_RESET);

	for (char i = 0; i < COMPRIMENTO+1; i++) {

		printf(ANSI_COLOR_CYAN "\n  #" ANSI_COLOR_RESET);
		for (char j = 0; j < LARGURA+1; j++) {
			printf(" ");
		}

		printf(ANSI_COLOR_CYAN "#" ANSI_COLOR_RESET);
	}

	printf("\n  ");
	for (char i = 0; i < LARGURA + 3; i++)
		printf(ANSI_COLOR_CYAN "#" ANSI_COLOR_RESET);

	SetPosition(27, 7);
	printf(ANSI_COLOR_GREEN "  /= = = = = = = =\\" ANSI_COLOR_RESET);
	SetPosition(27, 8);
	printf(ANSI_COLOR_GREEN "  |               |" ANSI_COLOR_RESET);
	SetPosition(27, 9);
	printf(ANSI_COLOR_GREEN "  \\= = = = = = = =/" ANSI_COLOR_RESET);

	SetPosition(29, 20);
	printf("    +---+       +------+");
	SetPosition(29, 21);
	printf("    | W |       | <--' |");
	SetPosition(29, 22);
	printf("+---+---+---+   +-+    |");
	SetPosition(29, 23);
	printf("| A | S | D |     |    |");
	SetPosition(29, 24);
	printf("+---+---+---+     +----+");

	SetPosition(31, 8);
	printf("Score:");
}

void input() {
	// verifica botão carregado
	if (_kbhit()) {
		switch (_getch()) {
		case 'A':
		case 'a':
				last_state = LEFT;
			break;
		case 'D':
		case 'd':
				last_state = RIGHT;
			break;
		case 'W':
		case 'w':
				last_state = UP;
			break;
		case 'S':
		case 's':
				last_state = DOWN;
			break;
		default:
			break;
		}
	}
}

void play() {
	//gera nova fruta && verifica se nao coincide com a cobra
	if (apanhou_fruta) {
		char flag = 0;
		int i = 0;

		do {
			apanhou_fruta = 0;
			fruta.pos_x = rand() % LARGURA;
			fruta.pos_y = rand() % COMPRIMENTO;

			for (i = 0; i < LARGURA * COMPRIMENTO; i++) {
				if (fruta.pos_x == body[i].pos_x && fruta.pos_y == body[i].pos_y)
					break;
			}

			if (i == LARGURA * COMPRIMENTO)
				flag = 1;

		} while (!flag);
	}

	for (int i = (LARGURA * COMPRIMENTO) - 2; i >= 0; i--) {
		if (body[i].pos_x != -2) {
			body[i + 1] = body[i];
		}
	}

	// verifica botão carregado
	switch (last_state) {
	case LEFT:
		if (last_state_real == RIGHT) { // nao pode virar 180 graus
			body[0].pos_x = body[1].pos_x + 1;
			last_state_real = RIGHT;
			last_state = RIGHT;
		}
		else {
			body[0].pos_x = body[1].pos_x - 1;
			last_state_real = LEFT;
			last_state = LEFT;
		}
		body[0].pos_y = body[1].pos_y;
		break;
	case RIGHT:
		if (last_state_real == LEFT) { // nao pode virar 180 graus
			body[0].pos_x = body[1].pos_x - 1;
			last_state_real = LEFT;
			last_state = LEFT;
		}
		else {
			body[0].pos_x = body[1].pos_x + 1;
			last_state_real = RIGHT;
			last_state = RIGHT;
		}
		body[0].pos_y = body[1].pos_y;
		break;
	case UP:
		if (last_state_real == DOWN) { // nao pode virar 180 graus
			body[0].pos_y = body[1].pos_y + 1;
			last_state_real = DOWN;
			last_state = DOWN;
		}
		else {
			body[0].pos_y = body[1].pos_y - 1;
			last_state_real = UP;
			last_state = UP;
		}
		body[0].pos_x = body[1].pos_x;
		break;
	case DOWN:
		if (last_state_real == UP) { // nao pode virar 180 graus
			body[0].pos_y = body[1].pos_y - 1;
			last_state_real = UP;
			last_state = UP;
		}
		else {
			body[0].pos_y = body[1].pos_y + 1;
			last_state_real = DOWN;
			last_state = DOWN;
		}
		body[0].pos_x = body[1].pos_x;
		break;
	default:
		break;
	}

	// verifica se apanhou a fruta
	if (body[0].pos_x == fruta.pos_x && body[0].pos_y == fruta.pos_y) {
		apanhou_fruta = 1;
		body_length++;
	}

	// game over - bateu nas paredes
	if (body[0].pos_x >= LARGURA + 1 || body[0].pos_x <= -1 ||
		body[0].pos_y >= COMPRIMENTO + 1 || body[0].pos_y <= -1) {
		game_state = GAME_OVER;
	}

	// game over - bateu no proprio corpo
	for (int i = 1; i < LARGURA*COMPRIMENTO; i++) {
		if (body[0].pos_x == body[i].pos_x && body[0].pos_y == body[i].pos_y) {
			game_state = GAME_OVER;
		}
		if (body[0].pos_x == -2)
			break;
	}

	// elimina a ultima parte do corpo
	body[body_length].pos_x = -2;
	body[body_length].pos_y = -2;

	// desenha cobra + fruta
	if(game_state == PLAY) {
		clear_game_area();

		SetPosition(fruta.pos_x + 3, fruta.pos_y + 8);
		printf(ANSI_COLOR_RED "*" ANSI_COLOR_RESET);

		for (int i = 0; i < LARGURA*COMPRIMENTO; i++) {
			if (body[i].pos_x != -2) {
				SetPosition(body[i].pos_x + 3, body[i].pos_y + 8);
				if(i == 0)
					printf(ANSI_COLOR_BLUE "O" ANSI_COLOR_RESET);
				else
				printf("O");
			}
			else
				break;
		}

		SetPosition(38, 8);
		printf("%d", (body_length-3)*10);

		HideCursor();
	}
	else if (game_state == GAME_OVER) {

		SetPosition(29, 11);
		printf(ANSI_COLOR_RED "+---+---+---+--+-+--+---+---+---+" ANSI_COLOR_RESET);
		SetPosition(29, 12);
		printf(ANSI_COLOR_RED "| G | a | m | e| |o | v | e | r |" ANSI_COLOR_RESET);
		SetPosition(29, 13);
		printf(ANSI_COLOR_RED "+---+---+---+--+-+--+---+---+---+" ANSI_COLOR_RESET);


		SetPosition(29, 15);
		printf(ANSI_COLOR_RED "+------------+" ANSI_COLOR_RESET);
		SetPosition(29, 16);
		printf(ANSI_COLOR_RED "| " ANSI_COLOR_RESET "PLAY AGAIN " ANSI_COLOR_RED "|" ANSI_COLOR_RESET);
		SetPosition(29, 17);
		printf(ANSI_COLOR_RED "+------------+" ANSI_COLOR_RESET);

		SetPosition(50, 15);
		printf(" ------ ");
		SetPosition(50, 16);
		printf("| EXIT |");
		SetPosition(50, 17);
		printf(" ------ ");

		HideCursor();

		char retry = 0;
		char pos = 0;
		do {

			while (!_kbhit());

			switch (_getch()) {
			case 'A':
			case 'a':
				SetPosition(29, 15);
				printf(ANSI_COLOR_RED "+------------+" ANSI_COLOR_RESET);
				SetPosition(29, 16);
				printf(ANSI_COLOR_RED "| " ANSI_COLOR_RESET "PLAY AGAIN " ANSI_COLOR_RED "|" ANSI_COLOR_RESET);
				SetPosition(29, 17);
				printf(ANSI_COLOR_RED "+------------+" ANSI_COLOR_RESET);

				SetPosition(50, 15);
				printf(" ------ ");
				SetPosition(50, 16);
				printf("| EXIT |");
				SetPosition(50, 17);
				printf(" ------ ");

				pos = 0;
				HideCursor();
				break;
			case 'D':
			case 'd':
				SetPosition(29, 15);
				printf(" ------------ ");
				SetPosition(29, 16);
				printf("| PLAY AGAIN |");
				SetPosition(29, 17);
				printf(" ------------ ");

				SetPosition(50, 15);
				printf(ANSI_COLOR_RED "+------+" ANSI_COLOR_RESET);
				SetPosition(50, 16);
				printf(ANSI_COLOR_RED "| " ANSI_COLOR_RESET "EXIT " ANSI_COLOR_RED "|" ANSI_COLOR_RESET);
				SetPosition(50, 17);
				printf(ANSI_COLOR_RED "+------+" ANSI_COLOR_RESET);

				pos = 1;
				HideCursor();
				break;
			case '\r':
				if (pos)
					exit(1);
				else {
					new_game();
					retry = 1;
				}
				break;
			default:
				break;
			}
			
		} while (!retry);
	}
}

void escolhe_tempo() {
	if (body_length - 3 < 10)
		trigger = 220;
	else if(body_length - 3 >= 10 && body_length - 3 < 20)
		trigger = 200;
	else if (body_length - 3 >= 20 && body_length - 3 < 30)
		trigger = 180;
	else if (body_length - 3 >= 30 && body_length - 3 < 40)
		trigger = 160;
	else if (body_length - 3 >= 40 && body_length - 3 < 50)
		trigger = 140;
	else if (body_length - 3 >= 50 && body_length - 3 < 60)
		trigger = 120;
	else if (body_length - 3 >= 60)
		trigger = 100;

}

void clear_game_area() {
	for (char i = 0; i <= COMPRIMENTO; i++) {
		SetPosition(3, i + 8);
		for (char j = 0; j <= LARGURA; j++) {
			printf(" ");
		}
	}
}