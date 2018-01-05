#include <curses.h>
#include <string.h>

#include "game.h"
#include "input.h"
#include "screen.h"

extern unsigned int scale;
extern unsigned int *buf;
extern int row;
extern int col;
extern volatile int cont;

int parse_input (unsigned int bg_color, unsigned int fg_color, int key) {
    int ret = 0;

    switch (key) {
    /* Move the cursor */
    case KEY_UP:
        if (row - (int)scale >= 0) {
            paint (screen.fb, bg_color);
            row -= scale;
        }
        break;
    case KEY_DOWN:
        if (row + scale <= screen.height - scale) {
            paint (screen.fb, bg_color);
            row += scale;
        }
        break;
    case KEY_LEFT:
        if (col - (int)scale >= 0) {
            paint (screen.fb, bg_color);
            col -= scale;
        }
        break;
    case KEY_RIGHT:
        if (col + scale <= screen.width - scale) {
            paint (screen.fb, bg_color);
            col += scale;
        }
        break;
    /* Toggle cell */
    case ' ':
        if (*(buf + position ()) == bg_color)
            paint (buf, fg_color);
        else
            paint (buf, bg_color);
        break;
    /* Play/pause */
    case '\n':
        if (cont != 2)
            cont = 2;
        else
            cont = 0;
        break;
    /* Step */
    case 's':
    case 'S':
        if (cont != 2)
            cont = 1;
        break;
    /* Quit (case insensitive) */
    case 'q':
    case 'Q':
        ret = 1;
        break;
    default:
        break;
    }

    return ret;
}
