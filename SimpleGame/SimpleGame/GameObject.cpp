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
