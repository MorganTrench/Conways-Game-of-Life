


/* Imports */
// Standard
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <thread>
#include <vector>
#include <algorithm>
#include <chrono>
//Custom
#include "Cell.h"

/* Structure and Globals */
// Grid
int gridHeight, gridWidth;

// GUI
int windowWidth, windowHeight;
GLFWwindow* window;
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void drawCell(int i, int j, int lifetime);

/* Code */
int main(int argc, char *argv[]){

	/* Argument Parsing */
	// TODO something here with argc and argv, maybe a global options object
	windowWidth = 800; windowHeight = 600;
	gridWidth = 80; gridHeight = 60;

	/* GUI */
	// Initialise GLFW
	std::cout << "GLFW" << std::endl;
	std::cout << "\tInitialising GLFW..." << std::endl;
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Create Window (and context)
	std::cout << "\tCreating Window and Context..." << std::endl;
	window = glfwCreateWindow(windowWidth, windowHeight, "Conway's Game of Life", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Change Argument to 1 for 60fps cap, 0 for unlimited;

	// Set callbacks
	std::cout << "\tSetting Callbacks / Event Handlers..." << std::endl;
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);

	std::cout << "Initialisation..." << std::endl;
	/* Memory Reservation */
	std::cout << "\tAllocating Memory..." << std::endl;
	std::vector< std::vector< Cell > > space ( gridWidth, std::vector<Cell> ( gridHeight, Cell() ) );

	/* Intial State */
	std::cout << "\tSetting up start start..." << std::endl;
	// Clear Screen (black by default)
	glClear(GL_COLOR_BUFFER_BIT);
	// Seed the Screen
  	srand (time(NULL));
	for (int i = 0; i < gridWidth; i++){
		for (int j = 0; j < gridHeight; j++){
			int r = rand() % 100;
			if (r >= 90)
				space[i][j].setState(alive);
		}
	}
	// space[5][10].setState(alive);
	// space[5][11].setState(alive);
	// space[5][12].setState(alive);

	// space[35][25].setState(alive);
	// space[36][25].setState(alive);
	// space[37][25].setState(alive);
	// space[38][25].setState(alive);
	// space[39][25].setState(alive);

	/* Main Loop */
	std::cout << "Beginning Main Loop..." << std::endl;
	while (!glfwWindowShouldClose(window)){
		for (int i = 0; i < gridWidth; i++){
			for (int j = 0; j < gridHeight; j++){
				if (space[i][j].getState() == alive){
					// Draw
					drawCell(i, j, space[i][j].getLifeTime());
					// Increment alive neighbour count for cells
					for (int di = -1; di < 2; di++){
						for(int dj = -1; dj < 2; dj++){
							if ((di != 0) || (dj != 0)){ // Don't increment self
								// Add code here if toroidal universe
								int ti = i + di; int tj = j + dj;
								if ((i + di) == gridWidth)
									ti = 0;
								if ((j + dj) == gridHeight)
									tj = 0;
								if ((i + di) == -1)
									ti = gridWidth - 1;
								if ((j + dj) == -1)
									tj = gridHeight - 1;
								space[ti][tj].incrementNeighbourCount();
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < gridWidth; i++){
			for (int j = 0; j < gridHeight; j++){
				space[i][j].step();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		// Update Screen, clear buffer and get events
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}

	/* Terminate */
	std::cout << "Ending..." << std::endl;
	std::cout << "\tFreeing memory..." << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "\tTerminating..." << std::endl;
	exit(EXIT_SUCCESS);
}

void drawCell(int i, int j, int lifetime){
	double rgb [3] = { 1.0f, 4.0f, 0.0f};
	float sqWidth = 2.0 / gridWidth;
	float sqHeight = 2.0 / gridHeight;
	glBegin(GL_QUADS);
	glColor3f(rgb[0], rgb[1]/lifetime, rgb[2]);
    glVertex3f((-1.0 + i*sqWidth), (-1.0 + j*sqHeight), 0);
	glVertex3f((-1.0 + i*sqWidth), (-1.0 + (j+1)*sqHeight), 0);
	glVertex3f((-1.0 + (i+1)*sqWidth), (-1.0 + (j+1)*sqHeight), 0);
	glVertex3f((-1.0 + (i+1)*sqWidth), (-1.0 + j*sqHeight), 0);
    glEnd();
}

/* GLFW Error Callback */
void error_callback(int error, const char* description){
	fputs(description, stderr);
}

/* GLFW Keyboard Input callback function */
// Currently allows 'esc' key to terminate the program
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}