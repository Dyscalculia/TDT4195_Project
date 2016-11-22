#ifndef DRAWBOARD_HPP
#define DRAWBOARD_HPP
#pragma once

#include "boardHelpers.h"

/**
Creates a vertex array object containing vertices representing an hourglass.
Note: this has not been tested, since it was never used.

@param xRange The range in the x direction where the shape should be drawn within.
@param yRange The range in the y direction where the shape should be drawn within.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateHourglass(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a square.

@param xRange The range in the x direction where the shape should be drawn within.
@param yRange The range in the y direction where the shape should be drawn within.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateSquare(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a skewed square.

@param xRange The range in the x direction where the shape should be drawn within.
@param yRange The range in the y direction where the shape should be drawn within.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateSquareSkewd(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a triangle.

@param xRange The range in the x direction where the shape should be drawn within.
@param yRange The range in the y direction where the shape should be drawn within.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateTriangle(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a Pacman shape.

@param center The center of the shape.
@param radius The radius (from the center) of the shape.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param trianglesAmount The amount of triangles a full 360 degrees circle should consist of. The higher the number, the smoother the circle will look.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreatePacman(struct CoordinateXY center, float radius, float z, float height, unsigned int trianglesAmount, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a hexagon shape.

@param center The center of the shape.
@param radius The radius (from the center) of the shape.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateHexagon(struct CoordinateXY center, float radius, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a V shape.

@param xRange The range in the x direction where the shape should be drawn within.
@param yRange The range in the y direction where the shape should be drawn within.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateV(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Creates a vertex array object containing vertices representing a star shape having 5 corners.

@param center The center of the shape.
@param radius The radius (from the center) of the shape.
@param z The z value of the shape.
@param height The height of the extruded shape.
@param color The RGBA color of the shape.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateStar(struct CoordinateXY center, float radius, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);

/**
Extrudes the last present triangle in the supplied arrays. Will add a triangle below the current one, and duplicate the colors.
Will then create the three "walls" between the two triangles by using already existing indices.

@param vertices A pointer to an array containing the vertices for the current shape to be extruded.
@param indices A pointer to an array containing the indices for the current shape to be extruded.
@param colors A pointer to an array containing the colors for the current shape to be extruded.
@param indicesWritePosPtr A pointer to the next available/free index in the indices array. Will be updated to contain the next free index after the extrusion.
@param nextDrawNumberPtr A pointer to the next available/free index in the vertices array. Will be updated to contain the next free index after the extrusion.
@param colorWritePosPtr A pointer to the next available/free index in the color array. Will be updated to contain the next free index after the extrusion.
@param zDifference The difference in the z value between the top and the bottom of the shape. This will represent the height of the extruded shape.
*/
void ExtrudedTriangle(float* vertices, unsigned int* indices, float* colors, unsigned int* indicesWritePosPtr, unsigned int* nextDrawNumberPtr, unsigned int* colorWritePosPtr, float zDifference);

/**
Updates the vertices and colors of the supplied arrays.

@param l The current write location in the arrays.
@param xyz The coordinates that should be written to the vertices array.
@param color The color values that should be written to the color array.
@param vertices A pointer to an array containing the vertices for the current shape to be updated.
@param colors A pointer to an array containing the colors for the current shape to be updated.
*/
inline void UpdateVertexAndColorBuffer(unsigned int l, struct CoordinateXYZ xyz, struct ColorRGBA color, float* vertices, float* colors);

/**
Creates a vertex array object with the supplied vertices, colors and indices.

@param vertexCoordinates A pointer to an array containing the vertices for the current shape to be added.
@param vertexRGBA A pointer to an array containing the colors for the current shape to be added.
@param indices A pointer to an array containing the indices for the current shape to be added.
@param vertexCount The amount of items in the vertex array.
@param colorCount The amount of items in the color array.
@param indicesCount The amount of items in the index array.
@param vaoid Optionally possible to specify a vertex array object ID.
@return The ID of the vertex array object containing the shape.
*/
unsigned int CreateVAOWithTriangles(float* vertexCoordinates, float* vertexRGBA, unsigned int* indices, unsigned int vertexCount, unsigned int colorCount, unsigned int indicesCount, unsigned int vaoid = 0);

#endif