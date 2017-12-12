#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <chrono>
#include <stdlib.h>

#define MAX_BUILDING_COUNT 6
#define MAX_BULLET_COUNT 50
#define MAX_CHARACTER_COUNT 20
#define MAX_TEAM1_COUNT 10
#define MAX_TEAM2_COUNT 10
#define MAX_ARROW_COUNT 10
#define WIDTH 500
#define HEIGHT 800
#define GLUT_BITMAP_TIMES_ROMAN_10
#define GLUT_BITMAP_TIMES_ROMAN_24
#define GLUT_BITMAP_HELVETICA_10
#define GLUT_BITMAP_HELVETICA_12
#define GLUT_BITMAP_HELVETICA_18

enum OBJECT_TYPE {
	OBJECT_BUILDING,
	OBJECT_CHARACTER,
	OBJECT_BULLET,
	OBJECT_ARROW
};

void Normalize(float& f1, float& f2);