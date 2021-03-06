#include "stdafx.h"

void display_game(void);
void time_trigger(void);
void new_game(void);
void input(void);
void play(void);

typedef struct s_position {
	char pos_x;
	char pos_y;
} position_t;

struct s_position body[LARGURA*COMPRIMENTO];
struct s_position fruta;

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
		clock_t before = clock();
		time_trigger();

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
		initial_play();
	}

	HideCursor();
}

void display_game() 
{
	print_logo();
	print_board();
	print_score();
}

void input() {
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
	if (game_state == PLAY) {
		clear_game_area();

		SetPosition(fruta.pos_x + 3, fruta.pos_y + 8);
		printf(ANSI_COLOR_RED "*" ANSI_COLOR_RESET);

		for (int i = 0; i < LARGURA*COMPRIMENTO; i++) {
			if (body[i].pos_x != -2) {
				SetPosition(body[i].pos_x + 3, body[i].pos_y + 8);
				if (i == 0)
					printf(ANSI_COLOR_BLUE "O" ANSI_COLOR_RESET);
				else
					printf("O");
			}
			else
				break;
		}

		SetPosition(38, 8);
		printf("%d", (body_length - 3) * 10);

		HideCursor();
	}
	else if (game_state == GAME_OVER) {

		print_gameOver();
		HideCursor();

		char retry = 0;
		char pos = 0;
		do {

			while (!_kbhit());

			switch (_getch()) {
			case 'A':
			case 'a':
				print_playAgain();
				pos = 0;
				break;
			case 'D':
			case 'd':
				print_exit();
				pos = 1;
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

void time_trigger()
{
	if (body_length - 3 < 10)
		trigger = 220;
	else if (body_length - 3 >= 10 && body_length - 3 < 20)
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