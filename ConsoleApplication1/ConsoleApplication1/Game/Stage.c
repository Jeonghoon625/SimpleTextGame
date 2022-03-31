#include "stdafx.h"
#include "Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // 목표 개수
static int32_t s_boxOnGoalCount = 0; // 현재 맞는 개수
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;
char parseMapType(int i, int j, char mapType)
{
	switch (mapType)
	{
		//각 맵 타입별로 해줘야 하는 일들
	}

	//반환은 행에 다다랐을 때

	/*if (ch == '\n')
	{
		break;
	}


	s_map[i][j] = ch;*/
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
	//입력에 대해서 처리를 함
	//게임이 클리어 됐는지도 파악해야함
}
const char** GetMap()
{
	return s_map;
}