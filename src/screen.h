#ifndef SCREEN_H_20171217_134650
#define SCREEN_H_20171217_134650

#include <linux/fb.h>

struct screen_s {
    struct fb_var_screeninfo info;
    struct fb_fix_screeninfo finfo;
    unsigned int width;
    unsigned int height;
    unsigned int *fb;
};

struct screen_s screen;
/* Used to scale the UI */
unsigned int scale;

/* Hide the cursor */
void cursor_hide ();

/* Show the cursor */
void cursor_show ();

/* Move the cursor to top left */
void cursor_home ();

/* Clears the screen */
void clear_text ();

/* Uses the global row/col to return a position */
unsigned int position ();

/* Turns row,col into an absolute position */
unsigned int position_abs (unsigned int row, unsigned int col);

/* Draws the pixel using global vars row and col */
void paint (unsigned int *buf, unsigned int color);

/* Draws the pixel to the screen at position pos */
void paint_pos (unsigned int *buf, unsigned int row,
                unsigned int col, unsigned int color);

#endif
