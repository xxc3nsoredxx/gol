#include <string.h>

#include "game.h"
#include "screen.h"

/* The game board */
extern unsigned int *buf;
/* The next round */
extern unsigned int *next;
extern struct screen_s screen;
extern unsigned int scale;

unsigned int neighbors (unsigned int row, unsigned int col,
                        unsigned int bg_color) {
    unsigned int ret = 0;

    /* Test TL corner */
    if (row == 0 && col == 0) {
        if (*(buf + position_abs (row, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col)) != bg_color)
            ret++;
    }
    /* Test TR corner */
    else if (row == 0 && col == (screen.width - scale)) {
        if (*(buf + position_abs (row + scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col - scale)) != bg_color)
            ret++;
    }
    /* Test BL corner */
    else if (row == screen.height - scale && col == 0) {
        if (*(buf + position_abs (row - scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col + scale)) != bg_color)
            ret++;
    }
    /* Test BR corner */
    else if (row == screen.height - scale && col == screen.width - scale) {
        if (*(buf + position_abs (row - scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col - scale)) != bg_color)
            ret++;
    }
    /* Test top side */
    else if (row == 0) {
        if (*(buf + position_abs (row, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col - scale)) != bg_color)
            ret++;
    }
    /* Test right side */
    else if (col == screen.width - scale) {
        if (*(buf + position_abs (row - scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col - scale)) != bg_color)
            ret++;
    }
    /* Test bottom side */
    else if (row == screen.height - scale) {
        if (*(buf + position_abs (row - scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col - scale)) != bg_color)
            ret++;
    }
    /* Test left side */
    else if (col == 0) {
        if (*(buf + position_abs (row - scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col)) != bg_color)
            ret++;
    }
    /* Test inner */
    else {
        if (*(buf + position_abs (row - scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col + scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col)) != bg_color)
            ret++;
        if (*(buf + position_abs (row + scale, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row, col - scale)) != bg_color)
            ret++;
        if (*(buf + position_abs (row - scale, col - scale)) != bg_color)
            ret++;
    }

    return ret;
}

/* Steps through the game */
void step (unsigned int bg_color, unsigned int fg_color) {
    /* The next round */
    unsigned int row;
    unsigned int col;
    unsigned int n;

    /* The main logic for the game */
    for (row = 0; row < screen.height; row += scale) {
        for (col = 0; col < screen.width; col += scale) {
            n = neighbors (row, col, bg_color);
            if (n < 2)
                paint_pos (next, row, col, bg_color);
            else if (n == 2 && *(buf + position_abs (row, col)) == fg_color)
                paint_pos (next, row, col, fg_color);
            else if (n == 3)
                paint_pos (next, row, col, fg_color);
            else
                paint_pos (next, row, col, bg_color);
        }
    }

    memcpy (buf, next, screen.finfo.smem_len);
}
