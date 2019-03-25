#include "../Include/Common.h"
#include "../Include/ViewManager.h"

#define MENU_EXIT 3

using namespace glm;
using namespace std;

//shader program
GLuint program;


void My_Init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// initialize shaders
	program = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char** vsSource = LoadShaderSource("../Asset/vertex.vs.glsl");
	char** fsSource = LoadShaderSource("../Asset/fragment.fs.glsl");
	glShaderSource(vs, 1, vsSource, NULL);
	glShaderSource(fs, 1, fsSource, NULL);
	FreeShaderSource(vsSource);
	FreeShaderSource(fsSource);
	glCompileShader(vs);
	glCompileShader(fs);
	ShaderLog(vs);
	ShaderLog(fs);

	// attach shader to program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glUseProgram(program);
	
	// define data
	float data[18] = {
		-0.5f, -0.4f, 0.0f,		// position
		0.5f, -0.4f, 0.0f,
		0.0f, 0.6f, 0.0f,

		1.0f, 0.0f, 0.0f,		// color
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
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

	glVertexAttribPointer(0,         // index 
						  3,         // element number
						  GL_FLOAT,  // data type
						  GL_FALSE,  // normalize data
						  0,         // stride of data
						  0          // offset in vbo
						  );


	glVertexAttribPointer(1,         // index 
						  3,         // element number
						  GL_FLOAT,  // data type
						  GL_FALSE,  // normalize data
						  0,         // stride of data
						  (void*)(sizeof(float) * 9)); //offset

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// update shaders' input variable
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

// reshape event
void My_Reshape(int width, int height) {
	glViewport(0, 0, width, height);
}

// keyboard event
void My_Keyboard(unsigned char key, int x, int y) {
	printf("Key %c is pressed at (%d, %d)\n", key, x, y);
}

// mouse event
void My_Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			printf("Mouse %d is pressed at (%d, %d)\n", button, x, y);
		} else if (state == GLUT_UP) {
			printf("Mouse %d is released at (%d, %d)\n", button, x, y);
		}
	} else if (button == GLUT_RIGHT_BUTTON) {
		printf("Mouse %d is pressed\n", button);
	}
}

// mouse moving event
void My_Mouse_Moving(int x, int y) {
}

// special key event
void My_SpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		printf("F1 is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_PAGE_UP:
		printf("Page up is pressed at (%d, %d)\n", x, y);
		break;
	case GLUT_KEY_LEFT:
		printf("Left arrow is pressed at (%d, %d)\n", x, y);
		break;
	default:
		printf("Other special key is pressed at (%d, %d)\n", x, y);
		break;
	}
}

// menu event
void My_Menu(int id) {
	switch (id) {
	case MENU_EXIT:
		exit(0);
		break;
	default:
		break;
	}
}

void addMenu() {
	int menu_main = glutCreateMenu(My_Menu);
	int menu_entry = glutCreateMenu(My_Menu);
	glutSetMenu(menu_main);
	glutAddMenuEntry("Exit", MENU_EXIT);
	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// timer event
void My_Timer(int val) {
	const GLuint msecs = 16;

	glutPostRedisplay();
	glutTimerFunc(msecs,     // time step
				  My_Timer,  // callback
				  val        // a number/id to identify timer event
 				  );
}


int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Buffer");
	glewInit();

	// print debug information 
	DumpInfo();
	
	My_Init();
	addMenu();

	// glut callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutMouseFunc(My_Mouse);
	glutKeyboardFunc(My_Keyboard);
	glutSpecialFunc(My_SpecialKeys);
	glutTimerFunc(16, My_Timer, 0);
	glutPassiveMotionFunc(My_Mouse_Moving);
	glutMotionFunc(My_Mouse_Moving);

	// main loop.
	glutMainLoop();

	return 0;
}