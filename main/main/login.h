#ifndef _LOGIN_H
#define _LOGIN_H

#include "common.h"
#include "file.h"

BOOL CALLBACK LoginProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SignInProc(HWND hDIg, UINT iMessage, WPARAM wParam, LPARAM lParam);
bool identify(TCHAR *id, TCHAR *pw); //�α��ν� �Էµ� ������ Ȯ���Ͽ� �α��� ���ɿ��� �Ǵ�
bool idOverlapCheck(TCHAR *); //���̵� �ߺ�üũ
enum { IDC_signId=100,IDC_signpw,IDC_signName}; //ȸ������ ����Ʈ�� �ڵ� �� ����
extern BOOL loginState; //�α��� üũ
extern HINSTANCE g_hInst;
extern MEMBER **member;
extern int memberNum;
extern BOOK **book;
extern MEMBER *current;
extern HWND hWndMain;
#endif // !LOGIN_FRAME_H

#pragma once