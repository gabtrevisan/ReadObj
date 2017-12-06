/*
* Gabriela de Campos Trevisan
* Disciplina de Computação Gráfica - Ciência da Computação - Unisinos
*
*/

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SOIL 
#include <SOIL.h>

// Classes from https://learnopengl.com/
#include "Shader.h"
#include "Camera.h"

// Read Obj file
#include "Scene.h"

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
GLuint LoadTexture(const char* file);

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool    keys[1024];

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float posX = 0.0f, posY = 0.0f, posZ = 0.0f;
float scl = 1.0f;
float rot = 0.0f;
int x = 0, y = 0, z = 0;

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ReadObj", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	/* get version info */
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Scene scene("../../scene.txt");

	camera.Position = scene.getCamPos();

	float lightX = scene.getLightX();
	float lightY = scene.getLightY();
	float lightZ = scene.getLightZ();

	float lightAmbX = scene.getLightAmbX();
	float lightAmbY = scene.getLightAmbY();
	float lightAmbZ = scene.getLightAmbZ();

	float lightDifX = scene.getLightDifX();
	float lightDifY = scene.getLightDifY();
	float lightDifZ = scene.getLightDifZ();

	float lightSpecX = scene.getLightSpecX();
	float lightSpecY = scene.getLightSpecY();
	float lightSpecZ = scene.getLightSpecZ();

	float bgColorR = scene.getBgColorR();
	float bgColorG = scene.getBgColorG();
	float bgColorB = scene.getBgColorB();

	int numVAOs = 0;

	for (int i = 0; i < scene.getObjects().size(); i++)
	{
		numVAOs += scene.getObjects()[i].getObj().getGroups()->size();
	}
		 
	char* shaderVS = "../shaders/lighting.vs";
	char* shaderFrag = "../shaders/lighting.frag";

	// Build and compile our shader program
	Shader ourShader(shaderVS, shaderFrag);

	GLuint vVBO, nVBO, tVBO;
	GLuint* VAO = new GLuint[numVAOs];
	GLuint* textures = new GLuint[numVAOs];
	int v = 0;
	for (int i = 0; i < scene.getObjects().size(); i++)
	{
		Object object = scene.getObjects()[i];
		Obj obj = object.getObj();

		for (int i = 0; i < obj.getGroups()->size(); i++)
		{		
			glGenBuffers(1, &vVBO);
			glBindBuffer(GL_ARRAY_BUFFER, vVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.getGroups()->at(i).vertices.size(), &obj.getGroups()->at(i).vertices[0], GL_STATIC_DRAW);
	
			if (obj.getGroups()->at(i).normals.size() > 0) {
				glGenBuffers(1, &nVBO);
				glBindBuffer(GL_ARRAY_BUFFER, nVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.getGroups()->at(i).normals.size(), &obj.getGroups()->at(i).normals[0], GL_STATIC_DRAW);
			}

			if (obj.getGroups()->at(i).textures.size() > 0) {
				glGenBuffers(1, &tVBO);
				glBindBuffer(GL_ARRAY_BUFFER, tVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj.getGroups()->at(i).textures.size(), &obj.getGroups()->at(i).textures[0], GL_STATIC_DRAW);
			}

			glGenVertexArrays(1, &VAO[v]);
			glBindVertexArray(VAO[v]);

			// Position attribute
			glBindBuffer(GL_ARRAY_BUFFER, vVBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
			glEnableVertexAttribArray(0);

			if (obj.getGroups()->at(i).normals.size() > 0) {
				// Normal attribute
				glBindBuffer(GL_ARRAY_BUFFER, nVBO);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
				glEnableVertexAttribArray(1);
			}

			if (obj.getGroups()->at(i).textures.size() > 0) {
				// Texture coords attribute
				glBindBuffer(GL_ARRAY_BUFFER, tVBO);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
				glEnableVertexAttribArray(2);
				string texturePath = "../objs/" + obj.getGroups()->at(i).material.getMapKd();
				int texture = LoadTexture(texturePath.c_str());
				textures[v] = texture;
			} else {
				textures[v] = 0;
			}

			v++;
		}	
	}

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	for (int i = 0; i < numVAOs; i++)
		glBindVertexArray(i);

	//Habilita o z-buffer
	glEnable(GL_DEPTH_TEST);

	GLuint texture;
	string texturePath;

	float t = 0.0f;
	int lastAnimation = 0;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Render
		// Clear the colorbuffer
		glClearColor(bgColorR, bgColorG, bgColorB, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Use cooresponding shader when setting uniforms/drawing objects
		ourShader.Use();

		GLint viewPosLoc = glGetUniformLocation(ourShader.Program, "viewPos");

		GLint lightPosLoc = glGetUniformLocation(ourShader.Program, "lightPos");
		GLint lightAmbientLoc = glGetUniformLocation(ourShader.Program, "lightAmbient");
		GLint lightDiffuseLoc = glGetUniformLocation(ourShader.Program, "lightDiffuse");
		GLint lightSpecularLoc = glGetUniformLocation(ourShader.Program, "lightSpecular");

		GLint coefSpecLoc = glGetUniformLocation(ourShader.Program, "coefSpec");

		GLint ambient = glGetUniformLocation(ourShader.Program, "matAmbient");
		GLint diffuse = glGetUniformLocation(ourShader.Program, "matDiffuse");
		GLint specular = glGetUniformLocation(ourShader.Program, "matSpecular");

		
		glUniform3f(lightPosLoc, lightX, lightY, lightZ);
		glUniform3f(lightAmbientLoc, lightAmbX, lightAmbY, lightAmbZ);
		glUniform3f(lightDiffuseLoc, lightDifX, lightDifY, lightDifZ);
		glUniform3f(lightSpecularLoc, lightSpecX, lightSpecY, lightSpecZ);
		glUniform1f(coefSpecLoc, scene.getCoefSpec());
		
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

		// create transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);		
		glm::mat4 view = camera.GetViewMatrix();
		// Get their uniform location
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projLoc = glGetUniformLocation(ourShader.Program, "projection");
		// Pass them to the shaders
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection
		// matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		v = 0;
		for (int i = 0; i < scene.getObjects().size(); i++)
		{
			Object object = scene.getObjects()[i];
			Obj obj = object.getObj();

			posX = object.getPosX();
			posY = object.getPosY();
			posZ = object.getPosZ();
			scl = object.getScale();
			rot = object.getRot();
			x = object.getX();
			y = object.getY();
			z = object.getZ();

			if (object.getAnimation()->curves.size() > 0) {
				t += 0.01;
				if (t > 1.0f) {
					t = 0.0f;
					lastAnimation++;
					if (lastAnimation >= object.getAnimation()->curves.size())
						lastAnimation = 0;
				}
				
				glm::vec2 p = object.getAnimation()->curves.at(lastAnimation).calc(t);

				posX = p.x;
				posY = p.y;
			}

			// calculate the model matrix for each object and pass it to shader before drawing

			glm::mat4 model;

			model = glm::translate(model, glm::vec3(posX, posY, posZ));
			model = glm::rotate(model, rot, glm::vec3(x, y, z));
			model = glm::scale(model, glm::vec3(scl));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			for (int i = 0; i < obj.getGroups()->size(); i++) {
				if (obj.getGroups()->at(i).indicesVT.size() > 0) {
					glBindTexture(GL_TEXTURE_2D, textures[v]);
				}

				if (obj.getGroups()->at(i).material.getName() != "") {
					glUniform3f(ambient, obj.getGroups()->at(i).material.getKaX(), obj.getGroups()->at(i).material.getKaY(), obj.getGroups()->at(i).material.getKaZ());
					glUniform3f(diffuse, obj.getGroups()->at(i).material.getKdX(), obj.getGroups()->at(i).material.getKdY(), obj.getGroups()->at(i).material.getKdZ());
					glUniform3f(specular, obj.getGroups()->at(i).material.getKsX(), obj.getGroups()->at(i).material.getKsY(), obj.getGroups()->at(i).material.getKsZ());
				}

				glBindVertexArray(VAO[v]);
				glDrawArrays(GL_TRIANGLES, 0, obj.getGroups()->at(i).vertices.size() / 3);
				v++;
			}
		}
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	for (int i = 0; i < numVAOs; i++)
		glDeleteVertexArrays(1, &VAO[i]);
	glDeleteBuffers(1, &vVBO);
	glDeleteBuffers(1, &nVBO);
	glDeleteBuffers(1, &tVBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

GLuint LoadTexture(const char* file)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); 
	return textureID;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}