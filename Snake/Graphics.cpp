#include "stdafx.h"
#include "Graphics.h"

void print_logo(void)
{
	printf(ANSI_COLOR_RED "   _____ " ANSI_COLOR_RESET "            _        \n");
	printf(ANSI_COLOR_RED "  / ____|" ANSI_COLOR_RESET "           | |       \n");
	printf(ANSI_COLOR_RED " | (___  " ANSI_COLOR_RESET "_ __   __ _| | _____ \n");
	printf(ANSI_COLOR_RED "  \\___ \\" ANSI_COLOR_RESET "| '_ \\ / _` | |/ / _ \\\n");
	printf(ANSI_COLOR_RED "  ____) " ANSI_COLOR_RESET "| | | | (_| |   <  __/\n");
	printf(ANSI_COLOR_RED " |_____/" ANSI_COLOR_RESET "|_| |_|\\__,_|_|\\_\\___|\n");
	printf("\n  ");
}

void print_board(void)
{
	for (char i = 0; i < LARGURA + 3; i++)
		printf(ANSI_COLOR_CYAN "#" ANSI_COLOR_RESET);

	for (char i = 0; i < COMPRIMENTO + 1; i++) {

		printf(ANSI_COLOR_CYAN "\n  #" ANSI_COLOR_RESET);
		for (char j = 0; j < LARGURA + 1; j++) {
			printf(" ");
		}

		printf(ANSI_COLOR_CYAN "#" ANSI_COLOR_RESET);
	}

	printf("\n  ");
	for (char i = 0; i < LARGURA + 3; i++)
		printf(ANSI_COLOR_CYAN "#" ANSI_COLOR_RESET);
}

void print_score(void)
{
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

void print_gameOver(void)
{
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
}

void print_playAgain(void)
{
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
}

void print_exit(void)
{
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
	HideCursor();
}

void clear_game_area(void)
{
	for (char i = 0; i <= COMPRIMENTO; i++) {
		SetPosition(3, i + 8);
		for (char j = 0; j <= LARGURA; j++) {
			printf(" ");
		}
	}
}

void initial_play(void)
{
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