#include <windows.h>
#include <string.h>
#include "E:\\Windows_API\\define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND     hwnd;  //���ھ��
    MSG      msg;  //��Ϣ
    WNDCLASS wndclass;  //������

    hInst=hInstance;

    /**********�ڢٲ���ע�ᴰ����**********/
    //Ϊ������ĸ����ֶθ�ֵ
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //���ڷ��
    wndclass.lpfnWndProc  = WndProc;  //���ڹ���
    wndclass.cbClsExtra   = 0;  //��ʱ����Ҫ���
    wndclass.cbWndExtra   = 0;  //��ʱ����Ҫ���
    wndclass.hInstance    = hInstance;  //��ǰ���ھ��
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //����ͼ��
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //�����ʽ
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //���ڱ�����ˢ
    wndclass.lpszMenuName = NULL ;  //���ڲ˵�
    wndclass.lpszClassName= szClassName;  //��������

    //ע�ᴰ��
    RegisterClass(&wndclass);

    /*****�ڢڲ�����������(���ô�����ʾ����)*****/
    hwnd=CreateWindow(
        szClassName,  //�����������
        TEXT("�û�"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        500,  //��ʼ��ʱx���λ��
        250,  //��ʼ��ʱy���λ��
        500,  //���ڿ��
        300,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

    /**********�ڢ۲�����Ϣѭ��**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
    }
    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    extern struct user user[1000];

    //��ʱ�ӵ�
    static int pos=0;
    static int UserAns=2;
    static int UserPos=0;
    strcpy(user[1].Name,"test");
    strcpy(user[1].Password,"123456");
    strcpy(user[2].Name,"John");
    strcpy(user[2].Password,"12345678");

    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    MSG msg;
    HDC hdc;
    RECT rc;
    POINT p;

//��ʼ�����
    static INT initCursor=0;
//1:��¼ 2:ע�� 3:��������
    static INT LoginMode=1;
//����
    static HFONT hFont;
//��¼ ע��
    static HWND hLabUsername;
    static HWND hLabPassword;
    static HWND hEditUsername;
    static HWND hEditPassword;
//��������
    static HWND hLabNewPassword;
    static HWND hEditNewPassword;
//��ť:��¼ ע�� ��������
    static HWND hBtnLogin;
    static HWND hBtnRegister;
    static HWND hBtnReset;
//ȷ�ϰ�ť
    static HWND hBtnSubmit;
    static HPEN hPenRed,hPenWhite;

    TCHAR szUsername[50];
    TCHAR szPassword[50];
    TCHAR szNewPassword[50];
    TCHAR szUserInfo[200];

    RegisterHotKey(NULL,0x0001,MOD_CONTROL,'W');
    RegisterHotKey(NULL,0x0002,VK_TAB,NULL);
    RegisterHotKey(NULL,0x0003,VK_RETURN,NULL);

    switch(message)
    {
        case WM_CREATE:
            //��������
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //��������
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hLabUsername=CreateWindow(
                TEXT("static"),TEXT("�û��� "),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                70,50,70,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            hLabPassword=CreateWindow(
                TEXT("static"),TEXT("���� "),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                70,90,70,26,
                hWnd,(HMENU)2,hInst,NULL
            );

            hEditUsername=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                150,50,200,26,
                hWnd,(HMENU)3,hInst,NULL
            );

            hEditPassword=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
                150,90,200,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            hLabNewPassword=CreateWindow(
                TEXT("static"),TEXT(""),
                WS_CHILD | SS_CENTERIMAGE | SS_RIGHT,
                70,130,70,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            hEditNewPassword=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD,
                150,130,200,26,
                hWnd,(HMENU)6,hInst,NULL
            );
            //ģʽ:��¼
            hBtnLogin=CreateWindow(
                TEXT("button"),TEXT("��¼"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                280,220,50,25,
                hWnd,(HMENU)7,hInst,NULL
            );
            //ģʽ:ע��
            hBtnRegister=CreateWindow(
                TEXT("button"),TEXT("ע��"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                335,220,50,25,
                hWnd,(HMENU)8,hInst,NULL
            );
            //ģʽ:��������
            hBtnReset=CreateWindow(
                TEXT("button"),TEXT("��������"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                390,220,80,25,
                hWnd,(HMENU)9,hInst,NULL
            );
            //ȷ�ϰ�ť
            hBtnSubmit=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                210,170,80,40,
                hWnd,(HMENU)10,hInst,NULL
            );

            SendMessage(hLabUsername,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditUsername,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabNewPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditNewPassword,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnLogin,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnRegister,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnReset,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnSubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch(wmId)
            {
                //��¼
                case 7:
                    SetWindowText(hLabPassword,"���� ");
                    ShowWindow(hLabNewPassword,SW_HIDE);
                    ShowWindow(hEditNewPassword,SW_HIDE);
                    LoginMode=1;
                    //��ͼ
                    hdc=GetDC(hWnd);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,335,220,NULL);
                    LineTo(hdc,335,245);
                    LineTo(hdc,385,245);
                    LineTo(hdc,385,220);
                    LineTo(hdc,335,220);
                    MoveToEx(hdc,390,220,NULL);
                    LineTo(hdc,390,245);
                    LineTo(hdc,470,245);
                    LineTo(hdc,470,220);
                    LineTo(hdc,390,220);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,280,220,NULL);
                    LineTo(hdc,280,245);
                    LineTo(hdc,330,245);
                    LineTo(hdc,330,220);
                    LineTo(hdc,280,220);

                    //�������λ��
                    GetWindowText(hEditUsername,szUsername,50);
                    if (strcmp(szUsername,"")==0)
                    {
                        GetWindowRect(hEditUsername,&rc);
                        SetCursorPos(rc.left,rc.top);
                        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    }
                    else
                    {
                        GetWindowText(hEditPassword,szPassword,50);
                        if (strcmp(szPassword,"")==0)
                        {
                            GetWindowRect(hEditPassword,&rc);
                            SetCursorPos(rc.left,rc.top);
                            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        }
                        else
                        {
                            GetWindowRect(hBtnSubmit,&rc);
                            SetCursorPos(rc.left+40,rc.top+20);
                        }
                    }
                    break;
                //ע��
                case 8:
                    SetWindowText(hLabNewPassword,"����һ�� ");
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    LoginMode=2;
                    //��ͼ
                    hdc=GetDC(hWnd);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,280,220,NULL);
                    LineTo(hdc,280,245);
                    LineTo(hdc,330,245);
                    LineTo(hdc,330,220);
                    LineTo(hdc,280,220);
                    MoveToEx(hdc,390,220,NULL);
                    LineTo(hdc,390,245);
                    LineTo(hdc,470,245);
                    LineTo(hdc,470,220);
                    LineTo(hdc,390,220);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,335,220,NULL);
                    LineTo(hdc,335,245);
                    LineTo(hdc,385,245);
                    LineTo(hdc,385,220);
                    LineTo(hdc,335,220);
                    //�������λ��
                    GetWindowText(hEditUsername,szUsername,50);
                    if (strcmp(szUsername,"")==0)
                    {
                        GetWindowRect(hEditUsername,&rc);
                        SetCursorPos(rc.left,rc.top);
                        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    }
                    else
                    {
                        GetWindowText(hEditPassword,szPassword,50);
                        if (strcmp(szPassword,"")==0)
                        {
                            GetWindowRect(hEditPassword,&rc);
                            SetCursorPos(rc.left,rc.top);
                            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        }
                        else
                        {
                            GetWindowText(hEditNewPassword,szPassword,50);
                            if (strcmp(szPassword,"")==0)
                            {
                                GetWindowRect(hEditNewPassword,&rc);
                                SetCursorPos(rc.left,rc.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            else
                            {
                                GetWindowRect(hBtnSubmit,&rc);
                                SetCursorPos(rc.left+40,rc.top+20);
                            }
                        }
                    }
                    break;
                //��������
                case 9:
                    SetWindowText(hLabPassword,"������ ");
                    SetWindowText(hLabNewPassword,"������ ");
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    LoginMode=3;
                    UpdateWindow(hWnd);
                    //��ͼ
                    hdc=GetDC(hWnd);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,280,220,NULL);
                    LineTo(hdc,280,245);
                    LineTo(hdc,330,245);
                    LineTo(hdc,330,220);
                    LineTo(hdc,280,220);
                    MoveToEx(hdc,335,220,NULL);
                    LineTo(hdc,335,245);
                    LineTo(hdc,385,245);
                    LineTo(hdc,385,220);
                    LineTo(hdc,335,220);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,390,220,NULL);
                    LineTo(hdc,390,245);
                    LineTo(hdc,470,245);
                    LineTo(hdc,470,220);
                    LineTo(hdc,390,220);

                    //�������λ��
                    GetWindowText(hEditUsername,szUsername,50);
                    if (strcmp(szUsername,"")==0)
                    {
                        GetWindowRect(hEditUsername,&rc);
                        SetCursorPos(rc.left,rc.top);
                        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    }
                    else
                    {
                        GetWindowText(hEditPassword,szPassword,50);
                        if (strcmp(szPassword,"")==0)
                        {
                            GetWindowRect(hEditPassword,&rc);
                            SetCursorPos(rc.left,rc.top);
                            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                        }
                        else
                        {
                            GetWindowText(hEditNewPassword,szPassword,50);
                            if (strcmp(szPassword,"")==0)
                            {
                                GetWindowRect(hEditNewPassword,&rc);
                                SetCursorPos(rc.left,rc.top);
                                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                                mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                            }
                            else
                            {
                                GetWindowRect(hBtnSubmit,&rc);
                                SetCursorPos(rc.left+40,rc.top+20);
                            }
                        }
                    }
                    break;
                //�ύ
                case 10:
                    GetWindowText(hEditUsername,szUsername,100);
                    GetWindowText(hEditPassword,szPassword,100);
                    GetWindowText(hEditNewPassword,szNewPassword,100);
                    switch(LoginMode)
                    {
                            //��¼
                            case 1:
                                //����û�������
                                pos=find_name(UserAns,szUsername);
                                if (pos==0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���¼ʧ�ܣ�\r\n�û�������\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                }
                                //������벻��ȷ
                                else if (strcmp(szPassword,user[pos].Password)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���¼ʧ�ܣ�\r\n�������벻��ȷ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                }
                                //����ɹ�
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("%s\r\n��¼�ɹ�"),hEditUsername);
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_OK);
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                            //ע��
                            case 2:
                                //����û��Ѿ�����
                                if (find_name(UserAns,szUsername)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ʧ�ܣ�\r\n�û��Ѿ�����\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //������������С��6λ
                                else if (strlen(szPassword)<6)
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ʧ�ܣ�\r\n���õ�����Ӧ��С��6λ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //���������������벻һ��
                                else if (strcmp(szPassword,szNewPassword)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ʧ�ܣ�\r\n������������벻һ��\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //����ɹ�
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("�û�ע��ɹ���\r\n�û��˺ţ�%s\r\n�û����룺%s"),szUsername,szPassword);
                                    UserAns++;
                                    strcpy(user[UserAns].Name,szUsername);
                                    strcpy(user[UserAns].Password,szPassword);
                                    InitUser(UserAns);
                                    wsprintf(szUserInfo,TEXT("�������Ƹ�����Ϣ"));
                                    int nSelect=MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_YESNO);
                                    if (nSelect==IDYES)
                                    {
                                        //���Ƹ�����Ϣ
                                    }
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                            //��������
                            case 3:
                                //����û�������
                                pos=find_name(UserAns,szUsername);
                                if (pos==0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ʧ�ܣ�\r\n�û�������\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //�����������벻��ȷ
                                else if (strcmp(szPassword,user[pos].Password)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ʧ�ܣ�\r\n�������벻��ȷ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //��������������С��6λ
                                else if (strlen(szNewPassword)<6)
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ʧ�ܣ�\r\n���õ�����Ӧ��С��6λ\r\n����������"));
                                    MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_ICONINFORMATION);
                                    //������������
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //����ɹ�
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("�û���������ɹ���\r\n�û��˺ţ�%s\r\n���û����룺%s"),szUsername,szNewPassword);
                                    strcpy(user[pos].Password,szPassword);
                                    wsprintf(szUserInfo,TEXT("�������Ƹ�����Ϣ"));
                                    int nSelect=MessageBox(hWnd,szUserInfo,TEXT("��Ϣ����"),MB_YESNO);
                                    if (nSelect==IDYES)
                                    {
                                        //���Ƹ�����Ϣ
                                    }
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;

                            default:
                                return DefWindowProc(hWnd,message,wParam,lParam);
                    }
            }
            break;

        case WM_KEYDOWN:
            switch((TCHAR)wParam)
            {
                case VK_RETURN:
                    SendMessage(hWnd,WM_COMMAND,(WPARAM)10,0);
                    break;
                default:
                    return DefWindowProc(hWnd, message, wParam, lParam);
            }
            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            //ѡ���� ��ʼ����¼״̬
            static INT initPaint=0;
            if (initPaint==0)
            {
                hdc=GetDC(hWnd);
                SelectObject(hdc,hPenRed);
                MoveToEx(hdc,280,220,NULL);
                LineTo(hdc,280,245);
                LineTo(hdc,330,245);
                LineTo(hdc,330,220);
                LineTo(hdc,280,220);
                initPaint=1;
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            DeleteObject(hFont);
            DeleteObject(hPenRed);
            DeleteObject(hPenWhite);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
//    free(user);
    return 0;
}
