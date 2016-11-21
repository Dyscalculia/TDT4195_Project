#ifndef BOARDHELPER_HPP
#define BOARDHELPER_HPP
#pragma once

enum MoveDirection { Up, Down, Left, Right };
enum MoveResult { OutsideBoard, Uninitialized, AlreadyOccupied, AlreadyMoving, Moved };

struct Range
{
	float start, end;
};

struct CoordinateXY
{
	float x, y;
};

struct CoordinateXYZ
{
	float x, y, z;
};

struct ColorRGBA
{
	float r, g, b, a;
};

inline struct ColorRGBA ToggleColors(struct ColorRGBA now, struct ColorRGBA alt1, struct ColorRGBA alt2)
{
	return (now.r == alt1.r && now.g == alt1.g && now.b == alt1.b && now.a == alt1.a) ? alt2 : alt1;
}

#endif