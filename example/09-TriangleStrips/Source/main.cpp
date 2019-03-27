#include <Common.h>
#include <ViewManager.h>

#define MENU_Entry1 1
#define MENU_Entry2 2
#define MENU_EXIT   3

using namespace glm;
using namespace std;

//uniform id
struct {
	GLint  mv_matrix;
	GLint  proj_matrix;
} uniforms;

//model info
typedef struct {
} Shape;

GLuint vao;
GLuint buffer;
GLint mv_location;
GLint proj_location;
GLuint program;			//shader program
mat4 proj_matrix;		//projection matrix
float aspect;

Shape m_shape;
ViewManager	m_camera;

static const GLfloat triangle_positions[] = {
	 0.25f,  0.25f,  0.25f,
	-0.25f, -0.25f,  0.25f,
	-0.25f,  0.25f,  0.25f,

	 0.25f, -0.25f,  0.25f,
	-0.25f, -0.25f,  0.25f,
	 0.25f,  0.25f,  0.25f,
};

static const GLfloat triangle_strips_positions[] = {
	 0.25f, -0.25f,  0.25f,
	-0.25f, -0.25f,  0.25f,
	 0.25f,  0.25f,  0.25f,
	-0.25f,  0.25f,  0.25f,
};

GLuint offset = 0;


void My_Init() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// shaders
	program = glCreateProgram();

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	char** vsSource = LoadShaderSource("../Asset/triangle_strips.vs.glsl");
	char** fsSource = LoadShaderSource("../Asset/triangle_strips.fs.glsl");
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

	// vbo
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
}

// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat one = 1.0f;
	glClearBufferfv(GL_COLOR, 0, black);
	glClearBufferfv(GL_DEPTH, 0, &one);

	glUseProgram(program);

	// // plot triangle
	// glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_positions), triangle_positions, GL_STATIC_DRAW);
	// glDrawArrays(GL_TRIANGLES, 0, 6);

	// plot strip
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_strips_positions), triangle_strips_positions, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

	glutSwapBuffers();
}

// reshape event
void My_Reshape(int width, int height) {
	glViewport(0, 0, width, height);

	float viewportAspect = (float)width / (float)height;
	proj_matrix = perspective(deg2rad(50.0f), viewportAspect, 0.1f, 100.0f);
}

// timer event
void My_Timer(int val) {
	glutPostRedisplay();
	glutTimerFunc(16, My_Timer, val);
}

// mouse event
void My_Mouse(int button, int state, int x, int y) {
	m_camera.mouseEvents(button, state, x, y);

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

// keyboard event
void My_Keyboard(unsigned char key, int x, int y) {
	printf("Key %c is pressed at (%d, %d)\n", key, x, y);
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

//menu event
void My_Menu(int id) {
	switch (id) {
	case MENU_Entry1:
		printf("Entry1 is selected.\n");
		break;
	case MENU_Entry2:
		printf("Entry2 is selected.\n");
		break;
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
	glutAddSubMenu("Entry", menu_entry);
	glutAddMenuEntry("Exit", MENU_EXIT);

	glutSetMenu(menu_entry);
	glutAddMenuEntry("Print Entry1", MENU_Entry1);
	glutAddMenuEntry("Print Entry2", MENU_Entry2);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void My_Mouse_Moving(int x, int y) {
	m_camera.mouseMoveEvent(x, y);
}


int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Triangles");
	glewInit();

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