#include <curses.h>
#include <string.h>

#include "input.h"
#include "screen.h"

extern unsigned int scale;
extern unsigned int *buf;
extern volatile int quit;
extern int key;
extern unsigned int row;
extern unsigned int col;

void start_input (unsigned int bg_color, unsigned int curs_color) {
    while (!quit) {
        memcpy (screen.fb, buf, screen.finfo.smem_len);
        paint (screen.fb, curs_color);
        key = getch ();
        switch (key) {
        case 'q':
        case 'Q':
            quit = 1;
            break;
        /* Move the cursor */
        case KEY_UP:
            if (row > 0) {
                paint (screen.fb, bg_color);
                row -= scale;
            }
            break;
        case KEY_DOWN:
            if (row < screen.height) {
                paint (screen.fb, bg_color);
                row += scale;
            }
            break;
        case KEY_LEFT:
            if (col > 0) {
                paint (screen.fb, bg_color);
                col -= scale;
            }
            break;
        case KEY_RIGHT:
            if (col < screen.width) {
                paint (screen.fb, bg_color);
                col += scale;
            }
            break;
        default:
            break;
        }
    }
}
