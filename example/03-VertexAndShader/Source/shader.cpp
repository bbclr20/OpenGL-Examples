#include "GL/glew.h"
#include "GL/freeglut.h"


GLuint program;
GLuint triangle_buffer;
GLuint triangle_vao;

static const GLfloat triangle_vertices[] = {
	-0.4f, -0.4f, 0.0f, 1.0f,
	 0.0f,  0.4f, 0.0f, 1.0f,
	 0.4f, -0.4f, 0.0f, 1.0f,
};

const char* vsSource = R"glsl(
	#version 400

	layout (location = 0) in vec4 position;

	void main()
	{
		gl_Position = position;
	}
)glsl";

const char* fsSource = R"glsl(
	#version 400

	out vec4 color;

	void main()
	{
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}
)glsl";


void My_Init() {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glewInit();
	//Initialize shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vs, 1, &vsSource, NULL);
	glShaderSource(fs, 1, &fsSource, NULL);

	glCompileShader(vs);
	glCompileShader(fs);

	//Attach Shader to program
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	// vbo
	glGenBuffers(1, &triangle_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices) * sizeof(float), &triangle_vertices[0], GL_STATIC_DRAW);
	
	// vao
	glGenVertexArrays(1, &triangle_vao);
	glBindVertexArray(triangle_vao);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

// GLUT callback. Called to draw the scene.
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update shaders' input variable
	glUseProgram(program);
	{
		glBindVertexArray(triangle_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Shader");

	// invoke custom initialize function
	My_Init();

	//Register GLUT callback functions
	glutDisplayFunc(My_Display);

	// main loop.
	glutMainLoop();

	return 0;
}
