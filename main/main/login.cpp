 #include "login.h"

TCHAR id[30];
TCHAR pw[30];
HWND hLoginDlg;
MEMBER **awaiter;  //ȸ���³� �Ǳ� ������ ����ڵ�

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
							MessageBox(hDIg, "ȸ�������� �ɶ����� ��ٷ��ּ���", "ȸ������ �Ϸ�", MB_OK);
						}

						return TRUE;

					case IDOK:  //���⼭ ���̵�� �н����� txt���Ͽ��� üũ�ϱ�
			
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

BOOL CALLBACK SignInProc(HWND hDIg, UINT iMessage, WPARAM wParam, LPARAM lParam) { //ȸ�� ���� ��ȭ����

	HWND hId, hPw, hName;
	static TCHAR signId[30], signpw[30], signName[10];
	

	switch (iMessage) {

	case WM_INITDIALOG:
		
						hId = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER|ES_AUTOHSCROLL, 100, 50, 100, 20, hDIg, (HMENU)IDC_signId, g_hInst, NULL);
						hPw = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 100, 90, 100, 20, hDIg, (HMENU)IDC_signpw, g_hInst, NULL);
						hName = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 100, 130, 100, 20, hDIg, (HMENU)IDC_signName, g_hInst, NULL);

						SendMessage(hId, EM_LIMITTEXT,20, 0); //����Ʈ�� ���� �� ����
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
							   
								if (idOverlapCheck(signId) == true) {//���̵�� �ߺ��� �Ǹ� �ȵ�
									writeWait(signId, signpw, signName); //ȸ������ txt�� ��������� ����Ѵ�.
									lstrcpy(signId, "");  //���� �޴� �������� �ٽ� �ʱ�ȭ
									lstrcpy(signpw, "");
									lstrcpy(signName, "");
									EndDialog(hDIg, IDOK);

								}
								else {
									MessageBox(hDIg, "���̵� �ߺ� �Դϴ�.", "�Է� ����", MB_OK);
								}
								
								
							}
							else {
								MessageBox(hDIg, "�Է��� ����� ���ּ���", "�Է� ����", MB_OK);
								
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
		printf("�Է¾�������");
		return false;
	}  
	  //ȸ�� üũ 
	while (i<memberNum) {
		
		//printf("%d��°", i + 1);

		if (lstrcmp(member[i]->id, id) == 0) {
			
			if (lstrcmp(member[i]->pw, pw) != 0) {
				MessageBox(hLoginDlg, "��~~~~~~��� Ʋ�ȴ��", "����", MB_OK);
				return false;
			}
			else {
				if (lstrcmp(member[i]->clientCheck , "true")==0) {
					current = member[i];  //�α����� �Ϸ��
					return true;
				}
				else {
					MessageBox(hLoginDlg, "�³� ��ٸ�����^___^", "��������", MB_OK);
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