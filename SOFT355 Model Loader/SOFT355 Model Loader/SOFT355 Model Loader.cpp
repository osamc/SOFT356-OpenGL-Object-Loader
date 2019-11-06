
#include <iostream>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp> //includes GLM
#include <iostream>
#include <string>
#include "ModelLoader.h"

int main()
{

	std::string fileLocation, doWeContinue;
	Model model;

	do {

		do {
			std::cout << "Please input the file location of the object\n";
			std::cin >> fileLocation;
			model = loadFromFile(fileLocation);

			if (!model.createdSuccessfully) {
				std::cout << "There was an issue loading your file, please try another" << std::endl;
			}

		} while (!model.createdSuccessfully);

		glfwInit();

		GLFWwindow* window = glfwCreateWindow(800, 600, fileLocation.c_str(), NULL, NULL);

		glfwMakeContextCurrent(window);
		glewInit();

		model.init();
		GLfloat xdelta = 0.0f;
		GLfloat ydelta = 0.0f;
		GLfloat zdelta = 0.0f;
		GLfloat scale = 1.0f;

		do {
			// uncomment to draw only wireframe 
			 //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			model.draw(xdelta, ydelta, zdelta, scale);
			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				ydelta += 1.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				ydelta -= 1.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
				xdelta -= 1.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				xdelta -= -1.0f;
			}

			if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
				scale += 0.005f;
			}

			if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
				scale += -0.005f;
			}

			if (scale < 0) {
				scale = 0;
			}


		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);


		glfwDestroyWindow(window);

		glfwTerminate();

		std::cout << "Type \"quit\" to exit out of the application, enter anything else to prompted to load another file" << std::endl;
		std::cin >> doWeContinue;

	} while (!doWeContinue._Equal("quit"));

	

}
