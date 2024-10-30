#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include "define.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;

HDC hdc,mdc;
HBITMAP bg;

struct movie movie[1000];
//��ǰ�༭�ĵ�Ӱ���
long total_movie,pos_movie;

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
    wndclass.cbClsExtra   = 0;  //��ʱ����Ҫ����
    wndclass.cbWndExtra   = 0;  //��ʱ����Ҫ����
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
        5,  //��ʼ��ʱy���λ��
        800,  //���ڿ���
        825,  //���ڸ߶�
        NULL,  //�����ھ��
        NULL,  //���ڲ˵����
        hInstance,  //��ǰ���ڵľ��
        NULL  //��ʹ�ø�ֵ
    );

    //��ʾ����
    ShowWindow(hwnd,iCmdShow);
    //���£����ƣ�����
    UpdateWindow(hwnd);

//��ʼ��
    //��Ӱ��Ŵ�0��ʼ �����½�״̬,���½��ĵ�Ӱ��ŵ�ͬ�ڵ�Ӱ����
    pos_movie=total_movie;
    //д���������Ӱ���
    SendMessage(hwnd,WM_COMMAND,(WPARAM)34,NULL);
    //�����Ӱ��Ϣ
    fileclose_movie();

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

    bool vis_edit=true,vis_page=true,vis_photo=false;
    long i,number;

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
    static HWND hLabProfessorMark;
    static HWND hEditProfessorMark;
    static HWND hLabUserMark;
    static HWND hEditUserMark;
    static HWND hLabMarkStandard;
    static HWND hBtnMarkStandard;
    //��ӳʱ��͵ص�
    static HWND hLabTime;
    static HWND hEditTime;
    static HWND hLabPlace;
    static HWND hEditPlace;
    //��Ӱ���
    static HWND hEditIntroduce;
    //����ͼƬ�����ӡ���Ӱ ���Ե�ַ
    static HWND hLabPhotoAddress;
    static HWND hEditPhotoAddress;
    static HWND hLabTorrentAddress;
    static HWND hEditTorrentAddress;
    static HWND hLabFileAddress;
    static HWND hEditFileAddress;
    //ȷ�ϰ�ť
    static HWND hBtnModifySubmit;
    //�½���Ӱ���鿴��Ӱ��ť
    static HWND hBtnNewMovie;
    static HWND hBtnCheckMovie;
    static HWND hEditCheckMovie;

    //�ַ���,��������
    TCHAR szTextBuf[100],szNumBuf[100],szPassage[1000];

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
                90,40,120,40,
                hWnd,(HMENU)1,hInst,NULL
            );

            hEditMovieName=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,40,345,40,
                hWnd,(HMENU)2,hInst,NULL
            );
            //��Ӱ���
            hLabMovieMode=CreateWindow(
                TEXT("static"),TEXT("��Ӱ���:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hWnd,(HMENU)3,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("ϲ��"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                240,92,65,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                310,92,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                380,92,65,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                450,92,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("�ഺ"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                520,92,65,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                240,122,65,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("�ƻ�"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                310,122,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("���"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                380,122,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            checkboxCrime=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                450,122,65,26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //�ʺ�����
            hLabMovieMood=CreateWindow(
                TEXT("static"),TEXT("�ʺ�����:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,166,120,40,
                hWnd,(HMENU)13,hInst,NULL
            );

            checkboxHappy=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | WS_GROUP,
                240,158,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            checkboxExcited=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                310,158,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            checkboxProud=CreateWindow(
                TEXT("button"),TEXT("�Ժ�"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                380,158,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            checkboxSad=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                450,158,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            checkboxAngry=CreateWindow(
                TEXT("button"),TEXT("��ŭ"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                520,158,65,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            checkboxScared=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                240,188,65,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            checkboxAshamed=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                310,188,65,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            checkboxAnxious=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
                380,188,65,26,
                hWnd,(HMENU)21,hInst,NULL
            );
            //����
            //����
            hLabOverallMark=CreateWindow(
                TEXT("static"),TEXT("��������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,225,120,40,
                hWnd,(HMENU)22,hInst,NULL
            );
            //����һ������
            movie[pos_movie].OverallMark=movie[pos_movie].ProfessorMark*movie[pos_movie].RatioMark+movie[pos_movie].UserMark/movie[pos_movie].UserNumber*(1-movie[pos_movie].RatioMark);
            sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].OverallMark);
            hEditOverallMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                215,225,55,40,
                hWnd,(HMENU)23,hInst,NULL
            );

            //ר������
            hLabProfessorMark=CreateWindow(
                TEXT("static"),TEXT("ר������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                280,225,120,40,
                hWnd,(HMENU)24,hInst,NULL
            );
            //ר��һ��Ҫ����
            sprintf(szTextBuf,TEXT("%.1f"),movie[pos_movie].ProfessorMark);
            hEditProfessorMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                405,225,55,40,
                hWnd,(HMENU)25,hInst,NULL
            );

            //�û�����
            hLabUserMark=CreateWindow(
                TEXT("static"),TEXT("�û�����:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                470,225,120,40,
                hWnd,(HMENU)26,hInst,NULL
            );

            if (movie[pos_movie].UserMark==0)
                sprintf(szTextBuf,TEXT("��"));
            else
                sprintf(szTextBuf,TEXT("%.1f/%d��"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
            hEditUserMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
                595,225,155,40,
                hWnd,(HMENU)27,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                hLabMarkStandard=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                140,275,450,40,
                hWnd,(HMENU)28,hInst,NULL
            );

            hBtnMarkStandard=CreateWindow(
                TEXT("button"),TEXT("���ֹ���"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                620,275,80,40,
                hWnd,(HMENU)29,hInst,NULL
            );

            hLabTime=CreateWindow(
                TEXT("static"),TEXT("�й���ӳʱ��:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,325,150,40,
                hWnd,(HMENU)30,hInst,NULL
            );

            hEditTime=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                245,325,150,40,
                hWnd,(HMENU)31,hInst,NULL
            );

            hLabPlace=CreateWindow(
                TEXT("static"),TEXT("��Ƭ����/��ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                405,325,170,40,
                hWnd,(HMENU)32,hInst,NULL
            );

            hEditPlace=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                580,325,170,40,
                hWnd,(HMENU)33,hInst,NULL
            );
            //��Ӱ���
            hEditIntroduce=CreateWindow(
                TEXT("edit"),NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
                90,375,660,200,
                hWnd,(HMENU)34,hInst,NULL
            );

            //����ͼƬ ���Ե�ַ
            hLabPhotoAddress=CreateWindow(
                TEXT("static"),TEXT("ͼƬ��ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,585,120,40,
                hWnd,(HMENU)35,hInst,NULL
            );

            hEditPhotoAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,585,510,40,
                hWnd,(HMENU)36,hInst,NULL
            );
            //�������� ���Ե�ַ
            hLabTorrentAddress=CreateWindow(
                TEXT("static"),TEXT("���ӵ�ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,635,120,40,
                hWnd,(HMENU)37,hInst,NULL
            );

            hEditTorrentAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,635,510,40,
                hWnd,(HMENU)38,hInst,NULL
            );
            //������Ƶ ���Ե�ַ
            hLabFileAddress=CreateWindow(
                TEXT("static"),TEXT("��Ƶ��ַ:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,685,120,40,
                hWnd,(HMENU)39,hInst,NULL
            );

            hEditTorrentAddress=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,685,510,40,
                hWnd,(HMENU)40,hInst,NULL
            );

            hBtnModifySubmit=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                360,735,80,40,
                hWnd,(HMENU)41,hInst,NULL
            );

            hBtnNewMovie=CreateWindow(
                TEXT("button"),TEXT("�½���Ӱ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                250,5,100,30,
                hWnd,(HMENU)42,hInst,NULL
            );

            hBtnCheckMovie=CreateWindow(
                TEXT("button"),TEXT("�޸ĵ�Ӱ"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER | BS_VCENTER,
                360,5,100,30,
                hWnd,(HMENU)43,hInst,NULL
            );

            hEditCheckMovie=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                470,5,100,30,
                hWnd,(HMENU)44,hInst,NULL
            );

            //��Ӱ��
            SendMessage(hLabMovieName,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditMovieName,WM_SETFONT,(WPARAM)hFontNumber,NULL);
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
            SendMessage(hLabMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            //��ӳʱ��͵ص�
            SendMessage(hLabTime,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditTime,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            SendMessage(hLabPlace,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditPlace,WM_SETFONT,(WPARAM)hFontNumber,NULL);
            //��Ӱ���
            SendMessage(hEditIntroduce,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //����ͼƬ�����ӡ���Ӱ ���Ե�ַ
            SendMessage(hLabPhotoAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditPhotoAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hLabTorrentAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditTorrentAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hLabFileAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditFileAddress,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            //ȷ�ϰ�ť
            SendMessage(hBtnModifySubmit,WM_SETFONT,(WPARAM)hFont,NULL);
            //�½���Ӱ���鿴��Ӱ��ť
            SendMessage(hBtnNewMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnCheckMovie,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hEditCheckMovie,WM_SETFONT,(WPARAM)hFont,NULL);

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
            switch (wmId)
            {
                //�ı�ר������
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
                //���ֹ���
                case 29:
                    wsprintf(szTextBuf,TEXT("�û�����������\r\n <5\t\t\tר��100%% �û�0%% \r\n 5~100\t\t\tר��70%% �û�30%% \r\n 101~1000\t\tר��50%% �û�50%% \r\n >1001\t\t\tר��30%% �û�70%%"));
                    MessageBox(hWnd,szTextBuf,TEXT("���ֹ���"),MB_ICONINFORMATION);
                    break;
                //��Ӱ���
                case 34:
                    GetWindowText(hEditIntroduce,szTextBuf,1000);
                    if (strlen(szTextBuf)==0)
                    {
                        rect.left=0;
                        rect.right=300;
                        rect.top=600;
                        rect.bottom=900;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        DrawText(
                            hdc,
                            TEXT("�������Ӱ���"),
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    else
                    {
                        rect.left=0;
                        rect.right=300;
                        rect.top=600;
                        rect.bottom=900;
                        hdc=GetDC(hWnd);
                        SelectObject(hdc,hFontNumber);
                        for (i=0;i<strlen("�������Ӱ���");i++)
                            szTextBuf[i]=' ';
                        szTextBuf[i]='\0';
                        DrawText(
                            hdc,
                            szTextBuf,
                            -1,
                            &rect,
                            DT_SINGLELINE | DT_CENTER | DT_VCENTER
                        );
                    }
                    break;

                //ͼƬ��ַ
                case 36:
                    SendMessage(hWnd,WM_PAINT,(WPARAM)36,NULL);
                    break;
                //ȷ�ϰ�ť
                case 41:
                    GetWindowText(hEditMovieName,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("��Ӱ���Ʋ���Ϊ��"),TEXT("����"),MB_OK);
                        break;
                    }
                    vis_edit=true;
                    for (i=0;i<total_movie;i++)
                        if (strcmp(szTextBuf,movie[i].Name)==0)
                        {
                            vis_edit=false;
                            break;
                        }
                    if (!vis_edit)
                    {
                        MessageBox(hWnd,TEXT("��Ӱ�����ѱ�ʹ��"),TEXT("����"),MB_OK);
                        break;
                    }
                    //ר������
                    GetWindowText(hEditProfessorMark,szTextBuf,100);
                    if (!(strlen(szTextBuf)==3 && szTextBuf[1]=='.' && szTextBuf[0]>='0' && szTextBuf[0]<='9' && szTextBuf[2]>='0' && szTextBuf[2]<='9'))
                    {
                        MessageBox(hWnd,TEXT("ר��������д����"),TEXT("����"),MB_OK);
                        break;
                    }
                    //��ӳʱ��
                    GetWindowText(hEditTime,szTextBuf,100);
                    if (strlen(szTextBuf)==0)
                    {
                        MessageBox(hWnd,TEXT("��ӳʱ�䲻��Ϊ��"),TEXT("����"),MB_OK);
                        break;
                    }
                    vis_edit=true;
                    for (i=0;i<10;i++)
                        if (i!=4 && i!=7 && (szTextBuf[i]<'0' || szTextBuf[i]>'9'))
                        {
                            vis_edit=false;
                            break;
                        }
                    if (vis_edit==false || strlen(szTextBuf)!=10 || szTextBuf[4]!='-' || szTextBuf[7]!='-')
                    {
                        MessageBox(hWnd,TEXT("��ӳʱ����д����"),TEXT("����"),MB_OK);
                        break;
                    }
                    //����Ӱȷ�ϴ���ʱҪ total_movie++;
                    if (pos_movie==total_movie) total_movie++;
                    //example 2008-01-01
                    strncpy(szNumBuf,szTextBuf,4);
                    movie[pos_movie].year=atoi(szNumBuf);
                    strncpy(szNumBuf,szTextBuf+5,2);
                    movie[pos_movie].month=atoi(szNumBuf);
                    strncpy(szNumBuf,szTextBuf+8,2);
                    movie[pos_movie].day=atoi(szNumBuf);
                    //name address
                    GetWindowText(hEditMovieName,szTextBuf,100);
                    strcpy(movie[pos_movie].Name,szTextBuf);
                    GetWindowText(hEditPlace,szTextBuf,100);
                    strcpy(movie[pos_movie].Country,szTextBuf);
                    GetWindowText(hEditPhotoAddress,szTextBuf,100);
                    strcpy(movie[pos_movie].Photo,szTextBuf);
                    GetWindowText(hEditTorrentAddress,szTextBuf,100);
                    strcpy(movie[pos_movie].Torrent,szTextBuf);
                    GetWindowText(hEditFileAddress,szTextBuf,100);
                    strcpy(movie[pos_movie].File,szTextBuf);
                    GetWindowText(hEditIntroduce,szPassage,1000);
                    strcpy(movie[pos_movie].Passage,szPassage);
                    //Category mood
                    //IsDlgButtonChecked(hWnd,x) xΪ��ʶ�� BST_CHECDKED Ϊ����
                    for (i=1;i<10;i++)
                        if (IsDlgButtonChecked(hWnd,3+i)==BST_CHECKED) movie[pos_movie].Category[i]=true;
                            else movie[pos_movie].Category[i]=false;
                    for (i=1;i<10;i++)
                        if (IsDlgButtonChecked(hWnd,13+i)==BST_CHECKED) movie[pos_movie].Mood[i]=true;
                            else movie[pos_movie].Mood[i]=false;
                    //Mark �������֡�ר�����������޸Ķ����ģ��������ﲻ�ò���
                    break;
                //�½� ���
                case 42:
                    SetWindowText(hEditMovieName,"");
                    SetWindowText(hEditTime,"");
                    SetWindowText(hEditPlace,"");
                    SetWindowText(hEditIntroduce,"");
                    SetWindowText(hEditPhotoAddress,"");
                    SetWindowText(hEditTorrentAddress,"");
                    SetWindowText(hEditFileAddress,"");
                    sprintf(szTextBuf,TEXT("%.1f/%d��"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
                    SetWindowText(hEditOverallMark,"");
                    SetWindowText(hEditProfessorMark,"");
                    SetWindowText(hEditUserMark,"0/0��");
                    SetWindowText(hLabMarkStandard,"����:0.1~9.9,ר������100%,�û�����0%");
                    vis_photo=true;
                    SendMessage(hWnd,WM_PAINT,(WPARAM)36,NULL);
                    vis_photo=false;
                    //��Ӱ��Ŵ�0��ʼ�������½��ĵ�Ӱ���Ϊtotal_movie
                    pos_movie=total_movie;
                    movie[pos_movie].Number=pos_movie;
                    movie[pos_movie].RatioMark=1.0;
                    movie[pos_movie].UserNumber=0;
                    movie[pos_movie].OverallMark=0;
                    movie[pos_movie].ProfessorMark=0;
                    movie[pos_movie].UserMark=0;
                    for (i=1;i<=9;i++) movie[pos_movie].Category[i]=false;
                    for (i=1;i<=9;i++) movie[pos_movie].Mood[i]=false;
                    break;
                //�鿴 ��ȫ
                case 45:
                    SetWindowText(hEditMovieName,movie[pos_movie].Name);
                    sprintf(szTextBuf,TEXT("%d-%d-%d"),movie[pos_movie].year,movie[pos_movie].month,movie[pos_movie].day);
                   SetWindowText(hEditTime,szTextBuf);
//                    SetWindowText(hEditPlace,movie[pos_movie].Country);
//                    SetWindowText(hEditIntroduce,movie[pos_movie].Passage);
//                    SetWindowText(hEditPhotoAddress,movie[pos_movie].Photo);
//                    SetWindowText(hEditTorrentAddress,movie[pos_movie].Torrent);
//                    SetWindowText(hEditFileAddress,movie[pos_movie].File);
//                    SetWindowText(hEditOverallMark,movie[pos_movie].OverallMark);
//                    SetWindowText(hEditProfessorMark,movie[pos_movie].ProfessorMark);
                    sprintf(szTextBuf,TEXT("%.1f/%d��"),movie[pos_movie].UserMark/movie[pos_movie].UserNumber,movie[pos_movie].UserNumber);
                    SetWindowText(hEditUserMark,szTextBuf);
                    sprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%"),(int)(movie[pos_movie].RatioMark*100.0+0.5),(int)(100.0-100.0*movie[pos_movie].RatioMark));
                    SetWindowText(hLabMarkStandard,szTextBuf);
                    SendMessage(hWnd,WM_PAINT,(WPARAM)36,NULL);
                    break;
                //��ת
                case 44:
                    GetWindowText(hEditCheckMovie,szTextBuf,100);
                    if (strlen(szTextBuf)==0) break;
                    vis_page=true;
                    if (szTextBuf[0]=='0') vis_page=false;
                    for (i=0;i<strlen(szTextBuf);i++)
                        if (szTextBuf[i]<48 || szTextBuf[i]>57)
                        {
                            vis_page=false;
                            break;
                        }
                    if (vis_page)
                    {
                        page=atoi(szTextBuf);
                        if (page<=total_movie)
                        {
                            pos_movie=page-1;
                            SendMessage(hWnd,WM_COMMAND,(WPARAM)45,NULL);
                        }
                    }

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }
            break;

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            switch (wParam)
            {
                case 34:
                    GetWindowRect(hEditIntroduce,&rect);
                    hdc=GetDC(hWnd);
                    TextOut(hdc,rect.left,rect.top,"�������Ӱ���",14);
                    break;

                case 36:
                    //����ͼƬ
                    GetWindowRect(hEditMovieName,&rect);
                    GetWindowText(hEditPhotoAddress,szTextBuf,100);
                    if (vis_photo) strcpy(szTextBuf,"E:\\MovieSoftware\\Photo\\white.bmp");
                    hdc=GetDC(hWnd);
                    mdc=CreateCompatibleDC(hdc);
                    bg=(HBITMAP)LoadImage(
                        NULL,
                        szTextBuf,
                        IMAGE_BITMAP,120,160,LR_LOADFROMFILE
                    );
                    SelectObject(mdc,bg);
                    BitBlt(hdc,rect.left+50,rect.top-50,120,160,mdc,0,0,SRCAND);
                    break;
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            DeleteObject(hFont);
            DeleteObject(hFontTitle);
            DeleteObject(hFontNumber);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}