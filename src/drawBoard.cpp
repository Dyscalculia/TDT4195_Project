// To allow the use of the M_PI value.
#define _USE_MATH_DEFINES

#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <math.h>
#include "drawBoard.h"
#include "boardHelpers.h"
#include "sceneGraph.hpp"

unsigned int CreateHourglass(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 9 * 2;
	unsigned int colorCount = 12 * 2;
	unsigned int indicesCount = 3 * 2;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0;

	// Triangle 1
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { (xRange.start + xRange.end) / 2.0f, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;

	// Triangle 2
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { (xRange.start + xRange.end) / 2.0f, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos] = nextDrawNumber;

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreateSquare(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 18 * 2;
	unsigned int colorCount = 24 * 2;
	unsigned int indicesCount = 6 * 4 * 2;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	// Triangle 1
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	// Triangle 2
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreateSquareSkewd(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 18 * 2;
	unsigned int colorCount = 24 * 2;
	unsigned int indicesCount = 6 * 4 * 2;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	// Triangle 1
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start + 1.0f, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	// Triangle 2
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start + 1.0f, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end + 1.0f, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreateTriangle(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 9 * 2;
	unsigned int colorCount = 12 * 2;
	unsigned int indicesCount = 3 * 4 * 2;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	// Triangle
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { (xRange.end + xRange.start) / 2.0f, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreatePacman(struct CoordinateXY center, float radius, float z, float height, unsigned int trianglesAmount, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 10 * trianglesAmount * 2;
	unsigned int colorCount = 13 * trianglesAmount * 2;
	unsigned int indicesCount = 6 * 4 * trianglesAmount * 2;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	float iIncrease = 360.0f / static_cast<float>(trianglesAmount);

	for (float i = 0.0f, x = 0.0f, y = 0.0f; i < 359; i += iIncrease)
	{
		if (i > 180 && i < 270)
			continue;

		UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
		indices[indicesWritePos++] = nextDrawNumber++;

		x = center.x + radius * cos(toRadians(i));
		y = center.y + radius * sin(toRadians(i));

		UpdateVertexAndColorBuffer(nextDrawNumber, { x, y, z }, color, vertices, colors);
		indices[indicesWritePos++] = nextDrawNumber++;

		x = center.x + radius * cos(toRadians(i + iIncrease));
		y = center.y + radius * sin(toRadians(i + iIncrease));

		UpdateVertexAndColorBuffer(nextDrawNumber, { x, y, z }, color, vertices, colors);
		indices[indicesWritePos++] = nextDrawNumber++;

		colorWritePos += 12;
		ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);
	}

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreateHexagon(struct CoordinateXY center, float radius, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 6 * 9 * 2;
	unsigned int colorCount = 6 * 12 * 2;
	unsigned int indicesCount = 12 * 3 * 2 + 6 * 3 * 6;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius / 2.0f, center.y - radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius / 2.0f, center.y - radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius / 2.0f, center.y + radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius / 2.0f, center.y + radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius / 2.0f, center.y - radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius / 2.0f, center.y + radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius / 2.0f, center.y - radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius / 2.0f, center.y + radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius, center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreateV(struct Range xRange, struct Range yRange, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	struct CoordinateXY center = { (xRange.start + xRange.end) / 2, (yRange.start + yRange.end) / 2 };

	unsigned int vertexCount = 36 * 2;
	unsigned int colorCount = 48 * 2;
	unsigned int indicesCount = 12 * 2 + 6 * 3 * 4;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	// Triangle 1
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start + 0.7f, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	// Triangle 2
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.start + 0.7f, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, yRange.end - 1.4f, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	// Triangle 3
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end - 0.7f, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	// Triangle 4
	UpdateVertexAndColorBuffer(nextDrawNumber, { xRange.end - 0.7f, yRange.start, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, yRange.end, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, yRange.end - 1.4f, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

unsigned int CreateStar(struct CoordinateXY center, float radius, float z, float height, struct ColorRGBA color, unsigned int vaoid)
{
	unsigned int vertexCount = 9 * 5 * 2;
	unsigned int colorCount = 12 * 5 * 2;
	unsigned int indicesCount = 6 * 5 + 6 * 3 * 5;

	// Allocating buffers
	float* vertices = new float[vertexCount];
	unsigned int* indices = new unsigned int[indicesCount];
	float* colors = new float[colorCount];

	unsigned int indicesWritePos = 0, nextDrawNumber = 0, colorWritePos = 0;

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y + radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - (radius * 0.5f), center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + (radius * 0.5f), center.y, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - radius, center.y + (radius * 0.2f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y - (radius * 0.6f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y + (radius * 0.4f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + radius, center.y + (radius * 0.2f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y + (radius * 0.4f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y - (radius * 0.6f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - (radius * 0.7f), center.y - radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y - (radius * 0.6f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x - (radius * 0.4f), center.y + (radius * 0.1f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + (radius * 0.7f), center.y - radius, z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x + (radius * 0.4f), center.y + (radius * 0.1f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	UpdateVertexAndColorBuffer(nextDrawNumber, { center.x, center.y - (radius * 0.6f), z }, color, vertices, colors);
	indices[indicesWritePos++] = nextDrawNumber++;
	colorWritePos += 12;
	ExtrudedTriangle(vertices, indices, colors, &indicesWritePos, &nextDrawNumber, &colorWritePos, height);

	unsigned int vao_id = CreateVAOWithTriangles(vertices, colors, indices, vertexCount, colorCount, indicesCount, vaoid);

	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao_id;
}

void ExtrudedTriangle(float* vertices, unsigned int* indices, float* colors, unsigned int* indicesWritePosPtr, unsigned int* nextDrawNumberPtr, unsigned int* colorWritePosPtr, float zDifference)
{
	unsigned int currentIndicesStart = *nextDrawNumberPtr;
	unsigned int currentVertexCount = currentIndicesStart * 3;
	unsigned int indicesWritePos = *indicesWritePosPtr;
	unsigned int currentColorCount = *colorWritePosPtr;

	for (int i = 0; i < 9; i += 3)
	{
		vertices[currentVertexCount + i + 0] = vertices[currentVertexCount - (9 - i - 0)];
		vertices[currentVertexCount + i + 1] = vertices[currentVertexCount - (9 - i - 1)];
		vertices[currentVertexCount + i + 2] = vertices[currentVertexCount - (9 - i - 2)] + zDifference;
	}

	for (int i = 0; i < 12; i += 4)
	{
		colors[currentColorCount + i + 0] = colors[currentColorCount - (12 - i - 0)];
		colors[currentColorCount + i + 1] = colors[currentColorCount - (12 - i - 1)];
		colors[currentColorCount + i + 2] = colors[currentColorCount - (12 - i - 2)];
		colors[currentColorCount + i + 3] = colors[currentColorCount - (12 - i - 3)];
	}

	// Bottom
	indices[indicesWritePos++] = currentIndicesStart + 0;
	indices[indicesWritePos++] = currentIndicesStart + 2;
	indices[indicesWritePos++] = currentIndicesStart + 1;

	// Side 1
	indices[indicesWritePos++] = currentIndicesStart - 3;
	indices[indicesWritePos++] = currentIndicesStart + 0;
	indices[indicesWritePos++] = currentIndicesStart + 1;

	indices[indicesWritePos++] = currentIndicesStart - 2;
	indices[indicesWritePos++] = currentIndicesStart - 3;
	indices[indicesWritePos++] = currentIndicesStart + 1;

	// Side 2
	indices[indicesWritePos++] = currentIndicesStart - 3;
	indices[indicesWritePos++] = currentIndicesStart + 2;
	indices[indicesWritePos++] = currentIndicesStart + 0;

	indices[indicesWritePos++] = currentIndicesStart - 3;
	indices[indicesWritePos++] = currentIndicesStart - 1;
	indices[indicesWritePos++] = currentIndicesStart + 2;

	// Side 3
	indices[indicesWritePos++] = currentIndicesStart + 2;
	indices[indicesWritePos++] = currentIndicesStart - 1;
	indices[indicesWritePos++] = currentIndicesStart - 2;

	indices[indicesWritePos++] = currentIndicesStart - 2;
	indices[indicesWritePos++] = currentIndicesStart + 1;
	indices[indicesWritePos++] = currentIndicesStart + 2;

	*nextDrawNumberPtr += 3;
	*indicesWritePosPtr = indicesWritePos;
	*colorWritePosPtr += 12;
}

inline void UpdateVertexAndColorBuffer(unsigned int l, struct CoordinateXYZ xyz, struct ColorRGBA color, float* vertices, float* colors)
{
	vertices[3 * l + 0] = xyz.x;
	vertices[3 * l + 1] = xyz.y;
	vertices[3 * l + 2] = xyz.z;
	colors[4 * l + 0] = color.r;
	colors[4 * l + 1] = color.g;
	colors[4 * l + 2] = color.b;
	colors[4 * l + 3] = color.a;
}

unsigned int CreateVAOWithTriangles(float* vertexCoordinates, float* vertexRGBA, unsigned int* indices, unsigned int vertexCount, unsigned int colorCount, unsigned int indicesCount, unsigned int vaoid)
{
	// VAO
	glGenVertexArrays(1, &vaoid); // Create new VAO by asking driver to create buffer for us
	glBindVertexArray(vaoid); // Bind the VAO

	// Create Vertex VBO
	unsigned int vboVertexid = 0;
	glGenBuffers(1, &vboVertexid); // Create new VBO by asking driver to create buffer for us
	glBindBuffer(GL_ARRAY_BUFFER, vboVertexid); // Bind the VBO, telling the driver it's a VBO
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertexCoordinates, GL_STATIC_DRAW); // Transfer data to the GPU
	unsigned int vertexAttribID1 = 0;
	glVertexAttribPointer(vertexAttribID1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Sets the format of the buffer. 3 = x,y,z
	glEnableVertexAttribArray(vertexAttribID1); // Enable VBO to serve as input to the rendering pipeline

	// Create Color VBO
	unsigned int vboColorid = 0;
	glGenBuffers(1, &vboColorid); // Create new VBO by asking driver to create buffer for us
	glBindBuffer(GL_ARRAY_BUFFER, vboColorid); // Bind the VBO, telling the driver it's a VBO
	glBufferData(GL_ARRAY_BUFFER, colorCount * sizeof(float), vertexRGBA, GL_STATIC_DRAW); // Transfer data to the GPU
	unsigned int colorAttribID1 = 1;
	glVertexAttribPointer(colorAttribID1, 4, GL_FLOAT, GL_FALSE, 0, 0); // Sets the format of the buffer. 4 = rgba
	glEnableVertexAttribArray(colorAttribID1); // Enable VBO to serve as input to the rendering pipeline

	// Index buffer:
	unsigned int ibid = 0; // index buffer id
	glGenBuffers(1, &ibid); // Generate another buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibid); // Bind the index buffer, telling the driver it's an index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW); // Transfer data to the GPU

	return vaoid;
}