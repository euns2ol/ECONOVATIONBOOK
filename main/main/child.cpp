#include "child.h"
#include "client.h"
#include "file.h"
//childLeft
HWND hClientList,hBookList;//ȸ�� ��� ����Ʈ,���� ��� ����Ʈ
LVCOLUMN clientCOL;
LVITEM clientLI;
LVCOLUMN bookCOL;
LVITEM bookLI;

//childBottom
HWND  hClientSetting ,hBookSetting,hBorrow,hReturn;//ȯ�漳�� ��ư (ȸ�� ����,å ���� ,å ���� ,å �ݳ�)
enum { IDC_clientSetting = 1000 ,IDC_bookSetting,IDC_borrow,IDC_Return};

LRESULT CALLBACK  ChildTopProc(HWND hTopWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	
	switch (iMessage) {

	case WM_CREATE:
		

		return 0;

	}

	return (DefWindowProc(hTopWnd, iMessage, wParam, lParam));
}

LRESULT CALLBACK  ChildLeftProc(HWND hLeftWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	int i;

	switch (iMessage) {

	case WM_CREATE:

		InitCommonControls();

		hClientList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, 0, 0
			, hLeftWnd, NULL, g_hInst, NULL);

		clientCOL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		clientCOL.fmt = LVCFMT_LEFT;
		clientCOL.cx = 132;
		clientCOL.pszText = TEXT("�̸�");
		clientCOL.iSubItem = 0;
		ListView_InsertColumn(hClientList, 0, &clientCOL);

		clientCOL.pszText = TEXT("���̵�");
		clientCOL.iSubItem = 1;
		ListView_InsertColumn(hClientList, 1, &clientCOL);
                       
		if (member != NULL) {
			for (i = 0; i < memberNum; i++) {
				clientLI.mask = LVIF_TEXT;
				clientLI.iItem = i;
				clientLI.iSubItem = 0;
				clientLI.pszText = member[i]->name;
				ListView_InsertItem(hClientList, &clientLI);
				ListView_SetItemText(hClientList, i, 1, member[i]->id);
			}
		}  



		    return 0;

	case WM_SIZE:  

			MoveWindow(hClientList, 10, 10, LOWORD(lParam) - 20, crt.bottom*0.5, TRUE);
			return 0;
	}

	return (DefWindowProc(hLeftWnd, iMessage, wParam, lParam));

}

LRESULT CALLBACK  ChildMiddleProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {

	case WM_CREATE:
		         
		   return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}


LRESULT CALLBACK  ChildRightProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	
	int i;
	TCHAR rent[20];

	switch (iMessage) {

	case WM_CREATE:
	    
		InitCommonControls();
		hBookList = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 0, 0, 0, 0
				, hWnd, NULL, g_hInst, NULL); //������� ����Ʈ ����
		ListView_SetExtendedListViewStyle(hBookList, LVS_EX_FULLROWSELECT);

		bookCOL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		bookCOL.fmt = LVCFMT_LEFT;
		bookCOL.cx = 300;
		bookCOL.pszText = TEXT("������");
		bookCOL.iSubItem = 0;
		ListView_InsertColumn(hBookList, 0, &bookCOL);

		bookCOL.pszText = TEXT("����");
		bookCOL.cx = 150;
		bookCOL.iSubItem = 1;
		ListView_InsertColumn(hBookList, 1, &bookCOL);
		 
		bookCOL.pszText = TEXT("���ǻ�");
		bookCOL.iSubItem = 2;
		ListView_InsertColumn(hBookList, 2, &bookCOL);

		bookCOL.pszText = TEXT("������");
		bookCOL.iSubItem = 3;
		ListView_InsertColumn(hBookList, 3, &bookCOL);

		bookCOL.pszText = TEXT("������");
		bookCOL.iSubItem = 4;
		ListView_InsertColumn(hBookList, 4, &bookCOL);

		bookCOL.pszText = TEXT("�뿩 ����");
		bookCOL.cx = 100;
		bookCOL.iSubItem = 5;
		ListView_InsertColumn(hBookList, 5, &bookCOL);

		bookCOL.pszText = TEXT("�� ��");
		bookCOL.iSubItem = 6;
		ListView_InsertColumn(hBookList, 6, &bookCOL);

		readBook(); //���� ��ϵ��� �ҷ��´�.

		if (book != NULL) {
			for (i = 0; i < bookNumber; i++) {
				bookLI.mask = LVIF_TEXT;
				bookLI.iItem = i;
				bookLI.iSubItem = 0;
				bookLI.pszText = book[i]->bookName;
				ListView_InsertItem(hBookList, &bookLI);
				ListView_SetItemText(hBookList, i, 1, book[i]->Author);
				ListView_SetItemText(hBookList, i, 2, book[i]->publisher);
				ListView_SetItemText(hBookList, i, 3, book[i]->publishDay);
				
				if (book[i]->rent == true) {
					lstrcmp(rent,"����");
				}
				else {
					lstrcmp(rent, "�Ұ���");
				}

				ListView_SetItemText(hBookList, i, 5,rent);
			}
		}

		return 0;

	case WM_SIZE:
		
		GetClientRect(hWndMain, &crt);
	    MoveWindow(hBookList, 20, 10,crt.right*0.77, crt.bottom*0.4, TRUE);
	    
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}

LRESULT CALLBACK  ChildBottomProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	int i;

	switch (iMessage) {

	case WM_CREATE:

		hClientSetting = CreateWindow(TEXT("button"), TEXT("ȸ�� ����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_clientSetting, g_hInst, NULL);
		hBookSetting = CreateWindow(TEXT("button"), TEXT("���� ����"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_bookSetting, g_hInst, NULL);
		hBorrow= CreateWindow(TEXT("button"), TEXT("���� �뿩"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_borrow, g_hInst, NULL);
		hReturn= CreateWindow(TEXT("button"), TEXT("���� �ݳ�"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_Return, g_hInst, NULL);

	    return 0;

	case WM_SIZE:

		MoveWindow(hClientSetting, 10, 10, crt.right*0.15, 50, TRUE);
		MoveWindow(hBookSetting, 310, 10, crt.right*0.15, 50, TRUE);
		MoveWindow(hBorrow, 610, 10, crt.right*0.15, 50, TRUE);
		MoveWindow(hReturn, 910, 10, crt.right*0.15, 50, TRUE);

	    return 0;

	case WM_COMMAND:

		switch (LOWORD(wParam)) {
	
			case IDC_clientSetting:
		                                    
				if (lstrcmp(current->id, TEXT("root")) == 0) {
							
					if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_CLIENTSETTING), hWnd, clientSettingProc) == IDOK) {

						ListView_DeleteAllItems(hClientList);
									
						if (member != NULL) {
							for (i = 0; i < memberNum; i++) {
								clientLI.mask = LVIF_TEXT;
								clientLI.iItem = i;
								clientLI.iSubItem = 0;
								clientLI.pszText = member[i]->name;
								ListView_InsertItem(hClientList, &clientLI);
								ListView_SetItemText(hClientList, i, 1, member[i]->id);
							}
						}
					}
								   
				}else {
					MessageBox(hWndMain,TEXT( "�ź��� �ʹ� ���׿� ^__^ "), TEXT("���� �Ұ�"), MB_OK);
				}

				break; //ȸ�� ����
		
			case IDC_bookSetting:
		
				break; //���� ����
		
			case IDC_borrow:
		
				break; //�뿩
		
			case IDC_Return:
		
				break; //�ݳ�

			}

       return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}

