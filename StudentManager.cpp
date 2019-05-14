// StudentManager.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "StudentManager.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

struct LOGIN_INFO {								//로그인 
	char name[100];
	char password[20];
};

LOGIN_INFO g_sLoginInfo;
HWND g_MainWnd;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
INT_PTR CALLBACK    DlgProc1(HWND, UINT, WPARAM, LPARAM);	
INT_PTR CALLBACK    DlgProc2(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgProc3(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DlgProc4(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	hInst = hInstance;

	//Login Dialog
	if (DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), 0, DlgProc2) == -1)
		return 0;
	
	// Main Dialog
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DlgProc1);
	return 0;
}

// Main Dialog
INT_PTR CALLBACK DlgProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	char string[100];
	switch (message)
	{
	case WM_INITDIALOG:
		g_MainWnd = hDlg;
		sprintf(string, "%s", "Score Management Program");
		SetWindowText(hDlg, string);
		return (INT_PTR)TRUE;

	case WM_CLOSE:
		EndDialog(hDlg,0);
		return(INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_32771:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3),hDlg, DlgProc3);
			sprintf(string, "Score Management Program ver 0.0 / Mr.%s Hello", g_sLoginInfo.name);
			SetWindowText(g_MainWnd, string);
			return(INT_PTR)TRUE;
		case ID_32772:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG4), hDlg, DlgProc4);
			return(INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

//Login Dialog
INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//file pointer
	FILE *fp;
	static LOGIN_INFO sLoginInfo;
	static HWND hIDWnd, hPassword;
	LOGIN_INFO sInputLogin;
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
		//open secret text file 
		//text in secret text file get to sLogininfo struct
	case WM_INITDIALOG:
		fp = fopen("secret.txt", "r");
		fscanf(fp, "%s %s", sLoginInfo.name, sLoginInfo.password);
		fclose(fp);
		return (INT_PTR)TRUE;

		//Dialog close
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//Click OK Button
		case IDOK:
			// Entering values in Dialog get to each struct variable
			GetDlgItemText(hDlg, IDC_EDIT1, sInputLogin.name, 12);
			GetDlgItemText(hDlg, IDC_EDIT2, sInputLogin.password, 12);

			//Compare sLoginInfo's name value with sInputLogin's name value
			if (strcmp(sLoginInfo.name, sInputLogin.name) != 0)
			{
				MessageBox(0, "ID is invalid", "Error", MB_OK);
				SetDlgItemText(hDlg, IDC_EDIT1, "");
				SetFocus(GetDlgItem(hDlg, IDC_EDIT1));
				return (INT_PTR)TRUE;						
			}
			//Compare sLoginInfo's password value with sInputLogin's password value
			if (strcmp(sLoginInfo.password, sInputLogin.password) != 0)
			{
				MessageBox(0, "Password is invalid", "Error", MB_OK);
				SetDlgItemText(hDlg, IDC_EDIT2, "");
				SetFocus(GetDlgItem(hDlg, IDC_EDIT2));
				return (INT_PTR)TRUE;						
			}

			//If all pass, Set Current sLogininfo vale as g_sLoginInfo value
			memcpy(&g_sLoginInfo, &sLoginInfo, sizeof(LOGIN_INFO));
			EndDialog(hDlg, 1);				//winmain의 첫 dialogbox로 값을 전달
			return (INT_PTR)TRUE;

			//Click Cancel Button 
		case IDCANCEL:
			EndDialog(hDlg, -1);			//winmain의 첫 dialogbox로 값을 전달
			return (INT_PTR)TRUE;

		}
	}
	return (INT_PTR)FALSE;
}

// Modify ID & Password
INT_PTR CALLBACK DlgProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LOGIN_INFO sLoginInfo;
	char string[100];
	FILE *fp;
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
		//SET current ID to edit control
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT1, g_sLoginInfo.name);
		return (INT_PTR)TRUE;
		
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return(INT_PTR)TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//Click OK Button
		case IDOK:
			//set edit control value to each variable value 
			GetDlgItemText(hDlg, IDC_EDIT2, sLoginInfo.name, 12);
			GetDlgItemText(hDlg, IDC_EDIT3, sLoginInfo.password, 12);
			GetDlgItemText(hDlg, IDC_EDIT4, string, 12);
			
			//compare password to change with password verification
			if (strcmp(sLoginInfo.password, string) != 0)
			{
				MessageBox(0, "비밀번호가 다릅니다.", "에러", MB_OK);
				SetDlgItemText(hDlg, IDC_EDIT3, "");
				SetDlgItemText(hDlg, IDC_EDIT4, "");
				SetFocus(GetDlgItem(hDlg, IDC_EDIT3));
				return (INT_PTR)TRUE;
			}

			//If all pass, save changed value to secret.txt file
			fp = fopen("secret.txt", "w");
			fprintf(fp, "%s %s", sLoginInfo.name,sLoginInfo.password);
			fclose(fp);
			//Set current sLoginInfo to g_sLoginIngo
			memcpy(&g_sLoginInfo, &sLoginInfo, sizeof(LOGIN_INFO));
			EndDialog(hDlg, 0);				
			return (INT_PTR)TRUE;

		case IDCANCEL:
			EndDialog(hDlg, LOWORD(lParam));			
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

