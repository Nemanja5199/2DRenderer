#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"VAO.h"
#include"VBO.h"
#include"shaderClass.h"
#include"EBO.h"
#include"Texture.h"





int main() {


	glfwInit(); //incijalzacija glfw

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// definisemo koji opengl koristimo
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Paket funckija

	GLFWwindow* window = glfwCreateWindow(800, 800, "2DRenderer", NULL, NULL);//prozor

	if (window == NULL) {

		std::cout << "Greska prilikom ucitavanje prozora" << std::endl;

		glfwTerminate();
		return -1;
	}

	GLfloat vertices[] =
	{ //     COORDINATES     /        COLORS      /   TexCoord  //
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
		-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
		 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
	};

	// Indices for vertices order
	GLuint indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2 // Lower triangle
	};
	
	glfwMakeContextCurrent(window);
	


	gladLoadGL();

	glViewport(0, 0, 800, 800);//deo na kome zelimo da visimo renderovanje


	

	//Kreiranje programa za bafere
	Shader shaderProgram("default.vert", "default.frag");

	//Generisanje VAO
	VAO VAO1;
	VAO1.Bind();
	//Generisanje VBO
	VBO VBO1(vertices, sizeof(vertices));
	//Generisanje EBO
	EBO EBO1(indices, sizeof(indices));
	//Bindovanje VAO sa VBO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	//Unbajdovanje svih bafera
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	

	Texture FTN("Ftn Cacak.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

	FTN.texUnit(shaderProgram, "tex0", 0);
	
	
	
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.5f, 0.13f, 0.17f, 1.0f);// Definiseno pozadnisku boju
		glClear(GL_COLOR_BUFFER_BIT);// ciscenje bafera posle svakog frejma
		shaderProgram.Activate();//Aktiviranje pograma
		glUniform1f(uniID, 0.5f);// dodeljivanje unifrom vrednosti 
		FTN.Bind();//Povezivanje Teksture
		VAO1.Bind();// Povezivanje VAO bafera
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);// Crtanje kvadrata
		glfwSwapBuffers(window);// zamena prednjeg i zadnjeg bafera
	}


	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	FTN.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);

	glfwTerminate();




}