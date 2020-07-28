#include "Terminal.h"
// #include "Color.h"

#if defined(_WIN32)
#include <curses.h>
#else
#include <ncurses.h>
#endif



Terminal::Terminal(int width, int height)
{
	initscr();
	resize_term(height, width);

	cbreak();
	keypad(stdscr, true);
	noecho();
	curs_set(0);
	timeout(0);
	start_color();


	init_pair(BLUE_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair(BLUE_GREY, COLOR_CYAN, COLOR_WHITE);
	init_pair(GREEN_GREY, COLOR_GREEN, COLOR_WHITE);
	init_pair(RED_GREY, COLOR_RED, COLOR_WHITE);
	init_pair(BLACK_BLUE, COLOR_BLACK, COLOR_CYAN);
	init_pair(BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(BLACK_RED, COLOR_BLACK, COLOR_RED);
	init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
}
int Terminal::width() const
{
	return COLS;
}

int Terminal::height() const
{
	return LINES;
}

void Terminal::set_cell(int x, int y, char symbol, int colorpair){
		attron(COLOR_PAIR(colorpair));
		mvaddch(y, x, symbol);
		attroff(COLOR_PAIR(colorpair));

}

//BEFORE the "global" define of the colorpairs

// void Terminal::set_cell2(int x, int y, char symbol, color fg, color bg )
// {
// 	if(fg == color::Blue && bg == color::Black){
// 		attron(COLOR_PAIR(BLUE_BLACK));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(BLUE_BLACK));
// 	}
// 	else if(fg == color::Green && bg == color::Black){
// 		attron(COLOR_PAIR(GREEN_BLACK));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(GREEN_BLACK));
// 	}
// 	else if(fg == color::Red && bg == color::Black){
// 		attron(COLOR_PAIR(RED_BLACK));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(RED_BLACK));
// 	}
// 	else if(fg == color::Blue && bg == color::Grey){
// 		attron(COLOR_PAIR(BLUE_GREY));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(BLUE_GREY));
// 	}
// 	else if(fg == color::Green && bg == color::Grey){
// 		attron(COLOR_PAIR(GREEN_GREY));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(GREEN_GREY));
// 	}
// 	else if(fg == color::Red && bg == color::Grey){
// 		attron(COLOR_PAIR(RED_GREY));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(RED_GREY));
// 	}
// 	else if(fg == color::Black && bg == color::Blue){
// 		attron(COLOR_PAIR(BLACK_BLUE));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(BLACK_BLUE));
// 	}
// 	else if(fg == color::Black && bg == color::Green){
// 		attron(COLOR_PAIR(BLACK_GREEN));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(BLACK_GREEN));
// 	}
// 	else if(fg == color::Black && bg == color::Red){
// 		attron(COLOR_PAIR(BLACK_RED));
// 		mvaddch(y, x, symbol);
// 		attroff(COLOR_PAIR(BLACK_RED));
// 	}
// 	else{
// 		mvaddch(y, x, symbol);
// 	}
// }

void Terminal::draw_text(int x, int y, const std::string& text)
{
	mvaddstr(y, x, text.c_str());
}

void Terminal::clear()
{
	::clear();
}

void Terminal::close()
{
	endwin();
	curs_set(1);
}

void Terminal::sleep(int ms)
{
	napms(ms);
}

char Terminal::get_key() const
{
	return wgetch(stdscr);
}
