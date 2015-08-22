


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
void drawCell(int i, int j);

/* Code */
int main(int argc, char *argv[]){

	/* Argument Parsing */
	// TODO something here with argc and argv, maybe a global options object
	windowWidth = 800; windowHeight = 600;
	gridWidth = 20;	gridHeight = 15;

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
	std::vector< std::vector< std::vector<Cell> > > space(gridWidth, std::vector< std::vector<Cell> >(gridHeight, std::vector<Cell>(2, Cell())));

	/* Intial State */
	std::cout << "\tSetting up start start..." << std::endl;
	// Clear Screen (black by default)
	glClear(GL_COLOR_BUFFER_BIT);
	// Reference Layer
	int k = 0;

	/* Main Loop */
	std::cout << "Beginning Main Loop..." << std::endl;
	// Test output
	std::cout << "DEBUG: " << space.size() << " " << space[0].size() << " " << space[0][0].size() << std::endl;
	// DEBUG
	space[5][5][0].setState(alive);
	space[5][6][0].setState(alive);
	space[5][7][0].setState(alive);
	while (!glfwWindowShouldClose(window)){
		for(int i = 0; i < gridWidth; i++){
			for(int j = 0; j < gridHeight; j++){
				if (space[i][j][k].getState() == alive){
					// Draw
					drawCell(i, j);
					// Increment Neighbours
					if (k == 0){k = 1;} else {k = 0;}
					for (int dx = -1; dx <= 1; dx++){
						for (int dy = -1; dy <= 1; dy++){
							if (((i + dx) > 0) && ((i + dx) < gridWidth))
								if (((j + dy) > 0) && ((j + dy) < gridHeight))
									space[i][j][k].alive_neighbours += 1;
						}
					}
					if (k == 0){k = 1;} else {k = 0;}
				}
			}
		}
		// Switch Future and Present
		if (k == 0){k = 1;} else {k = 0;}
		for(int i = 0; i < gridWidth; i++){
			for(int j = 0; j < gridHeight; j++){
				space[i][j][k].step();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

void drawCell(int i, int j){
	double rgb [3] = { 1.0f, 2.0f, 0.0f};
	float sqWidth = 2.0 / gridWidth;
	float sqHeight = 2.0 / gridHeight;
	glBegin(GL_QUADS);
	glColor3f(rgb[0], rgb[1], rgb[2]);
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