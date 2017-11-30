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
	//배경 로드하기
	//텍스쳐 에니메이션 로드하기
	AnimationID1 = g_Renderer->CreatePngTexture("./resource/image/attack1.png");
	AnimationID2 = g_Renderer->CreatePngTexture("./resource/image/attack2.png");
	particleID1 = g_Renderer->CreatePngTexture("./resource/image/particle1.png");
	//particleID2 = g_Renderer->CreatePngTexture("./resource/image/particle2.png");
	addObject(-150, 350, 0, OBJECT_BUILDING,0);
	addObject(150, 350, 0, OBJECT_BUILDING, 0);
	addObject(0, 350, 0, OBJECT_BUILDING, 0);
	addObject(-150, -350, 0, OBJECT_BUILDING, 1);
	addObject(150, -350, 0, OBJECT_BUILDING, 1);
	addObject(0, -350, 0, OBJECT_BUILDING, 1);
	spawnTime = 0;
	delay = 7;
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
			printf("이미 꽉 찼습니다\n");
			return;
		}
		BuildingArray[BuildingArraySize] = new GameObject(fx, fy, fz, type, team);
		BuildingArraySize++;
		break;
	case OBJECT_BULLET:
		if (BulletArraySize == MAX_BULLET_COUNT)
		{
			printf("이미 꽉 찼습니다\n");
			return;
		}
		BulletArray[BulletArraySize] = new GameObject(fx, fy, fz, type, team);
		particleTime[BulletArraySize] = 0;
		BulletArraySize++;
		break;
	case OBJECT_CHARACTER:
		if (CharacterArraySize == MAX_CHARACTER_COUNT)
		{
			printf("이미 꽉 찼습니다\n");
			return;
		}
		if (team1ArraySize == MAX_TEAM1_COUNT)
		{
			printf("이미 꽉 찼습니다\n");
			return;
		}
		if (team2ArraySize == MAX_TEAM2_COUNT)
		{
			printf("이미 꽉 찼습니다\n");
			return;
		}
		CharacterArray[CharacterArraySize] = new GameObject(fx, fy, fz, type, team);
		ArrowArrayTime[CharacterArraySize] = 3.0f;
		particleTime[CharacterArraySize] = 0.0f;
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
		printf("이미 꽉 찼습니다\n");
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
		particleTime[i] += time;
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		CharacterArray[i]->update(time);
		ArrowArrayTime[i] += time;
		if (ArrowArrayTime[i] > 3.0f)
		{
			addArrow(CharacterArray[i]->getX(), CharacterArray[i]->getY(), CharacterArray[i]->getZ(), CharacterArray[i]->getTeam(), CharacterArray[i]->getTeam());
			ArrowArrayTime[i] -= 3.0f;
		}
		AnimationTimer[i] += time*10;
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			ArrowArray[i][j]->update(time);
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
	spawnTime += time;
	if (spawnTime > 5.0)
	{
		addObject(rand() % 490 - 245, rand() % 390, 0, OBJECT_CHARACTER, 0);
		spawnTime -= 5.0;
	}
	delay += time;
}

void SceneMgr::collisionCheck()
{
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		for (int j = 0; j < BuildingArraySize; ++j)
		{
			if (CharacterArray[i]->collisionCheck(BuildingArray[j]))//캐릭터-빌딩 충돌체크
			{
				CharacterArray[i]->SetCollision(true);
				BuildingArray[j]->lifeDown(CharacterArray[i]->getLife());
			}
		}
		for (int j = 0; j < BulletArraySize; ++j)
		{
			if (CharacterArray[i]->collisionCheck(BulletArray[j]))//캐릭터-불렛 충돌체크
			{
				CharacterArray[i]->lifeDown(BulletArray[j]->getLife());
				BulletArray[j]->SetCollision(true);
			}
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			for (int k = 0; k < CharacterArraySize; ++k)//캐릭터-화살 충돌체크
			{
				if (CharacterArray[k]->collisionCheck(ArrowArray[i][j])) //자신이 쏜 화살 확인
				{
					CharacterArray[k]->lifeDown(ArrowArray[i][j]->getLife());
					ArrowArray[i][j]->SetCollision(true);
				}
			}
			for (int k = 0; k < BuildingArraySize; ++k)
			{
				if (ArrowArray[i][j]->collisionCheck(BuildingArray[k]))//빌딩-화살 충돌체크
				{
					BuildingArray[k]->lifeDown(ArrowArray[i][j]->getLife());
					ArrowArray[i][j]->SetCollision(true);
				}
			}
		}
	}
	for (int i = 0; i < BulletArraySize; ++i)
	{
		for (int j = 0; j < BuildingArraySize; ++j)
		{
			if (BulletArray[i]->collisionCheck(BuildingArray[j]))
			{
				BuildingArray[j]->lifeDown(BulletArray[i]->getLife());
				BulletArray[i]->SetCollision(true);
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
		/*if (BuildingArray[i]->getLifeTime() < 0)
		{
			delete BuildingArray[i];
			BuildingArraySize--;
			for (int j = i; j < BuildingArraySize; ++j)
			{
				BuildingArray[j] = BuildingArray[j + 1];
			}
			i--;
			continue;
		}*/
		BuildingArray[i]->SetCollision(false);
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		if (CharacterArray[i]->GetCollision() == true)
		{
			CharacterArraySize--;
			if (CharacterArray[i]->getTeam() == 0)
				team1ArraySize--;
			else
				team2ArraySize--;
			delete CharacterArray[i];
			for (int j = i; j < CharacterArraySize; ++j)
			{
				CharacterArray[j] = CharacterArray[j + 1];
				AnimationTimer[j] = AnimationTimer[j + 1];
			}
			i--;
			continue;
		}
		if (CharacterArray[i]->getLife() <= 0)
		{
			CharacterArraySize--;
			if (CharacterArray[i]->getTeam() == 0)
				team1ArraySize--;
			else
				team2ArraySize--;
			delete CharacterArray[i];
			for (int j = i; j < CharacterArraySize; ++j)
			{
				CharacterArray[j] = CharacterArray[j + 1];
			}
			i--;
			continue;
		}
		/*if (CharacterArray[i]->getLifeTime() < 0)
		{
			CharacterArraySize--;
			if (CharacterArray[i]->getTeam() == 0)
				team1ArraySize--;
			else
				team2ArraySize--;
			delete CharacterArray[i];
			for (int j = i; j < CharacterArraySize; ++j)
			{
				CharacterArray[j] = CharacterArray[j + 1];
			}
			i--;
			continue;
		}*/
		CharacterArray[i]->SetCollision(false);
	}
	for (int i = 0; i < 2; ++i)
	{
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
			/*if (ArrowArray[i][j]->getLifeTime() < 0)
			{
				delete ArrowArray[i][j];
				ArrowArraySize[i]--;
				for (int k = j; k < ArrowArraySize[i]; ++k)
				{
					ArrowArray[i][k] = ArrowArray[i][k + 1];
				}
				j--;
				continue;
			}*/
		}
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
				particleTime[j] = particleTime[j + 1];
			}
			i--;
			continue;
		}
		/*if (BulletArray[i]->getLifeTime() < 0)
		{
			delete BulletArray[i];
			BulletArraySize--;
			for (int j = i; j < BulletArraySize; ++j)
			{
				BulletArray[j] = BulletArray[j + 1];
			}
			i--;
			continue;
		}*/
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
		{
			g_Renderer->DrawTexturedRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 1, 1, 1, BuildingID1, g->getLevel());
			g_Renderer->DrawSolidRectGauge(g->getX(), g->getY()+g->getSize()/2+5, g->getZ(), g->getSize(), 5, 1, 0, 0, 1, (float)g->getLife()/250, g->getLevel());
		}

		else
		{
			g_Renderer->DrawTexturedRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 1, 1, 1, BuildingID2, g->getLevel());
			g_Renderer->DrawSolidRectGauge(g->getX(), g->getY() + g->getSize() / 2 + 5, g->getZ(), g->getSize(), 5, 0, 0, 1, 1, (float)g->getLife() / 250, g->getLevel());
		}
	}
	int dirX, dirY;
	for (int i = 0; i < BulletArraySize; ++i)
	{
		g = BulletArray[i];
		//fColor = g->getColor();
		if (g->getTeam() == 0)
			//g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 0, 0, 1, g->getLevel());
		{
			if (g->getVectorX() > 0.3)
				dirX = -1;
			else if (g->getVectorX() < -0.3)
				dirX = 1;
			else
				dirX = 0;
			if (g->getVectorY() > 0.3)
				dirY = -1;
			else if (g->getVectorY() < -0.3)
				dirY = 1;
			else
				dirY = 0;
			g_Renderer->DrawParticle(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 0, 0, 1, dirX, dirY, particleID1, particleTime[i]);
		}
		else
		{
			if (g->getVectorX() > 0.3)
				dirX = -1;
			else if (g->getVectorX() < -0.3)
				dirX = 1;
			else
				dirX = 0;
			if (g->getVectorY() > 0.3)
				dirY = -1;
			else if (g->getVectorY() < -0.3)
				dirY = 1;
			else
				dirY = 0;
			g_Renderer->DrawParticle(g->getX(), g->getY(), g->getZ(), g->getSize(), 0, 0, 1, 1, dirX, dirY, particleID1, particleTime[i]);
		}
	}
	for (int i = 0; i < CharacterArraySize; ++i)
	{
		g = CharacterArray[i];
		//fColor = g->getColor();
		if (g->getTeam() == 0)
		{
			//g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 0, 0, 1, g->getLevel());
			g_Renderer->DrawTexturedRectSeq(g->getX(), g->getY(), g->getZ(), g->getSize()*8, 1, 0, 0, 1, AnimationID1, ((int)AnimationTimer[i])%9, 0, 9, 1, g->getLevel());
			g_Renderer->DrawSolidRectGauge(g->getX(), g->getY() + g->getSize() / 2 + 5, g->getZ(), g->getSize(), 2, 1, 0, 0, 1, (float)g->getLife() / 250, g->getLevel());
		}
		else
		{
			//g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0, 0, 1, 1, g->getLevel());
			g_Renderer->DrawTexturedRectSeq(g->getX(), g->getY(), g->getZ(), g->getSize() * 8, 1, 0, 0, 1, AnimationID2, ((int)AnimationTimer[i]) % 9, 0, 9, 1, g->getLevel());
			g_Renderer->DrawSolidRectGauge(g->getX(), g->getY() + g->getSize() / 2 + 5, g->getZ(), g->getSize(), 2, 0, 0, 1, 1, (float)g->getLife() / 250, g->getLevel());
		}
		
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < ArrowArraySize[i]; ++j)
		{
			g = ArrowArray[i][j];
			//fColor = g->getColor();
			if (g->getTeam() == 0)
				g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 0.5, 0.2, 0.7, 1, g->getLevel());
			else
				g_Renderer->DrawSolidRect(g->getX(), g->getY(), g->getZ(), g->getSize(), 1, 1, 0, 1, g->getLevel());
		}
	}
}

float SceneMgr::getDelay()
{
	return delay;
}

