#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(float fx, float fy, float fz, int ty, int te)
{
	PositionX = fx;
	PositionY = fy;
	PositionZ = fz;
	type = ty;
	team = te;
	switch (type)
	{
	case OBJECT_CHARACTER:
		size = 20;
		life = 10;
		lifetime = 500;
		speed = 300.0f;
		while (xVector*yVector == 0)
		{
			xVector = rand() % 10 - 5;
			yVector = rand() % 10 - 5;
		}
		Normalize(xVector, yVector);
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 1.0f;
		color[3] = 1.0f;
		level = 0.2;
		break;
	case OBJECT_BUILDING:
		size = 50;
		life = 250;
		lifetime = 1000;
		speed = 0;
		xVector = 0;
		yVector = 0;
		color[0] = 1.0f;
		color[1] = 1.0f;
		color[2] = 0.0f;
		color[3] = 1.0f;
		level = 0.1;
		break;
	case OBJECT_BULLET:
		life = 20;
		lifetime = 100;
		speed = 200.0f;
		size = 10;
		while (xVector*yVector == 0)
		{
			xVector = rand() % 10 - 5;
			yVector = rand() % 10 - 5;
		}
		Normalize(xVector, yVector);
		color[0] = 1.0f;
		color[1] = 0.0f;
		color[2] = 0.0f;
		color[3] = 1.0f;
		level = 0.3;
		break;
	case OBJECT_ARROW:
		size = 2;
		speed = 100.0f;
		life = 10;
		lifetime = 100;
		while (xVector*yVector == 0)
		{
			xVector = rand() % 10 - 5;
			yVector = rand() % 10 - 5;
		}
		Normalize(xVector, yVector);
		color[0] = 0.0f;
		color[1] = 1.0f;
		color[2] = 0.0f;
		color[3] = 1.0f;
		level = 0.3;
	}
}

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

void GameObject::update(float time)//버그 수정
{
	if (PositionX > WIDTH / 2 - 5 - size / 2)
	{
		xVector = -xVector;
		PositionX = WIDTH / 2 - size/2-5;
	}
	if (PositionX < -(WIDTH / 2) + 5 + size / 2)
	{
		xVector = -xVector;
		PositionX = -WIDTH / 2 + size / 2+5;
	}
	PositionX += xVector*time*speed;
	if (PositionY > HEIGHT / 2 - 5 - size / 2)
	{
		PositionY = HEIGHT / 2 - size / 2-5;
		yVector = -yVector;
	}
	if (PositionY < -(HEIGHT / 2) + 5 + size / 2)
	{
		PositionY = -HEIGHT / 2 + size / 2+5;
		yVector = -yVector;
	}
	PositionY += yVector*time*speed;
	minusLifeTime(time);
}

bool GameObject::collisionCheck(GameObject * other)
{
	if (team == other->getTeam())
		return false;
	if (((PositionX + size / 2) > (other->PositionX - other->size / 2))
		&& ((PositionX - size / 2) < (other->PositionX + other->size / 2))
		&& ((PositionY - size / 2) < (other->PositionY + other->size / 2))
		&& ((PositionY + size / 2) > (other->PositionY - other->size / 2))
		)
	{
		return true;
	}
	return false;
}

int GameObject::lifeDown(int i)
{
	life -= i;
	return life;
}

void GameObject::SetCollision(bool b)
{
	collide = b;
}

bool GameObject::GetCollision()
{
	return collide;
}

float GameObject::minusLifeTime(float t)
{
	return lifetime -= t;
}
