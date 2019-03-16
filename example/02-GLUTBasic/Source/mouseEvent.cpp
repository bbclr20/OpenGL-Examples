#include "../Include/Common.h"
#include <math.h>

#define SIZE_1		1
#define SIZE_2		2
#define MENU_EXIT   3

using namespace std;

enum MyColor{Red,Green,Blue};
MyColor myColor = Red;

float			aspect;			

float			timer_interval = 16;

float			rotateAngle = 0.0f;
float			rotateSpeed = 30.0f;

float			oldbackGray;
float			backgroundGray = 1.0f;
float			clickPt_x;


float			teapot_posX = 0.0f;
float			teapot_posY = 0.0f;
float			teapot_size = 1.0f;

float clamp(float v, float min, float max);

// 渲染事件, 用來在場景上繪製東西
void My_Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 2.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glTranslatef(teapot_posX, teapot_posY, 0.0f);
	glRotatef(rotateAngle, 0.0f, 1.0f,0.0f);
	
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

// 視窗重塑事件, 當視窗大小改變時被呼叫
void My_Reshape(int width, int height) {
	aspect = width * 1.0f / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(60.0f, aspect, 0.1f, 10.0f);
}

//計時器事件, 經指定時間後該函式被呼叫
void My_Timer(int val) {
	glutPostRedisplay();
	glutTimerFunc(timer_interval, My_Timer, val);
	rotateAngle += rotateSpeed * timer_interval * 0.001; 
}

//滑鼠事件, 滑鼠經點擊或釋放時觸發
void My_Mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {      //取得的按鍵為滑鼠左鍵
		if (state == GLUT_DOWN) {          //按鍵狀態為點擊時的瞬間
			oldbackGray = backgroundGray;  //儲存當下背景明暗度
			clickPt_x = x;                 //儲存當下x軸的滑鼠位置
		}
	}
}

//鍵盤事件, 接收到鍵盤字元輸入時被呼叫
void My_Keyboard(unsigned char key, int x, int y) {
	if (key == 'W' || key == 'w') {
		teapot_posY += 0.05f;
	} else if (key == 'S' || key == 's') {
		teapot_posY -= 0.05f;
	} else if (key == 'A' || key == 'a') {
		teapot_posX -= 0.05f;
	} else if (key == 'D' || key == 'd') {
		teapot_posX += 0.05f;
	}
}

//鍵盤事件, 接收到鍵盤功能鍵或方向鍵時被呼叫
void My_SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {
		myColor = Red;
	} else if (key == GLUT_KEY_F2) {
		myColor = Green;
	} else if (key == GLUT_KEY_F3) {
		myColor = Blue;
	}
}

//選單事件, 當選單的條目被選取時被呼叫
void My_Menu(int id) {
	if (id == SIZE_1) {
		teapot_size = 1.0f;
	} else if (id == SIZE_2) {
		teapot_size = 2.0f;
	} else if (id == MENU_EXIT) {
		exit(0);
	}
}

//滑鼠拖曳事件, 滑鼠進行拖曳時觸發
void Mouse_Moving(int x, int y) {
	backgroundGray = (x - clickPt_x) * 0.005f + oldbackGray; //根據滑鼠移動到的座標與點擊時的座標的向量差，計算明亮度
	backgroundGray = clamp(backgroundGray, 0.0f, 1.0f);      //避免計算值超過範圍
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);

	glutCreateWindow("glut"); 

	glClearColor(backgroundGray, backgroundGray, backgroundGray, 1.0f);
	DumpInfo();

	//定義選單結構
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

	//註冊GLUT回呼事件
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutMouseFunc(My_Mouse);        //註冊滑鼠按鍵的回呼事件
	glutKeyboardFunc(My_Keyboard);
	glutSpecialFunc(My_SpecialKeys);
	glutTimerFunc(timer_interval, My_Timer, 0);           
	glutMotionFunc(Mouse_Moving);  //註冊滑鼠拖曳時的回呼事件  

	// 進入主迴圈
	glutMainLoop();
	
	return 0;
}

float clamp(float v,float min,float max) {
	if (v >= max){
		return max;
	} else if (v <= min) {
		return min;
	} else {
		return v;
	}
}
