#ifndef CREATESCENE_HPP
#define CREATESCENE_HPP
#pragma once

#include "sceneGraph.hpp"

/**
Adds an hourglass shape to the Scene Graph tree.
Note: this has not been tested, since it was never used.

@param z The z value relative to the parent node.
@param squareLenX The length of the square it can be drawn within in the x direction.
@param squareLenY The length of the square it can be drawn within in the y direction.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddHourglass(float z, float squareLenX, float squareLenY, struct ColorRGBA color);

/**
Adds a hexagon shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param center The center of the drawing area.
@param radius The radius of the drawing area.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddHexagon(float z, struct CoordinateXY center, float radius, struct ColorRGBA color);

/**
Adds a pacman shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param center The center of the drawing area.
@param radius The radius of the drawing area.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddPacman(float z, struct CoordinateXY center, float radius, struct ColorRGBA color);

/**
Adds a triangle shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param center The center of the drawing area.
@param squareLenX The length of the square it can be drawn within in the x direction.
@param squareLenY The length of the square it can be drawn within in the y direction.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddTriangle(float z, struct CoordinateXY center, float squareLenX, float squareLenY, struct ColorRGBA color);

/**
Adds a square shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param squareLenX The length of the square it can be drawn within in the x direction.
@param squareLenY The length of the square it can be drawn within in the y direction.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddSquare(float z, float squareLenX, float squareLenY, struct ColorRGBA color);

/**
Adds a skewed square shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param center The center of the drawing area.
@param drawLenX The allowed length to draw from the center in the x direction.
@param drawLenY The allowed length to draw from the center in the y direction.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddSquareSkewd(float z, struct CoordinateXY center, float drawLenX, float drawLenY, struct ColorRGBA color);

/**
Adds a V shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param center The center of the drawing area.
@param drawLenX The allowed length to draw from the center in the x direction.
@param drawLenY The allowed length to draw from the center in the y direction.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddV(float z, struct CoordinateXY center, float drawLenX, float drawLenY, struct ColorRGBA color);

/**
Adds a star shape to the Scene Graph tree.

@param z The z value relative to the parent node.
@param center The center of the drawing area.
@param radius The radius of the drawing area.
@param color The desired color of the shape.
@return The Scene Graph Node containing the shape.
*/
SceneNode* AddStar(float z, struct CoordinateXY center, float radius, struct ColorRGBA color);

/**
Creates the board, including all the squares and all the design-stuff around it.

@param xRange The range in the x direction where the board should be drawn within.
@param yRange The range in the y direction where the board should be drawn within.
@param squaresX The amount of squares that should be drawn in the x direction.
@param squaresY The amount of squares that should be drawn in the y direction.
@param z The z value of the board.
@param color1 The starting color of the top left corner.
@param color2 The next color after color1.
@return The Scene Graph Node containing the board.
*/
SceneNode* CreateBoard(struct Range xRange, struct Range yRange, unsigned int squaresX, unsigned int squaresY, float z, struct ColorRGBA color1, struct ColorRGBA color2);

#endif