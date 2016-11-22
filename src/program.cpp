/**
TDT4195 Visual Computing Fundamentals, Project Fall 2016
program.cpp
Purpose: Contains the rendering loop, and code to move and animate different parts of the board.

@author Stian Hanssen, Håkon Hukkelås, Magnus Melseth Karlsen
*/

// Local headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include "boardHelpers.h"
#include "executePythonScript.h"
#include "glm/ext.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include "program.hpp"
#include "sceneGraph.hpp"

#pragma region Global Variables

// The shaders, initialized later on
Gloom::Shader* shader;

// Used for camera
glm::vec3 offset(0.0, 0.0, 0.0);
glm::vec3 scalefactor(1.0, 1.0, 1.0);
float rotateVertical = 0;
float rotateHorizontal = 0;

// For moving shapes around
int SelectedNodeGraphIndex = -1;
SceneNode* SelectedNode = nullptr;

// The board, containing all children
SceneNode* BoardNode = nullptr;

// The amount of squares in the X and Y direction
unsigned int SquaresX;
unsigned int SquaresY;

// Used for the fly-in effect
float startHorRotation = -0.3;
float endHorRotation = -0.5;
float rotationSpeed = 1.0f;
glm::vec3 startOffset(0.0, 100.0, 0.0);
glm::vec3 endOffset(0.0, 12.0, 0.0);
float offsetSpeed = 1.0f;
bool flyInEnabled = false;

// Used for the shake on error effect
bool shakeBoardEnabled = false;
float shakeLeft = 1.0f;
float shakeRight = 1.0f;
float shakeSpeed = 20.0f;
bool shakingLeft = true;
bool shakingRight = false;

#pragma endregion Global Variables

void runProgram(GLFWwindow* window)
{
	std::cout << "Remember to add all the python files to the running directory!" << std::endl;
	std::cout << "Remember to add all the shader files to the running directory!" << std::endl << std::endl;

	std::cout << "Using center of shape given by python script: " << ((USE_INPUT_CENTER_OF_SHAPE) ? "True" : "False") << ". Change this by pressing \"k\"." << std::endl << std::endl;
	std::cout << "Change the camera by pressing:" << std::endl;
	std::cout << "\t[1]: Birdseye view" << std::endl;
	std::cout << "\t[2]: Angled view" << std::endl;
	std::cout << "\t[3]: Angled view 2 with rotation" << std::endl;
	std::cout << "\t[4]: Angled view 3" << std::endl;
	std::cout << "Load the different boards by pressing:" << std::endl;
	std::cout << "\t[6]: Test board" << std::endl;
	std::cout << "\t[7]: Easy 1" << std::endl;
	std::cout << "\t[8]: Easy 2" << std::endl;
	std::cout << "\t[9]: Difficult 1" << std::endl;
	std::cout << "\t[0]: Difficult 2" << std::endl;
	std::cout << "You can move shapes around by pressing:" << std::endl;
	std::cout << "\t[n]: Select next shape" << std::endl;
	std::cout << "\t[Arrows]: Move shape around" << std::endl;

	// The amount of squares to draw in the board
	SquaresX = 8;
	SquaresY = 5;

	// Set GLFW callback mechanism(s)
	glfwSetKeyCallback(window, keyboardCallback);

	// Enable depth (Z) buffer (accept "closest" fragment)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Configure miscellaneous OpenGL settings
	glEnable(GL_CULL_FACE);

	// Set default color after clearing the color buffer
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

	// Set up your scene here (create Vertex Array Objects, etc.)
	shader = new Gloom::Shader();
	// Load shader files

	shader->makeBasicShader(GetAbsolutePath("simple.vert"), GetAbsolutePath("simple.frag"));

	glm::vec3 xaxis(1.0, 0.0, 0.0);
	glm::vec3 yaxis(0.0, 1.0, 0.0);

	printGLError();

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw your scene here
		float timeDelta = getTimeDeltaSeconds();
		if (BoardNode != nullptr)
		{
			FlyIn(timeDelta);
			ShakeBoard(timeDelta);
			UpdateBoard(BoardNode, timeDelta);

			glm::mat4 identity;
			glm::mat4 rotate = glm::rotate(identity, rotateVertical, yaxis);
			rotate = glm::rotate(rotate, rotateHorizontal, xaxis);
			glm::mat4x4 scale = glm::scale(rotate, scalefactor);
			glm::mat4x4 translate = glm::translate(scale, offset);
			glm::mat4x4 projection = glm::perspective(glm::radians(90.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 1.0f, 100.0f) * translate;

			shader->activate(); // Activate shader program
			RenderBoard(BoardNode, projection);
			shader->deactivate(); // Deactivate shader program
			printGLError();
		}

		// Handle other events
		glfwPollEvents();

		// Flip buffers
		glfwSwapBuffers(window);
	}
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
	{
		return;
	}

	// Use escape key for terminating the GLFW window
	if (key == GLFW_KEY_ESCAPE)
	{
		shader->destroy();
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_W)
	{
		// Forward
		offset.z += 0.5;
	}
	else if (key == GLFW_KEY_A)
	{
		// left
		offset.x -= 0.2;
	}
	else if (key == GLFW_KEY_S)
	{
		// backward
		offset.z -= 0.5;
	}
	else if (key == GLFW_KEY_D)
	{
		// right
		offset.x += 0.2;
	}
	else if (key == GLFW_KEY_LEFT_SHIFT)
	{
		// Up
		offset.y += 0.2;
	}
	else if (key == GLFW_KEY_LEFT_CONTROL)
	{
		// Down
		offset.y -= 0.2;
	}
	else if (key == GLFW_KEY_Q)
	{
		// Rotate vertically
		rotateVertical -= 0.2;
	}
	else if (key == GLFW_KEY_E)
	{
		// Rotate vertically
		rotateVertical += 0.2;
	}
	else if (key == GLFW_KEY_LEFT_ALT)
	{
		// Rotate horizontally
		rotateHorizontal += 0.2;
	}
	else if (key == GLFW_KEY_X)
	{
		// Rotate horizontally
		rotateHorizontal -= 0.2;
	}
	else if (key == GLFW_KEY_1)
	{
		// Set camera state 1
		offset = glm::vec3(0.0, 0.0, -8.0);
		rotateHorizontal = 0;
		rotateVertical = 0;
		scalefactor = glm::vec3(1.0, 1.0, 1.0);

		BoardNode->rotationSpeedRadians = 0.0f;
	}
	else if (key == GLFW_KEY_2)
	{
		// Set camera state 2
		offset = glm::vec3(0.0, 16.0, 0.0);
		rotateHorizontal = -1.0;
		rotateVertical = 0;
		scalefactor = glm::vec3(1.0, 1.0, 1.0);

		BoardNode->rotationSpeedRadians = 0.0f;
	}
	else if (key == GLFW_KEY_3)
	{
		// Set camera state 3
		offset = glm::vec3(0.0, 16.0, 0.0);
		rotateHorizontal = -0.6;
		rotateVertical = 0;
		scalefactor = glm::vec3(1.0, 1.0, 1.0);

		BoardNode->rotationSpeedRadians = 0.1f;
	}
	else if (key == GLFW_KEY_4)
	{
		// Set camera state 4
		offset = glm::vec3(0.0, 16.0, 0.0);
		rotateHorizontal = -toRadians(30.0f);
		rotateVertical = 0;
		scalefactor = glm::vec3(1.0, 1.0, 1.0);

		BoardNode->rotationSpeedRadians = 0.0f;
	}
	else if (key == GLFW_KEY_N)
	{
		// Select piece
		SelectNextFigure();
	}
	else if (key == GLFW_KEY_UP)
	{
		// Move piece up
		TryToMove(Up);
	}
	else if (key == GLFW_KEY_DOWN)
	{
		// Move piece down
		TryToMove(Down);
	}
	else if (key == GLFW_KEY_LEFT)
	{
		// Move piece left
		TryToMove(Left);
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		// Move piece right
		TryToMove(Right);
	}
	else if (key == GLFW_KEY_6)
	{
		// Load test board
		BoardNode = nullptr;
		SelectedNodeGraphIndex = -1;
		SelectedNode = nullptr;
		ReadTestFile(&BoardNode, SquaresX, SquaresY);
		getTimeDeltaSeconds(); // reset counter
		offset = startOffset;
		rotateHorizontal = startHorRotation;
		flyInEnabled = true;
	}
	else if (key == GLFW_KEY_7)
	{
		// Load easy board 1
		BoardNode = nullptr;
		SelectedNodeGraphIndex = -1;
		SelectedNode = nullptr;
		ReadEasy1(&BoardNode, SquaresX, SquaresY);
		getTimeDeltaSeconds(); // reset counter
		offset = startOffset;
		rotateHorizontal = startHorRotation;
		flyInEnabled = true;
	}
	else if (key == GLFW_KEY_8)
	{
		// Load easy board 2
		BoardNode = nullptr;
		SelectedNodeGraphIndex = -1;
		SelectedNode = nullptr;
		ReadEasy2(&BoardNode, SquaresX, SquaresY);
		getTimeDeltaSeconds(); // reset counter
		offset = startOffset;
		rotateHorizontal = startHorRotation;
		flyInEnabled = true;
	}
	else if (key == GLFW_KEY_9)
	{
		// Load difficult board 1
		BoardNode = nullptr;
		SelectedNodeGraphIndex = -1;
		SelectedNode = nullptr;
		ReadDifficult1(&BoardNode, SquaresX, SquaresY);
		getTimeDeltaSeconds(); // reset counter
		offset = startOffset;
		rotateHorizontal = startHorRotation;
		flyInEnabled = true;
	}
	else if (key == GLFW_KEY_0)
	{
		// Load difficult board 2
		BoardNode = nullptr;
		SelectedNodeGraphIndex = -1;
		SelectedNode = nullptr;
		ReadDifficult2(&BoardNode, SquaresX, SquaresY);
		getTimeDeltaSeconds(); // reset counter
		offset = startOffset;
		rotateHorizontal = startHorRotation;
		flyInEnabled = true;
	}
	else if (key == GLFW_KEY_K)
	{
		// Toggle using input center of shapes
		USE_INPUT_CENTER_OF_SHAPE = !USE_INPUT_CENTER_OF_SHAPE;
		std::cout << "Toggeling. Using center of shape reported by python script (new value): " << ((USE_INPUT_CENTER_OF_SHAPE) ? "True" : "False") << ". Reload the board to see the change in action." << std::endl;
	}
}

void FlyIn(float timeDeltaSeconds)
{
	if (!flyInEnabled)
		return;

	if (offset.y > endOffset.y)
		offset.y += (endOffset.y - startOffset.y) *  offsetSpeed * timeDeltaSeconds;
	else
	{
		offset.y = endOffset.y;

		if (rotateHorizontal > endHorRotation)
			rotateHorizontal += (endHorRotation - startHorRotation) * rotationSpeed * timeDeltaSeconds;
		else
		{
			rotateHorizontal = endHorRotation;
			flyInEnabled = false;
		}
	}
}

void ShakeBoard(float timeDeltaSeconds)
{
	if (!shakeBoardEnabled)
		return;

	if (shakingLeft)
	{
		if (BoardNode->x < shakeLeft)
			BoardNode->x += shakeSpeed * timeDeltaSeconds;
		else
		{
			BoardNode->x = shakeLeft;
			shakingLeft = false;
			shakingRight = true;
		}
	}
	else if (shakingRight)
	{
		if (BoardNode->x > shakeRight)
			BoardNode->x -= shakeSpeed * timeDeltaSeconds;
		else
		{
			BoardNode->x = shakeRight;
			shakingRight = false;
		}
	}
	else
	{
		if (BoardNode->x < 0.0f)
			BoardNode->x += shakeSpeed * timeDeltaSeconds;
		else
		{
			BoardNode->x = 0.0;
			shakeBoardEnabled = false;
			shakingLeft = true;
		}
	}
}

int Next2DMatrixIndex(MoveDirection direction)
{
	if (SelectedNodeGraphIndex < 0)
		return -1;

	if (direction == Left)
		return (SelectedNodeGraphIndex % SquaresX == 0) ? -1 : SelectedNodeGraphIndex - 1;
	else if (direction == Right)
		return ((SelectedNodeGraphIndex + 1) % SquaresX == 0) ? -1 : SelectedNodeGraphIndex + 1;
	else if (direction == Down)
		return (static_cast<int>(SelectedNodeGraphIndex - SquaresX) < 0) ? -1 : SelectedNodeGraphIndex - SquaresX;
	else if (direction == Up)
		return (SelectedNodeGraphIndex + SquaresX >= SquaresX * SquaresY) ? -1 : SelectedNodeGraphIndex + SquaresX;
	else
		return -1;
}

void SelectNextFigure()
{
	if (SelectedNode != nullptr)
	{
		SelectedNode->lift = false;
	}

	bool foundPrevious = SelectedNode == nullptr;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < BoardNode->children.size(); i++)
		{
			if ((BoardNode->children[i]->children.size()) > 0)
			{
				if (!foundPrevious)
				{
					if (BoardNode->children[i]->children[0] == SelectedNode)
						foundPrevious = true;
					continue;
				}

				SelectedNodeGraphIndex = i;
				SelectedNode = BoardNode->children[i]->children[0];
				SelectedNode->lift = true;
				return;
			}
		}
	}
}

MoveResult MoveFigure(int newIndex)
{
	if (newIndex < 0)
		return OutsideBoard;

	if (SelectedNodeGraphIndex < 0)
		return Uninitialized;

	if (BoardNode->children[newIndex]->children.size() > 0)
		return AlreadyOccupied;

	if (SelectedNode->animateToPoint)
		return AlreadyMoving;

	SelectedNode->animateToX = SelectedNode->x;
	SelectedNode->animateToY = SelectedNode->y;
	SelectedNode->animateToZ = SelectedNode->z;
	SelectedNode->x += BoardNode->children[SelectedNodeGraphIndex]->x - BoardNode->children[newIndex]->x;
	SelectedNode->y += BoardNode->children[SelectedNodeGraphIndex]->y - BoardNode->children[newIndex]->y;
	SelectedNode->z += BoardNode->children[SelectedNodeGraphIndex]->z - BoardNode->children[newIndex]->z;
	SelectedNode->animateFromX = SelectedNode->x;
	SelectedNode->animateFromY = SelectedNode->y;
	SelectedNode->animateFromZ = SelectedNode->z;
	SelectedNode->animateToPoint = true;

	removeChild(BoardNode->children[SelectedNodeGraphIndex], SelectedNode);
	addChild(BoardNode->children[newIndex], SelectedNode);
	SelectedNodeGraphIndex = newIndex;
	return Moved;
}

void TryToMove(MoveDirection direction)
{
	int newIndex = Next2DMatrixIndex(direction);
	MoveResult result = MoveFigure(newIndex);
	if (result == OutsideBoard || result == AlreadyOccupied)
	{
		shakeBoardEnabled = true;
	}
}

void UpdateBoard(SceneNode* rootNode, float timeDeltaSeconds)
{
	// Rotates node
	if (rootNode->rotationSpeedRadians != 0)
	{
		if (rootNode->rotationSpeedRadians != 0.0)
		{
			glm::vec3 pointingAtCenterOfParent = glm::cross(glm::vec3(rootNode->x, rootNode->y, rootNode->z), rootNode->rotationDirection);
			if (pointingAtCenterOfParent.x != 0.0 || pointingAtCenterOfParent.y != 0.0 || pointingAtCenterOfParent.z != 0.0)
				rootNode->currentTransformationMatrix = glm::rotate(rootNode->currentTransformationMatrix, rootNode->rotationSpeedRadians * timeDeltaSeconds, pointingAtCenterOfParent);
			else
				rootNode->currentTransformationMatrix = glm::rotate(rootNode->currentTransformationMatrix, rootNode->rotationSpeedRadians * timeDeltaSeconds, rootNode->rotationDirection);
		}
	}

	// Lifts or lowers node
	if (rootNode->lift == true && rootNode->currentZAdd < 1.0f)
	{
		rootNode->currentZAdd += static_cast<float>(rootNode->liftSpeed * timeDeltaSeconds);
		rootNode->currentTransformationMatrix = glm::translate(rootNode->currentTransformationMatrix, glm::vec3(0, 0, rootNode->liftSpeed * timeDeltaSeconds));
	}
	else if (!rootNode->lift && rootNode->currentZAdd > 0.0)
	{
		rootNode->currentZAdd -= static_cast<float>(rootNode->liftSpeed * timeDeltaSeconds);
		rootNode->currentTransformationMatrix = glm::translate(rootNode->currentTransformationMatrix, glm::vec3(0, 0, -rootNode->liftSpeed * timeDeltaSeconds));
	}

	// Moves/animates node
	if (rootNode->animateToPoint && rootNode->animationSpeed > 0.0f)
	{
		if (rootNode->x == rootNode->animateToX && rootNode->y == rootNode->animateToY && rootNode->z == rootNode->animateToZ)
			rootNode->animateToPoint = false;

		rootNode->x += (rootNode->animateToX - rootNode->animateFromX) *  rootNode->animationSpeed * timeDeltaSeconds;
		if ((rootNode->x > rootNode->animateToX && rootNode->x > rootNode->animateFromX) || (rootNode->x < rootNode->animateToX && rootNode->x < rootNode->animateFromX))
			rootNode->x = rootNode->animateToX;

		rootNode->y += (rootNode->animateToY - rootNode->animateFromY) * rootNode->animationSpeed * timeDeltaSeconds;
		if ((rootNode->y > rootNode->animateToY && rootNode->y > rootNode->animateFromY) || (rootNode->y < rootNode->animateToY && rootNode->y < rootNode->animateFromY))
			rootNode->y = rootNode->animateToY;

		rootNode->z += (rootNode->animateToZ - rootNode->animateFromZ) * rootNode->animationSpeed * timeDeltaSeconds;
		if ((rootNode->z > rootNode->animateToZ && rootNode->z > rootNode->animateFromZ) || (rootNode->z < rootNode->animateToZ && rootNode->z < rootNode->animateFromZ))
			rootNode->z = rootNode->animateToZ;
	}

	// Process children recursively
	for (int i = 0; i < rootNode->children.size(); i++)
	{
		UpdateBoard(rootNode->children[i], timeDeltaSeconds);
	}
}

void RenderBoard(SceneNode* rootNode, glm::mat4x4 parentMatrix)
{
	// The naming of the variables are a bit off, but they get the job done.
	glm::mat4x4 model = glm::translate(rootNode->currentTransformationMatrix, glm::vec3(rootNode->x, rootNode->y, rootNode->z));
	glm::mat4x4 mvp = parentMatrix * model;

	if (rootNode->vertexArrayObjectID != -1)
	{
		glm::mat4x4 mvpScaled = glm::scale(mvp, glm::vec3(1.0, 1.0, 1.0) * rootNode->scaleFactor);
		glBindVertexArray(rootNode->vertexArrayObjectID); // Sets up vaoid to be drawn
		glUniformMatrix4fv(2, 1, GL_FALSE, &mvpScaled[0][0]); // Input uniform matrix
		glDrawElements(GL_TRIANGLES, rootNode->indicesCount, GL_UNSIGNED_INT, nullptr);
	}

	for (int i = 0; i < rootNode->children.size(); i++)
	{
		RenderBoard(rootNode->children[i], mvp);
	}
}