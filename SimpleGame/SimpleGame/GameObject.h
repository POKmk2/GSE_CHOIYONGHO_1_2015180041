#pragma once
#include "stdafx.h"

class GameObject
{
	float PositionX;
	float PositionY;
	float PositionZ;
	float size;
	float color[4];
	float xVector=0;
	float yVector=0;
	float speed = 0;
	int life = 1000;
	float lifetime = 10.0f;
	bool collide = false;
	int type = 0;
	int team = 0;
	float level = 1;
public:
	GameObject(float fx, float fy, float fz, int type, int team=-1);
	virtual ~GameObject();
	void Render();

	float getX() { return PositionX; }
	float getY() { return PositionY; }
	float getZ() { return PositionZ; }
	float getSize() { return size; }
	float* getColor() { return color; }
	int getLife() { return life; }
	int getTeam() { return team; }
	float getLifeTime() { return lifetime; }
	float getLevel() { return level; }
	float getVectorX() { return xVector; }
	float getVectorY() { return yVector; }

	void setX(float fx) { PositionX = fx; }
	void setY(float fy) { PositionY = fy; }
	void setZ(float fz) { PositionZ = fz; }
	void setSize(float fsize) { size = fsize; }
	void setColor(float* fcolor);
	void setLife(int l) {life = l;}
	void setLifeTime(float f) { lifetime = f; }
	void setTeam(int t) { team = t; }

	void draw();
	void update(float time);
	bool collisionCheck(GameObject* other);
	int lifeDown(int i);
	void SetCollision(bool b);
	bool GetCollision();
	float minusLifeTime(float t);
};

