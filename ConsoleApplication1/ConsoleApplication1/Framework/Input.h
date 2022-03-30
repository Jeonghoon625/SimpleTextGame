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
/// �Է� ���¸� ������Ʈ�Ѵ�.
/// </summary>
void UpdateInput();

/// <summary>
/// ���� �����ӿ� ��ư�� ���ȴ��� üũ�Ѵ�.
/// </summary>
/// <param name="keyCode"> ���� Ű �ڵ� </param>
/// <returns>���ȴٸ� true, �ƴϸ� false</returns>
bool GetButtonDown(EKeyCode keyCode);

/// <summary>
/// ���� �����ӿ� ��ư�� �������� üũ�Ѵ�.
/// </summary>
/// <param name="keycode">���� Ű �ڵ�</param>
/// <returns>���ٸ� ture, �ƴϸ� false</returns>
bool GetButtonUp(EKeyCode keycode);

/// <summary>
/// ��ư�� ��� �������� üũ�Ѵ�.
/// </summary>
/// <param name="keycode">���� Ű �ڵ�</param>
/// <returns>���ȴٸ� true, �ƴϸ� false</returns>
bool GetButton(EKeyCode keycode);
