#ifndef _COMMON_H
#define _COMMON_H

#include <windows.h>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>

typedef struct BOOK {
	TCHAR ISBN[9];  //ISBN 코드
	TCHAR bookName[50];  //책이름
	TCHAR Author[50]; //작가
	TCHAR publishDay[15];  //출판일
	TCHAR publisher[50]; //출판사
	int version;   //몇 판
	bool rent; //대여가능 여부
	TCHAR reserveId[20]; //예약한사람 아이디
}BOOK;

typedef struct MEMBER {
	TCHAR id[20];//아이디
	TCHAR name[10]; //이름
	TCHAR pw[15]; //비밀번호
    TCHAR clientCheck[10]; //회원여부 회장이 승인하면 서비스 이용 가능 (기본값 false)
    TCHAR reservaiton[10]; //예약 책 빌릴 수 있는 지 여부
}MEMBER;


#endif // !
#pragma once
