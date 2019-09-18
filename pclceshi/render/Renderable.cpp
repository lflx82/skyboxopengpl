

// TODO: 添加要在此处预编译的标头


#include"Renderable.h"
Renderable::Renderable()
{

}

Renderable::~Renderable()
{

}

void Renderable::setWindow(int width, int height)
{
	this->win_width = width;
	this->win_height = height;
}

int Renderable::getWindowWidth() 
{
	return this->win_width;
}

int Renderable::getWindowHeight()
{
	return this->win_height;
}

void Renderable::init()
{

}

void Renderable::drawobj(glm::mat4 model)
{

}

void Renderable::selectTriangle(int x, int y)
{

}

void Renderable::reInitData() 
{

}
