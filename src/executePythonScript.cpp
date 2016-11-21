#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include "executePythonScript.h"
#include "boardHelpers.h"
#include "sceneGraph.hpp"
#include "createScene.h"

struct ColorRGBA color1 = { 1.0, 0.0, 0.0, 1.0 };
struct ColorRGBA color2 = { 0.3f, 0.3f, 0.9f, 1.0 };

unsigned int translateCoordinatesToArrayIndex(struct CoordinateXY coord, struct Range xRange, struct Range yRange, unsigned int squaresX, unsigned int squaresY)
{
	float squareXLen = (xRange.end - xRange.start) / (float)squaresX;
	float squareYLen = (yRange.end - yRange.start) / (float)squaresY;

	unsigned int xPos = coord.x / squareXLen;
	unsigned int yPos = coord.y / squareYLen;

	return (yPos * squaresX) + xPos;
}

struct CoordinateXY translateCoordinatesToCenterOfSquare(struct CoordinateXY coord, struct Range xRange, struct Range yRange, unsigned int squaresX, unsigned int squaresY)
{
	float squareXLen = (xRange.end - xRange.start) / (float)squaresX;
	float squareYLen = (yRange.end - yRange.start) / (float)squaresY;

	unsigned int xPos = coord.x / squareXLen;
	unsigned int yPos = coord.y / squareYLen;

	return{ (float)xPos, (float)yPos };
}

std::vector<std::string> split(const std::string &s, char splitchr)
{
	std::vector<std::string> returnVec;
	std::stringstream strm(s);
	std::string itm;
	while (std::getline(strm, itm, splitchr))
	{
		returnVec.push_back(itm);
	}

	return returnVec;
}

void getContent(const std::string &s, unsigned int* x, unsigned int* y, std::string* info)
{
	std::vector<std::string> split1 = split(s, ')');
	std::string part1 = split1[0];
	std::string part2 = split1[1];

#ifdef _WIN32
	size_t endpos = part2.find_last_not_of("\r\n");
#else
	size_t endpos = part2.find_last_not_of("\n");
#endif

	*info = part2.substr(1, endpos);

	std::vector<std::string> splitCoord = split(part1, ',');
	std::string xsplit = splitCoord[0];
	std::string ysplit = splitCoord[1];

	*x = std::stoi(xsplit.substr(1, xsplit.length() - 1));
	*y = std::stoi(ysplit.substr(0, ysplit.length()));
}


void drawInstruction(SceneNode** BoardNode, std::string type, unsigned int x, unsigned int y, struct Range xRange, struct Range yRange, unsigned int squaresX, unsigned int squaresY, float squareLenX, float squareLenY)
{
	unsigned int index = translateCoordinatesToArrayIndex({ (float)x, (float)y }, xRange, yRange, squaresX, squaresY);

	struct CoordinateXY centerOfShape = { squareLenX / 2.0f, squareLenY / 2.0f };
	//struct CoordinateXY centerOfShape = translateCoordinatesToCenterOfSquare({ (float)x, (float)y }, xRange, yRange, squaresX, squaresY);
	//float lenToClosestEdgeX = min(centerOfShape.x, squareLenX - centerOfShape.x);

	SceneNode* snShape;

	if (type == "star")
		snShape = AddStar(0.1f, centerOfShape, squareLenX / 2.0f, { 0.4f, 0.4f, 1.0, 1.0f });
	else if (type == "square")
		snShape = AddSquareSkewd(0.1f, squareLenX, squareLenY, { 0.3f, 1.0, 0.3f, 1.0f });
	else if (type == "hexagon1")
		snShape = AddHexagon(0.1f, centerOfShape, squareLenX / 2.0f, { 0.0, 0.0, 0.0, 1.0f });
	else if (type == "hexagon2")
		snShape = AddHexagon(0.1f, centerOfShape, squareLenX / 2.0f, { 1.0, 1.0, 1.0, 1.0f });
	else if (type == "pacman")
		snShape = AddPacman(0.1f, centerOfShape, squareLenX / 2.0f, { 1.0, 0.4f, 0.4f, 1.0f });
	else if (type == "triangle")
		snShape = AddTriangle(0.1f, squareLenX, squareLenY, { 1.0, 0.0, 1.0, 1.0f });
	else if (type == "v")
		snShape = AddV(0.1f, squareLenX, squareLenY, { 0.0, 1.0, 1.0, 1.0f });


	addChild((*BoardNode)->children[index], snShape);
}

void ReadFile(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY, const char* cmd)
{
	printf("\n\nProcessing, please wait...\n");

	struct Range origxRange, origyRange;

	std::string output = execAndRead(cmd);

	std::istringstream strm(output);

	std::string initial;
	std::getline(strm, initial);
	std::string initInfo;
	unsigned int initx, inity;
	getContent(initial, &initx, &inity, &initInfo);
	std::cout << initx << " " << inity << " " << initInfo << std::endl;

	origxRange = { 0.0, (float)initx };
	origyRange = { 0.0, (float)inity };

	struct ColorRGBA firstColor = (initInfo == "red") ? color1 : color2;
	struct ColorRGBA secondColor = (initInfo == "red") ? color2 : color1;

	if (SquaresY % 2 == 0)
	{
		firstColor = ToggleColors(firstColor, color1, color2);
		secondColor = ToggleColors(secondColor, color1, color2);
	}

	*BoardNode = CreateBoard({ -16.0f, 16.0f }, { -10.0f, 10.0f }, SquaresX, SquaresY, -15.0f, firstColor, secondColor);
	float squareLenX = 4;
	float squareLenY = 4;

	std::string line;
	std::string lineInfo;
	unsigned int linex, liney;
	while (std::getline(strm, line))
	{
		getContent(line, &linex, &liney, &lineInfo);
		std::cout << linex << " " << liney << " " << lineInfo << std::endl;
		drawInstruction(BoardNode, lineInfo, linex, liney, origxRange, origyRange, SquaresX, SquaresY, squareLenX, squareLenY);
	}
}

void ReadEasy1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY)
{
	ReadFile(BoardNode, SquaresX, SquaresY, "python C:\\Users\\mmkar\\Documents\\visdat_prosjekt\\gloom\\build\\gloom\\Debug\\area_segmentation.py e1");
}

void ReadEasy2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY)
{
	ReadFile(BoardNode, SquaresX, SquaresY, "python C:\\Users\\mmkar\\Documents\\visdat_prosjekt\\gloom\\build\\gloom\\Debug\\area_segmentation.py e2");
}

void ReadDifficult1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY)
{
	ReadFile(BoardNode, SquaresX, SquaresY, "python C:\\Users\\mmkar\\Documents\\visdat_prosjekt\\gloom\\build\\gloom\\Debug\\area_segmentation.py d1");
}

void ReadDifficult2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY)
{
	ReadFile(BoardNode, SquaresX, SquaresY, "python C:\\Users\\mmkar\\Documents\\visdat_prosjekt\\gloom\\build\\gloom\\Debug\\area_segmentation.py d2");
}

#ifdef _WIN32

std::string execAndRead(const char* cmd)
{
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}
	return result;
}

#else

std::string execAndRead(const char* cmd)
{
	char buffer[128];
	std::string result = "";
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
	if (!pipe) throw std::runtime_error("popen() failed!");
	while (!feof(pipe.get())) {
		if (fgets(buffer, 128, pipe.get()) != NULL)
			result += buffer;
	}
	return result;
}

#endif

