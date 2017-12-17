#include <unistd.h>
#include <linux/fb.h>

#include "screen.h"

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
void clear () {
    write (1, CSI, 2);
    write (1, "2J", 2);
}

/* Turns row,col into an absolute position */
unsigned int position (unsigned int row, unsigned int col) {
    unsigned int ll = screen.finfo.line_length;
    unsigned int bpp = screen.info.bits_per_pixel;
    return (row * (ll / (bpp / 8))) + col;
}

/* Draws the pixel to the screen */
void paint (unsigned int *buf, unsigned int pos, unsigned int color) {
    if (pos != (unsigned int)-1) *(buf + pos) = color;
}
