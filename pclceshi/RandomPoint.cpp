#include "pch.h"
#include "RandomPoint.h"
#define PI  3.1415926

RandomPoint::RandomPoint()
{
	m_foy = 60;
	m_rotationX=0;
	m_rotationZ = 90;
    m_eyepos = glm::vec3(0, 0, 0);

}


RandomPoint::~RandomPoint()
{

	delete m_shader2;
	m_shader2 = NULL;
	
	for(int i=0;i<6;i++)
	{
		if (m_quadVertices[i] != NULL)
		{
			delete[] m_quadVertices[i];
			m_quadVertices[i] = NULL;
		}
		if (m_quadVerticesTex[i] != NULL)
		{
			delete[] m_quadVerticesTex[i];
			m_quadVerticesTex[i] = NULL;
		}
	}


}



void RandomPoint::Skybox(float x, float y, float z, float width, float height, float length)
{
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;

	glm::vec3 a0 = glm::vec3(x, y, z + length);
	glm::vec3 a1 = glm::vec3(x, y + height, z + length);
	glm::vec3 a2 = glm::vec3(x + width, y + height, z + length);
	glm::vec3 a3 = glm::vec3(x + width, y, z + length);

	glm::vec2 tex0[6];
	glm::vec2 tex1[6];
	glm::vec2 tex2[6];
	glm::vec2 tex3[6];
	for (int i = 0; i < 6; i++)
	{
		if (i == 0 || i == 1)
		{
			tex0[i] = glm::vec2(1.0f, 1.0f);
			tex1[i] = glm::vec2(1.0f, 0.0f);
			tex2[i] = glm::vec2(0.0f, 0.0f);
			tex3[i] = glm::vec2(0.0f, 1.0f);
		}
		if (i == 2)
		{
			tex0[i] = glm::vec2(1.0f, 0.0f);
			tex1[i] = glm::vec2(0.0f, 0.0f);
			tex2[i] = glm::vec2(0.0f, 1.0f);
			tex3[i] = glm::vec2(1.0f, 1.0f);
		}
		if (i == 3)
		{
			tex0[i] = glm::vec2(0.0f, 1.0f);
			tex1[i] = glm::vec2(1.0f, 1.0f);
			tex2[i] = glm::vec2(1.0f, 0.0f);
			tex3[i] = glm::vec2(0.0f, 0.0f);
		}
		if (i == 4 || i == 5)
		{
			tex0[i] = glm::vec2(0.0f, 1.0f);
			tex1[i] = glm::vec2(1.0f, 1.0f);
			tex2[i] = glm::vec2(1.0f, 0.0f);
			tex3[i] = glm::vec2(0.0f, 0.0f);
		}
	}
	for (int i = 0; i < 6; i++)
	{
		m_npointSize[i] = 6;
		m_quadVertices[i] = new GLfloat[m_npointSize[i] * 3];
		m_quadVerticesTex[i] = new GLfloat[m_npointSize[i] * 2];
		if (i == 0)  // Draw Front side
		{
			a0 = glm::vec3(x, y, z + length);
			a1 = glm::vec3(x, y + height, z + length);
			a2 = glm::vec3(x + width, y + height, z + length);
			a3 = glm::vec3(x + width, y, z + length);
		}
		if (i == 1)  // Draw Back side
		{
			a0 = glm::vec3(x + width, y, z);
			a1 = glm::vec3(x + width, y + height, z);
			a2 = glm::vec3(x, y + height, z);
			a3 = glm::vec3(x, y, z);
		}
		if (i == 2)  // Draw Left side
		{
			a0 = glm::vec3(x, y + height, z);
			a1 = glm::vec3(x, y + height, z + length);
			a2 = glm::vec3(x, y, z + length);
			a3 = glm::vec3(x, y, z);
		}
		if (i == 3)  //Draw Right side
		{
			a0 = glm::vec3(x + width, y, z);
			a1 = glm::vec3(x + width, y, z + length);
			a2 = glm::vec3(x + width, y + height, z + length);
			a3 = glm::vec3(x + width, y + height, z);
		}
		// Draw Up side
		if (i == 4)
		{
			a0 = glm::vec3(x + width, y + height, z);
			a1 = glm::vec3(x + width, y + height, z + length);
			a2 = glm::vec3(x, y + height, z + length);
			a3 = glm::vec3(x, y + height, z);
		}
		// Draw Down side
		if (i == 5)
		{
			a0 = glm::vec3(x, y, z);
			a1 = glm::vec3(x, y, z + length);
			a2 = glm::vec3(x + width, y, z + length);
			a3 = glm::vec3(x + width, y, z);
		}
		for (int j = 0; j < m_npointSize[i]; j++)
		{
			glm::vec3 b0 = a0;
			glm::vec2 texb = tex0[i];
			if (j == 0)
			{
				b0 = a0;
				texb = tex0[i];
			}
			if (j == 1)
			{
				b0 = a1;
				texb = tex1[i];
			}
			if (j == 2)
			{
				b0 = a2;
				texb = tex2[i];
			}
			if (j == 3)
			{
				b0 = a0;
				texb = tex0[i];
			}
			if (j == 4)
			{
				b0 = a2;
				texb = tex2[i];
			}
			if (j == 5)
			{
				b0 = a3;
				texb = tex3[i];
			}
			m_quadVertices[i][j * 3 + 0] = b0.x;
			m_quadVertices[i][j * 3 + 1] = b0.y;
			m_quadVertices[i][j * 3 + 2] = b0.z;

			m_quadVerticesTex[i][j * 2 + 0] = texb.x;
			m_quadVerticesTex[i][j * 2 + 1] = texb.y;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		glGenVertexArrays(1, &quadVAOId[i]);
		// Step2: ��������VBO ���� ��������
		glGenBuffers(1, &quadVBOId[i]);
		glGenBuffers(1, &quadVBOId2[i]);

		glBindVertexArray(quadVAOId[i]);

		glBindBuffer(GL_ARRAY_BUFFER, quadVBOId[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_npointSize[i] * 3, m_quadVertices[i], GL_STATIC_DRAW);
		// Step3: ָ��������ʽ  �����ö�������
		// ����λ������	
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, quadVBOId2[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*m_npointSize[i] * 2, m_quadVerticesTex[i], GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}


void RandomPoint::init2()
{
	//SetBall(10, 0, 0, 0);
	Skybox(0, 0, 0, 10, 10, 10);
	m_shader2 = new Shader("shader/randompointvvv2.vertex", "shader/randompointvvv2.frag");

	glGenTextures(1, &m_mapId);
	cv::Mat frameALL = cv::imread("pano/00000-pano.jpg");
	int nVideoWALL = frameALL.cols;
	int nVideoHALL = frameALL.rows;
	cv::cvtColor(frameALL, frameALL, cv::COLOR_BGR2RGB);
	glBindTexture(GL_TEXTURE_2D, m_mapId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nVideoWALL, nVideoHALL, 0, GL_RGB, GL_UNSIGNED_BYTE, frameALL.data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	string str[6];
	str[0] = "texture/front.jpg";
	str[1] = "texture/back.jpg";
	str[2] = "texture/left.jpg";
	str[3] = "texture/right.jpg";
	str[4] = "texture/up.jpg";
	str[5] = "texture/down.jpg";
	for(int i=0;i<6;i++)
	{
		glGenTextures(1, &m_ImgId[i]);
		cv::Mat frameALL = cv::imread(str[i]);
		int nVideoWALL = frameALL.cols;
		int nVideoHALL = frameALL.rows;
		cv::cvtColor(frameALL, frameALL, cv::COLOR_BGR2RGB);
		glBindTexture(GL_TEXTURE_2D, m_ImgId[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nVideoWALL, nVideoHALL, 0, GL_RGB, GL_UNSIGNED_BYTE, frameALL.data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

}


void RandomPoint::draw2(glm::mat4 model)
{
	m_modelMatrix = model;
	glm::mat4 projection = glm::perspective(glm::radians(GLfloat(m_foy)), float(win_width) / win_height, 0.1f, 600.0f); // ͶӰ����
	m_projection = projection;

	//glm::vec3 up = glm::vec3(0, 0, 1);
	glm::vec3 up = glm::vec3(0, 1, 0);

	m_rotationZ = fmax(m_rotationZ, 0.2);
	m_rotationZ = fmin(m_rotationZ, 179.8);

	glm::vec3 at1= glm::vec3(0, 0, 1);
	glm::vec3 at2 = glm::vec3(0, 0, 1);
	float fai = m_rotationX * PI / 180.0;
	float stai = m_rotationZ * PI / 180.0;
	
	at1[0] = (float)(2 * sin(stai) * cos(fai));
	at1[2] = (float)(2 * sin(stai) * sin(fai));
	at1[1] = (float)(2 * cos(stai));


	glm::vec4 glmv4 = glm::vec4(0, 0, 0, 1.0f);

	m_eyepos.x = glmv4.x;
	m_eyepos.y = glmv4.y;
	m_eyepos.z = glmv4.z;

	at2 = m_eyepos + at1;
	glm::mat4 view = glm::lookAt(m_eyepos, at2, up);

	m_view = view;

	m_shader2->use();
	glUniformMatrix4fv(glGetUniformLocation(m_shader2->programId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader2->programId, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(m_shader2->programId, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1f(glGetUniformLocation(m_shader2->programId, "w"), m_touming);

	for (int i = 0; i <6; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_ImgId[i]);
		glUniform1i(glGetUniformLocation(m_shader2->programId, "texture"), 0);
		glBindVertexArray(quadVAOId[i]);
		glDrawArrays(GL_TRIANGLES, 0, m_npointSize[i]);
		glBindVertexArray(0);
	}

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

}
void  RandomPoint::setWindow(int width, int height)
{
	this->win_width = width;
	this->win_height = height;
}

int  RandomPoint::getWindowWidth()
{
	return this->win_width;
}

int  RandomPoint::getWindowHeight()
{
	return this->win_height;
}
