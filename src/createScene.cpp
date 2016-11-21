/**
TDT4195 Visual Computing Fundamentals, Project Fall 2016
createScene.cpp
Purpose: Contains code to add nodes to the Scene Graph tree.

@author Stian Hanssen, Håkon Hukkelås, Magnus Melseth Karlsen
*/

#include "sceneGraph.hpp"
#include "drawBoard.h"

SceneNode* AddHourglass(float z, float squareLenX, float squareLenY, struct ColorRGBA color)
{
	SceneNode* snSquare = createSceneNode();
	snSquare->x = 0.0; snSquare->y = 0.0; snSquare->z = z;
	snSquare->scaleFactor = 1.0;
	snSquare->rotationSpeedRadians = 0.0;
	snSquare->indicesCount = 6;
	snSquare->vertexArrayObjectID = CreateHourglass({ 0.0f, squareLenX }, { 0.0f, squareLenY }, 0.0, -0.1f, color);

	return snSquare;
}

SceneNode* AddSquare(float z, float squareLenX, float squareLenY, struct ColorRGBA color)
{
	SceneNode* snSquare = createSceneNode();
	snSquare->x = 0.0; snSquare->y = 0.0; snSquare->z = z;
	snSquare->scaleFactor = 1.0;
	snSquare->rotationSpeedRadians = 0.0;
	snSquare->indicesCount = 48;
	snSquare->liftSpeed = 5.0f;
	snSquare->animationSpeed = 5.0f;
	snSquare->vertexArrayObjectID = CreateSquare({ 0.0f, squareLenX }, { 0.0f, squareLenY }, 0.0, -0.1f, color);

	return snSquare;
}

SceneNode* AddSquareSkewd(float z, struct CoordinateXY center, float drawLenX, float drawLenY, struct ColorRGBA color)
{
	SceneNode* snSquare = createSceneNode();
	snSquare->x = 0.0; snSquare->y = 0.0; snSquare->z = z;
	snSquare->scaleFactor = 1.0;
	snSquare->rotationSpeedRadians = 0.0;
	snSquare->indicesCount = 48;
	snSquare->liftSpeed = 5.0f;
	snSquare->animationSpeed = 5.0f;
	snSquare->vertexArrayObjectID = CreateSquareSkewd({ center.x - (drawLenX / 2.0f), center.x + (drawLenX / 2.0f) - 1.0f }, { center.y - (drawLenY / 2.0f), center.y + (drawLenY / 2.0f) }, 0.0, -0.1f, color);

	return snSquare;
}

SceneNode* AddTriangle(float z, struct CoordinateXY center, float drawLenX, float drawLenY, struct ColorRGBA color)
{
	SceneNode* snTriangle = createSceneNode();
	snTriangle->x = 0.0; snTriangle->y = 0.0; snTriangle->z = z;
	snTriangle->scaleFactor = 1.0;
	snTriangle->rotationSpeedRadians = 0.0;
	snTriangle->indicesCount = 24;
	snTriangle->liftSpeed = 5.0f;
	snTriangle->animationSpeed = 5.0f;
	snTriangle->vertexArrayObjectID = CreateTriangle({ center.x - (drawLenX / 2.0f), center.x + (drawLenX / 2.0f) }, { center.y - (drawLenY / 2.0f), center.y + (drawLenY / 2.0f) }, 0.0, -0.1f, color);

	return snTriangle;
}

SceneNode* AddPacman(float z, struct CoordinateXY center, float radius, struct ColorRGBA color)
{
	SceneNode* snPacman = createSceneNode();
	snPacman->x = 0.0; snPacman->y = 0.0; snPacman->z = z;
	snPacman->scaleFactor = 1.0;
	snPacman->rotationSpeedRadians = 0.0;
	snPacman->indicesCount = 6 * 4 * 100 * 2;
	snPacman->liftSpeed = 5.0f;
	snPacman->animationSpeed = 5.0f;
	snPacman->vertexArrayObjectID = CreatePacman(center, radius, 0.0, -0.1f, 100, color);

	return snPacman;
}

SceneNode* AddHexagon(float z, struct CoordinateXY center, float radius, struct ColorRGBA color)
{
	SceneNode* snHexagon = createSceneNode();
	snHexagon->x = 0.0; snHexagon->y = 0.0; snHexagon->z = z;
	snHexagon->scaleFactor = 1.0;
	snHexagon->rotationSpeedRadians = 0.0;
	snHexagon->indicesCount = 12 * 3 * 2 + 6 * 3 * 6;
	snHexagon->liftSpeed = 5.0f;
	snHexagon->animationSpeed = 5.0f;
	snHexagon->vertexArrayObjectID = CreateHexagon(center, radius, 0.0, -0.1f, color);
	return snHexagon;
}

SceneNode* AddV(float z, struct CoordinateXY center, float drawLenX, float drawLenY, struct ColorRGBA color)
{
	SceneNode* snV = createSceneNode();
	snV->x = 0.0; snV->y = 0.0; snV->z = z;
	snV->scaleFactor = 1.0;
	snV->rotationSpeedRadians = 0.0;
	snV->indicesCount = 12 * 2 + 6 * 3 * 4;
	snV->liftSpeed = 5.0f;
	snV->animationSpeed = 5.0f;
	snV->vertexArrayObjectID = CreateV({ center.x - (drawLenX / 2.0f), center.x + (drawLenX / 2.0f) }, { center.y - (drawLenY / 2.0f), center.y + (drawLenY / 2.0f) }, 0.0, -0.1f, color);

	return snV;
}

SceneNode* AddStar(float z, struct CoordinateXY center, float radius, struct ColorRGBA color)
{
	SceneNode* snStar = createSceneNode();
	snStar->x = 0.0; snStar->y = 0.0; snStar->z = z;
	snStar->scaleFactor = 1.0;
	snStar->rotationSpeedRadians = 0.0;
	snStar->indicesCount = 6 * 5 + 6 * 3 * 5;
	snStar->liftSpeed = 5.0f;
	snStar->animationSpeed = 5.0f;
	snStar->vertexArrayObjectID = CreateStar(center, radius, 0.0, -0.1f, color);

	return snStar;
}

SceneNode* CreateBoard(struct Range xRange, struct Range yRange, unsigned int squaresX, unsigned int squaresY, float z, struct ColorRGBA color1, struct ColorRGBA color2)
{
	float squareLenX = (xRange.end - xRange.start) / squaresX;
	float squareLenY = (yRange.end - yRange.start) / squaresY;

	SceneNode* snBoard = createSceneNode();
	snBoard->x = 0.0; snBoard->y = 0.0; snBoard->z = z;
	snBoard->scaleFactor = 1.0;
	snBoard->rotationSpeedRadians = 0.0;
	snBoard->rotationDirection = glm::vec3(0.0, 0.0, 1.0);
	snBoard->indicesCount = 0;
	snBoard->vertexArrayObjectID = -1;

	int x = 0;
	int y = 0;
	struct ColorRGBA color = color1;
	for (int i = 0; i < squaresX * squaresY; i++, x++)
	{
		if (x == squaresX)
		{
			y++;
			x = 0;
			if (squaresX % 2 == 0)
				color = ToggleColors(color, color1, color2);
		}

		SceneNode* snSquare = createSceneNode();
		snSquare->vertexArrayObjectID = CreateSquare({ 0, squareLenX }, { 0, squareLenY }, 0, -0.3f, color);
		snSquare->x = xRange.start + x*squareLenX; snSquare->y = yRange.start + y*squareLenY; snSquare->z = 0.0;
		snSquare->scaleFactor = 1.0;
		snSquare->rotationSpeedRadians = 0.0;
		snSquare->indicesCount = 48;

		addChild(snBoard, snSquare);

		color = ToggleColors(color, color1, color2);
	}

	SceneNode* snBottom = createSceneNode();
	snBottom->vertexArrayObjectID = CreateSquare({ xRange.start - 3.0f, xRange.end + 3.0f }, { yRange.start - 3.0f, yRange.end + 3.0f }, 0, -3.0f, { 0.49f, 0.25f, 0.0f, 1.0f });
	snBottom->x = 0.0; snBottom->y = 0.0; snBottom->z = -0.3f;
	snBottom->scaleFactor = 1.0;
	snBottom->rotationSpeedRadians = 0.0;
	snBottom->indicesCount = 48;
	addChild(snBoard, snBottom);

	SceneNode* snBottomLine = createSceneNode();
	snBottomLine->vertexArrayObjectID = CreateSquare({ xRange.start - 1.5f, xRange.end + 1.5f }, { 0.0, 1.0f }, 0, 0.3f, { 0.29f, 0.15f, 0.0f, 1.0f });
	snBottomLine->x = 0.0; snBottomLine->y = yRange.start - 2.0f; snBottomLine->z = -0.299f;
	snBottomLine->scaleFactor = 1.0;
	snBottomLine->rotationSpeedRadians = 0.0;
	snBottomLine->indicesCount = 48;
	addChild(snBoard, snBottomLine);

	SceneNode* snTopLine = createSceneNode();
	snTopLine->vertexArrayObjectID = CreateSquare({ xRange.start - 1.5f, xRange.end + 1.5f }, { 0.0, 1.0f }, 0, 0.3f, { 0.29f, 0.15f, 0.0f, 1.0f });
	snTopLine->x = 0.0; snTopLine->y = yRange.end + 1.0f; snTopLine->z = -0.299f;
	snTopLine->scaleFactor = 1.0;
	snTopLine->rotationSpeedRadians = 0.0;
	snTopLine->indicesCount = 48;
	addChild(snBoard, snTopLine);

	SceneNode* snLeftLine = createSceneNode();
	snLeftLine->vertexArrayObjectID = CreateSquare({ 0.0, 1.0f }, { yRange.start - 2.0f, yRange.end + 2.0f }, 0, 0.3f, { 0.29f, 0.15f, 0.0f, 1.0f });
	snLeftLine->x = xRange.start - 2.0f; snLeftLine->y = 0.0; snLeftLine->z = -0.299f;
	snLeftLine->scaleFactor = 1.0;
	snLeftLine->rotationSpeedRadians = 0.0;
	snLeftLine->indicesCount = 48;
	addChild(snBoard, snLeftLine);

	SceneNode* snRightLine = createSceneNode();
	snRightLine->vertexArrayObjectID = CreateSquare({ 0.0, 1.0f }, { yRange.start - 2.0f, yRange.end + 2.0f }, 0, 0.3f, { 0.29f, 0.15f, 0.0f, 1.0f });
	snRightLine->x = xRange.end + 1.0f; snRightLine->y = 0.0; snRightLine->z = -0.299f;
	snRightLine->scaleFactor = 1.0;
	snRightLine->rotationSpeedRadians = 0.0;
	snRightLine->indicesCount = 48;
	addChild(snBoard, snRightLine);

	return snBoard;
}