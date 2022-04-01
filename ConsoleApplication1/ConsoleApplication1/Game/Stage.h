#pragma once

//역할
//1. 스테이지를 불러옴
//2. 스테이지 현재 상황을 보관
//3. 스테이지가 클리어 됐는지

typedef enum MapType
{
	MAPTYPE_WALL = '#',
	MAPTYPE_PLAYER = 'P',
	MAPTYPE_BOX = 'a',
	MAPTYPE_GOAL = 'O',
	MAPTYPE_BOX_ON_GOAL = '@',
	MAPTYPE_PATH = ' '
} EMapType;

typedef enum StageLevel
{
	STAGE_01 = 1,
	STAGE_MAX
} EStageLevel;

/// <summary>
/// 타이틀을 로딩한다.
/// </summary>
void LoadTitle();

/// <summary>
/// 스테이지를 로딩한다.
/// </summary>
void LoadStage(EStageLevel level);

/// <summary>
/// 스테이지를 업데이트한다.
/// </summary>
void UpdateStage();

/// <summary>
/// 맵을 반환한다.
/// </summary>
/// <returns></returns>
const char** GetMap();
