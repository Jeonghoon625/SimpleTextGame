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
		if(posX == goal[i].s_goalX && posY == goal[i].s_goalY)
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
		s_boxOnGoalCount += 1;
		return true;
	}

	return false;
}

bool canBoxMove(Box box, EKeyCode keyCode)
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

	switch (s_map[s_NextboxX][s_NextboxY])
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
	int32_t s_NextPlayerX = s_playerX;
	int32_t s_NextPlayerY = s_playerY;

	if (GetButtonDown(KEYCODE_W))
	{
		s_NextPlayerX--;
		if (canPlayerMove(s_playerX - 1, s_playerY, KEYCODE_W))
		{
			if (GoalPos(s_playerX, s_playerY))
			{
				s_map[s_playerX][s_playerY] = 'O';
			}
			else
			{
				s_map[s_playerX][s_playerY] = ' ';
			}

			s_map[--s_playerX][s_playerY] = 'P';
		}
	}

	else if (GetButtonDown(KEYCODE_A))
	{
		s_NextPlayerY--;
		if (canPlayerMove(s_playerX, s_playerY - 1, KEYCODE_A))
		{
			if (GoalPos(s_playerX, s_playerY))
			{
				s_map[s_playerX][s_playerY] = 'O';
			}
			else
			{
				s_map[s_playerX][s_playerY] = ' ';
			}
			s_map[s_playerX][--s_playerY] = 'P';
		}

	}

	else if (GetButtonDown(KEYCODE_S))
	{
		s_NextPlayerX++;
		if (canPlayerMove(s_playerX + 1, s_playerY, KEYCODE_S))
		{
			if (GoalPos(s_playerX, s_playerY))
			{
				s_map[s_playerX][s_playerY] = 'O';
			}
			else
			{
				s_map[s_playerX][s_playerY] = ' ';
			}
			s_map[++s_playerX][s_playerY] = 'P';
		}
	}

	else if (GetButtonDown(KEYCODE_D))
	{
		s_NextPlayerY++;
		if (canPlayerMove(s_playerX, s_playerY + 1, KEYCODE_D))
		{
			if (GoalPos(s_playerX, s_playerY))
			{
				s_map[s_playerX][s_playerY] = 'O';
			}
			else
			{
				s_map[s_playerX][s_playerY] = ' ';
			}
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
		s_playerX = i;
		s_playerY = j;
		s_map[i][j] = mapType;
		return true;

	case 'O':
		goal[s_goalCount].s_goalX = i;
		goal[s_goalCount].s_goalY = j;

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

	for (size_t i = 3; i < MAP_SIZE; ++i)
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
		sprintf_s(s_map[0], sizeof(s_map[0]), "> Stage %d", stageNum);
		sprintf_s(s_map[1], sizeof(s_map[1]), "> 개수 : %d", s_boxOnGoalCount);
	}
}

const char** GetMap()
{
	return (char**)s_map;
}

