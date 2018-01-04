#ifndef COLOR_H_20171217_134220
#define COLOR_H_20171217_134220

#define ABS(X) (((X) < 0) ? (-1 * (X)) : (X))

#define GREEN 0x00FF00
#define LGRAY 0xD3D3D3
#define BLACK 0x000000

/* Creates an rgb color from hsv values */
unsigned int color (int h, float s, float v);

#endif
