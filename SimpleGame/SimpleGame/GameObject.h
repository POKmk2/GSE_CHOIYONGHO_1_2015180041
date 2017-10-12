#pragma once
#include <stdlib.h>
#include "stdafx.h"
class GameObject
{
	float PositionX;
	float PositionY;
	float PositionZ;
	float size;
	float color[4];
	float xVector;
	float yVector;
public:
	GameObject(float fx, float fy, float fz, float fsize)
	{
		PositionX = fx;
		PositionY = fy;
		PositionZ = fz;
		size = fsize;
		for (int i = 0; i < 4; ++i)
			color[i] = (rand() % 255) / 255.0;
		xVector = (rand() % 100) / 10.0;
		yVector = (rand() % 100) / 10.0;
	}
	virtual ~GameObject();
	void Render();

	float getX() { return PositionX; }
	float getY() { return PositionY; }
	float getZ() { return PositionZ; }
	float getSize() { return size; }
	float* getColor() { return color; }

	void setX(float fx) { PositionX = fx; }
	void setY(float fy) { PositionY = fy; }
	void setZ(float fz) { PositionZ = fz; }
	void setSize(float fsize) { size = fsize; }
	void setColor(float* fcolor);

	void draw();
	void update(float time);
};

