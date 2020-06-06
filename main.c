#include <stdio.h>
#include <ncurses.h>

int main(void) {
	initscr();

	WINDOW * win;
	win = newwin(200, 200, 0, 0);

	while(true){};

	return 0;
}
