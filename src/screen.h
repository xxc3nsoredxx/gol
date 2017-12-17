#ifndef SCREEN_H_20171217_134650
#define SCREEN_H_20171217_134650

struct screen_s {
    struct fb_var_screeninfo info;
    struct fb_fix_screeninfo finfo;
};

struct screen_s screen;

/* Hide the cursor */
void cursor_hide ();

/* Show the cursor */
void cursor_show ();

/* Move the cursor to top left */
void cursor_home ();

/* Clears the screen */
void clear ();

/* Turns row,col into an absolute position */
unsigned int position (unsigned int row, unsigned int col);

/* Draws the pixel to the screen */
void paint (unsigned int *buf, unsigned int pos, unsigned int color);

#endif
