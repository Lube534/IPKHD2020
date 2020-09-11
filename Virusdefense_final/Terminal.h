#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
// #include "Color.h"


#define BLUE_BLACK     1
#define GREEN_BLACK    2
#define RED_BLACK      3
#define BLUE_GREY      4
#define GREEN_GREY     5
#define RED_GREY       6
#define BLACK_BLUE     7
#define BLACK_GREEN    8
#define BLACK_RED      9
#define WHITE_BLACK    10
#define YELLOW_BLACK   11
#define BLACK_YELLOW   12


class Terminal
{
    public:
        /**
        * Initializes the terminal with a given width and height.
        *
        * @param width The width of the terminal
        * @param height The height of the terminal
        */
        Terminal(int width, int height);

        /**
        * Gives the width of the terminal in cells.
        */
        int width() const;

        /**
        * Gives the height of the terminal in cells.
        */
        int height() const;

        /**
        * Gets the keyboard input. Simply returns the pressed key.
        *
        * @returns The pressed key character.
        */
        char get_key() const;

        /**
        * Set a given cell at coordinates (x, y) to the given symbol.
        * Access outside of the bounds of the terminal is ignored.
        * Can draw in color, marked by parameter colorpair.
        *
        * @param x The x coordinate
        * @param y The y coordinate
        * @param colorpair The fore- and background colorpair
        * @param symbol The symbol to set the cell to
        */

        void set_cell(int x, int y, char symbol, int colorpair);

        /**
        * Draws text starting at the given cell coordinates (x, y).
        * Access outside of the bounds of the terminal is ignored.
        *
        * @param x The x coordinate
        * @param y The y coordinate
        * @param text The text to draw to the terminal.
        */
        void draw_text(int x, int y, const std::string& text);

        /**
        * Clears the terminal. Call this on every frame for interactive
        * applications like games.
        */
        void clear();

        /**
        * Closes the terminal and resets everything to normal.
        */
        void close();

        /**
        * Pauses the Application for a short amount of time. Time is
        * given in milliseconds.
        *
        * @param ms Time in milliseconds.
        */
        void sleep(int ms);
};

#endif
