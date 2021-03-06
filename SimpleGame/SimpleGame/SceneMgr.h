#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "Sound.h"
class SceneMgr
{
	GameObject* BuildingArray[MAX_BUILDING_COUNT];
	int BuildingArraySize = 0;
	GameObject* CharacterArray[MAX_CHARACTER_COUNT];
	int CharacterArraySize = 0;
	int team1ArraySize = 0;
	int team2ArraySize = 0;
	GameObject* BulletArray[MAX_BULLET_COUNT];
	float particleTime[MAX_BULLET_COUNT] = { 0, };
	int BulletArraySize = 0;
	GameObject* ArrowArray[2][MAX_ARROW_COUNT];
	int ArrowArraySize[2] = { 0, };
	float ArrowArrayTime[MAX_CHARACTER_COUNT] = { 0, };
	float bulletTime[MAX_BUILDING_COUNT] = { 0, };
	Renderer *g_Renderer = NULL;
	int BuildingID1;
	int BuildingID2;
	int AnimationID1;
	float AnimationTimer[MAX_CHARACTER_COUNT];
	int AnimationID2;
	int particleID1;
	int particleID2;
	float spawnTime;
	float delay = 0;
	Sound* m_sound;
	int soundBG;
public:
	SceneMgr();
	~SceneMgr();
	GameObject* getBuildingObject(int index);
	GameObject* getCharacterObject(int index);
	GameObject* getBulletObject(int index);
	GameObject** getArrowObject(int character);
	int getBuildingArraySize();
	int getCharacterArraySize();
	int getBulletArraySize();
	int getArrowArraySize(int character);
	void addObject(float fx, float fy, float fz,int type, int team=-1); 
	void addArrow(float fx, float fy, float fz, int character, int team); 
	void update(float time);
	void collisionCheck();
	void Render();
	float getDelay();
	void setDelay(float f) { delay = f; }
};

