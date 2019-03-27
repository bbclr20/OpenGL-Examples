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

GLuint square_buffer;
GLuint square_vao;
GLuint program;			//shader program
mat4 proj_matrix;		//projection matrix
float aspect;

Shape m_shape;
ViewManager m_camera;

static const GLfloat square_vertices[] = {
	-1.0f, -1.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, 0.0f, 1.0f,
	 1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f, 0.0f, 1.0f
};

static const GLfloat instance_colors[] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f
};

static const GLfloat instance_positions[] = {
	-2.0f, -2.0f, 0.0f, 0.0f,
	 2.0f, -2.0f, 0.0f, 0.0f,
	 2.0f,  2.0f, 0.0f, 0.0f,
	-2.0f,  2.0f, 0.0f, 0.0f
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
	char** vsSource = LoadShaderSource("../Asset/Instanced_Rendering.vs.glsl");
	char** fsSource = LoadShaderSource("../Asset/Instanced_Rendering.fs.glsl");
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
	glGenBuffers(1, &square_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, square_buffer);

	GLuint dataSize = sizeof(square_vertices) + sizeof(instance_colors) + sizeof(instance_positions); 
	glBufferData(GL_ARRAY_BUFFER, 
				 dataSize, 
				 NULL, 
				 GL_STATIC_DRAW
				 );
	
	glBufferSubData(GL_ARRAY_BUFFER, 
					offset, 
					sizeof(square_vertices), 
					square_vertices
					);
	offset += sizeof(square_vertices);
	
	glBufferSubData(GL_ARRAY_BUFFER, 
					offset, 
					sizeof(instance_colors), 
					instance_colors
					);
	offset += sizeof(instance_colors);
	
	glBufferSubData(GL_ARRAY_BUFFER, 
					offset, 
					sizeof(instance_positions), 
					instance_positions
					);
	offset += sizeof(instance_positions);

	// vao
	glGenVertexArrays(1, &square_vao);
	glBindVertexArray(square_vao);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(square_vertices));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(square_vertices) + sizeof(instance_colors)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
}

// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);

	glUseProgram(program);
	glBindVertexArray(square_vao);
	glDrawArraysInstanced(GL_TRIANGLE_FAN, // mode 
						  0,               // first 
						  4,               // count // try 3 for fun
						  4                // instance count
						  );

	glutSwapBuffers();
}

// render event
void My_Reshape(int width, int height) {
	aspect = width * 1.0f / height;
	m_camera.SetWindowSize(width, height);
	glViewport(0, 0, width, height);
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

// menu event
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
	glutCreateWindow("Instance");
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

	// event loop
	glutMainLoop();

	return 0;
}