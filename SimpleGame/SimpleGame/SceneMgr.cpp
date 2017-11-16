#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr()
{
	g_Renderer = new Renderer(WIDTH, HEIGHT);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	BuildingID1 = g_Renderer->CreatePngTexture("./resource/image/buildingtexture.png");
	BuildingID2 = g_Renderer->CreatePngTexture("./resource/image/buildingtexture2.png");
	addObject(-150, 350, 0, OBJECT_BUILDING,0);
	addObject(150, 350, 0, OBJECT_BUILDING, 0);
	addObject(0, 350, 0, OBJECT_BUILDING, 0);
	addObject(-150, -350, 0, OBJECT_BUILDING, 1);
	addObject(150, -350, 0, OBJECT_BUILDING, 1);
	addObject(0, -350, 0, OBJECT_BUILDING, 1);
}


SceneMgr::~SceneMgr()
{
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		for (int j = 0; j<ArrowArraySize[i]; ++j)
			delete ArrowArray[i][j];
		delete CharacterArray[i];
	}
	for (int i = 0; i < BuildingArraySize; ++i)
	{
		delete BuildingArray[i];
	}
	for (int i = 0; i < BulletArraySize; ++i)
	{
		delete BulletArray[i];
	}
	
	delete g_Renderer;
}

GameObject * SceneMgr::getBuildingObject(int index)
{
	if (index > BuildingArraySize)
		return nullptr;
	return (BuildingArray[index]);
}

GameObject * SceneMgr::getCharacterObject(int index)
{
	if (index > CharacterArraySize)
		return nullptr;
	return (CharacterArray[index]);
}

GameObject * SceneMgr::getBulletObject(int index)
{
	if (index > BulletArraySize)
		return nullptr;
	return (BulletArray[index]);
}

GameObject ** SceneMgr::getArrowObject(int character)
{
	if (character > CharacterArraySize)
		return nullptr;
	return (ArrowArray[character]);
}

int SceneMgr::getBuildingArraySize()
{
	return BuildingArraySize;
}

int SceneMgr::getCharacterArraySize()
{
	return CharacterArraySize;
}

int SceneMgr::getBulletArraySize()
{
	return BulletArraySize;
}

int SceneMgr::getArrowArraySize(int character)
{
	return ArrowArraySize[character];
}


void SceneMgr::addObject(float fx, float fy, float fz, int type, int team)
{
	switch (type)
	{
	case OBJECT_BUILDING:
		if (BuildingArraySize == MAX_BUILDING_COUNT)
		{
			printf("ÀÌ¹Ì ²Ë Ã¡½À´Ï´Ù\n");
			return;
		}
		BuildingArray[BuildingArraySize] = new GameObject(fx, fy, fz, type, team);
		BuildingArraySize++;
		break;
	case OBJECT_BULLET:
		if (BulletArraySize == MAX_BULLET_COUNT)
		{
			printf("ÀÌ¹Ì ²Ë Ã¡½À´Ï´Ù\n");
			return;
		}
		BulletArray[BulletArraySize] = new GameObject(fx, fy, fz, type, team);
		BulletArraySize++;
		break;
	case OBJECT_CHARACTER:
		if (CharacterArraySize == MAX_CHARACTER_COUNT)
		{
			printf("ÀÌ¹Ì ²Ë Ã¡½À´Ï´Ù\n");
			return;
		}
		if (team1ArraySize == MAX_TEAM1_COUNT)
		{
			printf("ÀÌ¹Ì ²Ë Ã¡½À´Ï´Ù\n");
			return;
		}
		if (team2ArraySize == MAX_TEAM2_COUNT)
		{
			printf("ÀÌ¹Ì ²Ë Ã¡½À´Ï´Ù\n");
			return;
		}
		CharacterArray[CharacterArraySize] = new GameObject(fx, fy, fz, type, team);
		ArrowArraySize[CharacterArraySize] = 0;
		if (team == 0)
			team1ArraySize++;
		else
			team2ArraySize++;
		CharacterArraySize++;
		break;
	}

}

void SceneMgr::addArrow(float fx, float fy, float fz, int character, int team)
{
	if (ArrowArraySize[character] == MAX_ARROW_COUNT)
	{
		printf("ÀÌ¹Ì ²Ë Ã¡½À´Ï´Ù\n");
		return;
	}
	ArrowArray[character][ArrowArraySize[character]] = new GameObject(fx, fy, fz, OBJECT_ARROW, team);
	ArrowArraySize[character]++;
}

void SceneMgr::update(float time)
{
	for (int i = 0; i < BuildingArraySize; ++i)
	{
		BuildingArray[i]->update(time);
	}
	for (int i = 0; i < BulletArraySize; ++i)
	{
		BulletArray[i]->update(time);
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		CharacterArray[i]->update(time);
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			ArrowArray[i][j]->update(time);
		}
		ArrowArrayTime[i] += time;
		if (ArrowArrayTime[i] > 0.5f)
		{
			addArrow(CharacterArray[i]->getX(), CharacterArray[i]->getY(), CharacterArray[i]->getZ(), i, CharacterArray[i]->getTeam());
			ArrowArrayTime[i] -= 0.5f;
		}
	}
	for (int i = 0; i < BuildingArraySize; ++i)
	{
		bulletTime[i] += time;
		if ((bulletTime[i] > 10.0) && (BuildingArraySize != 0))
		{
			addObject(BuildingArray[i]->getX(), BuildingArray[i]->getY(), BuildingArray[i]->getZ(), OBJECT_BULLET, BuildingArray[i]->getTeam());
			bulletTime[i] -= 10.0f;
		}
	}
	/*if (ObjectArray[i]->minusLifeTime(time)<0)
	{
		delete ObjectArray[i];
		size--;
		for (int j = i; j < size; ++j)
		{
			ObjectArray[j] = ObjectArray[j + 1];
		}
		--i;
	}*/
	collisionCheck();
}

void SceneMgr::collisionCheck()
{
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		for (int j = 0; j < BuildingArraySize; ++j)
		{
			if (CharacterArray[i]->collisionCheck(BuildingArray[j]))
			{
				CharacterArray[i]->SetCollision(true);
				BuildingArray[j]->lifeDown(CharacterArray[i]->getLife());
			}
		}
		for (int j = 0; j < BulletArraySize; ++j)
		{
			if (CharacterArray[i]->collisionCheck(BulletArray[j]))
			{
				CharacterArray[i]->lifeDown(BulletArray[j]->getLife());
				BulletArray[j]->SetCollision(true);
			}
		}
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			if (CharacterArray[i]->collisionCheck(ArrowArray[i][j])) //ÀÚ½ÅÀÌ ½ð È­»ì È®ÀÎ
			{
				CharacterArray[i]->lifeDown(ArrowArray[i][j]->getLife());
				ArrowArray[i][j]->SetCollision(true);
			}
			for (int k = 0; k < BuildingArraySize; ++k)
			{
				if (ArrowArray[i][j]->collisionCheck(BuildingArray[k]))
				{
					BuildingArray[k]->lifeDown(ArrowArray[i][j]->getLife());
					ArrowArray[i][j]->SetCollision(true);
				}
			}
		}
	}
	for (int i = 0; i < BuildingArraySize; ++i)
	{
		if (BuildingArray[i]->getLife() <= 0)
		{
			delete BuildingArray[i];
			BuildingArraySize--;
			for (int j = i; j < BuildingArraySize; ++j)
			{
				BuildingArray[j] = BuildingArray[j + 1];
			}
			i--;
			continue;
		}
		if (BuildingArray[i]->getLifeTime() < 0)
		{
			delete BuildingArray[i];
			BuildingArraySize--;
			for (int j = i; j < BuildingArraySize; ++j)
			{
				BuildingArray[j] = BuildingArray[j + 1];
			}
			i--;
			continue;
		}
		BuildingArray[i]->SetCollision(false);
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		if (CharacterArray[i]->GetCollision() == true)
		{
			for (int j = 0; j < ArrowArraySize[i]; ++j)
			{
				delete ArrowArray[i][j];
			}
			ArrowArraySize[i] = 0;
			CharacterArraySize--;
			if (CharacterArray[i]->getTeam() == 0)
				team1ArraySize--;
			else
				team2ArraySize--;
			delete CharacterArray[i];
			for (int j = i; j < CharacterArraySize; ++j)
			{
				CharacterArray[j] = CharacterArray[j + 1];
				ArrowArraySize[j] = ArrowArraySize[j + 1];
				for (int k = 0; k < ArrowArraySize[j]; ++k)
				{
					ArrowArray[j][k] = ArrowArray[j + 1][k];
				}
			}
			i--;
			continue;
		}
		if (CharacterArray[i]->getLife() <= 0)
		{
			for (int j = 0; j < ArrowArraySize[i]; ++j)
			{
				delete ArrowArray[i][j];
			}
			ArrowArraySize[i] = 0;
			CharacterArraySize--;
			if (CharacterArray[i]->getTeam() == 0)
				team1ArraySize--;
			else
				team2ArraySize--;
			delete CharacterArray[i];
			for (int j = i; j < CharacterArraySize; ++j)
			{
				CharacterArray[j] = CharacterArray[j + 1];
				ArrowArraySize[j] = ArrowArraySize[j + 1];
				for (int k = 0; k < ArrowArraySize[j]; ++k)
				{
					ArrowArray[j][k] = ArrowArray[j + 1][k];
				}
			}
			i--;
			continue;
		}
		if (CharacterArray[i]->getLifeTime() < 0)
		{
			for (int j = 0; j < ArrowArraySize[i]; ++j)
			{
				delete ArrowArray[i][j];
			}
			ArrowArraySize[i] = 0;
			CharacterArraySize--;
			if (CharacterArray[i]->getTeam() == 0)
				team1ArraySize--;
			else
				team2ArraySize--;
			delete CharacterArray[i];
			for (int j = i; j < CharacterArraySize; ++j)
			{
				CharacterArray[j] = CharacterArray[j + 1];
				ArrowArraySize[j] = ArrowArraySize[j + 1];
				for (int k = 0; k < ArrowArraySize[j]; ++k)
				{
					ArrowArray[j][k] = ArrowArray[j + 1][k];
				}
			}
			i--;
			continue;
		}
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			if (ArrowArray[i][j]->GetCollision() == true)
			{
				delete ArrowArray[i][j];
				ArrowArraySize[i]--;
				for (int k = j; k < ArrowArraySize[i]; ++k)
				{
					ArrowArray[i][k] = ArrowArray[i][k + 1];
				}
				j--;
				continue;
			}
			if (ArrowArray[i][j]->getLifeTime() < 0)
			{
				delete ArrowArray[i][j];
				ArrowArraySize[i]--;
				for (int k = j; k < ArrowArraySize[i]; ++k)
				{
					ArrowArray[i][k] = ArrowArray[i][k + 1];
				}
				j--;
				continue;
			}
		}
		CharacterArray[i]->SetCollision(false);
	}
	for (int i = 0; i < BulletArraySize; ++i)
	{
		if (BulletArray[i]->GetCollision() == true)
		{
			delete BulletArray[i];
			BulletArraySize--;
			for (int j = i; j < BulletArraySize; ++j)
			{
				BulletArray[j] = BulletArray[j + 1];
			}
			i--;
			continue;
		}
		if (BulletArray[i]->getLifeTime() < 0)
		{
			delete BulletArray[i];
			BulletArraySize--;
			for (int j = i; j < BulletArraySize; ++j)
			{
				BulletArray[j] = BulletArray[j + 1];
			}
			i--;
			continue;
		}
		BulletArray[i]->SetCollision(false);
	}
}

void SceneMgr::Render()
{
	GameObject* g;
	float* fColor;
	for (int i = 0; i < BuildingArraySize; ++i)
	{
		g = BuildingArray[i];
		//fColor = g->getColor();
		if (g->getTeam() == 0)
			g_Renderer->DrawTexturedRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0, 0, 0, 0, BuildingID1);
		else
			g_Renderer->DrawTexturedRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0, 0, 0, 0,  BuildingID2);
	}
	for (int i = 0; i < BulletArraySize; ++i)
	{
		g = BulletArray[i];
		//fColor = g->getColor();
		if (g->getTeam() == 0)
			g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 0, 0, 1);
		else
			g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0, 0, 1, 1);
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		g = CharacterArray[i];
		//fColor = g->getColor();
		if (g->getTeam() == 0)
			g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 0, 0, 1);
		else
			g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0, 0, 1, 1);
		
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			g = ArrowArray[i][j];
			//fColor = g->getColor();
			if (g->getTeam() == 0)
				g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0.5, 0.2, 0.7, 1);
			else
				g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 1, 0, 1);
		}
	}
}

