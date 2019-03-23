#include "../Include/Common.h"

#define SIZE_1		1
#define SIZE_2		2
#define MENU_EXIT   3

const float TIMER_INTERVAL = 16;

enum Color{ Red, Green, Blue} ;
Color myColor = Red;

float aspect;			
float rotateAngle = 0.0f;

float oldbackGray;
float backgroundGray = 1.0f;
float clickPt_x;


float teapot_posX = 0.0f;
float teapot_posY = 0.0f;
float teapot_size = 1.0f;

float clamp(float v, float min, float max);

// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);

	// set model view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 5.0,
		      0.0, 0.0, 0.0,
		      0.0, 1.0, 0.0);

	glTranslatef(teapot_posX, teapot_posY, 0.0f);
	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	
	if (myColor == Red) {
		glColor3b(125, 0, 0);
	} else if (myColor == Green) {
		glColor3b(0, 125, 0);
	} else if (myColor == Blue) {
		glColor3b(0, 0, 125);
	}
	
	glutWireTeapot(teapot_size);
    glutSwapBuffers();
}

// reshape event
void My_Reshape(int width, int height) {
	aspect = width * 1.0f / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, aspect, 0.1f, 10.0f);
}

// timer event
void My_Timer(int val) {
	const float rotateSpeed = 30.0f;
	glutPostRedisplay();
	glutTimerFunc(TIMER_INTERVAL, My_Timer, val);
	rotateAngle += rotateSpeed * TIMER_INTERVAL * 0.001; 
}

// keyboard event
void My_Keyboard(unsigned char key, int x, int y) {
	const float step = 0.05f;
    
    if (key == 'W' || key == 'w') {
		teapot_posY += step;
	} else if (key == 'S' || key == 's') {
		teapot_posY -= step;
	} else if (key == 'A' || key == 'a') {
		teapot_posX -= step;
	} else if (key == 'D' || key == 'd') {
		teapot_posX += step;
	}
	glutPostRedisplay();	
}

//special key event
void My_SpecialKeys(int key, int x, int y) {
	switch (key) {
        case GLUT_KEY_F1:
            myColor = Red;
            break;
        
        case GLUT_KEY_F2:
            myColor = Green;
            break;
        
        case GLUT_KEY_F3:
            myColor = Blue;
            break;
        
        default:
            break;
    }
}

// menu event
void My_Menu(int id) {
	 switch (id) {
        case SIZE_1:
            teapot_size = 1.0f;
            break;

        case SIZE_2:
            teapot_size = 2.0f;
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
	glutAddSubMenu("Teapot size", menu_entry);
	glutAddMenuEntry("Exit", MENU_EXIT);

	glutSetMenu(menu_entry);
	glutAddMenuEntry("1.0", SIZE_1);
	glutAddMenuEntry("2.0", SIZE_2);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// mouse event
void My_Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			oldbackGray = backgroundGray;
			clickPt_x = x;
		}
	}
}

// drag event
void Mouse_Moving(int x, int y) {
	backgroundGray = (x - clickPt_x) * 0.005f + oldbackGray; 
	backgroundGray = clamp(backgroundGray, 0.0f, 1.0f);
}


int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);

	glutCreateWindow("glut"); 

	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);
	DumpInfo();


	// glut callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	addMenu();
	glutMouseFunc(My_Mouse);
	glutKeyboardFunc(My_Keyboard);
	glutSpecialFunc(My_SpecialKeys);
	glutTimerFunc(TIMER_INTERVAL, My_Timer, 0);           
	glutMotionFunc(Mouse_Moving);  

	// main loop
	glutMainLoop();
	
	return 0;
}

float clamp(float v, float min, float max) {
	if (v >= max){
		return max;
	} else if (v <= min) {
		return min;
	} else {
		return v;
	}
}
