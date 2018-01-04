#include <unistd.h>
#include <linux/fb.h>

#include "screen.h"

extern unsigned int scale;
extern unsigned int row;
extern unsigned int col;

const char *CSI = "\x1B[";

/* Hide the cursor */
void cursor_hide () {
    write (1, CSI, 2);
    write (1, "?25l", 4);
}

/* Show the cursor */
void cursor_show () {
    write (1, CSI, 2);
    write (1, "?25h", 4);
}

/* Move the cursor to top left */
void cursor_home () {
    write (1, CSI, 2);
    write (1, "H", 1);
}

/* Clears the screen */
void clear_text () {
    write (1, CSI, 2);
    write (1, "2J", 2);
}

/* Uses the global row/col to return a position */
unsigned int position () {
    return position_abs (row, col);
}

/* Turns row,col into an absolute position */
unsigned int position_abs (unsigned int row_p, unsigned int col_p) {
    unsigned int ll = screen.finfo.line_length;
    unsigned int bpp = screen.info.bits_per_pixel;
    return (row_p * (ll / (bpp / 8))) + col_p;
}

/* Draws the pixel using global vars row and col */
void paint (unsigned int *buf, unsigned int color) {
    unsigned int d_row;
    unsigned int d_col;

    for (d_row = 0; d_row < scale; d_row++)
        for (d_col = 0; d_col < scale; d_col++)
            paint_pos (buf, position_abs (row + d_row, col + d_col), color);
}

/* Draws the pixel to the screen at position pos */
void paint_pos (unsigned int *buf, unsigned int pos, unsigned int color) {
    *(buf + pos) = color;
}
