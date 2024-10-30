#include <windows.h>

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
    hwnd = CreateWindow(
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
    ShowWindow (hwnd, iCmdShow);
    //���£����ƣ�����
    UpdateWindow (hwnd);

    /**********�ڢ۲�����Ϣѭ��**********/
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage (&msg);  //������Ϣ
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
    INT wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc,mdc;
    HBITMAP bg;

    static HFONT hFont;
    static HFONT hFontTitle;
    static HFONT hFontMark;
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
    static HWND hLabProfessorMark;
    static HWND hLabUserMark;
    static HWND hLabUserScore;
    static HWND hLabUserPerson;
    static HWND hLabOverallMark;
    static HWND hEditProfessorMark;
    static HWND hEditUserMark;
    static HWND hEditUserScore;
    static HWND hEditUserPerson;
    static HWND hEditOverallMark;
    static HWND hLabMarkStandard;
    static HWND hBtnMarkStandardShow;

    TCHAR szTextBuf[100];
    TCHAR Movie_Name[50]="������è";
    FLOAT ProfessorMark=7.8,UserMark=8.5,OverallMark;
//ר��ռ�ı���(100Ϊ��) ����������
    INT RatioMark=60,OverallNumber=100;

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

            hFontMark=CreateFont(
                -28,-14,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("����")
            );
            //��Ӱ��
            hLabMovieName=CreateWindow(
                TEXT("static"),TEXT("��Ӱ����"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,100,120,40,
                hWnd,(HMENU)1,hInst,NULL
            );

            hEditMovieName=CreateWindow(
                TEXT("edit"),TEXT(""),
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                240,100,450,40,
                hWnd,(HMENU)2,hInst,NULL
            );
            //��Ӱ���
            hLabMovieMode=CreateWindow(
                TEXT("static"),TEXT("��Ӱ���"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,160,120,40,
                hWnd,(HMENU)3,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("ϲ��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,160,65,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,160,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,160,65,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,160,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("�ഺ"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                520,160,65,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,190,65,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("�ƻ�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,190,65,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("���"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,190,65,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            checkboxCrime=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,190,65,26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //�ʺ�����
            hLabMovieMood=CreateWindow(
                TEXT("static"),TEXT("�ʺ����飺"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,230,120,40,
                hWnd,(HMENU)13,hInst,NULL
            );

            checkboxHappy=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX | WS_GROUP,
                240,230,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            checkboxExcited=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,230,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            checkboxProud=CreateWindow(
                TEXT("button"),TEXT("�Ժ�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,230,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );

            checkboxSad=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                450,230,65,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            checkboxAngry=CreateWindow(
                TEXT("button"),TEXT("��ŭ"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                520,230,65,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            checkboxScared=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                240,260,65,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            checkboxAshamed=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                310,260,65,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            checkboxAnxious=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                380,260,65,26,
                hWnd,(HMENU)21,hInst,NULL
            );
            //����
            hLabOverallMark=CreateWindow(
                TEXT("static"),TEXT("��������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                90,300,120,40,
                hWnd,(HMENU)22,hInst,NULL
            );


            OverallMark=(RatioMark*ProfessorMark+(100-RatioMark)*UserMark)/100.0;
            sprintf(szTextBuf,TEXT("%.1f"),OverallMark);
            hEditOverallMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
                220,300,55,40,
                hWnd,(HMENU)23,hInst,NULL
            );

            hLabProfessorMark=CreateWindow(
                TEXT("static"),TEXT("ר������:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                290,300,120,40,
                hWnd,(HMENU)24,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("%.1f"),ProfessorMark);
            hEditProfessorMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                420,300,55,40,
                hWnd,(HMENU)25,hInst,NULL
            );

            hLabUserMark=CreateWindow(
                TEXT("static"),TEXT("�û�����:"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_RIGHT | SS_CENTERIMAGE,
                490,300,120,40,
                hWnd,(HMENU)26,hInst,NULL
            );

            sprintf(szTextBuf,TEXT("%.1f"),UserMark);
            hEditUserMark=CreateWindow(
                TEXT("edit"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                620,300,55,40,
                hWnd,(HMENU)27,hInst,NULL
            );

            wsprintf(szTextBuf,TEXT("����:0.1~9.9,ר������%d%%,�û�����%d%%,����������%d"),RatioMark,100-RatioMark,OverallNumber);
            hLabMarkStandard=CreateWindow(
                TEXT("static"),szTextBuf,
                WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
                90,360,550,40,
                hWnd,(HMENU)28,hInst,NULL
            );
            //������Ա���˺ſ����޸�����,���û����˺Ų����޸����� ES_READONLY �Ƿ�Ϊֻ������ֹ�û�������޸ı༭�ؼ��е��ı���
            //������Ա�˺�:hEditOverallMark���ɸ� hEditProfessorMark��hEditUserMark�ɸ�
            hBtnMarkStandardShow=CreateWindow(
                TEXT("button"),TEXT("���ֹ���"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_CENTER,
                650,360,80,40,
                hWnd,(HMENU)29,hInst,NULL
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
            SendMessage(hLabProfessorMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hLabUserMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hLabUserScore,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hLabUserPerson,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hLabOverallMark,WM_SETFONT,(WPARAM)hFontTitle,NULL);
            SendMessage(hEditProfessorMark,WM_SETFONT,(WPARAM)hFontMark,NULL);
            SendMessage(hEditUserMark,WM_SETFONT,(WPARAM)hFontMark,NULL);
            SendMessage(hEditUserScore,WM_SETFONT,(WPARAM)hFontMark,NULL);
            SendMessage(hEditUserPerson,WM_SETFONT,(WPARAM)hFontMark,NULL);
            SendMessage(hEditOverallMark,WM_SETFONT,(WPARAM)hFontMark,NULL);
            SendMessage(hEditOverallMark,WM_SETFONT,(WPARAM)hFontMark,NULL);
            SendMessage(hLabMarkStandard,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(hBtnMarkStandardShow,WM_SETFONT,(WPARAM)hFont,NULL);
            break;

        case WM_COMMAND:
            wmId    = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            switch (wmId)
            {
                case 29:
                    wsprintf(szTextBuf,TEXT("�û�����������\r\n <100               ר��100%% �û�0%% \r\n 100~1000        ר��80%% �û�20%% \r\n 1000~10000     ר��60%% �û�40%% \r\n 10000~100000 ר��40%% �û�60%% \r\n >100000          ר��30%% �û�70%%"));
                    MessageBox(hWnd,szTextBuf,TEXT("���ֹ���"),MB_ICONINFORMATION);
                    break;

                default:
                    return DefWindowProc(hWnd,message,wParam,lParam);
            }

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
//����ͼƬ
            hdc=GetDC(hWnd);
            mdc=CreateCompatibleDC(hdc);
            bg=(HBITMAP) LoadImage (
                NULL,
                TEXT("E:\\Windows_API\\u=2727223183,2005069255&fm=58.jpg"),
                IMAGE_BITMAP,
                121,161,
                LR_LOADFROMFILE
            );
            SelectObject(mdc,bg);
            BitBlt(hdc,50,50,121,161,mdc,0,0,SRCAND);

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
