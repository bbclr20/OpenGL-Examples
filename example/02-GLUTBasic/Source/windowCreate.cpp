#include "../Include/Common.h"
#include <math.h>

#define SIZE_1		1
#define SIZE_2		2
#define MENU_EXIT   3

using namespace std;		

float backgroundGray = 1.0f;


// 渲染事件, 用來在場景上繪製東西
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清除緩存器
	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);
    glutSwapBuffers();                                   //交換前後緩存器
}

int main(int argc, char *argv[]) {

	// 初始化GLUT,並創立一個視窗.
	glutInit(&argc, argv); //初始化GLUT指令

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100); //設定初始化視窗位置
	glutInitWindowSize(600, 600);     //設定初始化視窗大小
	
	glutCreateWindow("glut");         //創立一個GLUT視窗
	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f); //設定清除顏色
	
	//註冊GLUT回呼事件
	////////////////////
	glutDisplayFunc(My_Display);      //註冊渲染事件
	////////////////////
	
	// 進入主迴圈
	glutMainLoop();

	return 0;
}
