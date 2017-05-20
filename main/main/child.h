#ifndef _CHILD_H
#define _CHILD_H
#include "common.h"

LRESULT CALLBACK  ChildTopProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK  ChildLeftProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK  ChildBottomProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK  ChildRightProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK  ChildMiddleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
extern HWND hWndMain;
extern HINSTANCE g_hInst;
extern RECT crt;
extern MEMBER **member;
extern BOOK **book;
extern int memberNum;
extern MEMBER *current;

#endif // !_CHILD_H

#pragma once
