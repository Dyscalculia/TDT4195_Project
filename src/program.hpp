#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#pragma once

// System headers
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include "sceneGraph.hpp"
#include "boardHelpers.h"

// Main OpenGL program
void runProgram(GLFWwindow* window);

// GLFW callback mechanisms
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

/**
Creates an animation where the camera comes flying towards the board. Run once every frame to make it possible for the Fly-in animation to work.

@param timeDeltaSeconds The time in seconds since the last frame.
*/
void FlyIn(float timeDeltaSeconds);

/**
Slightly shakes the board to show that an action could not be done. Run once every frame to make it possible for the shake animation to work.

@param timeDeltaSeconds The time in seconds since the last frame.
*/
void ShakeBoard(float timeDeltaSeconds);

/**
Based on the current position of the selected shape, and the desired direction of movement, the next index in the array containing the board squares.

@param direction The desired direction of movement.
@return The index representing the square which needs to be the new parent.
*/
int Next2DMatrixIndex(MoveDirection direction);

/**
Selects the next shape/piece that can be selected and moved around on the board.
*/
void SelectNextFigure();

/**
Tries to move the selected shape/piece to the desired new index.

@param newIndex The new index, where the selected shape should be moved.
@return The result of the operation, telling whether or not the operation was successful.
*/
MoveResult MoveFigure(int newIndex);

/**
Tries to move the selected shape/piece in the desired direction. Will shake the board if the move is impossible.

@param direction The desired direction of movement.
*/
void TryToMove(MoveDirection direction);

/**
Renders the Scene Graph tree to the screen. Run once every frame to make it possible to see the objects.

@param rootNode The root node of the Scene Graph tree.
@param parentMatrix The transformation matrix of the node above in the scene graph tree.
*/
void RenderBoard(SceneNode* rootNode, glm::mat4x4 parentMatrix);

/**
Updates properties of a Scene Graph tree using recursion. Run once every frame to make it possible for the animations to work.

@param rootNode The root node of the Scene Graph tree.
@param timeDeltaSeconds The time in seconds since the last frame.
*/
void UpdateBoard(SceneNode* rootNode, float timeDeltaSeconds);

// Checks for whether an OpenGL error occurred. If one did,
// it prints out the error type and ID
inline void printGLError() {
	int errorID = glGetError();

	if (errorID != GL_NO_ERROR) {
		std::string errorString;

		switch (errorID) {
		case GL_INVALID_ENUM:
			errorString = "GL_INVALID_ENUM";
			break;
		case GL_INVALID_OPERATION:
			errorString = "GL_INVALID_OPERATION";
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			errorString = "GL_OUT_OF_MEMORY";
			break;
		case GL_STACK_UNDERFLOW:
			errorString = "GL_STACK_UNDERFLOW";
			break;
		case GL_STACK_OVERFLOW:
			errorString = "GL_STACK_OVERFLOW";
			break;
		default:
			errorString = "[Unknown error ID]";
			break;
		}

		fprintf(stderr, "An OpenGL error occurred (%i): %s.\n",
			errorID, errorString.c_str());
	}
}

#endif