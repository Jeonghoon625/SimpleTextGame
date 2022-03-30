#pragma once

#include <stdint.h>
#include <stdbool.h>
typedef enum KeyCode
{
	W = 'w',
	A = 'a',
	S = 's',
	D = 'd',
} EKeyCode;

/// <summary>
/// 입력 상태를 업데이트한다.
/// </summary>
void UpdateInput();

/// <summary>
/// 현재 프레임에 버튼이 눌렸는지 체크한다.
/// </summary>
/// <param name="keyCode"> 가상 키 코드 </param>
/// <returns>눌렸다면 true, 아니면 false</returns>
bool GetButtonDown(EKeyCode keyCode);

/// <summary>
/// 현재 프레임에 버튼이 떼었는지 체크한다.
/// </summary>
/// <param name="keycode">가상 키 코드</param>
/// <returns>떴다면 ture, 아니면 false</returns>
bool GetButtonUp(EKeyCode keycode);

/// <summary>
/// 버튼이 계속 눌렀는지 체크한다.
/// </summary>
/// <param name="keycode">가상 키 코드</param>
/// <returns>눌렸다면 true, 아니면 false</returns>
bool GetButton(EKeyCode keycode);

