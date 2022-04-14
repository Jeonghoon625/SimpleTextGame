#include "stdafx.h"
#include "Stage.h"
#include "Framework/Timer.h"
#include "Framework/Input.h"

static int stageNum = 1;
static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // 목표 개수
static int32_t s_boxOnGoalCount = 0; // 현재 맞는 개수
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;
static double runTime;
static double timer;

typedef struct
{
	int32_t s_boxX;
	int32_t s_boxY;
} Box;
static Box box;
typedef struct
{
	int32_t s_goalX;
	int32_t s_goalY;
} Goal;
static Goal goal[Max_goalCount];

bool GoalPos(int posX, int posY)
{
	for (int i = 0; i < s_goalCount; i++)
	{
		if (posX == goal[i].s_goalX && posY == goal[i].s_goalY)
		{
			return true;
		}
	}

	return false;
}

bool BoxOnGoal(int posX, int posY)
{
	if (s_map[posX][posY] == 'O')
	{
		s_boxOnGoalCount++;
		return true;
	}

	return false;
}

bool canBoxMove(Box box, EKeyCode keyCode)
{
	int32_t s_nextBoxX = box.s_boxX;
	int32_t s_nextBoxY = box.s_boxY;

	if (keyCode == 'W')
	{
		s_nextBoxX--;
	}

	else if (keyCode == 'A')
	{
		s_nextBoxY--;
	}

	else if (keyCode == 'S')
	{
		s_nextBoxX++;
	}

	else if (keyCode == 'D')
	{
		s_nextBoxY++;
	}

	switch (s_map[s_nextBoxX][s_nextBoxY])
	{
	case '#':
		return false;

	case 'a':
		return false;

	case '@':
		return false;

	default:
		return true;
	}
}

void BoxMove(Box box, EKeyCode keyCode)
{
	int32_t s_NextboxX = box.s_boxX;
	int32_t s_NextboxY = box.s_boxY;

	if (keyCode == 'W')
	{
		s_NextboxX--;
	}

	else if (keyCode == 'A')
	{
		s_NextboxY--;
	}

	else if (keyCode == 'S')
	{
		s_NextboxX++;
	}

	else if (keyCode == 'D')
	{
		s_NextboxY++;
	}

	if (BoxOnGoal(s_NextboxX, s_NextboxY))
	{
		s_map[s_NextboxX][s_NextboxY] = '@';
	}
	else
	{
		s_map[s_NextboxX][s_NextboxY] = 'a';
	}
}

bool canPlayerMove(int32_t posX, int32_t posY, EKeyCode keyCode)
{
	switch (s_map[posX][posY])
	{
	case '#':
		return false;

	case 'a':
		box.s_boxX = posX;
		box.s_boxY = posY;

		if (canBoxMove(box, keyCode))
		{
			BoxMove(box, keyCode);
			return true;
		}
		else
		{
			return false;
		}

	case '@':
		box.s_boxX = posX;
		box.s_boxY = posY;

		if (canBoxMove(box, keyCode))
		{
			BoxMove(box, keyCode);
			s_boxOnGoalCount--;
			return true;
		}
		else
		{
			return false;
		}

	default:
		return true;
	}
}

void PlayerMove()
{
	int32_t s_nextPlayerX = s_playerX;
	int32_t s_nextPlayerY = s_playerY;

	if (GetButtonDown(KEYCODE_W))
	{
		s_nextPlayerX--;
		if (canPlayerMove(s_playerX - 1, s_playerY, KEYCODE_W))
		{
			s_map[s_playerX][s_playerY] = GoalPos(s_playerX, s_playerY) ? 'O' : ' ';
			s_map[--s_playerX][s_playerY] = 'P';
		}
	}

	else if (GetButtonDown(KEYCODE_A))
	{
		s_nextPlayerY--;
		if (canPlayerMove(s_playerX, s_playerY - 1, KEYCODE_A))
		{
			s_map[s_playerX][s_playerY] = GoalPos(s_playerX, s_playerY) ? 'O' : ' ';
			s_map[s_playerX][--s_playerY] = 'P';
		}

	}

	else if (GetButtonDown(KEYCODE_S))
	{
		s_nextPlayerX++;
		if (canPlayerMove(s_playerX + 1, s_playerY, KEYCODE_S))
		{
			s_map[s_playerX][s_playerY] = GoalPos(s_playerX, s_playerY) ? 'O' : ' ';
			s_map[++s_playerX][s_playerY] = 'P';
		}
	}

	else if (GetButtonDown(KEYCODE_D))
	{
		s_nextPlayerY++;
		if (canPlayerMove(s_playerX, s_playerY + 1, KEYCODE_D))
		{
			s_map[s_playerX][s_playerY] = GoalPos(s_playerX, s_playerY) ? 'O' : ' ';
			s_map[s_playerX][++s_playerY] = 'P';
		}
	}

	else if (GetButtonDown(KEYCODE_R))
	{
		LoadStage(STAGE_01);
	}
}

char parseMapType(size_t i, size_t j, char mapType)
{
	switch (mapType)
	{
	case '\n':
		return false;

	case 'P':
		s_playerX = (int)i;
		s_playerY = (int)j;
		s_map[i][j] = mapType;
		return true;

	case 'O':
		goal[s_goalCount].s_goalX = (int)i;
		goal[s_goalCount].s_goalY = (int)j;

		s_goalCount++;
		s_map[i][j] = mapType;
		return true;

	default:
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

	sprintf_s(path, sizeof(path), "Stage/Stage%02d.txt", stageNum);
	FILE* fp = NULL;
	fopen_s(&fp, path, "r");
	assert(fp != NULL);

	clearStage();

	for (size_t i = 6; i < MAP_SIZE; ++i)
	{
		for (size_t j = 0; j < MAP_SIZE; ++j)
		{
			char ch = fgetc(fp);

			if (false == parseMapType(i, j, ch))
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

	sprintf_s(s_map[0], sizeof(s_map[0]), "> Stage %d", stageNum);
	sprintf_s(s_map[3], sizeof(s_map[3]), "[Move] : W A S D");
	sprintf_s(s_map[4], sizeof(s_map[4]), "[RESET] : R");
}

bool StageOver()
{
	if (s_boxOnGoalCount == s_goalCount)
	{
		stageNum++;
		if (stageNum < 4)
		{
			LoadStage(STAGE_01);
			return true;
		}

		else
		{
			clearStage();
			sprintf_s(s_map[0], sizeof(s_map[0]), "#####################");
			sprintf_s(s_map[1], sizeof(s_map[1]), "# C   L   E   A   R #");
			sprintf_s(s_map[2], sizeof(s_map[2]), "#####################");
			return true;
		}
	}

	return false;
}

void UpdateStage()
{
	PlayerMove();
	if (!StageOver())
	{
		runTime += GetDeltaTime();
		sprintf_s(s_map[1], sizeof(s_map[1]), "> Goal : %d", s_boxOnGoalCount);
		sprintf_s(s_map[2], sizeof(s_map[2]), "> RunTime : %.0fs", runTime);
	}
}

const char** GetMap()
{
	return (char**)s_map;
}

void Delaytime(float intervaltick)
{
	float delayTime = intervaltick + 0.5f;

	if (timer >= intervaltick)
	{
	}

	if (timer >= delayTime)
	{
		timer = 0.0f;
	}

	timer += GetDeltaTime();
}
