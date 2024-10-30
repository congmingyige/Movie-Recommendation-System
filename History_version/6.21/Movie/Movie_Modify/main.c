#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "E:\\Movie\\define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

    HDC hdc,mdc;
    HBITMAP bg;

struct movie movie[1000];

int pos_movie;

float MovieMark=0;

int Init=0;

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

//修改为输入！
    if (Init==0)
    {
    pos_movie=0;
    strcpy(movie[pos_movie].Name,"功夫熊猫");
    movie[pos_movie].OverallMark=8.0;
    movie[pos_movie].ProfessorMark=8.0;
    movie[pos_movie].UserMark=750;
    movie[pos_movie].UserNumber=100;
    movie[pos_movie].RatioMark=0.7;
    Init=1;           //如果int WINAPI WinMain()多次使用，则这个不能省
    }

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
        TEXT("电影后台管理"),  //窗口标题（出现在标题栏）
        WS_OVERLAPPEDWINDOW,  //窗口风格
        300,  //初始化时x轴的位置
        20,  //初始化时y轴的位置
        800,  //窗口宽度
        800,  //窗口高度
        NULL,  //父窗口句柄
        NULL,  //窗口菜单句柄
        hInstance,  //当前窗口的句柄
        NULL  //不使用该值
    );

    //显示窗口
    ShowWindow(hwnd,iCmdShow);
    //更新（绘制）窗口
    UpdateWindow(hwnd);

//插入图片
            hdc=GetDC(hwnd);
            mdc=CreateCompatibleDC(hdc);
            bg=(HBITMAP)LoadImage(
                NULL,
                TEXT("E:\\test.bmp"),
                IMAGE_BITMAP,100,140,LR_LOADFROMFILE
            );
            SelectObject(mdc,bg);
            BitBlt(hdc,0,400,100,140,mdc,0,0,SRCAND);

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
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    RECT rect;

    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
//电影名
    static HWND hLabMovieName;
    static HWND hEditMovieName;
//电影类别
    static HWND hLabMovieMode;
    static HWND checkboxComedy;
    static HWND checkboxRomance;
    static HWND checkboxAction;
    static HWND checkboxCartoon;
    static HWND checkboxTeen;
    static HWND checkboxFeature;
    static HWND checkboxSci_Fic;
    static HWND checkboxThriller;
    static HWND checkboxCrime;
//适合心情
    static HWND hLabMovieMood;
    static HWND checkboxHappy;
    static HWND checkboxExcited;
    static HWND checkboxProud;
    static HWND checkboxSad;
    static HWND checkboxAngry;
    static HWND checkboxScared;
    static HWND checkboxAshamed;
    static HWND checkboxAnxious;
//评分
    static HWND hLabOverallMark;
    static HWND hEditOverallMark;
    static HWND hLabMark;
    static HWND hEditMark;
    static HWND hLabProfessorMark;
    static HWND hEditProfessorMark;
    static HWND hLabUserMark;
    static HWND hEditUserMark;
    static HWND hLabMarkStandard;
    static HWND hBtnMarkStandard;
    //字符串,用于输入
    TCHAR szTextBuf[100],szNumBuf[100];

    switch(message)
    {
        case WM_CREATE:
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

            //电影名
            hLabMovieName=CreateWindow(
                TEXT("static"),TEXT("电影名:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hWnd,(HMENU)1,hInst,NULL
            );

            hEditMovieName=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,100,345,40,
                hWnd,(HMENU)2,hInst,NULL
            );
            //电影类别
            hLabMovieMode=CreateWindow(
                TEXT("static"),TEXT("电影类别:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,160,120,40,
                hWnd,(HMENU)3,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("喜剧"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,152,65,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("爱情"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,152,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("动作"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,152,65,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("动画"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,152,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("青春"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                520,152,65,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("剧情"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,182,65,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("科幻"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,182,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("惊悚"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,182,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            checkboxCrime=CreateWindow(
                TEXT("button"),TEXT("犯罪"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,182,65,26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //适合心情
            hLabMovieMood=CreateWindow(
                TEXT("static"),TEXT("适合心情:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,226,120,40,
                hWnd,(HMENU)13,hInst,NULL
            );

            checkboxHappy=CreateWindow(
                TEXT("button"),TEXT("高兴"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX | WS_GROUP,
                240,218,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            checkboxExcited=CreateWindow(
                TEXT("button"),TEXT("激动"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,218,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            checkboxProud=CreateWindow(
                TEXT("button"),TEXT("自豪"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,218,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            checkboxSad=CreateWindow(
                TEXT("button"),TEXT("伤心"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,218,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            checkboxAngry=CreateWindow(
                TEXT("button"),TEXT("愤怒"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                520,218,65,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            checkboxScared=CreateWindow(
                TEXT("button"),TEXT("害怕"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,248,65,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            checkboxAshamed=CreateWindow(
                TEXT("button"),TEXT("羞愧"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,248,65,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            checkboxAnxious=CreateWindow(
                TEXT("button"),TEXT("忐忑"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,248,65,26,
                hWnd,(HMENU)21,hInst,NULL
            );
            //评分
            //总评
            hLabOverallMark=CreateWindow(
                TEXT("static"),TEXT("总体评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,285,120,40,
                hWnd,(HMENU)22,hInst,NULL
            );
            //总评一定会有
            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
            sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
            hEditOverallMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                215,285,55,40,
                hWnd,(HMENU)23,hInst,NULL
            );

            //专家评分
            hLabProfessorMark=CreateWindow(
                TEXT("static"),TEXT("专家评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                280,285,120,40,
                hWnd,(HMENU)24,hInst,NULL
            );
            //专家一定要评分
            sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].ProfessorMark);
            hEditProfessorMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                405,285,55,40,
                hWnd,(HMENU)25,hInst,NULL
            );

            //用户评分
            hLabUserMark=CreateWindow(
                TEXT("static"),TEXT("用户评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                470,285,120,40,
                hWnd,(HMENU)26,hInst,NULL
            );

            if (movie[pos_movie].UserMark==0)
                sprintf(szTextBuf,TEXT("无"));
            else
                sprintf(szTextBuf,TEXT("%.1f/%d人"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
            hEditUserMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                595,285,155,40,
                hWnd,(HMENU)27,hInst,NULL
            );

            //个人评分
            hLabMark=CreateWindow(
                TEXT("static"),TEXT("请您评分:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,335,120,40,
                hWnd,(HMENU)28,hInst,NULL
            );

            if (MovieMark==0)
                sprintf(szTextBuf,TEXT("无"));
            else
                sprintf(szTextBuf,TEXT("%.1f"),MovieMark);
            hEditMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                215,335,55,40,
                hWnd,(HMENU)29,hInst,NULL
            );

                sprintf(szTextBuf,TEXT("分数:0.1~9.9,专家评分%d%%,用户评分%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                hLabMarkStandard=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                280,335,380,40,
                hWnd,(HMENU)30,hInst,NULL
            );

            hBtnMarkStandard=CreateWindow(
                TEXT("button"),TEXT("评分规则"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER,
                670,335,80,40,
                hWnd,(HMENU)31,hInst,NULL
            );

            //电影名
            SendMessage(hLabMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //电影类别
            SendMessage(hLabMovieMode,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(checkboxComedy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxRomance,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAction,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxCartoon,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxTeen,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxFeature,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxSci_Fic,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxThriller,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxCrime,WM_SETFONT,(WPARAM)hFont,NULL);
            //适合心情
            SendMessage(hLabMovieMood,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(checkboxHappy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxExcited,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxProud,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxSad,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAngry,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxScared,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAshamed,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAnxious,WM_SETFONT,(WPARAM)hFont,NULL);
            //评分
            SendMessage(hLabOverallMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditOverallMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabProfessorMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditProfessorMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabUserMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditUserMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditMark,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                case 25:
                    GetWindowText(hEditProfessorMark,szTextBuf,100);
                    if (strlen(szTextBuf)==3 && szTextBuf[1]=='.' && szTextBuf[0]>='0' && szTextBuf[0]<='9' && szTextBuf[2]>='0' && szTextBuf[2]<='9')
                    {
                        movie[pos_movie].ProfessorMark=(szTextBuf[0]-48.0)+(szTextBuf[2]-48.0)/10.0;
                        //获得专家评分、用户评分占总评的比例
                        if (movie[pos_movie].UserNumber<5) movie[pos_movie].RatioMark=1.0;
                            else if (movie[pos_movie].UserNumber<=100) movie[pos_movie].RatioMark=0.7;
                                else if (movie[pos_movie].UserNumber<=1000) movie[pos_movie].RatioMark=0.5;
                                    else movie[pos_movie].RatioMark=0.3;
                        //计算总评分数
                        movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
                        //输出总评分数
                        sprintf(szNumBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
                        SetWindowText(hEditOverallMark,szNumBuf);
                        //输出专家评分、用户评分占总评的比例
                        sprintf(szTextBuf,TEXT("分数:0.1~9.9,专家评分%d%%,用户评分%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                        SetWindowText(hLabMarkStandard,szTextBuf);
                    }
                    break;

                case 31:
                    wsprintf(szTextBuf,TEXT("用户评分人数：\r\n <5\t\t\t专家100%% 用户0%% \r\n 5~100\t\t\t专家70%% 用户30%% \r\n 101~1000\t\t专家50%% 用户50%% \r\n >1001\t\t\t专家30%% 用户70%%"));
                    MessageBox(hWnd,szTextBuf,TEXT("评分规则"),MB_ICONINFORMATION);
                    break;

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            GetWindowRect(hBtnMarkStandard,&rect);
//插入图片
            hdc=GetDC(hWnd);
            mdc=CreateCompatibleDC(hdc);
            bg=(HBITMAP)LoadImage(
                NULL,
                TEXT("E:\\test.bmp"),
                IMAGE_BITMAP,100,140,LR_LOADFROMFILE
            );
            SelectObject(mdc,bg);
            BitBlt(hdc,500,550,100,140,mdc,0,0,SRCAND);
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            DeleteObject(hFont);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
