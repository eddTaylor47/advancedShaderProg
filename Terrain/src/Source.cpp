#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Camera.h"

#include <Model.h>

#include<string>
#include <iostream>
#include <numeric>



// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(char const * path);
//unsigned int loadTexture2(char const * path);
void setVAO(vector <float> vertices);

// camera
Camera camera(glm::vec3(0,0,9));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//arrays
unsigned int VBO, VAO;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//light
glm::vec3 lightPos = glm::vec3(0.5f, 1.5f, 4.8f); // Light position
glm::vec3 ambientMat = glm::vec3(0.3f, 0.3f, 0.3f); // ambient material values
glm::vec3 diffuseMat = glm::vec3(1.0f, 1.0f, 1.0f); // diffuse material values
glm::vec3 specularMat = glm::vec3(0.6f, 0.6f, 0.6f); // specular material values

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "IMAT3907", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// simple vertex and fragment shader 
	Shader shader0("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs");
	Shader shader1("..\\shaders\\plainVert.vs", "..\\shaders\\normFrag.fs", "..\\shaders\\normGeo.gs");
	// load model with assimp
	Model model1("..\\resources\\nano\\nanosuit\\nanosuit.obj");
	//Model model2("..\\resources\\elephant\\elefante.obj");
	


	////============================ TASK ONE ===========================================
	//float points[] = {
	//					// x,    y,   z,    r,    g,    b,	//  u,    v
	//	               -2.5f, 0.0f, 0.0f//, 1.0f, 0.5f, 1.0f//, //1.0f, 1.0f,
	//	                //2.5f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, //1.0f, 1.0f,
	//	                //0.0f, 2.5f, 0.0f, 1.0f, 0.5f, 1.0f//, 1.0f, 1.0f
	//};

	//unsigned int VBO, VAO; //create identifiers for vbo and vao
	//glGenBuffers(1, &VBO); //generate vbo
	//glGenVertexArrays(1, &VAO); // generate vao
	//glBindVertexArray(VAO); //declare VAO to be a vertex array object
	//glBindBuffer(GL_ARRAY_BUFFER, VBO); //declare vbo to be a vertex buffer object
	//glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW); // declare the data stored in the vbo

	//glEnableVertexAttribArray(0); //enable the vertex array object on the gpu at index 0 for the first set of vertex data(x, y, z i.e. position)
	////set up at the index 0(1st arg), 3 values(2nd), of type float(3rd), bool flag for normalised data(4th, typically always false), stride is the size of 6 floats(5th, length of all of the vertex data), 
	////pointer to the index position of the starting index of the vertex array object(6th, is 0th position in gpu index)
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0); 
	//glEnableVertexAttribArray(1); //enable the next set of vertex data (r, g, b i.e. colour)
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0); // starting from index 1
	////glEnableVertexAttribArray(2); //enable the next set of vertex data (u, v i.e. texture UV coordinates)
	////glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0); // starting from index 2
	//glBindVertexArray(0); //bind the vertex array declared to start from index 0

	//=======================================================================

	glClearColor(1.f, 1.f, 1.f, 1.f);

	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
	    shader0.use();
	    shader0.setMat4("projection", projection); //upload projection matrix
		shader0.setMat4("view", view); //upload view matrix
		shader0.setMat4("model", model); //upload model matrix
		shader0.setVec3("viewPos", camera.Position); //upload camera position(viewPos)
		shader0.setVec3("lightPos", lightPos);
		shader0.setVec3("light.ambient", ambientMat);
		shader0.setVec3("light.diffuse", diffuseMat);
		shader0.setVec3("light.specular", specularMat);
		shader0.setVec3("light.position", lightPos);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //DRAWS WITH FILLED COLOUR
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // DRAWS WIREFRAME
		//glBindVertexArray(VAO); //bind the vertex array buffer from which we are drawing(VAO is set up above)
		//glDrawArrays(GL_TRIANGLES, 0, 3); //draw the array using tirangle primitives(1st param), starting from index 0 in enabled arrays(2nd), count of indices to draw(3rd)
		//glDrawArrays(GL_POINTS, 0, 1); //draw a point
		model1.Draw(shader0);

		shader1.use();
		shader1.setMat4("projection", projection); //upload projection matrix
		shader1.setMat4("view", view); //upload view matrix
		shader1.setMat4("model", model); //upload model matrix
		shader1.setFloat("vLength", 0.1f); //upload the uniform length
		shader1.setVec4("fColour", glm::vec4(1.f, 0.5f, 0.7f, 1.f));
		model1.Draw(shader1);

		//model = glm::translate(model, glm::vec3(50.f, 25.f, -50.f)); // translate elefante
		//model = glm::scale(model, glm::vec3(10.f)); // scale elefante
		//model = glm::rotate(model, glm::radians(90.f), glm::vec3(0.f, -1.f, 0.f)); //rotate elefante
		//shader.setMat4("model", model); //upload updated model matrix
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // DRAWS WIREFRAME
		//model2.Draw(shader); // draaw elefante with update model matrix

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}





// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_image_free(data);
		std::cout << "Loaded texture at path: " << path << " width " << width << " id " << textureID <<  std::endl;

	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
		
	}

	return textureID;
}


void setVAO(vector <float> vertices) {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);		
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(GLfloat)), vertices.data(), GL_STATIC_DRAW);

	//xyz
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



