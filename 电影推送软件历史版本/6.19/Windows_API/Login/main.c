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
        TEXT("用户"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        500,  //初始化时x轴的位置
        250,  //初始化时y轴的位置
        500,  //窗口宽度
        300,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd,iCmdShow);
    //更新（绘制）窗口
    UpdateWindow(hwnd);

    /**********第③步：消息循环**********/
    while(GetMessage(&msg,NULL,0,0))
    {
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage(&msg);  //分派消息
    }
    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    extern struct user user[1000];

    //临时加的
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

//初始化鼠标
    static INT initCursor=0;
//1:登录 2:注册 3:重置密码
    static INT LoginMode=1;
//字体
    static HFONT hFont;
//登录 注册
    static HWND hLabUsername;
    static HWND hLabPassword;
    static HWND hEditUsername;
    static HWND hEditPassword;
//重置密码
    static HWND hLabNewPassword;
    static HWND hEditNewPassword;
//按钮:登录 注册 重置密码
    static HWND hBtnLogin;
    static HWND hBtnRegister;
    static HWND hBtnReset;
//确认按钮
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
            //创建画笔
            hPenRed=CreatePen(PS_SOLID,2,RGB(255,0,0));
            hPenWhite=CreatePen(PS_SOLID,2,RGB(255,255,255));
            //创建字体
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("楷体")
            );

            hLabUsername=CreateWindow(
                TEXT("static"),TEXT("用户名 "),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                70,50,70,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            hLabPassword=CreateWindow(
                TEXT("static"),TEXT("密码 "),
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
            //模式:登录
            hBtnLogin=CreateWindow(
                TEXT("button"),TEXT("登录"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                280,220,50,25,
                hWnd,(HMENU)7,hInst,NULL
            );
            //模式:注册
            hBtnRegister=CreateWindow(
                TEXT("button"),TEXT("注册"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                335,220,50,25,
                hWnd,(HMENU)8,hInst,NULL
            );
            //模式:重置密码
            hBtnReset=CreateWindow(
                TEXT("button"),TEXT("重置密码"),
                WS_CHILD | WS_VISIBLE | BS_CENTER,
                390,220,80,25,
                hWnd,(HMENU)9,hInst,NULL
            );
            //确认按钮
            hBtnSubmit=CreateWindow(
                TEXT("button"),TEXT("确认"),
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
                //登录
                case 7:
                    SetWindowText(hLabPassword,"密码 ");
                    ShowWindow(hLabNewPassword,SW_HIDE);
                    ShowWindow(hEditNewPassword,SW_HIDE);
                    LoginMode=1;
                    //绘图
                    hdc=GetDC(hWnd);
                    //选择白笔消除
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
                    //选择红笔
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,280,220,NULL);
                    LineTo(hdc,280,245);
                    LineTo(hdc,330,245);
                    LineTo(hdc,330,220);
                    LineTo(hdc,280,220);

                    //更改鼠标位置
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
                //注册
                case 8:
                    SetWindowText(hLabNewPassword,"再输一遍 ");
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    LoginMode=2;
                    //绘图
                    hdc=GetDC(hWnd);
                    //选择白笔消除
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
                    //选择红笔
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,335,220,NULL);
                    LineTo(hdc,335,245);
                    LineTo(hdc,385,245);
                    LineTo(hdc,385,220);
                    LineTo(hdc,335,220);
                    //更改鼠标位置
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
                //重置密码
                case 9:
                    SetWindowText(hLabPassword,"旧密码 ");
                    SetWindowText(hLabNewPassword,"新密码 ");
                    ShowWindow(hLabNewPassword,SW_SHOW);
                    ShowWindow(hEditNewPassword,SW_SHOW);
                    LoginMode=3;
                    UpdateWindow(hWnd);
                    //绘图
                    hdc=GetDC(hWnd);
                    //选择白笔消除
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
                    //选择红笔
                    SelectObject(hdc,hPenRed);
                    MoveToEx(hdc,390,220,NULL);
                    LineTo(hdc,390,245);
                    LineTo(hdc,470,245);
                    LineTo(hdc,470,220);
                    LineTo(hdc,390,220);

                    //更改鼠标位置
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
                //提交
                case 10:
                    GetWindowText(hEditUsername,szUsername,100);
                    GetWindowText(hEditPassword,szPassword,100);
                    GetWindowText(hEditNewPassword,szNewPassword,100);
                    switch(LoginMode)
                    {
                            //登录
                            case 1:
                                //如果用户不存在
                                pos=find_name(UserAns,szUsername);
                                if (pos==0)
                                {
                                    wsprintf(szUserInfo,TEXT("用户登录失败：\r\n用户不存在\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                }
                                //如果密码不正确
                                else if (strcmp(szPassword,user[pos].Password)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("用户登录失败：\r\n密码输入不正确\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                }
                                //输入成功
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("%s\r\n登录成功"),hEditUsername);
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_OK);
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                            //注册
                            case 2:
                                //如果用户已经存在
                                if (find_name(UserAns,szUsername)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("用户注册失败：\r\n用户已经存在\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //如果输入的密码小于6位
                                else if (strlen(szPassword)<6)
                                {
                                    wsprintf(szUserInfo,TEXT("用户注册失败：\r\n设置的密码应不小于6位\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //如果两次输入的密码不一样
                                else if (strcmp(szPassword,szNewPassword)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("用户注册失败：\r\n两个输入的密码不一样\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //输入成功
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("用户注册成功：\r\n用户账号：%s\r\n用户密码：%s"),szUsername,szPassword);
                                    UserAns++;
                                    strcpy(user[UserAns].Name,szUsername);
                                    strcpy(user[UserAns].Password,szPassword);
                                    InitUser(UserAns);
                                    wsprintf(szUserInfo,TEXT("请您完善个人信息"));
                                    int nSelect=MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_YESNO);
                                    if (nSelect==IDYES)
                                    {
                                        //完善个人信息
                                    }
                                    ShowWindow(hWnd,SW_HIDE);
                                }
                                break;
                            //重置密码
                            case 3:
                                //如果用户不存在
                                pos=find_name(UserAns,szUsername);
                                if (pos==0)
                                {
                                    wsprintf(szUserInfo,TEXT("用户重置密码失败：\r\n用户不存在\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //如果输入的密码不正确
                                else if (strcmp(szPassword,user[pos].Password)!=0)
                                {
                                    wsprintf(szUserInfo,TEXT("用户重置密码失败：\r\n密码输入不正确\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //如果输入的新密码小于6位
                                else if (strlen(szNewPassword)<6)
                                {
                                    wsprintf(szUserInfo,TEXT("用户重置密码失败：\r\n设置的密码应不小于6位\r\n请重新输入"));
                                    MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_ICONINFORMATION);
                                    //清除输入的密码
                                    SetWindowText(hEditPassword,"");
                                    SetWindowText(hEditNewPassword,"");
                                }
                                //输入成功
                                else
                                {
                                    wsprintf(szUserInfo,TEXT("用户重置密码成功：\r\n用户账号：%s\r\n新用户密码：%s"),szUsername,szNewPassword);
                                    strcpy(user[pos].Password,szPassword);
                                    wsprintf(szUserInfo,TEXT("请您完善个人信息"));
                                    int nSelect=MessageBox(hWnd,szUserInfo,TEXT("信息提醒"),MB_YESNO);
                                    if (nSelect==IDYES)
                                    {
                                        //完善个人信息
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
            //选择红笔 初始化登录状态
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
