#include <string.h>

#include "game.h"
#include "screen.h"

/* The game board */
extern unsigned int *buf;
/* The next round */
extern unsigned int *next;
extern struct screen_s screen;
extern unsigned int scale;

unsigned int neighbors (unsigned int row, unsigned int col) {
    unsigned int ret = 0;

    /* Test TL corner */
    if (row == 0 && col == 0) {
        ret = 3;
    }
    /* Test TR corner */
    else if (row == 0 && col == screen.width - scale) {
    }
    /* Test BL corner */
    else if (row == screen.height - scale && col == 0) {
    }
    /* Test BR corner */
    else if (row == screen.height - scale && col == screen.width - scale) {
    }
    /* Test top side */
    else if (row == 0) {
    }
    /* Test right side */
    else if (col == screen.width - scale) {
    }
    /* Test bottom side */
    else if (row == screen.height - scale) {
    }
    /* Test left side */
    else if (col == 0) {
    }
    /* Test inner */
    else {
    }

    return ret;
}

/* Steps through the game */
void step (unsigned int bg_color, unsigned int fg_color) {
    /* The next round */
    unsigned int row;
    unsigned int col;

    for (row = 0; row < screen.height - scale; row += scale) {
        for (col = 0; col < screen.width - scale; col += scale) {
            if (*(buf + position_abs (row, col)) == fg_color)
                paint_pos (next, row, col, bg_color);
            else if (*(buf + position_abs (row, col)) == bg_color)
                paint_pos (next, row, col, fg_color);
        }
    }

    memcpy (buf, next, screen.finfo.smem_len);
}
