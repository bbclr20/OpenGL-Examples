#include "../Include/Common.h"
#include <math.h>

#define SIZE_1		1
#define SIZE_2		2
#define MENU_EXIT   3

using namespace std;

float aspect;			

float backgroundGray = 1.0f;

float teapot_size = 1.0f;

// 渲染事件, 用來在場景上繪製東西
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);

	glMatrixMode(GL_MODELVIEW);  //指定目前運算的矩陣為視覽座標矩陣及模塑座標矩陣
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);          //設定相機的位置，視點，y軸向量

	glColor3b(125, 0, 0);        //設定目前所使用的顏色
	glutWireTeapot(teapot_size); //畫出線框茶壺
    
    glutSwapBuffers();
}

// 視窗重塑事件, 當視窗大小改變時被呼叫
void My_Reshape(int width, int height) {
    
	aspect = width * 1.0f / height;
	glMatrixMode(GL_PROJECTION);                 //指定目前運算的矩陣為投影矩陣
	glLoadIdentity();                            //將目前指定的矩陣重設為單位矩陣
	glViewport(0, 0, width, height);             //視埠，將投影影像對應在視窗座標上
	gluPerspective(60.0f, aspect, 0.1f, 10.0f);  //投影模式為透視，並設定其參數
}


int main(int argc, char **argv) {
	// 初始化GLUT,並創立一個視窗.
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	
	glutCreateWindow("glut"); 
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//註冊GLUT回呼事件
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape); //註冊視窗重塑事件
    
	// 進入主迴圈
	glutMainLoop();
	
	return 0;
}
