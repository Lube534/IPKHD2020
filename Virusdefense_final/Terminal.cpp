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

	// init_color(00,00,00,00);
	/*
	0 = Black
	1 = Red
	2 = Green
	3 = Yellow
	4 = Blue
	5 = Purple
	6 = Cyan
	7 = White
	8 = Grey
	9 = Light red
	10 = Neon green
	11 = light yellow
	12 = light blue
	13 = light purple
	14 = turquoise
	15 = light white
	16 = black or undefined
	17 = dark dark dark dark blue
	18 = dark dark dark blue
	19 = dark dark blue
	20 = dark blue
	120 = interesting green
	130 = orange

	*/
	init_pair(BLUE_BLACK, COLOR_CYAN, COLOR_BLACK);
	init_pair(GREEN_BLACK, 120, COLOR_BLACK);
	init_pair(RED_BLACK, 9, COLOR_BLACK);
	init_pair(BLUE_GREY, COLOR_CYAN, COLOR_WHITE);
	init_pair(GREEN_GREY, 120, COLOR_WHITE);
	init_pair(RED_GREY, 9, COLOR_WHITE);
	init_pair(BLACK_BLUE, COLOR_BLACK, COLOR_CYAN);
	init_pair(BLACK_GREEN, COLOR_BLACK, 120);
	init_pair(9, COLOR_BLACK, 9);
	init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair(YELLOW_BLACK, 11, COLOR_BLACK);
	init_pair(BLACK_YELLOW, COLOR_BLACK, 11);

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
