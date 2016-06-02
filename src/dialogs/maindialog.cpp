/*
* MainDialog.cpp
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
#include "maindialog.h"
#include "..\resource.h"

// PRIVATE FUNCTIONS -----------------------------------------------------------

static void AddFileToList(HWND List, const char* Filename)
{
  if (Filename != NULL)
  {
    int Index = ListView_GetItemCount(List);
    /* Add a new item to the list view */
    LVITEM ItemInfo;
    ItemInfo.mask = 0;
    ItemInfo.iItem = Index;
    ItemInfo.iSubItem = 0;
    ListView_InsertItem(List,&ItemInfo);
    /* Set the item's other attributes */
    ListView_SetItemText(List,Index,0,(CHAR*)Filename);
    ListView_SetItemText(List,Index,1,NULL);
  }
}

static void AddListCollumn(HWND List, UINT Id, int Index, int Width)
{
  LVCOLUMN CollumnInfo;
  CollumnInfo.mask = LVCF_WIDTH | LVCF_TEXT;
  CollumnInfo.cx = Width;
  CollumnInfo.pszText = new char[MAX_PATH];
  LoadString(GetModuleHandle(NULL), Id, CollumnInfo.pszText, MAX_PATH);
  ListView_InsertColumn(List, Index, &CollumnInfo);
  delete[] CollumnInfo.pszText;
}

// WINAPI FUNCTIONS ------------------------------------------------------------

static BOOL __stdcall MainDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
    case WM_COMMAND: /* Process control messages */
    {
      switch (LOWORD(wParam))
      {
        case IDOK:
        {
          /* Apply the preferences */
          /* Close the dialog */
          SendMessage(hDlg, WM_CLOSE, 0, 0);
          break;
        }
        case IDCANCEL:
        {
          /* Close the dialog */
          SendMessage(hDlg, WM_CLOSE, 0, 0);
          break;
        }
      }
      return TRUE;
    }
    case WM_CLOSE:
    {
      /* Destroy the dialog */
      EndDialog(hDlg, wParam);
      /* Destroy the parent window */
      DestroyWindow((HWND)GetWindowLong(hDlg, GWL_HWNDPARENT));
      return TRUE;
    }
    case WM_INITDIALOG:
    {
      HWND Listview = GetDlgItem(hDlg, IDC_FILELIST);
      /* Enable full row selection */
      SendMessage(Listview, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
      /* Add  columns */
      AddListCollumn(Listview, IDS_FILELIST_COL1, 0, 240);
      AddListCollumn(Listview, IDS_FILELIST_COL2, 1, 240);
      return TRUE;
    }
  }
  return FALSE;
}

// PUBLIC FUNCTIONS ------------------------------------------------------------

void ShowMainDialog(HWND hParent)
{
  HINSTANCE Instance = (hParent != NULL ? (HINSTANCE)GetWindowLong(hParent, GWL_HINSTANCE) : GetModuleHandle(NULL));
  DialogBox(Instance,MAKEINTRESOURCE(IDD_MAIN),hParent,(DLGPROC)MainDialogProc);
}
