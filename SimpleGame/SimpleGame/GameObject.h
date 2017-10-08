#pragma once
#include <stdlib.h>
#include "stdafx.h"
class GameObject
{
	float x;
	float y;
	float z;
	float size;
	float color[4];
public:
	GameObject(float fx, float fy, float fz, float fsize)
	{
		x = fx;
		y = fy;
		z = fz;
		size = fsize;
		for (int i = 0; i < 4; ++i)
			color[i] = (rand() % 255) / 255.0;
	}
	virtual ~GameObject();
	void Render();

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getSize() { return size; }
	float* getColor() { return color; }

	void setX(float fx) { x = fx; }
	void setY(float fy) { y = fy; }
	void setZ(float fz) { z = fz; }
	void setSize(float fsize) { size = fsize; }
	void setColor(float* fcolor);

	void draw();
};

