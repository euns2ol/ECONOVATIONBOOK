#ifndef _FILE_H
#define _FILE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

extern MEMBER **member;
extern int memberNum;
extern BOOK **book;
extern int bookNumber;
extern MEMBER **awaiter;
extern int awaitNum;
void readawait(); //승낙 대기 중인 회원을 읽어온다(signup.txt)
void readclient(); //회원을 읽어온다 (client.txt)
void writeWait(TCHAR *, TCHAR *, TCHAR*); //회원가입시 회원을 파일에 입력 (signup.txt)
void writeRequestDelete(); //승낙 대기자들 삭제 시 파일에 다시 입력해준다. (signup.txt)
void writeMember(); //승낙 대기자들을 회원 파일에 입력한다 (client.txt)
void readBook();//도서목록을 읽어온다(book.txt)
#endif