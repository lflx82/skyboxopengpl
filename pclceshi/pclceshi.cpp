// pclceshi.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <GLEW/glew.h>
#include <GL/freeglut.h>
#include <GL/glui.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include"RandomPoint.h"
#include "opencv2/opencv.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/calib3d/calib3d.hpp" 
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/features2d/features2d.hpp"

#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/PCLPointCloud2.h>

GLUI_Spinner    *spinnerRotDX;

double  g_dTouming=0.5;

int     g_win_width = 1600;
int     g_win_height = 1060;
int     g_main_window;

int     last_x, last_y;
float   rotationX = 0.0,rotationY = 0.0;
double  g_fovy = 60;
int     g_gButton;
double  g_foymin = 10.0;
double  g_foymax = 90.0;


RandomPoint*  g_randomPoint = NULL;

int g_num=0;
int g_nummax = 0;

using  namespace cv;
using namespace pcl;

void  mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		last_x = x;
		last_y = y;
		g_gButton = GLUT_LEFT_BUTTON;	
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		g_gButton = GLUT_MIDDLE_BUTTON;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	//	g_randomPoint->selectTriangle(x, y);
		//g_randomPoint->selectPoint3D(x, y);
     	g_gButton = GLUT_RIGHT_BUTTON;
	}
	return;
}

void mouseWheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		g_randomPoint->m_foy = g_randomPoint->m_foy - 1;
	}
	else if (dir < 0)
	{
		g_randomPoint->m_foy = g_randomPoint->m_foy +1;
	}
	g_randomPoint->m_foy = fmax(g_foymin, fmin(g_foymax, g_randomPoint->m_foy));

	glutPostRedisplay();
	return;
}

void mouseMove(int x, int y)
{
	if (g_gButton == GLUT_LEFT_BUTTON)
	{
		g_randomPoint->m_rotationX = g_randomPoint->m_rotationX +(x - last_x);
		g_randomPoint->m_rotationZ = g_randomPoint->m_rotationZ + (y - last_y);
		last_x = x;
		last_y = y;
		glutPostRedisplay();
	}
}
// Keyboard handling:
//
void specialKeys(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		g_num++;
		if (g_num == g_nummax)
		{
			g_num = 0;
		}
	//	g_randomPoint->m_nPanoramaAllnum = g_num;
	//	g_randomPoint->UpData();
		glutPostRedisplay();
	}
	else if (key == 's')
	{
	}
	else if (key == 'a')
	{
	//	g_randomPoint->UpData();
		glutPostRedisplay();
	}
	else if (key == 'd')
	{

	}
	else if (key == 27)
	{
		glutDestroyWindow(g_main_window);
	}
	// Refresh the Window
	glutPostRedisplay();
}
void myGlutMotion(int x, int y)
{
	glutPostRedisplay();
}
// If the veiwport is resized:
void changeSize(int w, int h)
{
	g_win_width = w;
	g_win_height = h;
	g_randomPoint->setWindow(g_win_width, g_win_height);
	glViewport(0, 0, g_win_width, g_win_height);

}


void init()
{
	g_randomPoint = new RandomPoint();
	g_randomPoint->setWindow(g_win_width, g_win_height);
	g_randomPoint->init2();
	
}



void renderScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, g_win_width, (GLsizei)g_win_height);
	glm::mat4 modelMatrix = glm::mat4();
	//g_randomPoint->draw(modelMatrix);
	g_randomPoint->draw2(modelMatrix);
	glPopMatrix();

	glutSwapBuffers();
}

void control_cb(int control)
{
	float Rotdx = spinnerRotDX->get_float_val();
/*	float Rotdy = spinnerRotDY->get_float_val();
	float Rotdz = spinnerRotDZ->get_float_val();
	float Trandx = spinnerTranDX->get_float_val();
	float Trandy = spinnerTranDY->get_float_val();
	float Trandz = spinnerTranDZ->get_float_val();
	*/
	g_dTouming = Rotdx;
	g_randomPoint->m_touming = g_dTouming;
	//updata();
	glutPostRedisplay();

	return;
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(g_win_width, g_win_height);
	//g_w = g_win_width;
	//g_h = g_win_height;

	glutInitWindowPosition(0.0, 0.0);
	g_main_window = glutCreateWindow("全景正方体浏览");

	
	float version = GLUI_Master.get_version();
	GLUI *glui_window = GLUI_Master.create_glui_subwindow(g_main_window,GLUI_SUBWINDOW_RIGHT);
	glui_window->add_statictext("UI");

	spinnerRotDX = new GLUI_Spinner(glui_window, "Rotdx:", GLUI_SPINNER_FLOAT, 1, control_cb);
	spinnerRotDX->set_float_limits(0.0, +1.0);
	g_dTouming = 0.5;
	
	spinnerRotDX->set_float_val(g_dTouming);


	glui_window->set_main_gfx_window(g_main_window);
	

	// 初始化GLEW 获取OpenGL函数
	GLenum status = glewInit();
	if (status != GLEW_OK)
	{
		std::cout << "Error::GLEW glew version:" << glewGetString(GLEW_VERSION)
			<< " error string:" << glewGetErrorString(status) << std::endl;
		return 0;
	}

	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);

	glutKeyboardFunc(specialKeys);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutMouseWheelFunc(mouseWheel);
	init();

	g_randomPoint->m_touming = g_dTouming;
	glutMainLoop();
	
	return 0;
}