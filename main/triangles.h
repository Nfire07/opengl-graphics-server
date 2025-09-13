#ifndef TRIANGLES_H
#define TRIANGLES_H

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>



/* Structure to hold OpenGL buffer identifiers for a triangle */
typedef struct {
    unsigned int VAO;  /* Vertex Array Object ID */
    unsigned int VBO;  /* Vertex Buffer Object ID */
} TriangleBuffers;


/* 
 * Creates OpenGL buffers (VAO and VBO) for a triangle defined by three points in screen coordinates.
 * Converts screen coordinates to normalized device coordinates.
 *
 * Parameters:
 *  p1, p2, p3: Points defining the triangle vertices in screen space (pixels).
 *  screenWidth, screenHeight: Size of the rendering window, used for coordinate conversion.
 *
 * Returns:
 *  TriangleBuffers struct containing VAO and VBO IDs.
 *
 * Note:
 *  The caller is responsible for deleting these buffers when no longer needed.
 */
static TriangleBuffers createTriangleBuffers(Point p1, Point p2, Point p3, int screenWidth, int screenHeight) {
    /* Array to store the triangle vertices in NDC (x, y, z) */
    float vertices[9];

    /* Convert each point's screen coordinates (pixels) to NDC coordinates */
    vertices[0] = toNDCx(p1.x, screenWidth);
    vertices[1] = toNDCy(p1.y, screenHeight);
    vertices[2] = 0.0f; /* z-coordinate (2D, so 0) */

    vertices[3] = toNDCx(p2.x, screenWidth);
    vertices[4] = toNDCy(p2.y, screenHeight);
    vertices[5] = 0.0f;

    vertices[6] = toNDCx(p3.x, screenWidth);
    vertices[7] = toNDCy(p3.y, screenHeight);
    vertices[8] = 0.0f;

    TriangleBuffers buffers = {0};

    /* Generate and bind a Vertex Array Object (VAO) to store vertex attribute config */
    glGenVertexArrays(1, &buffers.VAO);
    glBindVertexArray(buffers.VAO);

    /* Generate and bind a Vertex Buffer Object (VBO) to store vertex data on GPU */
    glGenBuffers(1, &buffers.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, buffers.VBO);

    /* Upload vertex data to the GPU */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Configure vertex attribute pointer:
     * Attribute 0, 3 floats per vertex (x, y, z), no normalization,
     * tightly packed with no stride offset, data starts at buffer offset 0
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /* Unbind VAO to avoid accidental modification */
    glBindVertexArray(0);

    return buffers;
}

/* 
 * Draws the triangle using the provided VAO.
 *
 * Parameters:
 *  buffers: TriangleBuffers struct containing VAO and VBO IDs.
 */
static void drawTriangleBuffers(TriangleBuffers buffers) {
    glBindVertexArray(buffers.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

/* 
 * Deletes the OpenGL buffers associated with the triangle.
 * Must be called to free GPU resources when the triangle is no longer needed.
 *
 * Parameters:
 *  buffers: TriangleBuffers struct containing VAO and VBO IDs.
 */
static void deleteTriangleBuffers(TriangleBuffers buffers) {
    glDeleteBuffers(1, &buffers.VBO);
    glDeleteVertexArrays(1, &buffers.VAO);
}

/* 
 * Convenience function that creates buffers, draws the triangle, and deletes buffers immediately.
 * This is less efficient for repeated drawing but useful for quick one-time draws.
 *
 * Parameters:
 *  p1, p2, p3: Points defining the triangle vertices in screen space (pixels).
 *  screenWidth, screenHeight: Size of the rendering window.
 */
static void drawTriangleFromPoints(Point p1, Point p2, Point p3, int screenWidth, int screenHeight) {
    TriangleBuffers buffers = createTriangleBuffers(p1, p2, p3, screenWidth, screenHeight);
    drawTriangleBuffers(buffers);
    deleteTriangleBuffers(buffers);
}

#endif /* TRIANGLES_H */
