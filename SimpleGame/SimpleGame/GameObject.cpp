#include "stdafx.h"
#include "GameObject.h"


GameObject::~GameObject()
{
}

void GameObject::Render()
{

}

void GameObject::setColor(float * fcolor)
{
	for (int i = 0; i < 4; ++i)
	{
		color[i] = fcolor[i];
	}
}

void GameObject::update(float time)
{
	PositionX = PositionX += xVector*time;
	if (PositionX > 250 || PositionX < 250)
		xVector = -xVector;
	PositionY = PositionY += yVector*time;
	if (PositionY > 250 || PositionY < 250)
		yVector = -yVector;
}
