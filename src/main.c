#include <curses.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "color.h"
#include "input.h"
#include "screen.h"

/* Used to scale the UI */
#define SCALE 2

/* Global variables from headers */
/* struct screen_s {
 *    struct fb_var_screeninfo info;
 *    struct fb_fix_screeninfo finfo;
 *    unsigned int width;
 *    unsigned int height;
 *    unsigned int *fb;
 * };
 */
extern struct screen_s screen;
extern unsigned int scale;

/* Global variables */
unsigned int *buf;
volatile int quit;
int key;
unsigned int row;
unsigned int col;

int main () {
    int fb_file;
    WINDOW *main_win;
    unsigned int fg_color;
    unsigned int bg_color;
    unsigned int curs_color;

    /* Attempt to open the framebuffer */
    fb_file = open ("/dev/fb0", O_RDWR);
    if (fb_file == -1) {
        write (2, "Error opening framebuffer.\n", 27);
        return -1;
    }

    /* Attempt to get information about the screen */
    if (ioctl (fb_file, FBIOGET_VSCREENINFO, &(screen.info))) {
        write (2, "Error getting screen var info.\n", 31);
        close (fb_file);
        return -1;
    }
    if (ioctl (fb_file, FBIOGET_FSCREENINFO, &(screen.finfo))) {
        write (2, "Error getting screen fix info.\n", 31);
        close (fb_file);
        return -1;
    }
    screen.width = screen.info.xres;
    screen.height = screen.info.yres;
    scale = SCALE;

    /* Attempt to mmap the framebuffer */
    screen.fb = mmap (0, screen.finfo.smem_len, PROT_READ|PROT_WRITE,
                      MAP_SHARED, fb_file, 0);
    if ((long)screen.fb == (long)MAP_FAILED) {
        write (2, "Error mapping framebuffer to memory.\n", 37);
        close (fb_file);
        return -1;
    }

    /* Attempt to create a temp screen buffer */
    buf = calloc (screen.finfo.smem_len, 1);
    if (!buf) {
        write (2, "Error creating temp buffer.\n", 28);
        munmap (screen.fb, screen.finfo.smem_len);
        close (fb_file);
        return -1;
    }

    /* Start ncurses */
    main_win = initscr ();
    raw ();
    noecho ();
    keypad (main_win, TRUE);

    cursor_hide ();
    clear ();
    cursor_home ();

    printw ("Instructions:\n");
    printw ("\tArrow keys to move the cursor.\n");
    printw ("\tPress 'q' to quit.\n");
    printw ("Press any key to begin...");
    key = getch ();

    quit = 0;

    /* Initialize colors */
    fg_color = WHITE;
    bg_color = BLACK;
    curs_color = GREEN;

    /* Testing purposes only!!! */
    for (row = 0; row < 100 * scale; row += scale) {
        for (col = 0; col < 100 * scale; col += scale) {
            paint (buf, fg_color);
        }
    }
    /* Copy buffer to screen */
    memcpy (screen.fb, buf, screen.finfo.smem_len);

    /* Center the cursor */
    row = screen.height / 2;
    col = screen.width / 2;
    paint (screen.fb, curs_color);

    /* Input loop */
    /* TODO: Fix scaling wrap around bug */
    start_input (bg_color, curs_color);

    /* Close ncurses */
    endwin ();

    /* Clear the screen */
    memset (screen.fb, 0, screen.finfo.smem_len);
    clear_text ();
    cursor_home ();
    cursor_show ();

    /* Close the framebuffer */
    free (buf);
    munmap (screen.fb, screen.finfo.smem_len);
    close (fb_file);

    return 0;
}
