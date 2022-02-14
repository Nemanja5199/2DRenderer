#include"shaderClass.h"


std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


Shader::Shader(const char* vertexFile, const char* fragmentFile) {

	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Kreiranje vertex sejdera 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Prosledjivanje vrednosti sejderu
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Posto GPU ne moze da razume sorce code moramo da ga kompajliramo sada u masinskom kodu
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");


	//Kreiranje fragment sejdera 
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Prosledjivanje vrednosti sejderu
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Posto GPU ne moze da razume sorce code moramo da ga kompajliramo sada u masinskom kodu
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");


	//Da bi koristili ove sejdere moram oda ih stavimo u jedan sejder program
	ID = glCreateProgram();

	//Povezivanje sejdera sa programom
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	// Brisemo sejdere jel se vec nalaze u programu
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




}


void Shader::Activate() {

	glUseProgram(ID);

}

void Shader::Delete() {
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}