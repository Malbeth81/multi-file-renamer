/*
* Main.cpp - The program's entry point, WinMain.
*
* Copyright (C) 2010 Marc-André Lamothe.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Library General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#include "resource.h"
#include "dialogs\maindialog.h"
#include <windows.h>

#define ClassName "MultiFileRename"
#define WindowTitle "MultiFileRename"

HINSTANCE hInstance;
HWND hWindow;

// WINAPI FUNCTIONS ------------------------------------------------------------

LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
    case WM_CLOSE:
    {
      DestroyWindow(hWnd);
      return 0;
    }
    case WM_CREATE:
    {
      ShowMainDialog(hWnd);
      return 0;
    }
    case WM_DESTROY:
    {
      PostQuitMessage(0);
      return 0;
    }
  }
  return DefWindowProc(hWnd,Msg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdLine, int Show)
{
  MSG Messages;
  WNDCLASSEX WndClass;
  hInstance = hInst;
  /* Specify the window class information */
  WndClass.cbSize = sizeof(WNDCLASSEX);
  WndClass.lpszClassName = ClassName;
  WndClass.hInstance = hInstance;
  WndClass.lpfnWndProc = WindowProc;
  WndClass.style = 0;
  WndClass.hbrBackground = NULL;
  WndClass.hIcon = NULL;
  WndClass.hIconSm = NULL;
  WndClass.hCursor = NULL;
  WndClass.lpszMenuName = NULL;
  WndClass.cbClsExtra = 0;
  WndClass.cbWndExtra = 0;
  /* Register the new window class */
  if (RegisterClassEx(&WndClass) == 0)
    return 0;
  /* Create the window (invisible) */
  hWindow = CreateWindowEx(0,ClassName,WindowTitle,0,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,HWND_DESKTOP,NULL,hInstance,NULL);
  /* Message loop */
  while (GetMessage(&Messages,NULL,0,0) != 0)
  {
    TranslateMessage(&Messages);
    DispatchMessage(&Messages);
  }
  return 0;
}
