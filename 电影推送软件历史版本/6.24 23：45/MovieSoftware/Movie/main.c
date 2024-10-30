#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include "E:\\MovieSoftware\\define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void fileopen_movie();
void fileopen_user();

HINSTANCE hInst;
long total_movie,total_user,CurrentUser;
struct movie movie[1000];
struct user user[1000];

int vis_press=0;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
){
//���ݶ���
    fileopen_movie();
    fileopen_user();

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
        TEXT(""),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        200,  //��ʼ��ʱx���λ��
        5,  //��ʼ��ʱy���λ��
        1000,  //���ڿ��
        820,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    ShowWindow(hwnd,iCmdShow);
    UpdateWindow(hwnd);

            //��ʼ������
            SendMessage(hwnd,WM_PAINT,(WPARAM)0,NULL);

    /**********�ڢ۲�����Ϣѭ��**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage(&msg);  //������Ϣ
        //�ۿ���ʽ
        switch(msg.message)
        {
            case WM_KEYDOWN:
                //�ۿ���ʽ��ѡ��
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('1')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)5,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('2')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)6,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('3')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)7,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('4')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)8,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('5')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)9,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('6')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)10,NULL);
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('7')<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)11,NULL);
                //���ҷ���� PageHome PageEnd �޸�ҳ��
                if (GetKeyState(VK_HOME)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)14,NULL);
                if (GetKeyState(VK_END)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)15,NULL);
                //PageUP PageDown �޸�ҳ��
                if (GetKeyState(VK_PRIOR)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)12,NULL);
                if (GetKeyState(VK_NEXT)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)13,NULL);
                //�رմ���
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('W')<0)
                    SendMessage(hwnd,WM_DESTROY,NULL,NULL);
                //�����޸�ҳ�����ı���
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('P')<0)
                    SendMessage(hwnd,WM_COMMAND,100,NULL);
            break;
        }
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    static HPEN hPenRed;
    static HPEN hPenWhite;
    //����
    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
    //�û�����
    static HWND hBtnUser;
    static HWND hBtnUserInformation;
    static HWND hBtnWatchingHistory;
    //�ۿ���ʽ
    static HWND hLabShowMode;
    static HWND hBtnShowMode1;
    static HWND hBtnShowMode2;
    static HWND hBtnShowMode3;
    static HWND hBtnShowMode4;
    static HWND hBtnShowMode5;
    static HWND hBtnShowMode6;
    static HWND hBtnShowMode7;
    //��ʾҳ��,�ı�ҳ��
    static HWND hBtnPageUp;
    static HWND hBtnPageDown;
    static HWND hBtnPageBegin;
    static HWND hBtnPageEnd;
    static HWND hEditPage;
    static HWND hLabTotalPage;
    //��Ӱ��ʾ����
    static HWND hBtnMovieShow[10];

    TCHAR szTextBuf[100];

    //Ҫ����Ĳ���
    int i,j;
    static bool vis_Page=true;
    //LoginMode:0 δ��¼ 1:�ѵ�¼
    //DrawpΪ֮ǰѡ�Ĳ���,DrawqΪ����ѡ�Ĳ���
    static int LoginMode=1,ShowMode=1,DrawPrevious=1,DrawCurrent=1;
    static int EditPage=1,CurrentPage=1,TotalPage=10,MovieShowPos,MovieShowTotal=7;

    switch(message)
    {
        case WM_CREATE:
            //��������
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //��������
            hFont=CreateFont(
                -18,-9,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontTitle=CreateFont(
                -22,-11,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            hFontNumber=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );

            if (LoginMode==1) sprintf(szTextBuf,TEXT("�ѵ�¼"));
                else sprintf(szTextBuf,TEXT("���¼"));
            hBtnUser=CreateWindow(
                TEXT("button"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                700,20,60,30,
                hWnd,(HMENU)1,hInst,NULL
            );

            hBtnUserInformation=CreateWindow(
                TEXT("button"),TEXT("�û���Ϣ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                780,20,80,30,
                hWnd,(HMENU)2,hInst,NULL
            );
            if (LoginMode==0) ShowWindow(hBtnUserInformation,SW_HIDE);

            hBtnWatchingHistory=CreateWindow(
                TEXT("button"),TEXT("�ۿ���ʷ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                880,20,80,30,
                hWnd,(HMENU)3,hInst,NULL
            );
            if (LoginMode==0) ShowWindow(hBtnWatchingHistory,SW_HIDE);
            //��ʾ��ģʽ:��Ӱ����ʺ����顢��ӳʱ�䡢�������֡��û����֡�ר������
            hLabShowMode=CreateWindow(
                TEXT("static"),TEXT("�ۿ���ʽ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                30,200,80,30,
                hWnd,(HMENU)4,hInst,NULL
            );

            hBtnShowMode1=CreateWindow(
                TEXT("button"),TEXT("��Ӱ���"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,240,80,30,
                hWnd,(HMENU)5,hInst,NULL
            );

            hBtnShowMode2=CreateWindow(
                TEXT("button"),TEXT("�ʺ�����"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,280,80,30,
                hWnd,(HMENU)6,hInst,NULL
            );

            hBtnShowMode3=CreateWindow(
                TEXT("button"),TEXT("��ӳʱ��"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,320,80,30,
                hWnd,(HMENU)7,hInst,NULL
            );

            hBtnShowMode4=CreateWindow(
                TEXT("button"),TEXT("��������"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,360,80,30,
                hWnd,(HMENU)8,hInst,NULL
            );

            hBtnShowMode5=CreateWindow(
                TEXT("button"),TEXT("�û�����"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,400,80,30,
                hWnd,(HMENU)9,hInst,NULL
            );

            hBtnShowMode6=CreateWindow(
                TEXT("button"),TEXT("ר������"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,440,80,30,
                hWnd,(HMENU)10,hInst,NULL
            );

            hBtnShowMode7=CreateWindow(
                TEXT("button"),TEXT("�û�ģʽ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,480,80,30,
                hWnd,(HMENU)11,hInst,NULL
            );

            hBtnPageUp=CreateWindow(
                TEXT("button"),TEXT("<"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_LEFT | BS_VCENTER,
                800,650,30,30,
                hWnd,(HMENU)12,hInst,NULL
            );

            hBtnPageDown=CreateWindow(
                TEXT("button"),TEXT(">"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_RIGHT | BS_VCENTER,
                900,650,30,30,
                hWnd,(HMENU)13,hInst,NULL
            );

            hBtnPageBegin=CreateWindow(
                TEXT("button"),TEXT("<<"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_LEFT | BS_VCENTER,
                765,650,30,30,
                hWnd,(HMENU)14,hInst,NULL
            );

            hBtnPageEnd=CreateWindow(
                TEXT("button"),TEXT(">>"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_RIGHT | BS_VCENTER,
                935,650,30,30,
                hWnd,(HMENU)15,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("%d"),CurrentPage);
            hEditPage=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                835,650,60,30,
                hWnd,(HMENU)16,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("����%dҳ"),TotalPage);
            hLabTotalPage=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                765,700,200,30,
                hWnd,(HMENU)17,hInst,NULL
            );

//            MovieShowPos=(CurrentPage-1)*10;
//                    MovieShowPos++;
//                    if (MovieShowPos>MovieShowTotal) break;
            for (i=0;i<10;i++)
                hBtnMovieShow[i]=CreateWindow(
                    TEXT("button"),TEXT(""),
                    WS_CHILD | WS_VISIBLE | WS_BORDER | BS_RIGHT | BS_VCENTER,
                    120+(i%5)*170,300+(i/5)*270,150,30,
                    hWnd,(HMENU)(18+i),hInst,NULL
                );
            for (i=TotalPage+1;i<=10;i++)
                ShowWindow(hBtnMovieShow[i],SW_HIDE);

            //�û�����
            SendMessage(hBtnUser,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnUserInformation,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnWatchingHistory,WM_SETFONT,(WPARAM)hFont,NULL);
            //�ۿ���ʽ
            SendMessage(hLabShowMode,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode1,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode2,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode3,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode4,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode5,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode6,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode7,WM_SETFONT,(WPARAM)hFont,NULL);
            //��ʾҳ��,�ı�ҳ��
            SendMessage(hBtnPageUp,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnPageDown,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditPage,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hLabTotalPage,WM_SETFONT,(WPARAM)hFont,NULL);
            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                //Ctrl+P
                case 100:
                    if (vis_press==2) break;
                    else if (vis_press==1) vis_press=2;
                    GetWindowRect(hEditPage,&rect);
                    SetCursorPos(rect.left,rect.top);
                    mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    mouse_event(MOUSEEVENTF_LEFTUP | MOUSEEVENTF_ABSOLUTE,0,0,0,0);
                    break;

                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    DrawPrevious=DrawCurrent;
                    DrawCurrent=wmId-4;
                    ShowMode=wmId-4;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)wParam,NULL);
                    break;
                //PageUp
                case 12:
                    if (vis_press==2) break;
                    else if (vis_press==1) vis_press=2;
                    if (CurrentPage!=1)
                    {
                        CurrentPage--;
                        sprintf(szTextBuf,TEXT("%d"),CurrentPage);
                        SetWindowText(hEditPage,szTextBuf);
                        //��ת
                    }
                    break;
                //PageDown
                case 13:
                    if (CurrentPage!=TotalPage)
                    {
                        CurrentPage++;
                        sprintf(szTextBuf,TEXT("%d"),CurrentPage);
                        SetWindowText(hEditPage,szTextBuf);
                        //��ת
                    }
                    break;
                //PageBegin
                case 14:
                    sprintf(szTextBuf,TEXT("%d"),1);
                    SetWindowText(hEditPage,szTextBuf);
                    //��ת
                    break;
                //PageEnd
                case 15:
                    sprintf(szTextBuf,TEXT("%d"),TotalPage);
                    SetWindowText(hEditPage,szTextBuf);
                    //��ת
                    break;
                //ҳ���༭
                case 16:
                    GetWindowText(hEditPage,szTextBuf,100);
                    if (strlen(szTextBuf)==0) break;
                    vis_Page=true;
                    if (szTextBuf[0]=='0') vis_Page=false;
                    for (i=0;i<strlen(szTextBuf);i++)
                        if (szTextBuf[i]<48 || szTextBuf[i]>57)
                        {
                            vis_Page=false;
                            break;
                        }
                    if (vis_Page)
                    {
                        EditPage=atof(szTextBuf);
                        if (EditPage>0 && EditPage<=TotalPage)
                        {
                            CurrentPage=EditPage;
                            //��ת
                        }
                        //����ҳ����Χ��������
                        else
                        {
                            sprintf(szTextBuf,TEXT("%d"),CurrentPage);
                            SetWindowText(hEditPage,szTextBuf);
                        }
                    }
                    //��������ţ�������
                    else
                    {
                            sprintf(szTextBuf,TEXT("%d"),CurrentPage);
                            SetWindowText(hEditPage,szTextBuf);
                    }
                    break;


                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }

            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            switch(wParam)
            {
                case 0:
                    hdc=GetDC(hWnd);
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,30,200+ShowMode*40,NULL);
                    LineTo(hdc,30,230+ShowMode*40);
                    LineTo(hdc,110,230+ShowMode*40);
                    LineTo(hdc,110,200+ShowMode*40);
                    LineTo(hdc,30,200+ShowMode*40);
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    hdc=GetDC(hWnd);
                    //ѡ��ױ�����
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,30,200+DrawPrevious*40,NULL);
                    LineTo(hdc,30,230+DrawPrevious*40);
                    LineTo(hdc,110,230+DrawPrevious*40);
                    LineTo(hdc,110,200+DrawPrevious*40);
                    LineTo(hdc,30,200+DrawPrevious*40);
                    //ѡ����
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,30,200+DrawCurrent*40,NULL);
                    LineTo(hdc,30,230+DrawCurrent*40);
                    LineTo(hdc,110,230+DrawCurrent*40);
                    LineTo(hdc,110,200+DrawCurrent*40);
                    LineTo(hdc,30,200+DrawCurrent*40);
                    break;
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            DeleteObject(hPenRed);
            DeleteObject(hPenWhite);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
