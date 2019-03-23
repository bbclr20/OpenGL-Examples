#include "../Include/Common.h"

const float backgroundColor = 1.0f;


// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundColor, backgroundColor, backgroundColor, 1.0f);
    glutSwapBuffers();
}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// create a glut window
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("glut");
	
	// glut callback functions
	glutDisplayFunc(My_Display);
	
	// main loop
	glutMainLoop();
	return 0;
}
