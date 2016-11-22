#ifndef EXECPYTHONSCRIPT_HPP
#define EXECPYTHONSCRIPT_HPP
#pragma once

#include "sceneGraph.hpp"

extern bool USE_INPUT_CENTER_OF_SHAPE;

/**
Reads the output of the command, and uses the information to create the board.

@param BoardNode The Scene Graph node which the board should be located within.
@param SquaresX The amount of squares in the x direction which should be drawn in the board.
@param SquaresY The amount of squares in the y direction which should be drawn in the board.
@param cmd The command which should be executed.
*/
void ReadFile(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY, const char* cmd);

/**
Reads and processes the output of the python script when processing the "Easy 1" board.

@param BoardNode The Scene Graph node which the board should be located within.
@param SquaresX The amount of squares in the x direction which should be drawn in the board.
@param SquaresY The amount of squares in the y direction which should be drawn in the board.
*/
void ReadEasy1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);

/**
Reads and processes the output of the python script when processing the "Easy 2" board.

@param BoardNode The Scene Graph node which the board should be located within.
@param SquaresX The amount of squares in the x direction which should be drawn in the board.
@param SquaresY The amount of squares in the y direction which should be drawn in the board.
*/
void ReadEasy2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);

/**
Reads and processes the output of the python script when processing the "Difficult 1" board.

@param BoardNode The Scene Graph node which the board should be located within.
@param SquaresX The amount of squares in the x direction which should be drawn in the board.
@param SquaresY The amount of squares in the y direction which should be drawn in the board.
*/
void ReadDifficult1(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);

/**
Reads and processes the output of the python script when processing the "Difficult 2" board.

@param BoardNode The Scene Graph node which the board should be located within.
@param SquaresX The amount of squares in the x direction which should be drawn in the board.
@param SquaresY The amount of squares in the y direction which should be drawn in the board.
*/
void ReadDifficult2(SceneNode** BoardNode, unsigned int SquaresX, unsigned int SquaresY);

/**
Executes any given command, and returns the output from the command.

@param cmd The command which should be executed.
@return The output from the executed command.
*/
std::string execAndRead(const char* cmd);

#endif