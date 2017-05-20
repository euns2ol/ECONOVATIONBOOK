#include "client.h"
#include "file.h"
HWND waitClient,deleteClient; //승인대기자와 회원 삭제를 표시할 리스트 뷰

BOOL CALLBACK clientSettingProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	
	LVCOLUMN waitCOL;
	LVITEM waitLI;
	LVCOLUMN memberCOL;
	LVITEM memberLI;
	TCHAR deleteId[30];
	TCHAR deleteMemberId[20], deleteMemberName[10], deleteMemberPw[15],Name[10];
	int i,deleteCheck=0,deleteMemberCheck=0, permissionCheck=0,j; //승낙대기자 삭제,멤버 삭제,승낙대기자 등록체크
	int cnt,check=1;
	switch (iMessage) {
		
	case WM_INITDIALOG:
		InitCommonControls();
		waitClient = CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 40,60,590 ,200 
			, hDlg, NULL, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(waitClient, LVS_EX_CHECKBOXES); //체크박스를 가진 리스트뷰 생성
		
		deleteClient= CreateWindow(WC_LISTVIEW, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS,40 ,300 ,590 ,250 
			, hDlg, NULL, g_hInst, NULL);
		ListView_SetExtendedListViewStyle(deleteClient, LVS_EX_CHECKBOXES);

		waitCOL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		waitCOL.fmt = LVCFMT_LEFT;
		waitCOL.cx = 196;
		waitCOL.pszText = TEXT("이름");
		waitCOL.iSubItem = 0;
		ListView_InsertColumn(waitClient, 0, &waitCOL);

		waitCOL.pszText = TEXT("아이디");
		waitCOL.iSubItem = 1;
		ListView_InsertColumn(waitClient, 1, &waitCOL);

		waitCOL.pszText = TEXT("비밀번호");
		waitCOL.iSubItem = 2;
		ListView_InsertColumn(waitClient, 2, &waitCOL);
		
		
		  readawait();
		
		if (awaitNum!=0) {

			for (i = 0; i < awaitNum; i++) {
				waitLI.mask = LVIF_TEXT;
				waitLI.iItem = i;
				waitLI.iSubItem = 0;
				waitLI.pszText = awaiter[i]->name;
				ListView_InsertItem(waitClient, &waitLI);
				ListView_SetItemText(waitClient, i, 1, awaiter[i]->id);
				ListView_SetItemText(waitClient, i, 2, awaiter[i]->pw);

			}
		}  ////회원 승낙대기자들 리스트뷰 초기화

		memberCOL.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		memberCOL.fmt = LVCFMT_LEFT;
		memberCOL.cx = 196;
		memberCOL.pszText = TEXT("이름");
		memberCOL.iSubItem = 0;
		ListView_InsertColumn(deleteClient, 0, &memberCOL);

		memberCOL.pszText = TEXT("아이디");
		memberCOL.iSubItem = 1;
		ListView_InsertColumn(deleteClient, 1, &memberCOL);

		memberCOL.pszText = TEXT("비밀번호");
		memberCOL.iSubItem = 2;
		ListView_InsertColumn(deleteClient, 2, &memberCOL);

		if (memberNum != 0) {

			for (i = 0; i < memberNum; i++) {
				memberLI.mask = LVIF_TEXT;
				memberLI.iItem = i;
				memberLI.iSubItem = 0;
				memberLI.pszText = member[i]->name;
				ListView_InsertItem(deleteClient, &memberLI);
				ListView_SetItemText(deleteClient, i, 1, member[i]->id);
				ListView_SetItemText(deleteClient, i, 2, member[i]->pw);

			}
		}  ////회원들 리스트뷰 초기화


		return TRUE;

	case WM_COMMAND:
		                 
			switch (LOWORD(wParam)){
			case IDC_DELETE: //회원 요청대기자들 삭제 버튼
				cnt = awaitNum;
				if (awaiter != NULL) {
					for (i = 0; i < cnt; i++) {
						deleteCheck = 1;
						if (ListView_GetCheckState(waitClient, i) == true) {
							deleteCheck = 1;
							ListView_GetItemText(waitClient, i, 1, deleteId, 30);
							deleteRequest(deleteId);
											
						}
					}
				}					       
				if(deleteCheck==1)
					EndDialog(hDlg, IDOK);
								
				deleteCheck = 0;
				break;

			case IDOK:

				if (awaiter != NULL) {
					cnt = awaitNum;
					for (i = 0; i < cnt; i++) {
										
						if (ListView_GetCheckState(waitClient, i) == true) {
							permissionCheck++;
							ListView_GetItemText(waitClient, i, 1, deleteMemberId, sizeof(deleteMemberId));
							printf("id %sdd\n", deleteMemberId);
							ListView_GetItemText(waitClient, i, 0,deleteMemberName,sizeof(deleteMemberName));
									
					        printf("name %sdd\n", deleteMemberName);

							ListView_GetItemText(waitClient, i, 2, deleteMemberPw,15);
							printf("pw%sdd\n", deleteMemberPw);

							permissionClient(deleteMemberId,deleteMemberPw,deleteMemberName,permissionCheck); //회원 승낙
											
						}
					}
				}
																
				permissionCheck = 0; //회원 승낙 완료

				if (member != NULL) { //회원 삭제 시작
					cnt = memberNum;
					for (i = 0; i < cnt; i++) {

						if (ListView_GetCheckState(deleteClient, i) == true) {
							permissionCheck++;
							ListView_GetItemText(deleteClient, i, 1, deleteMemberId, sizeof(deleteMemberId));
							printf("id %sdd\n", deleteMemberId);
							ListView_GetItemText(deleteClient, i, 0,deleteMemberName, sizeof(deleteMemberName));
											
							printf("name %sdd\n", deleteMemberName);

							ListView_GetItemText(waitClient, i, 2, deleteMemberPw, 15);
							printf("pw%sdd\n", deleteMemberPw);

							if (deleteMember(deleteMemberId) == FALSE) {
								return TRUE;
							}
						}
					}

				}
								
				EndDialog(hDlg, IDOK);
				break;

			case IDCANCEL:
				EndDialog(hDlg, IDCANCEL);
				break;
			}
		return FALSE;
	}

	return FALSE;
}

void deleteRequest(TCHAR *id) {
	int i,j;
    
	if (awaitNum == 1) {
		
		FILE *fp;
		free(awaiter);
		fopen_s(&fp, "signup.txt", "w+");

		fclose(fp);

		return;
	}

	    for (i = 0; i < awaitNum; i++) {
		   if (lstrcmp(awaiter[i]->id,id) == 0) {
			  for (j = i; j < awaitNum - 1; j++) {
				
				lstrcpy(awaiter[j]->id, awaiter[j + 1]->id);
				lstrcpy(awaiter[j]->pw, awaiter[j + 1]->pw);
				lstrcpy(awaiter[j]->name, awaiter[j + 1]->name);

			    }
			
			free(awaiter[awaitNum-1]);


			awaitNum--;
		}
	}
  

          	writeRequestDelete();
}

void permissionClient(TCHAR *id, TCHAR *pw, TCHAR* name,int cnt) { //회원가입을 최종 승낙한다.
	int i,j;

	member = (MEMBER**)realloc(member, (memberNum + 1) * sizeof(MEMBER*));
	member[memberNum] = (MEMBER*)calloc(1, sizeof(MEMBER));

	
	wsprintf(member[memberNum]->id, id);
	member[memberNum]->id[lstrlen(member[memberNum]->id)] = TEXT('\0');
	wsprintf(member[memberNum]->pw, pw);
	member[memberNum]->pw[lstrlen(member[memberNum]->pw)] = TEXT('\0');
	wsprintf(member[memberNum]->name, name);
	member[memberNum]->name[lstrlen(member[memberNum]->name)] = TEXT('\0');
	lstrcpy(member[memberNum]->reservaiton ,"false");
	lstrcpy(member[memberNum]->clientCheck ,"true");
	//member[memberNum]->reservaiton[lstrlen(member[memberNum]->reservaiton)] = '\0';
	//member[memberNum]->clientCheck[lstrlen(member[memberNum]->clientCheck)] = '\0';

	//printf("%s %s %s %s %s\n", member[memberNum]->id, member[memberNum]->pw, member[memberNum]->name, member[memberNum]->clientCheck, member[memberNum]->reservaiton);
    memberNum++;  //멤버 할당 성공

	printf("멤버할당 성공 %s\n", member[memberNum - 1]->id);
    
	//승낙한 회원은 대기자에서 삭제한다.
	deleteRequest(id);

	
    writeMember(); //파일에 다시 써준다.
}

BOOL deleteMember(TCHAR *deleteMemberId) {

	int i, j;

	if (lstrcmp(deleteMemberId,"root")==0) {

		MessageBox(hWndMain, "회장은 삭제할수 없습니다!", "오류", MB_OK);
		return FALSE;
	}

	for (i = 0; i < memberNum; i++) {
		if (lstrcmp(member[i]->id, deleteMemberId) == 0) {
			for (j = i; j < memberNum - 1; j++) {

				lstrcpy(member[j]->id, member[j + 1]->id);
				lstrcpy(member[j]->pw, member[j + 1]->pw);
				lstrcpy(member[j]->name, member[j + 1]->name);

			}

			free(member[memberNum - 1]);


			memberNum--;
		}
	}


	writeMember();
	return TRUE;
}