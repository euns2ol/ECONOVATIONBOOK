#include "child.h"
#include "client.h"
#include "file.h"
//childLeft
HWND hClientList,hBookList;//회원 출력 리스트,도서 출력 리스트
LVCOLUMN clientCOL;
LVITEM clientLI;
LVCOLUMN bookCOL;
LVITEM bookLI;

//childBottom
HWND  hClientSetting ,hBookSetting,hBorrow,hReturn;//환경설정 버튼 (회원 관리,책 관리 ,책 대출 ,책 반납)
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
		clientCOL.pszText = TEXT("이름");
		clientCOL.iSubItem = 0;
		ListView_InsertColumn(hClientList, 0, &clientCOL);

		clientCOL.pszText = TEXT("아이디");
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
				, hWnd, NULL, g_hInst, NULL); //도서목록 리스트 생성
		ListView_SetExtendedListViewStyle(hBookList, LVS_EX_FULLROWSELECT);

		bookCOL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		bookCOL.fmt = LVCFMT_LEFT;
		bookCOL.cx = 300;
		bookCOL.pszText = TEXT("도서명");
		bookCOL.iSubItem = 0;
		ListView_InsertColumn(hBookList, 0, &bookCOL);

		bookCOL.pszText = TEXT("저자");
		bookCOL.cx = 150;
		bookCOL.iSubItem = 1;
		ListView_InsertColumn(hBookList, 1, &bookCOL);
		 
		bookCOL.pszText = TEXT("출판사");
		bookCOL.iSubItem = 2;
		ListView_InsertColumn(hBookList, 2, &bookCOL);

		bookCOL.pszText = TEXT("출판일");
		bookCOL.iSubItem = 3;
		ListView_InsertColumn(hBookList, 3, &bookCOL);

		bookCOL.pszText = TEXT("예약자");
		bookCOL.iSubItem = 4;
		ListView_InsertColumn(hBookList, 4, &bookCOL);

		bookCOL.pszText = TEXT("대여 여부");
		bookCOL.cx = 100;
		bookCOL.iSubItem = 5;
		ListView_InsertColumn(hBookList, 5, &bookCOL);

		bookCOL.pszText = TEXT("몇 판");
		bookCOL.iSubItem = 6;
		ListView_InsertColumn(hBookList, 6, &bookCOL);

		readBook(); //도서 목록들을 불러온다.

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
					lstrcmp(rent,"가능");
				}
				else {
					lstrcmp(rent, "불가능");
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

		hClientSetting = CreateWindow(TEXT("button"), TEXT("회원 관리"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_clientSetting, g_hInst, NULL);
		hBookSetting = CreateWindow(TEXT("button"), TEXT("도서 관리"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_bookSetting, g_hInst, NULL);
		hBorrow= CreateWindow(TEXT("button"), TEXT("도서 대여"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 0, 0, 0, hWnd, (HMENU)IDC_borrow, g_hInst, NULL);
		hReturn= CreateWindow(TEXT("button"), TEXT("도서 반납"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
					MessageBox(hWndMain,TEXT( "신분이 너무 낮네요 ^__^ "), TEXT("접근 불가"), MB_OK);
				}

				break; //회원 관리
		
			case IDC_bookSetting:
		
				break; //도서 관리
		
			case IDC_borrow:
		
				break; //대여
		
			case IDC_Return:
		
				break; //반납

			}

       return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));

}

