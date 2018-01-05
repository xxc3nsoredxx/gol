#ifndef GAME_H_20180104_140840
#define GAME_H_20180104_140840

/* The main game board */
unsigned int *game;
/* The buffer for the next generation */
unsigned int *next;
/* Used to tell the game to proceed a generation
 * 0 -> paused
 * 1 -> single step
 * 2 -> continuous
 */
volatile int cont;

/* Steps one generation forwards in the game */
void step (unsigned int bg_color, unsigned int fg_color);

#endif
