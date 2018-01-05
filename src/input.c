#include <curses.h>
#include <string.h>

#include "game.h"
#include "input.h"
#include "screen.h"

extern unsigned int scale;
extern unsigned int *buf;
extern volatile int quit;
extern int key;
extern int row;
extern int col;

void start_input (unsigned bg_color, unsigned fg_color, unsigned curs_color) {
    while (!quit) {
        memcpy (screen.fb, buf, screen.finfo.smem_len);
        paint (screen.fb, curs_color);
        key = getch ();
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
        /* Step */
        case 's':
        case 'S':
            step (bg_color, fg_color);
            break;
        /* Quit (case insensitive) */
        case 'q':
        case 'Q':
            quit = 1;
            break;
        default:
            break;
        }
    }
}
