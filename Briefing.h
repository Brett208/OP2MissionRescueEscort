#pragma once

#include "resource.h"
#include "odasl/odasl.h"
#include <richedit.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void ShowBriefing();
LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
