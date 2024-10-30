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
//数据读入
    fileopen_movie();
    fileopen_user();

    static TCHAR szClassName[] = TEXT("HelloWin");  //窗口类名
    HWND     hwnd;  //窗口句柄
    MSG      msg;  //消息
    WNDCLASS wndclass;  //窗口类

    hInst=hInstance;

    /**********第①步：注册窗口类**********/
    //为窗口类的各个字段赋值
    wndclass.style = CS_HREDRAW | CS_VREDRAW;  //窗口风格
    wndclass.lpfnWndProc  = WndProc;  //窗口过程
    wndclass.cbClsExtra   = 0;  //暂时不需要理解
    wndclass.cbWndExtra   = 0;  //暂时不需要理解
    wndclass.hInstance    = hInstance;  //当前窗口句柄
    wndclass.hIcon        = LoadIcon (NULL, IDI_APPLICATION);  //窗口图标
    wndclass.hCursor      = LoadCursor (NULL, IDC_ARROW);  //鼠标样式
    wndclass.hbrBackground= (HBRUSH) GetStockObject (WHITE_BRUSH);  //窗口背景画刷
    wndclass.lpszMenuName = NULL ;  //窗口菜单
    wndclass.lpszClassName= szClassName;  //窗口类名

    //注册窗口
    RegisterClass(&wndclass);

    /*****第②步：创建窗口(并让窗口显示出来)*****/
    hwnd=CreateWindow(
        szClassName,  //窗口类的名字
        TEXT(""),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        200,  //初始化时x轴的位置
        5,  //初始化时y轴的位置
        1000,  //窗口宽度
        820,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    ShowWindow(hwnd,iCmdShow);
    UpdateWindow(hwnd);

            //初始化矩形
            SendMessage(hwnd,WM_PAINT,(WPARAM)0,NULL);

    /**********第③步：消息循环**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
        //观看方式
        switch(msg.message)
        {
            case WM_KEYDOWN:
                //观看方式的选择
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
                //左右方向键 PageHome PageEnd 修改页数
                if (GetKeyState(VK_HOME)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)14,NULL);
                if (GetKeyState(VK_END)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)15,NULL);
                //PageUP PageDown 修改页数
                if (GetKeyState(VK_PRIOR)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)12,NULL);
                if (GetKeyState(VK_NEXT)<0)
                    SendMessage(hwnd,WM_COMMAND,(WPARAM)13,NULL);
                //关闭窗口
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('W')<0)
                    SendMessage(hwnd,WM_DESTROY,NULL,NULL);
                //到达修改页数的文本框
                if (GetKeyState(VK_CONTROL)<0 && GetKeyState('P')<0)
                    SendMessage(hwnd,WM_COMMAND,100,NULL);
            break;
        }
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;

    static HPEN hPenRed;
    static HPEN hPenWhite;
    //字体
    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
    //用户体验
    static HWND hBtnUser;
    static HWND hBtnUserInformation;
    static HWND hBtnWatchingHistory;
    //观看方式
    static HWND hLabShowMode;
    static HWND hBtnShowMode1;
    static HWND hBtnShowMode2;
    static HWND hBtnShowMode3;
    static HWND hBtnShowMode4;
    static HWND hBtnShowMode5;
    static HWND hBtnShowMode6;
    static HWND hBtnShowMode7;
    //显示页数,改变页数
    static HWND hBtnPageUp;
    static HWND hBtnPageDown;
    static HWND hBtnPageBegin;
    static HWND hBtnPageEnd;
    static HWND hEditPage;
    static HWND hLabTotalPage;
    //电影显示名字
    static HWND hBtnMovieShow[10];

    TCHAR szTextBuf[100];

    //要定义的部分
    int i,j;
    static bool vis_Page=true;
    //LoginMode:0 未登录 1:已登录
    //Drawp为之前选的部分,Drawq为现在选的部分
    static int LoginMode=1,ShowMode=1,DrawPrevious=1,DrawCurrent=1;
    static int EditPage=1,CurrentPage=1,TotalPage=10,MovieShowPos,MovieShowTotal=7;

    switch(message)
    {
        case WM_CREATE:
            //创建画笔
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //创建字体
            hFont=CreateFont(
                -18,-9,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("宋体")
            );

            hFontTitle=CreateFont(
                -22,-11,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("宋体")
            );

            hFontNumber=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("黑体")
            );

            if (LoginMode==1) sprintf(szTextBuf,TEXT("已登录"));
                else sprintf(szTextBuf,TEXT("请登录"));
            hBtnUser=CreateWindow(
                TEXT("button"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                700,20,60,30,
                hWnd,(HMENU)1,hInst,NULL
            );

            hBtnUserInformation=CreateWindow(
                TEXT("button"),TEXT("用户信息"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                780,20,80,30,
                hWnd,(HMENU)2,hInst,NULL
            );
            if (LoginMode==0) ShowWindow(hBtnUserInformation,SW_HIDE);

            hBtnWatchingHistory=CreateWindow(
                TEXT("button"),TEXT("观看历史"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                880,20,80,30,
                hWnd,(HMENU)3,hInst,NULL
            );
            if (LoginMode==0) ShowWindow(hBtnWatchingHistory,SW_HIDE);
            //显示的模式:电影类别、适合心情、上映时间、总体评分、用户评分、专家评分
            hLabShowMode=CreateWindow(
                TEXT("static"),TEXT("观看方式"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                30,200,80,30,
                hWnd,(HMENU)4,hInst,NULL
            );

            hBtnShowMode1=CreateWindow(
                TEXT("button"),TEXT("电影类别"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,240,80,30,
                hWnd,(HMENU)5,hInst,NULL
            );

            hBtnShowMode2=CreateWindow(
                TEXT("button"),TEXT("适合心情"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,280,80,30,
                hWnd,(HMENU)6,hInst,NULL
            );

            hBtnShowMode3=CreateWindow(
                TEXT("button"),TEXT("上映时间"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,320,80,30,
                hWnd,(HMENU)7,hInst,NULL
            );

            hBtnShowMode4=CreateWindow(
                TEXT("button"),TEXT("总体评分"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,360,80,30,
                hWnd,(HMENU)8,hInst,NULL
            );

            hBtnShowMode5=CreateWindow(
                TEXT("button"),TEXT("用户评分"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,400,80,30,
                hWnd,(HMENU)9,hInst,NULL
            );

            hBtnShowMode6=CreateWindow(
                TEXT("button"),TEXT("专家评分"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                30,440,80,30,
                hWnd,(HMENU)10,hInst,NULL
            );

            hBtnShowMode7=CreateWindow(
                TEXT("button"),TEXT("用户模式"),
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

            sprintf(szTextBuf,TEXT("总有%d页"),TotalPage);
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

            //用户体验
            SendMessage(hBtnUser,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnUserInformation,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnWatchingHistory,WM_SETFONT,(WPARAM)hFont,NULL);
            //观看方式
            SendMessage(hLabShowMode,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode1,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode2,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode3,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode4,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode5,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode6,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnShowMode7,WM_SETFONT,(WPARAM)hFont,NULL);
            //显示页数,改变页数
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
                        //跳转
                    }
                    break;
                //PageDown
                case 13:
                    if (CurrentPage!=TotalPage)
                    {
                        CurrentPage++;
                        sprintf(szTextBuf,TEXT("%d"),CurrentPage);
                        SetWindowText(hEditPage,szTextBuf);
                        //跳转
                    }
                    break;
                //PageBegin
                case 14:
                    sprintf(szTextBuf,TEXT("%d"),1);
                    SetWindowText(hEditPage,szTextBuf);
                    //跳转
                    break;
                //PageEnd
                case 15:
                    sprintf(szTextBuf,TEXT("%d"),TotalPage);
                    SetWindowText(hEditPage,szTextBuf);
                    //跳转
                    break;
                //页数编辑
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
                            //跳转
                        }
                        //超过页数范围，不操作
                        else
                        {
                            sprintf(szTextBuf,TEXT("%d"),CurrentPage);
                            SetWindowText(hEditPage,szTextBuf);
                        }
                    }
                    //有特殊符号，不操作
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
                    //选择白笔消除
                    SelectObject(hdc,hPenWhite);
                    MoveToEx(hdc,30,200+DrawPrevious*40,NULL);
                    LineTo(hdc,30,230+DrawPrevious*40);
                    LineTo(hdc,110,230+DrawPrevious*40);
                    LineTo(hdc,110,200+DrawPrevious*40);
                    LineTo(hdc,30,200+DrawPrevious*40);
                    //选择红笔
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
