#ifndef EXECPYTHONSCRIPT_HPP
#define EXECPYTHONSCRIPT_HPP
#pragma once

#include "sceneGraph.hpp"

extern bool USE_INPUT_CENTER_OF_SHAPE;

void ReadFile(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY, const char* cmd);
void ReadEasy1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
void ReadEasy2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
void ReadDifficult1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
void ReadDifficult2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
std::string execAndRead(const char* cmd);

#endif