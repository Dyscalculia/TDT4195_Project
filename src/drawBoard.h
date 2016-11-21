#ifndef DRAWBOARD_HPP
#define DRAWBOARD_HPP
#pragma once

#include "boardHelpers.h"

unsigned int CreateHourglass(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreateSquare(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreateSquareSkewd(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreateTriangle(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreatePacman(struct CoordinateXY center, float radius, float z, float height, unsigned int trianglesAmount, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreateHexagon(struct CoordinateXY center, float radius, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreateV(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
unsigned int CreateStar(struct CoordinateXY center, float radius, float z, float height, struct ColorRGBA color, unsigned int vaoid = 0);
void ExtrudedTriangle(float* vertices, unsigned int* indices, float* colors, unsigned int* indicesWritePosPtr, unsigned int* nextDrawNumberPtr, unsigned int* colorWritePosPtr, float zDifference);
inline void UpdateVertexAndColorBuffer(unsigned int l, struct CoordinateXYZ xyz, struct ColorRGBA color, float* vertices, float* colors);
unsigned int CreateVAOWithTriangles(float* vertexCoordinates, float* vertexRGBA, unsigned int* indices, unsigned int vertexCount, unsigned int colorCount, unsigned int indicesCount, unsigned int vaoid = 0);

#endif