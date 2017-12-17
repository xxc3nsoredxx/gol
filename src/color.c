#include "color.h"

/* Creates an rgb color from hsv values */
unsigned int color (int h, float s, float v) {
    unsigned int ret = 0;
    double c;
    double x;
    double m;
    double rp;
    double gp;
    double bp;
    unsigned char r;
    unsigned char g;
    unsigned char b;

    c = v * s;
    x = c * (1 - ABS(((h / 60) % 2) - 1));
    m = v - c;

    h %= 360;
    if (0 <= h && h < 60) {
        rp = c;
        gp = x;
        bp = 0;
    } else if (60 <= h && h < 120) {
        rp = x;
        gp = c;
        bp = 0;
    } else if (120 <= h && h < 180) {
        rp = 0;
        gp = c;
        bp = x;
    } else if (180 <= h && h < 240) {
        rp = 0;
        gp = x;
        bp = c;
    } else if (240 <= h && h < 300) {
        rp = x;
        gp = 0;
        bp = c;
    } else if (200 <= h && h < 360) {
        rp = c;
        gp = 0;
        bp = x;
    }

    r = (rp + m) * 255;
    g = (gp + m) * 255;
    b = (bp + m) * 255;

    ret |= r << 16;
    ret |= g << 8;
    ret |= b;

    return ret;
}
