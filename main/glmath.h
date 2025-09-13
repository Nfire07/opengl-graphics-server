#ifndef GLMATH_H
#define GLMATH_H

/* Define a simple structure to represent a 2D point with integer coordinates (screen space) */
typedef struct {
    int x;
    int y;
} Point;

/* 
 * Convert a pixel x-coordinate (screen space) to normalized device coordinates (NDC) in the range [-1, 1]
 * screenWidth is the width of the rendering window in pixels
 */
static float toNDCx(int px, int screenWidth) {
    return ((float)px / (float)screenWidth) * 2.0f - 1.0f;
}

/* 
 * Convert a pixel y-coordinate (screen space) to normalized device coordinates (NDC) in the range [-1, 1]
 * Note: y=0 is top of the screen, so conversion flips the y-axis to OpenGL coordinate system
 * screenHeight is the height of the rendering window in pixels
 */
static float toNDCy(int py, int screenHeight) {
    return 1.0f - ((float)py / (float)screenHeight) * 2.0f;
}

#endif /* GLMATH_H */
