 #include "login.h"

TCHAR id[30];
TCHAR pw[30];
HWND hLoginDlg;
MEMBER **awaiter;  //회원승낙 되기 전까지 대기자들

BOOL CALLBACK LoginProc(HWND hDIg, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	switch (iMessage) {

	case WM_INITDIALOG:
		hLoginDlg = hDIg;
		return TRUE;

	case WM_COMMAND:

					switch (LOWORD(wParam)) {
					case IDC_ID:
					case IDC_PW:

						switch (HIWORD(wParam)) {
						case EN_CHANGE:	
							GetDlgItemText(hDIg, IDC_ID, id, 30);
							GetDlgItemText(hDIg, IDC_PW, pw, 30);

							break;
						}

						return TRUE;

					case IDC_SIGNUP:
						if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_signUp), hDIg, SignInProc) == IDOK) {
							MessageBox(hDIg, "회원승인이 될때까지 기다려주세요", "회원가입 완료", MB_OK);
						}

						return TRUE;

					case IDOK:  //여기서 아이디와 패스워드 txt파일에서 체크하기
			
						if (identify(id, pw) == true) {
							EndDialog(hDIg, IDOK);
						}

						return TRUE;

	        	
					case IDCANCEL:
						PostQuitMessage(0);
						return TRUE;

					}
					break;
		
				}
	return FALSE;

}

BOOL CALLBACK SignInProc(HWND hDIg, UINT iMessage, WPARAM wParam, LPARAM lParam) { //회원 가입 대화상자

	HWND hId, hPw, hName;
	static TCHAR signId[30], signpw[30], signName[10];
	

	switch (iMessage) {

	case WM_INITDIALOG:
		
						hId = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER|ES_AUTOHSCROLL, 100, 50, 100, 20, hDIg, (HMENU)IDC_signId, g_hInst, NULL);
						hPw = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 100, 90, 100, 20, hDIg, (HMENU)IDC_signpw, g_hInst, NULL);
						hName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 100, 130, 100, 20, hDIg, (HMENU)IDC_signName, g_hInst, NULL);

						SendMessage(hId, EM_LIMITTEXT,20, 0); //에디트들 글자 수 제한
						SendMessage(hPw, EM_LIMITTEXT, 15, 0);
						SendMessage(hName, EM_LIMITTEXT, 8, 0);


		return TRUE;

	case WM_COMMAND:

						switch (LOWORD(wParam)){
						case IDC_signId:
						case IDC_signpw:
						case IDC_signName:
							switch (HIWORD(wParam)) {
							case EN_CHANGE:
								GetDlgItemText(hDIg, IDC_signId, signId, 30);
								GetDlgItemText(hDIg, IDC_signpw, signpw, 30);
								GetDlgItemText(hDIg, IDC_signName, signName, 10);
								break;
							}
							return TRUE;
						case IDOK:

							if (lstrlen(signId) >=3 && lstrlen(signpw) >=4 && lstrlen(signName) >=2) {
							   
								if (idOverlapCheck(signId) == true) {//아이디는 중복이 되면 안됨
									writeWait(signId, signpw, signName); //회원가입 txt에 대기정보를 기록한다.
									lstrcpy(signId, "");  //값을 받는 변수들은 다시 초기화
									lstrcpy(signpw, "");
									lstrcpy(signName, "");
									EndDialog(hDIg, IDOK);

								}
								else {
									MessageBox(hDIg, "아이디 중복 입니다.", "입력 오류", MB_OK);
								}
								
								
							}
							else {
								MessageBox(hDIg, "입력을 제대로 해주세요", "입력 오류", MB_OK);
								
							}

							lstrcpy(signId, "");
							lstrcpy(signpw, "");
							lstrcpy(signName, "");
							return TRUE;
						
						case IDCANCEL:
							
							EndDialog(hDIg, IDCANCEL);
							return TRUE;
						}

						break;
					}

	     return FALSE;
}

bool identify(TCHAR *id, TCHAR *pw) {

	int i=0;

	  if (strcmp(id,"")==0 || strcmp(pw,"")==0 ) {
		printf("입력안했지롱");
		return false;
	}  
	  //회원 체크 
	while (i<memberNum) {
		
		//printf("%d번째", i + 1);

		if (lstrcmp(member[i]->id, id) == 0) {
			
			if (lstrcmp(member[i]->pw, pw) != 0) {
				MessageBox(hLoginDlg, "땡~~~~~~비번 틀렸대요", "오류", MB_OK);
				return false;
			}
			else {
				if (lstrcmp(member[i]->clientCheck , "true")==0) {
					current = member[i];  //로그인이 완료됨
					return true;
				}
				else {
					MessageBox(hLoginDlg, "승낙 기다리세요^___^", "ㄱㄷㄱㄷ", MB_OK);
					return false;
				}
			}
		}

		i++;
	}

	return false;
}

bool idOverlapCheck(TCHAR *signId) {

	int i;

	for (i = 0; i < memberNum; i++) {
		if (lstrcmp(member[i]->id, signId) == 0)
			return false;
	}


	return true;
}