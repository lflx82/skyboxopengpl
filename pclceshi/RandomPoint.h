#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>
#include <Eigen/Dense> 

#include"render/Renderable.h"

#include "utils/shader.h"

#include <iostream>
#include "./utils/Arcball.h"

#include<vector>
#include "opencv2/opencv.hpp"

using namespace ExampleLib;
using namespace std;


class RandomPoint
{
public:
	RandomPoint();
	~RandomPoint();

	int getWindowWidth();
	int getWindowHeight();

	void  setWindow(int width, int height);
	void init2();
	void Skybox(float x, float y, float z, float width, float height, float length);
	void draw2(glm::mat4 model);
private:
	GLuint quadVAOId[6];
	GLuint quadVBOId[6];
	GLuint quadVBOId2[6];

	/*
	GLuint quadVAO3Id;
	GLuint quadVBO3Id;
	GLuint quadVBO3Id2;
*/
	Shader* m_shader2;


	const int SHADOW_WIDTH = 1920, SHADOW_HEIGHT = 1080;


	int   m_npointSize[6];
	GLfloat* m_quadVertices[6];
	GLfloat* m_quadVerticesTex[6];

public:
	float  m_foy;
	float  m_rotationX;
	float  m_rotationZ;

	float  m_fmax[3];
	float  m_fmin[3];

	glm::mat4 m_modelMatrix;
	glm::mat4 m_view;
	glm::mat4 m_projection;

	glm::vec3 m_eyepos;
	glm::vec3 m_at;
	int win_width, win_height;
	GLuint m_mapId;
	float  m_touming;
	GLuint m_ImgId[6];
};