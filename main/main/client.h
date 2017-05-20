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
void deleteRequest(TCHAR *id); //회원가입한 승낙 대기 회원을 삭제한다.
void permissionClient(TCHAR *id,TCHAR *pw,TCHAR* name,int); //회원가입을 최종 승낙한다.
BOOL deleteMember(TCHAR *deleteMemberId); //회원 삭제
#endif // !_CLIENT_H

#pragma once
