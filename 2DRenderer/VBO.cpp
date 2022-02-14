#include"VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size) {

	glGenBuffers(1, &ID);// Generisemo bafer 
	glBindBuffer(GL_ARRAY_BUFFER, ID);//povezujemo nas bafer sa njegovim tipom
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);// prosledjujemo podatke u bafer 
}


void VBO::Bind() {


	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);// razvezujemo bafer
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);//brisemo bafer 
}

