#include <windows.h>
#include "E:\\Movie\\define.h"s

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
    hwnd = CreateWindow(
        szClassName,  //窗口类的名字
        TEXT("信息完善"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        500/*CW_USEDEFAULT*/,  //初始化时x轴的位置
        250/*CW_USEDEFAULT*/,  //初始化时y轴的位置
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
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //翻译消息
        DispatchMessage (&msg);  //分派消息
    }

    return msg.wParam;
}

/**********第④步：窗口过程**********/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    extern struct user user[1000];
    TCHAR szTextBuf[100];
    int pos=1;
    int wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    static HFONT hFont;  //逻辑字体
    //单选 性别
    static HWND labSex;
    static HWND radioMale;
    static HWND radioFemale;
    //单选 定义
    static HWND labDefine;
    static HWND radioStudent;
    static HWND radioWorker;
    static HWND radioOther;
    //单选 年龄
    static HWND labAge;
    static HWND radioJuvenile;
    static HWND radioTeenage;
    static HWND radioAdult;
    static HWND radioOld;
    //单选 状态
    static HWND labSituation;
    static HWND radioHoliday;
    static HWND radioExam;
    static HWND radioRecovery;
    //多选 偏好
    static HWND labPreference;
    static HWND checkboxComedy;
    static HWND checkboxRomance;
    static HWND checkboxAction;
    static HWND checkboxCartoon;
    static HWND checkboxTeen;
    static HWND checkboxFeature;
    static HWND checkboxSci_Fic;
    static HWND checkboxThriller;
    static HWND checkboxCrime;
    //确认按钮
    static HWND btnSubmit;

    switch (message){
        case  WM_CREATE:
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("微软雅黑")
            );

            //选择性别
            labSex=CreateWindow(
                TEXT("static"),TEXT("性别："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,10,80,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            radioMale=CreateWindow(
                TEXT("button"), TEXT("男"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON  | WS_GROUP,
                95,10,50,26,
                hWnd,(HMENU)2,hInst,NULL
            );

            radioFemale=CreateWindow(
                TEXT("button"),TEXT("女"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                150,10,50,26,
                hWnd,(HMENU)3,hInst,NULL
            );

            //类别
            labDefine=CreateWindow(
                TEXT("static"),TEXT("类别："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,40,80,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            radioStudent=CreateWindow(
                TEXT("button"),TEXT("学生"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,40,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            radioWorker=CreateWindow(
                TEXT("button"),TEXT("工作者"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,40,80,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            radioOther=CreateWindow(
                TEXT("button"), TEXT("其它"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                250,40,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );
            //年龄
            labAge=CreateWindow(
                TEXT("static"), TEXT("年龄："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,70,80,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            radioJuvenile=CreateWindow(
                TEXT("button"),TEXT("未成年人"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,70,90,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            radioTeenage=CreateWindow(
                TEXT("button"),TEXT("青年人"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                190,70,75,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            radioAdult=CreateWindow(
                TEXT("button"),TEXT("成年人"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                270,70,75,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            radioOld=CreateWindow(
                TEXT("button"),TEXT("老人"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                350, 70, 60, 26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //状态
            labSituation=CreateWindow(
                TEXT("static"), TEXT("状态(选填)："),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,100,80,26,
                hWnd,(HMENU)13,hInst,NULL
            );

            radioHoliday=CreateWindow(
                TEXT("button"),TEXT("放假"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,100,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            radioExam=CreateWindow(
                TEXT("button"),TEXT("考试"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,100,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            radioRecovery=CreateWindow(
                TEXT("button"),TEXT("康复"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                235,100,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );
            //偏好
            labPreference=CreateWindow(
                TEXT("static"),TEXT("偏好(选填)："),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10,130,80,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("喜剧"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                95,130,65,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("爱情"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                165,130,65,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("动作"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                235,130,65,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("动画"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                305,130,65,26,
                hWnd,(HMENU)21,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("青春"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                375,130,65,26,
                hWnd,(HMENU)22,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("剧情"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                95,160,65,26,
                hWnd,(HMENU)23,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("科幻"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                165,160,65,26,
                hWnd,(HMENU)24,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("惊悚"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                235,160,65,26,
                hWnd,(HMENU)25,hInst,NULL
            );

            checkboxCrime=CreateWindow(
                TEXT("button"),TEXT("犯罪"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                305,160,65,26,
                hWnd,(HMENU)26,hInst,NULL
            );
            //确认按钮
            btnSubmit=CreateWindow(
                TEXT("button"),TEXT("确认"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT | SS_CENTER,
                210,200,80,30,
                hWnd,(HMENU)27,hInst,NULL
            );

            //性别
            SendMessage(labSex,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMale,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioFemale,WM_SETFONT,(WPARAM)hFont,NULL);
            //定义
            SendMessage(labDefine,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioStudent,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioWorker,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOther,WM_SETFONT,(WPARAM)hFont,NULL);
            //年龄
            SendMessage(labAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioJuvenile,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioTeenage,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioAdult,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOld,WM_SETFONT,(WPARAM)hFont,NULL);
            //状态
            SendMessage(labSituation,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioHoliday,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioExam,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioRecovery,WM_SETFONT,(WPARAM)hFont,NULL);
            //偏好
            SendMessage(labPreference,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxComedy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxRomance,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAction,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxCartoon,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxFeature,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxSci_Fic,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxThriller,WM_SETFONT,(WPARAM)hFont, NULL);
            SendMessage(checkboxCrime,WM_SETFONT,(WPARAM)hFont,NULL);
            //确认按钮
            SendMessage(btnSubmit,WM_SETFONT,(WPARAM)hFont,NULL);

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
//如果有被选中的话
            if (wmEvent==BN_CLICKED)
            {
                switch(wmId)
                {
                    case 2:user[pos].Sex=1; break;
                    case 3:user[pos].Sex=2; break;
                    case 5:user[pos].Define=1; break;
                    case 6:user[pos].Define=2; break;
                    case 7:user[pos].Define=3; break;
                    case 9:user[pos].Age=1; break;
                    case 10:user[pos].Age=2; break;
                    case 11:user[pos].Age=3; break;
                    case 12:user[pos].Age=4; break;
                    case 14:user[pos].Condition=1; break;
                    case 15:user[pos].Condition=2; break;
                    case 16:user[pos].Condition=3; break;
                    case 18:user[pos].Preference[1]=!user[pos].Preference[1]; break;
                    case 19:user[pos].Preference[2]=!user[pos].Preference[2]; break;
                    case 20:user[pos].Preference[3]=!user[pos].Preference[3]; break;
                    case 21:user[pos].Preference[4]=!user[pos].Preference[4]; break;
                    case 22:user[pos].Preference[5]=!user[pos].Preference[5]; break;
                    case 23:user[pos].Preference[6]=!user[pos].Preference[6]; break;
                    case 24:user[pos].Preference[7]=!user[pos].Preference[7]; break;
                    case 25:user[pos].Preference[8]=!user[pos].Preference[8]; break;
                    case 26:user[pos].Preference[9]=!user[pos].Preference[9]; break;
                    case 27:
                        wsprintf(szTextBuf,TEXT("     用户信息提交成功"));
                        int nSelect=MessageBox(hWnd,szTextBuf,TEXT("信息提醒"),MB_OK);
                        ShowWindow(hWnd,SW_HIDE);
                        UpdateWindow(hWnd);
                        break;
                    default:return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            // TODO:  在此添加任意绘图代码...
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    free(user);
    return 0;
}
