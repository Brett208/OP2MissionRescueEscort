#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <richedit.h>
#include "resource.h"
#include "odasl\odasl.h"

void ShowBriefing();
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);