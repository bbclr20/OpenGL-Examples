#include "../Include/Common.h"

float aspect;
float backgroundGray = 1.0f;
float teapot_size = 1.0f;

// render event
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);

	// set modelview
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 5.0,      // eye
		      0.0, 0.0, 0.0,      // center
		      0.0, 1.0, 0.0);     // up

	glColor3b(125, 0, 0);         // set color
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


int main(int argc, char **argv) {
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	
	glutCreateWindow("glut"); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// glut callback functions
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
    
	// main loop
	glutMainLoop();
	
	return 0;
}
