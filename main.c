#include <stdio.h>
#include <ncurses.h>

// Size of playing field
#define WIDTH 10
#define HEIGHT 10

/*	The playing field is calculated using the grid below
 *	This way, we do not have to create an array to store 
 *	the entirety of the playing field, but just where the
 *	snake occupies space.
 *
 *	For example, the index of a 4 by 4 playing field is 
 *	listed below.
 *	+-----------+
 *	|0 |1 |2 |3 |
 *	|--+--+--+--|
 *	|4 |5 |6 |7 |
 *	|--+--+--+--|
 *	|8 |9 |10|11|
 *	|--+--+--+--|
 *	|12|13|14|15|
 *	+-----------+
 *
 *	Use the coordinateToX and coordinateToY functions to
 *	find the x/y coordinates of each index.
 *
 *	The following table show the x/y coordinate of a 4 by 4
 *	playing field:
 *
 * +-------+-------+-------+-------+
 * | (0,1) | (1,1) | (2,1) | (3,1) |
 * +-------+-------+-------+-------+
 * | (0,2) | (1,2) | (2,2) | (3,2) |
 * +-------+-------+-------+-------+
 * | (0,3) | (1,3) | (2,3) | (3,3) |
 * +-------+-------+-------+-------+
 * | (0,4) | (1,4) | (2,4) | (3,4) |
 * +-------+-------+-------+-------+
 *
 */

// Array to store snake position
// snake[number on grid][time to live]
int snake[WIDTH*HEIGHT][2];	// TODO: dynamically allocated snake instead of setting hard value
int snakeHead;

void initGrid();
void initNcurses();
void printSnake();
void initSnake();
int coordinateToX(int input);
int coordinateToY(int input);

int	main () {
	// init
	initNcurses();
	initGrid();
	initSnake();

	// debug
	snake[0][0] = 50;
	snake[1][0] = 51;
	snake[2][0] = 52;
	snake[3][0] = 53;

	// Set snakeHead to last element in snake[][]
	for (int i = 0; i < sizeof(snake)/sizeof(snake[0]); i++) {
		if ( snake[i][0] != -1 )
			continue;

		snakeHead = snake[i-1][0];
		break;
	}

	printSnake();
	
	getch();

	endwin();
	return(0);
}

// Print snake on grid
void printSnake () {
	attron(COLOR_PAIR(1));
	for (int i = 0; i < sizeof(snake)/sizeof(snake[0]); i++) {
		// Don't print if snake does not exsist -1
		if ( snake[i][0] == -1 )
			continue;

		mvprintw(coordinateToY(snake[i][0])+1,coordinateToX(snake[i][0])*2+1,"  ");
	}

	attron(COLOR_PAIR(2));
	mvprintw(coordinateToY(snakeHead)+1,coordinateToX(snakeHead)*2+1,"  ");

	attroff(COLOR_PAIR(2));
}

// Initialize Snake
void initSnake () {
	for (int i = 0; i < sizeof(snake)/sizeof(snake[0]); i++) {
		snake[i][0] = -1;
		snake[i][1] = -1;
	}
}

// Initialize ncurses
void initNcurses () {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
}

// Prints screen, initialize grid
void initGrid () {
	// Enable Color
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_CYAN);	// Snake color
	init_pair(2, COLOR_BLACK, COLOR_GREEN);	// Snake head color
	init_pair(3, COLOR_BLACK, COLOR_RED);	// Apple color

	// Print top and bottom bars
	move(0,0);
	printw("+");
	for (int i = 0; i < WIDTH*2; i++)
		printw("-");
	printw("+");

	move(HEIGHT+1,0);
	printw("+");
	for (int i = 0; i < WIDTH*2; i++)
		printw("-");
	printw("+");

	// Print sidebars
	for (int i = 1; i < HEIGHT+1; i++)
		mvprintw(i,0,"|");

	for (int i = 1; i < HEIGHT+1; i++)
		mvprintw(i,WIDTH*2+1,"|");

}

// Parse the coordinate number system to array index (x)
int coordinateToX ( int input ) {
	return input%WIDTH;
}

// Parse the coordinate number system to array index (y)
int coordinateToY ( int input ) {
	return input/HEIGHT;
}
