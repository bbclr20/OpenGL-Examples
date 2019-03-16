#include "../Include/Common.h"
#include <math.h>

#define SIZE_1		1
#define SIZE_2		2
#define MENU_EXIT   3

using namespace std;

enum MyColor{Red,Green,Blue};
MyColor myColor = Red;

float aspect;			

float timer_interval = 16;

float rotateAngle = 0.0f;
float rotateSpeed = 30.0f;

float backgroundGray = 1.0f;

float teapot_posX = 0.0f;
float teapot_posY = 0.0f;
float teapot_size = 1.0f;

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

	glTranslatef(teapot_posX, teapot_posY, 0.0f); //將目前的矩陣乘上位移矩陣
	glRotatef(rotateAngle, 0.0f, 1.0f,0.0f);      //將目前的矩陣乘上旋轉矩陣
	
	if (myColor == Red) {
		glColor3b(125, 0, 0);					  //設定目前使用的顏色
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
	glutPostRedisplay();     //使程式於下次迴圈執行時更新畫面
	glutTimerFunc(timer_interval, My_Timer, val);
	rotateAngle += rotateSpeed * timer_interval * 0.001; //根據時間和速度計算並累積旋轉量
}

//鍵盤事件, 接收到鍵盤字元輸入時被呼叫
void My_Keyboard(unsigned char key, int x, int y) {
	if (key == 'W' || key == 'w') {     //當取得字元key為’W’或’w’時
		teapot_posY += 0.05f;          //茶壺位置的y軸位置值增加
	} else if (key == 'S' || key == 's') {
		teapot_posY -= 0.05f;
	} else if (key == 'A' || key == 'a') {
		teapot_posX -= 0.05f;
	} else if (key == 'D' || key == 'd') {
		teapot_posX += 0.05f;
	}
	glutPostRedisplay();
}

//鍵盤事件, 接收到鍵盤功能鍵或方向鍵時被呼叫
void My_SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) {         //當取得字鍵值key，對應鍵盤F1時
		myColor = Red;               //顏色列舉變數改為紅色
	} else if (key == GLUT_KEY_F2) {
		myColor = Green;
	} else if (key == GLUT_KEY_F3) {
		myColor = Blue;
	}
	glutPostRedisplay();
}

//選單事件, 當選單的條目被選取時被呼叫
void My_Menu(int id) {
	if (id == SIZE_1) {             //利用接收的值，判別被選擇的條目
		teapot_size = 1.0f;        //更改茶壺大小
	} else if (id == SIZE_2) {
		teapot_size = 2.0f;
	} else if (id == MENU_EXIT) {
		exit(0);
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {

	// 初始化GLUT,並創立一個視窗.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);

	glutCreateWindow("glut"); 

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//定義選單結構
	int menu_main = glutCreateMenu(My_Menu);  //建立空的選單
	int menu_entry = glutCreateMenu(My_Menu);

	glutSetMenu(menu_main);                    //設定目前指定的選單
	glutAddSubMenu("Teapot size", menu_entry); //將選單menu_entry，增設目前選單的子選單
	glutAddMenuEntry("Exit", MENU_EXIT);       //增設一個選項於目前的選單，並給予名稱與辨識用的整數值

	glutSetMenu(menu_entry);
	glutAddMenuEntry("1.0", SIZE_1);
	glutAddMenuEntry("2.0", SIZE_2);

	glutSetMenu(menu_main);
	glutAttachMenu(GLUT_RIGHT_BUTTON);         //將目前選單設為滑鼠右鍵按下時觸發彈出
	
	//註冊GLUT回呼事件
	glutDisplayFunc(My_Display);
	glutReshapeFunc(My_Reshape);
	glutKeyboardFunc(My_Keyboard);   //註冊當鍵盤字元鍵輸入時的回呼事件
	glutSpecialFunc(My_SpecialKeys); //註冊當鍵盤功能鍵輸入時的回呼事件
	glutTimerFunc(timer_interval, My_Timer, 0); //註冊當程式經過指定時間時的回呼事件                
	////////////////////
	
	// 進入主迴圈
	glutMainLoop();
	
	return 0;
}

float clamp(float v,float min,float max) {
	if (v >= max) {
		return max;
	} else if (v <= min) {
		return min;
	} else {
		return v;
	}
}
