#pragma once

#include <stdbool.h>

/// <summary>
///	렌더러를 초기화한다.
/// </summary>
/// <returns>초기화 성공이면 true 아니면 false</returns>
bool InitializeRenderer();

/// <summary>
///	맵을 그린다.
/// </summary>
/// <returns></returns>
void RenderMap();

void SetMessage(const char* message);
