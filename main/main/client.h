#ifndef _CLIENT_H
#define _CLIENT_H

#include "common.h"

extern MEMBER **member;
extern MEMBER **awaiter;
extern HINSTANCE g_hInst;
extern int awaitNum;
extern int memberNum;
extern HWND hWndMain;
BOOL CALLBACK clientSettingProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
void deleteRequest(TCHAR *id); //ȸ�������� �³� ��� ȸ���� �����Ѵ�.
void permissionClient(TCHAR *id,TCHAR *pw,TCHAR* name,int); //ȸ�������� ���� �³��Ѵ�.
BOOL deleteMember(TCHAR *deleteMemberId); //ȸ�� ����
#endif // !_CLIENT_H

#pragma once
