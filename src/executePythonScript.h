#ifndef EXECPYTHONSCRIPT_HPP
#define EXECPYTHONSCRIPT_HPP
#pragma once

#include <string>
#include "sceneGraph.hpp"

void ReadFile(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY, const char* cmd);
void ReadEasy1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
void ReadEasy2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
void ReadDifficult1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
void ReadDifficult2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);
std::string execAndRead(const char* cmd);

#endif