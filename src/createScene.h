#ifndef CREATESCENE_HPP
#define CREATESCENE_HPP
#pragma once

#include "sceneGraph.hpp"

SceneNode* AddHourglass(float z, float squareLenX, float squareLenY, struct ColorRGBA color);
SceneNode* AddHexagon(float z, struct CoordinateXY center, float radius, struct ColorRGBA color);
SceneNode* AddPacman(float z, struct CoordinateXY center, float radius, struct ColorRGBA color);
SceneNode* AddTriangle(float z, float squareLenX, float squareLenY, struct ColorRGBA color);
SceneNode* AddSquare(float z, float squareLenX, float squareLenY, struct ColorRGBA color);
SceneNode* AddSquareSkewd(float z, float squareLenX, float squareLenY, struct ColorRGBA color);
SceneNode* AddV(float z, float squareLenX, float squareLenY, struct ColorRGBA color);
SceneNode* AddStar(float z, struct CoordinateXY center, float radius, struct ColorRGBA color);
SceneNode* CreateBoard(struct Range xRange, struct Range yRange, unsigned int squaresX, unsigned int squaresY, float z, struct ColorRGBA color1, struct ColorRGBA color2);

#endif