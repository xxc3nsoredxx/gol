#include <curses.h>
#include <fcntl.h>
#include <omp.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "color.h"
#include "game.h"
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
extern unsigned int *game;
extern unsigned int *next;
extern struct screen_s screen;
extern unsigned int scale;
extern volatile int cont;

/* Global variables */
int row;
int col;
volatile int quit;

int main () {
    int fb_file;
    /* Used to build each frame */
    unsigned int *build;
    WINDOW *main_win;
    unsigned int fg_color;
    unsigned int bg_color;
    unsigned int curs_color;
    int key;
    int thread;

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

    /* Attempt to create a game board */
    game = calloc (screen.finfo.smem_len, 1);
    if (!game) {
        write (2, "Error creating game board.\n", 27);
        munmap (screen.fb, screen.finfo.smem_len);
        close (fb_file);
        return -1;
    }
    /* Attempt to create a buffer for the next generation */
    next = calloc (screen.finfo.smem_len, 1);
    if (!next) {
        write (2, "Error creating next round.\n", 27);
        munmap (screen.fb, screen.finfo.smem_len);
        free (game);
        close (fb_file);
        return -1;
    }
    /* Attempt to create a buffer to build each frame into */
    build = calloc (screen.finfo.smem_len, 1);
    if (!build) {
        write (2, "Error creating build buf.\n", 26);
        munmap (screen.fb, screen.finfo.smem_len);
        free (next);
        free (game);
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

    /* Print instructions */
    printw ("Instructions:\n");
    printw ("\tArrow keys to move the cursor.\n");
    printw ("\tSpace to toggle cell.\n");
    printw ("\tEnter to play/pause\n");
    printw ("\t's' to step the game (when paused)\n");
    printw ("\t'q' to quit.\n");
    printw ("Press any key to begin...");
    key = getch ();
    clear ();
    cursor_home ();

    /* Initialize colors */
    fg_color = LGRAY;
    bg_color = BLACK;
    curs_color = GREEN;

    /* Center the cursor */
    row = screen.height / 2;
    if (row % 2 == 1) row--;
    col = screen.width / 2;
    if (col % 2 == 1) col--;

    #pragma omp parallel private(thread) shared(game, quit, cont) num_threads(3)
    {
    thread = omp_get_thread_num ();
    quit = 0;
    cont = 0;
    /* Input loop */
    if (thread == 0) {
        while (!quit) {
            key = getch ();
            quit = parse_input (bg_color, fg_color, key);
        }
    }
    /* Build each frame */
    if (thread == 1) {
        while (!quit) {
            memcpy (screen.fb, build, screen.finfo.smem_len);
            memcpy (build, game, screen.finfo.smem_len);
            paint (build, curs_color);
        }
    }
    /* Game loop */
    else {
        while (!quit) {
            if (cont == 1) {
                step (bg_color, fg_color);
                cont = 0;
            } else if (cont == 2) {
                step (bg_color, fg_color);
            }
        }
    }
    }

    /* Close ncurses */
    endwin ();

    /* Clear the screen */
    memset (screen.fb, 0, screen.finfo.smem_len);
    clear_text ();
    cursor_home ();
    cursor_show ();

    /* Close the framebuffer */
    free (game);
    free (next);
    free (build);
    munmap (screen.fb, screen.finfo.smem_len);
    close (fb_file);

    return 0;
}
