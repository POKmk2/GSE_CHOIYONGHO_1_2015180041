#pragma once
class GameObject
{
	float x;
	float y;
	float z;
	float size;
public:
	GameObject(float fx, float fy, float fz, float fsize)
	{
		x = fx;
		y = fy;
		z = fz;
		size = fsize;
	}
	virtual ~GameObject();
	void Render();
};

