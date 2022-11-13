#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <time.h>

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // ������ ������� ���� ���������� �� ������ ���������� �������
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

TCHAR str[60];          // ������ ��� ������
HICON hIcon;            // ������ 
HWND hBut[10];          // ������ (����), 10� - ������
unsigned int u_p[9];    // ������ ������ ��������
unsigned int u_end = 0; // ���������� ������������� ������
HBITMAP hBmp[3];        // ������� - ����� - ������� 
BOOL b_var = true;      // ������� ��� �����
static int t = 0;       // ��� �������
static int t2 = 0;      // ��� �������
static int si_zero = 0; // ����� �������
static int si_cross = 0;// ����� ���������
static int si_draw = 0; // ������



BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{

    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetTimer(hWnd, 1, 1000, NULL); 
        SendMessage(hWnd, WM_SETICON, 1, LPARAM(hIcon));                                    // ������� ��������� �� ��������� ������ ����

        for (int i = 0; i < 9; i++)
        {
            hBut[i] = GetDlgItem(hWnd, IDC_BUTTON15 + i);                       //  �������� ������
            u_p[i] = 3;
        }
        hBut[9] = GetDlgItem(hWnd, IDC_BUTTON10);                               // ���������� ������ �������
        for (int i = 0; i < 3; i++)
            hBmp[i] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1 + i));  // ���������� �������� ��������-������
        return TRUE;
    }
    case WM_COMMAND:
    {
        u_end = 0;
        for (int i = 0; i < 10; i++) // ���� ���� 
        {
            // ����� ������ ������? 
            if (wp == IDC_BUTTON15 + i)
            {
                // ������ �������
                if (b_var)
                {
                    wsprintf(str, TEXT("��� �������"));
                    SetWindowText(hWnd, str);	// ������ ��������� � ��������� ����
                    SendMessage(hBut[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[0]));
                    EnableWindow(hBut[i], FALSE);
                    u_p[i] = 0;
                    b_var = false;
                }
                // ������ �����
                else
                {
                    wsprintf(str, TEXT("��� ���������"));
                    SetWindowText(hWnd, str);	// ������ ��������� � ��������� ����
                    SendMessage(hBut[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[1]));
                    EnableWindow(hBut[i], FALSE);
                    u_p[i] = 1;
                    b_var = true;
                }

                // �������� �� ����������
                {
                    if (u_p[0] == 0 && u_p[1] == 0 && u_p[2] == 0 ||    // ����� ������� �����
                        u_p[3] == 0 && u_p[4] == 0 && u_p[5] == 0 ||    // ����� ������� �����
                        u_p[6] == 0 && u_p[7] == 0 && u_p[8] == 0 ||    // ����� ������ �����

                        u_p[0] == 0 && u_p[3] == 0 && u_p[6] == 0 ||    // ������ ����� �����
                        u_p[1] == 0 && u_p[4] == 0 && u_p[7] == 0 ||    // ������ ������� �����
                        u_p[2] == 0 && u_p[5] == 0 && u_p[8] == 0 ||    // ������ ������ ����� 

                        u_p[0] == 0 && u_p[4] == 0 && u_p[8] == 0 ||    // ��������� 1
                        u_p[2] == 0 && u_p[4] == 0 && u_p[6] == 0)      // ��������� 2
                    {
                        int res = MessageBox(hWnd, TEXT("�������� ��������\n������ �������?"), TEXT("����� ����"), MB_YESNO);
                        if (res == IDYES)
                        {
                            t2 = t = 0;                                // ����� ��������������� �� �����
                            si_cross++;
                            for (int i = 0; i < 9; i++)
                            {
                                SendMessage(hBut[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[2]));   // �������� ���������
                                EnableWindow(hBut[i], true);     // ������� ���������� ��������� 
                                u_p[i] = 3;                                 // ����� �������� �������� �� 3��

                            }
                        }
                        else
                        {
                            KillTimer(hWnd, 1);                     // ���������� ������ 
                            EndDialog(hWnd, 0);                 // ��������� ��������� ������
                            return TRUE;
                        }
                    }

                    else if (u_p[0] == 1 && u_p[1] == 1 && u_p[2] == 1 ||   // ����� ������� �����
                        u_p[3] == 1 && u_p[4] == 1 && u_p[5] == 1 ||        // ����� ������� �����
                        u_p[6] == 1 && u_p[7] == 1 && u_p[8] == 1 ||        // ����� ������ �����

                        u_p[0] == 1 && u_p[3] == 1 && u_p[6] == 1 ||        // ������ ����� �����
                        u_p[1] == 1 && u_p[4] == 1 && u_p[7] == 1 ||        // ������ ������� �����
                        u_p[2] == 1 && u_p[5] == 1 && u_p[8] == 1 ||        // ������ ������ ����� 

                        u_p[0] == 1 && u_p[4] == 1 && u_p[8] == 1 ||        // ��������� 1
                        u_p[2] == 1 && u_p[4] == 1 && u_p[6] == 1)          // ��������� 2
                    {
                        int res = MessageBox(hWnd, TEXT("������ ��������\n������ �������?"), TEXT("����� ����"), MB_YESNO);
                        if (res == IDYES)
                        {
                            t2 = t = 0;
                            si_zero++;
                            for (int i = 0; i < 9; i++)
                            {
                                SendMessage(hBut[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[2]));
                                EnableWindow(hBut[i], true);
                                u_p[i] = 3;
                            }
                        }
                        else
                        {
                            KillTimer(hWnd, 1);
                            EndDialog(hWnd, 0); // ��������� ��������� ������
                            return TRUE;
                        }
                        break;
                    }

                    for (int i = 0; i < 9; i++)                             // �������� �� �����
                    {
                        if (u_p[i] == 3)
                        {
                            u_end++;
                            break;
                        }
                    }
                    if (u_end == 0) // ���� ���� ���� ���� ������ 
                    {
                        int res = MessageBox(hWnd, TEXT("�����\n������ �������?"), TEXT("����� ����"), MB_YESNO);
                        if (res == IDYES)
                        {
                            t2 = t = 0;
                            si_draw++;
                            for (int i = 0; i < 9; i++)
                            {
                                SendMessage(hBut[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(hBmp[2]));
                                EnableWindow(hBut[i], true);
                                u_p[i] = 3;
                            }
                        }
                        else
                        {
                            KillTimer(hWnd, 1);
                            EndDialog(hWnd, 0); // ��������� ��������� ������
                            return TRUE;
                        }
                    }
                }
            }
        }

    }
    break;
    case WM_TIMER:
        t += 1;	// ���������� ������
        if (t == 60)
        {
            t -= 60;
            t2++;
        }
        if (t < 10)
            wsprintfW(str, TEXT("������ ������� = %d, ��������� = %d, ������ = %d   ������: %d : 0%d"), si_zero, si_cross, si_draw, t2, t);
        else
            wsprintfW(str, TEXT("������ ������� = %d, ��������� = %d, ������ = %d   ������: %d : %d"), si_zero, si_cross, si_draw, t2, t);
        SendMessage(hBut[9], WM_SETTEXT, 0, LPARAM(str));
        break;
    case WM_CLOSE:
        EndDialog(hWnd, 0); // ��������� ��������� ������
        return TRUE;
    }
    return FALSE;
}