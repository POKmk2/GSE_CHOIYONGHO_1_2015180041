/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"


#include "Renderer.h"
#include "SceneMgr.h"

SceneMgr *g_SceneMgr = NULL;
std::chrono::system_clock::time_point start;
std::chrono::duration<float> sec;
std::chrono::system_clock::time_point spawnTime;


void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	g_SceneMgr->Render();
	sec = std::chrono::system_clock::now() - start;
	if (sec.count()>1/120)
	{
		g_SceneMgr->update(sec.count());
		start = std::chrono::system_clock::now();
	}
	
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	static bool g_LButtonDown;
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_DOWN)
	{
		g_LButtonDown = true;
	}
	if (button == GLUT_LEFT_BUTTON&& state == GLUT_UP)
	{
		g_LButtonDown = false;
		if ((-y + HEIGHT / 2 < 0) && (g_SceneMgr->getDelay() > 7.0))
		{
			g_SceneMgr->setDelay(0.0f);
			g_SceneMgr->addObject(x - WIDTH / 2, -y + HEIGHT / 2, 0, OBJECT_CHARACTER, 1);
		}
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}
	start = std::chrono::system_clock::now();
	spawnTime = std::chrono::system_clock::now();
	// Initialize Renderer
	g_SceneMgr = new SceneMgr;

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();
	
    return 0;
}

