#ifndef _COMMON_H
#define _COMMON_H

#include <windows.h>
#include "resource.h"
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>

typedef struct BOOK {
	TCHAR ISBN[9];  //ISBN �ڵ�
	TCHAR bookName[50];  //å�̸�
	TCHAR Author[50]; //�۰�
	TCHAR publishDay[15];  //������
	TCHAR publisher[50]; //���ǻ�
	int version;   //�� ��
	bool rent; //�뿩���� ����
	TCHAR reserveId[20]; //�����ѻ�� ���̵�
}BOOK;

typedef struct MEMBER {
	TCHAR id[20];//���̵�
	TCHAR name[10]; //�̸�
	TCHAR pw[15]; //��й�ȣ
    TCHAR clientCheck[10]; //ȸ������ ȸ���� �����ϸ� ���� �̿� ���� (�⺻�� false)
    TCHAR reservaiton[10]; //���� å ���� �� �ִ� �� ����
}MEMBER;


#endif // !
#pragma once
