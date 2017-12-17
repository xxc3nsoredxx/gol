#ifndef COLOR_H_20171217_134220
#define COLOR_H_20171217_134220

#define ABS(X) (((X) < 0) ? (-1 * (X)) : (X))

/* Creates an rgb color from hsv values */
unsigned int color (int h, float s, float v);

#endif
