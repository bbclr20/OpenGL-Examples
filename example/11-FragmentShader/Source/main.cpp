#include <Common.h>

#define MENU_EXIT 4

using namespace glm;

GLuint program;	//shader program

int shader_now = 0;

GLuint hawk_texture;
GLint Shader_now_Loc;
const GLint defalut_w = 640;
const GLint defalut_h = 480;

void My_Init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// shaders
	program = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char** vsSource = LoadShaderSource("../Asset/Simple_Example.vs.glsl");
	char** fsSource = LoadShaderSource("../Asset/Simple_Example.fs.glsl");
	glShaderSource(vs, 1, vsSource, NULL);
	glShaderSource(fs, 1, fsSource, NULL);
	FreeShaderSource(vsSource);
	FreeShaderSource(fsSource);
	glCompileShader(vs);
	glCompileShader(fs);
	ShaderLog(vs);
	ShaderLog(fs);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glUseProgram(program);


	float data[] = {
		0.8f, -0.8f, 1.0f, 0.0f,
	   -0.8f, -0.8f, 0.0f, 0.0f,
	   -0.8f,  0.8f, 0.0f, 1.0f,
		0.8f,  0.8f, 1.0f, 1.0f
	};

	// vbo
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	// vao
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// texture
	TextureData tdata = Load_png("../Asset/leaf.png");

	glGenTextures(1, &hawk_texture);
	glBindTexture(GL_TEXTURE_2D, hawk_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, tdata.width, tdata.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tdata.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glutSwapBuffers();
}

// reshape event
void My_Reshape(int width, int height) {
	glViewport(0, 0, width, height);
}

// timer event
void My_Timer(int val) {
	glutPostRedisplay();
	glutTimerFunc(16, My_Timer, val);
}

//menu event
void My_Menu(int id) {
	switch (id) {
	case MENU_EXIT:
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void addMenu() {
	int menu_main = glutCreateMenu(My_Menu);
	glutSetMenu(menu_main);
	glutAddMenuEntry("Exit", MENU_EXIT);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(defalut_w, defalut_h);
	glutCreateWindow("Image processing");
	glewInit();


	DumpInfo();
	My_Init();
	addMenu();

	// glut callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutTimerFunc(16, My_Timer, 0);

	// main loop
	glutMainLoop();

	return 0;
}