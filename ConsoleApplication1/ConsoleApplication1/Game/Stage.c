#include "stdafx.h"
#include "Stage.h"
#include "Framework/Input.h"
static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // 목표 개수
static int32_t s_boxOnGoalCount = 0; // 현재 맞는 개수
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;

void canMove(int32_t posX, int32_t posY)
{

}

void move()
{
	if (GetButtonDown(KEYCODE_W))
	{
		s_map[s_playerX][s_playerY] = ' ';
		s_map[--s_playerX][s_playerY] = 'P';
	}

	else if (GetButtonDown(KEYCODE_A))
	{
		s_map[s_playerX][s_playerY] = ' ';
		s_map[s_playerX][--s_playerY] = 'P';
	}

	else if (GetButtonDown(KEYCODE_S))
	{
		s_map[s_playerX][s_playerY] = ' ';
		s_map[++s_playerX][s_playerY] = 'P';
	}

	else if (GetButtonDown(KEYCODE_D))
	{
		s_map[s_playerX][s_playerY] = ' ';
		s_map[s_playerX][++s_playerY] = 'P';
	}
}

char parseMapType(size_t i, size_t j, char mapType)
{
	switch (mapType)
	{
	case '\n':
		return false;
	
	case 'P' :
		s_playerX = i;
		s_playerY = j;
		s_map[i][j] = mapType;
		return true;

	case 'O' :
		s_goalCount++;
		s_map[i][j] = mapType;
		return true;

	default :
		s_map[i][j] = mapType;
		return true;
	}
}

void clearStage()
{
	memset(s_map, ' ', sizeof(s_map));
	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		s_map[i][MAP_SIZE - 1] = '\0';
	}

	s_goalCount = 0;
	s_boxOnGoalCount = 0;
	s_playerX = 0;
	s_playerY = 0;
}

void LoadStage(EStageLevel level)
{
	assert(STAGE_01 <= level && level < STAGE_MAX);
	
	static char path[MAX_PATH] = { 0 };

	sprintf_s(path, sizeof(path), "Stage/Stage%02d.txt", (int32_t)level);
	FILE* fp = NULL;
	fopen_s(&fp, path, "r");
	assert(fp != NULL);

	clearStage();

	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		for (size_t j = 0; j < MAP_SIZE; ++j)
		{
			char ch = fgetc(fp);

			if (false == parseMapType(i,j,ch))
			{
				break;
			}
		}

		if (feof(fp))
		{
			break;
		}
	}

	fclose(fp);
}

void UpdateStage()
{
	move();

	//입력에 대해서 처리를 함
	//게임이 클리어 됐는지도 파악해야함
}

const char** GetMap()
{
	return (char**) s_map;
}