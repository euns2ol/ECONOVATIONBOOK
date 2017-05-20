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
void readawait(); //�³� ��� ���� ȸ���� �о�´�(signup.txt)
void readclient(); //ȸ���� �о�´� (client.txt)
void writeWait(TCHAR *, TCHAR *, TCHAR*); //ȸ�����Խ� ȸ���� ���Ͽ� �Է� (signup.txt)
void writeRequestDelete(); //�³� ����ڵ� ���� �� ���Ͽ� �ٽ� �Է����ش�. (signup.txt)
void writeMember(); //�³� ����ڵ��� ȸ�� ���Ͽ� �Է��Ѵ� (client.txt)
void readBook();//��������� �о�´�(book.txt)
#endif