#include "GL/glew.h"
#include "GL/freeglut.h"

using namespace std;

const int SIZE_1 = 1;
const int SIZE_2 = 2;
const int MENU_EXIT = 3;

const float BACKGROUND_COLOR = 0.10;
const float TIMER_INTERVAL = 16;

float teapot_posX = 0.0f;
float teapot_posY = 0.0f;
float teapot_size = 1.0f;

float rotateAngle = 90.0f;
float aspect;

enum Color{ Red, Green, Blue };
Color myColor = Red;

// render event
void My_Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f);
    
    // set model view
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 2.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glTranslatef(teapot_posX, teapot_posY, 0.0f);
	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);

    // set line color
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

    // set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, aspect, 0.1f, 10.0f);
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
	glutPostRedisplay();
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

void addMenu() {
	int menu_main = glutCreateMenu(My_Menu); 
    int menu_entry = glutCreateMenu(My_Menu);

    // set main menu
	glutSetMenu(menu_main);
	glutAddSubMenu("Teapot size", menu_entry); // add sub menu to item
	glutAddMenuEntry("Exit", MENU_EXIT);

    // set submenu
	glutSetMenu(menu_entry);
	glutAddMenuEntry("1.0", SIZE_1);
	glutAddMenuEntry("2.0", SIZE_2);

    // commit setting
	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// special key event
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
	glutPostRedisplay();
}

// timer event
void My_Timer(int val) {
    const float rotateSpeed = 30.0f;
	glutPostRedisplay();
	glutTimerFunc(TIMER_INTERVAL, My_Timer, val);
	rotateAngle += rotateSpeed * TIMER_INTERVAL * 0.001; //根據時間和速度計算並累積旋轉量
}


int main(int argc, char**argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello opengl");
    
    // glut callback functions
    glutDisplayFunc(My_Display);
    glutReshapeFunc(My_Reshape);
    addMenu();
    glutKeyboardFunc(My_Keyboard);
    glutSpecialFunc(My_SpecialKeys);
    glutTimerFunc(TIMER_INTERVAL, My_Timer, 0);

    glutMainLoop();
    return -1;
}