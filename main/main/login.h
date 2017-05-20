#ifndef _LOGIN_H
#define _LOGIN_H

#include "common.h"
#include "file.h"

BOOL CALLBACK LoginProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK SignInProc(HWND hDIg, UINT iMessage, WPARAM wParam, LPARAM lParam);
bool identify(TCHAR *id, TCHAR *pw); //로그인시 입력된 정보를 확인하여 로그인 가능여부 판단
bool idOverlapCheck(TCHAR *); //아이디 중복체크
enum { IDC_signId=100,IDC_signpw,IDC_signName}; //회원가입 에디트들 핸들 값 변수
extern BOOL loginState; //로그인 체크
extern HINSTANCE g_hInst;
extern MEMBER **member;
extern int memberNum;
extern BOOK **book;
extern MEMBER *current;
extern HWND hWndMain;
#endif // !LOGIN_FRAME_H

#pragma once