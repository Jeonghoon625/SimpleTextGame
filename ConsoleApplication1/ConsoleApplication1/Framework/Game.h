#pragma once

#include <stdint.h>
#include <stdbool.h>

/// <summary>
///	게임과 관련된 데이터를 초기화한다.
/// </summary>
/// <returns>정상적으로 초기화 했으면 true, 아니면 false</returns>
bool Initialize();

/// <summary>
///	게임을 동작시킨다.
/// </summary>
/// <returns>정상적으로 종료 됐다면0</returns>
int32_t Run();
