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
    static TCHAR szClassName[] = TEXT("HelloWin");  //��������
    HWND     hwnd;  //���ھ��
    MSG      msg;  //��Ϣ
    WNDCLASS wndclass;  //������

    hInst=hInstance;

//�޸�Ϊ���룡
    if (Init==0)
    {
    pos_movie=0;
    strcpy(movie[pos_movie].Name,"������è");
    movie[pos_movie].OverallMark=8.0;
    movie[pos_movie].ProfessorMark=8.0;
    movie[pos_movie].UserMark=750;
    movie[pos_movie].UserNumber=100;
    movie[pos_movie].RatioMark=0.7;
    Init=1;           //���int WINAPI WinMain()���ʹ�ã����������ʡ
    }

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
        TEXT("��Ӱ��̨����"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        300,  //��ʼ��ʱx���λ��
        20,  //��ʼ��ʱy���λ��
        800,  //���ڿ��
        800,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

//����ͼƬ
            hdc=GetDC(hwnd);
            mdc=CreateCompatibleDC(hdc);
            bg=(HBITMAP)LoadImage(
                NULL,
                TEXT("E:\\test.bmp"),
                IMAGE_BITMAP,100,140,LR_LOADFROMFILE
            );
            SelectObject(mdc,bg);
            BitBlt(hdc,0,400,100,140,mdc,0,0,SRCAND);

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
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    RECT rect;

    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontNumber;
//��Ӱ��
    static HWND hLabMovieName;
    static HWND hEditMovieName;
//��Ӱ���
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
//�ʺ�����
    static HWND hLabMovieMood;
    static HWND checkboxHappy;
    static HWND checkboxExcited;
    static HWND checkboxProud;
    static HWND checkboxSad;
    static HWND checkboxAngry;
    static HWND checkboxScared;
    static HWND checkboxAshamed;
    static HWND checkboxAnxious;
//����
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
    //�ַ���,��������
    TCHAR szTextBuf[100],szNumBuf[100];

    switch(message)
    {
        case WM_CREATE:
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

            //��Ӱ��
            hLabMovieName=CreateWindow(
                TEXT("static"),TEXT("��Ӱ��:"),
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
            //��Ӱ���
            hLabMovieMode=CreateWindow(
                TEXT("static"),TEXT("��Ӱ���:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,160,120,40,
                hWnd,(HMENU)3,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("ϲ��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,152,65,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,152,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,152,65,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,152,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("�ഺ"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                520,152,65,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,182,65,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("�ƻ�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,182,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("���"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,182,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            checkboxCrime=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,182,65,26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //�ʺ�����
            hLabMovieMood=CreateWindow(
                TEXT("static"),TEXT("�ʺ�����:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,226,120,40,
                hWnd,(HMENU)13,hInst,NULL
            );

            checkboxHappy=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX | WS_GROUP,
                240,218,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            checkboxExcited=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,218,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            checkboxProud=CreateWindow(
                TEXT("button"),TEXT("�Ժ�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,218,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            checkboxSad=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,218,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            checkboxAngry=CreateWindow(
                TEXT("button"),TEXT("��ŭ"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                520,218,65,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            checkboxScared=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,248,65,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            checkboxAshamed=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,248,65,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            checkboxAnxious=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,248,65,26,
                hWnd,(HMENU)21,hInst,NULL
            );
            //����
            //����
            hLabOverallMark=CreateWindow(
                TEXT("static"),TEXT("��������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,285,120,40,
                hWnd,(HMENU)22,hInst,NULL
            );
            //����һ������
            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
            sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
            hEditOverallMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                215,285,55,40,
                hWnd,(HMENU)23,hInst,NULL
            );

            //ר������
            hLabProfessorMark=CreateWindow(
                TEXT("static"),TEXT("ר������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                280,285,120,40,
                hWnd,(HMENU)24,hInst,NULL
            );
            //ר��һ��Ҫ����
            sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].ProfessorMark);
            hEditProfessorMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                405,285,55,40,
                hWnd,(HMENU)25,hInst,NULL
            );

            //�û�����
            hLabUserMark=CreateWindow(
                TEXT("static"),TEXT("�û�����:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                470,285,120,40,
                hWnd,(HMENU)26,hInst,NULL
            );

            if (movie[pos_movie].UserMark==0)
                sprintf(szTextBuf,TEXT("��"));
            else
                sprintf(szTextBuf,TEXT("%.1f/%d��"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
            hEditUserMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                595,285,155,40,
                hWnd,(HMENU)27,hInst,NULL
            );

            //��������
            hLabMark=CreateWindow(
                TEXT("static"),TEXT("��������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,335,120,40,
                hWnd,(HMENU)28,hInst,NULL
            );

            if (MovieMark==0)
                sprintf(szTextBuf,TEXT("��"));
            else
                sprintf(szTextBuf,TEXT("%.1f"),MovieMark);
            hEditMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                215,335,55,40,
                hWnd,(HMENU)29,hInst,NULL
            );

                sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                hLabMarkStandard=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                280,335,380,40,
                hWnd,(HMENU)30,hInst,NULL
            );

            hBtnMarkStandard=CreateWindow(
                TEXT("button"),TEXT("���ֹ���"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER,
                670,335,80,40,
                hWnd,(HMENU)31,hInst,NULL
            );

            //��Ӱ��
            SendMessage(hLabMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //��Ӱ���
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
            //�ʺ�����
            SendMessage(hLabMovieMood,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(checkboxHappy,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxExcited,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxProud,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxSad,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAngry,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxScared,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAshamed,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(checkboxAnxious,WM_SETFONT,(WPARAM)hFont,NULL);
            //����
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
                        //���ר�����֡��û�����ռ�����ı���
                        if (movie[pos_movie].UserNumber<5) movie[pos_movie].RatioMark=1.0;
                            else if (movie[pos_movie].UserNumber<=100) movie[pos_movie].RatioMark=0.7;
                                else if (movie[pos_movie].UserNumber<=1000) movie[pos_movie].RatioMark=0.5;
                                    else movie[pos_movie].RatioMark=0.3;
                        //������������
                        movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
                        //�����������
                        sprintf(szNumBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
                        SetWindowText(hEditOverallMark,szNumBuf);
                        //���ר�����֡��û�����ռ�����ı���
                        sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                        SetWindowText(hLabMarkStandard,szTextBuf);
                    }
                    break;

                case 31:
                    wsprintf(szTextBuf,TEXT("�û�����������\r\n <5\t\t\tר��100%% �û�0%% \r\n 5~100\t\t\tר��70%% �û�30%% \r\n 101~1000\t\tר��50%% �û�50%% \r\n >1001\t\t\tר��30%% �û�70%%"));
                    MessageBox(hWnd,szTextBuf,TEXT("���ֹ���"),MB_ICONINFORMATION);
                    break;

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            GetWindowRect(hBtnMarkStandard,&rect);
//����ͼƬ
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
