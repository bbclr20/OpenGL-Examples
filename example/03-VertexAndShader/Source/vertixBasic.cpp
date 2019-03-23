#include "GL/freeglut.h"

// GLUT callback. Called to draw the scene.
void My_Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update shaders' input variable
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex2f(-0.4f, -0.4f);
		glVertex2f( 0.0f,  0.4f);
		glVertex2f( 0.4f, -0.4f);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Vertex basics");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// glut callback functions
	glutDisplayFunc(My_Display);

	// main loop.
	glutMainLoop();

	return 0;
}