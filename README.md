# SOFT356 Object Loader using OpenGL

This is a project with the focus of loading object files and parsing them to be used with OpenGL. 

## Supported File Formats
```
.obj - Wavefront's Object file
.dae - Collada File format
```

## Usage
There is a simple main method that runs through the process of taking user input and a location to place the object. There is a folder called "media" within the project where the files you wish to render should go. A simple dialogue with the main method may look like:

```
Please enter a location you would like to place the camera in the form: x y z
Any non parsable format will result in the camera being placed at 0,0,0
0 0 0
Please input the file location of the object or enter "quit" to close.
media/creeper.obj
Creating from: media/creeper.obj
Please input Location you would like to render the object at in the format 'x y z'
0 0 -4
Please input the file location of the object or enter "quit" to close.
You can also type "render" to begin to render your scene.
render
You are able to close the window with the Q key
```

## Controls

Within the main method there are several controls that can be used to manipulate the loaded objects. They are:

- W,A,S,D for rotations in the x and y axis
-  \+,\- for growing and shrinking the models
- I,J,K,L for camera movement in the x and y axis
- U,O for camera movement in the z axis
- R to remove the newest loaded model
- Hold F to show the model in wireframe view


## Implimentation and Use
To use the project you will need to change the configuration of the project to point to a folder containing the glm library that can be found [here](https://glm.g-truc.net/0.9.9/index.html). You will also need to check that the nuget packages have been downloaded. The two this project uses are:

```
nupengl.core v0.1.0.1
nupengl.core.redist v0.1.0.1
```

Then a simple example of using the object loader to load and render a file may look like:

```cpp
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp> //includes GLM
#include <string>
#include "ModelLoader.h"
#include "ShaderLoader.h"

int main()
{

	std::string fileLocation = "media/creeper.obj";
	Model model = loadFromFile(fileLocation);

	glfwInit();

	//Create our window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Object Loader", NULL, NULL);

	glfwMakeContextCurrent(window);
	glewInit();

	model.init();
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	do {

		model.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		glClearBufferfv(GL_COLOR, 0, black);
		glClearColor(0.0f, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_Q) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

}
```
However within 'SOFT356 Model Loader.cpp' there is a more hands on demo that can be used as an example.

## Approach to parsing
#### Obj
A simple approach of going line by line for the obj file and looking at the first two letters of each line. 

```
v - vertex
vt - texture vertex
vn - normal vertex
f - face
```

For each variable we load it into a temporary vertex. Then after all of the face data is read in, we then process the data and load them into an Model object. This processing takes care of converting quadrilaterals into 2 separate triangles.

#### DAE
As DAE files are a specialised format of XML, we took the approach of using Regex to locate and extract the data required to form the model. This might not be the nicest or fastest method, but it was done without requiring any third party libraries. In the future I would like to come back and look at this again using additional libraries to see how I could speed it up.



## Multiple Objects
The model object was created using ENUMS and set values, this means when we call
```cpp
glGenVertexArrays(NumVAOs, VAOs);
glGenBuffers(NumBuffers, Buffers);
```
we are returned with unique values for VAOs and buffer ids. This means that there isn't any conflicts when attempting to create and render a model.

