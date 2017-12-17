#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "color.h"
#include "screen.h"

/* Global variables from headers */
extern struct screen_s screen;

/* Global variables */
volatile sig_atomic_t interrupted = 0;

void handler () {
    interrupted = 1;
}

int main () {
    int fb_file;
    unsigned int *fb;
    unsigned int *buf;
    sigset_t mask;
    struct sigaction usr_action;
    int row;
    int col;

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

    /* Attempt to mmap the framebuffer */
    fb = mmap (0, screen.finfo.smem_len, PROT_READ|PROT_WRITE,
               MAP_SHARED, fb_file, 0);
    if ((long)fb == (long)MAP_FAILED) {
        write (2, "Error mapping framebuffer to memory.\n", 37);
        close (fb_file);
        return -1;
    }

    /* Attempt to create a temp screen buffer */
    buf = calloc (screen.finfo.smem_len, 1);
    if (!buf) {
        write (2, "Error creating temp buffer.\n", 28);
        munmap (fb, screen.finfo.smem_len);
        close (fb_file);
        return -1;
    }

    /* Set up the SIGINT handler */
    sigfillset (&mask);
    usr_action.sa_handler = handler;
    usr_action.sa_mask = mask;
    usr_action.sa_flags = 0;
    sigaction (SIGINT, &usr_action, NULL);

    cursor_hide ();
    clear ();
    cursor_home ();

    for (row = 0; row < 100; row += 1) {
        for (col = 0; col < 100; col += 1) {
            paint (buf, position (row, col), color (120, 1, 1));
        }
    }
    /* Copy buffer to screen */
    memcpy (fb, buf, screen.finfo.smem_len);

    /* Wait for SIGINT */
    while (!interrupted);

    /* Clear the screen */
    memset (fb, 0, screen.finfo.smem_len);

    /* Close the framebuffer */
    free (buf);
    munmap (fb, screen.finfo.smem_len);
    close (fb_file);

    cursor_show ();

    return 0;
}
