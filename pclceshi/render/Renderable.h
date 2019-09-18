#pragma once
#include <GLM/glm.hpp>

class Renderable 
{
public:
	Renderable();
	virtual ~Renderable() = 0;

	void     setWindow(int width, int height);
	virtual  void init();
	virtual  void draw(glm::mat4 model);
	virtual  void selectTriangle(int x, int y);
	virtual  void reInitData();

	int getWindowWidth();
	int getWindowHeight();
   private:
	
	int win_width, win_height;
};