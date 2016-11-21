#ifndef BOARDHELPER_HPP
#define BOARDHELPER_HPP
#pragma once

#include <string>

/**
Specifies directions possible when moving a shape.
*/
enum MoveDirection { Up, Down, Left, Right };

/**
Specifies possible results when trying to move a shape.
*/
enum MoveResult { OutsideBoard, Uninitialized, AlreadyOccupied, AlreadyMoving, Moved };

/**
Specifies a range of float values.
*/
struct Range
{
	float start, end;
};

/**
Specifies two coordinates, x and y.
*/
struct CoordinateXY
{
	float x, y;
};

/**
Specifies three coordinates, x, y and z.
*/
struct CoordinateXYZ
{
	float x, y, z;
};

/**
Specifies color values (red, green, blue) and their aplha value.
*/
struct ColorRGBA
{
	float r, g, b, a;
};

/**
Toggles between two colors.

@param now The current color value.
@param alt1 Color alternative 1.
@param alt2 Color alternative 2.
@return The opposite color of the currently assigned color.
*/
inline struct ColorRGBA ToggleColors(struct ColorRGBA now, struct ColorRGBA alt1, struct ColorRGBA alt2);

/**
Gets the absolute path of a given filename, located in the same folder as the executable file.
Note: This supports Windows and Linux.

@param relativePath The filename of the file in the current folder.
@return The absolute path to the file.
*/
std::string GetAbsolutePath(std::string relativePath);

#endif