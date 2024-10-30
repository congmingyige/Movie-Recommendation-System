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
        TEXT("��Ϣ����"),  //���ڱ��⣨�����ڱ�������
        WS_OVERLAPPEDWINDOW,  //���ڷ��
        500/*CW_USEDEFAULT*/,  //��ʼ��ʱx���λ��
        250/*CW_USEDEFAULT*/,  //��ʼ��ʱy���λ��
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
    while( GetMessage(&msg, NULL, 0, 0) ){
        TranslateMessage(&msg);  //������Ϣ
        DispatchMessage (&msg);  //������Ϣ
    }

    return msg.wParam;
}

/**********�ڢܲ������ڹ���**********/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    extern struct user user[1000];
    TCHAR szTextBuf[100];
    int pos=1;
    int wmId,wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    static HFONT hFont;  //�߼�����
    //��ѡ �Ա�
    static HWND labSex;
    static HWND radioMale;
    static HWND radioFemale;
    //��ѡ ����
    static HWND labDefine;
    static HWND radioStudent;
    static HWND radioWorker;
    static HWND radioOther;
    //��ѡ ����
    static HWND labAge;
    static HWND radioJuvenile;
    static HWND radioTeenage;
    static HWND radioAdult;
    static HWND radioOld;
    //��ѡ ״̬
    static HWND labSituation;
    static HWND radioHoliday;
    static HWND radioExam;
    static HWND radioRecovery;
    //��ѡ ƫ��
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
    //ȷ�ϰ�ť
    static HWND btnSubmit;

    switch (message){
        case  WM_CREATE:
            hFont=CreateFont(
                -14,-7,0,0,400,
                FALSE,FALSE,FALSE,DEFAULT_CHARSET,
                OUT_CHARACTER_PRECIS,CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
                FF_DONTCARE,TEXT("΢���ź�")
            );

            //ѡ���Ա�
            labSex=CreateWindow(
                TEXT("static"),TEXT("�Ա�"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,10,80,26,
                hWnd,(HMENU)1,hInst,NULL
            );

            radioMale=CreateWindow(
                TEXT("button"), TEXT("��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON  | WS_GROUP,
                95,10,50,26,
                hWnd,(HMENU)2,hInst,NULL
            );

            radioFemale=CreateWindow(
                TEXT("button"),TEXT("Ů"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                150,10,50,26,
                hWnd,(HMENU)3,hInst,NULL
            );

            //���
            labDefine=CreateWindow(
                TEXT("static"),TEXT("���"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,40,80,26,
                hWnd,(HMENU)4,hInst,NULL
            );

            radioStudent=CreateWindow(
                TEXT("button"),TEXT("ѧ��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,40,65,26,
                hWnd,(HMENU)5,hInst,NULL
            );

            radioWorker=CreateWindow(
                TEXT("button"),TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,40,80,26,
                hWnd,(HMENU)6,hInst,NULL
            );

            radioOther=CreateWindow(
                TEXT("button"), TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                250,40,65,26,
                hWnd,(HMENU)7,hInst,NULL
            );
            //����
            labAge=CreateWindow(
                TEXT("static"), TEXT("���䣺"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,70,80,26,
                hWnd,(HMENU)8,hInst,NULL
            );

            radioJuvenile=CreateWindow(
                TEXT("button"),TEXT("δ������"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,70,90,26,
                hWnd,(HMENU)9,hInst,NULL
            );

            radioTeenage=CreateWindow(
                TEXT("button"),TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                190,70,75,26,
                hWnd,(HMENU)10,hInst,NULL
            );

            radioAdult=CreateWindow(
                TEXT("button"),TEXT("������"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                270,70,75,26,
                hWnd,(HMENU)11,hInst,NULL
            );

            radioOld=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                350, 70, 60, 26,
                hWnd,(HMENU)12,hInst,NULL
            );
            //״̬
            labSituation=CreateWindow(
                TEXT("static"), TEXT("״̬(ѡ��)��"),
                WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
                10,100,80,26,
                hWnd,(HMENU)13,hInst,NULL
            );

            radioHoliday=CreateWindow(
                TEXT("button"),TEXT("�ż�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP,
                95,100,65,26,
                hWnd,(HMENU)14,hInst,NULL
            );

            radioExam=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                165,100,65,26,
                hWnd,(HMENU)15,hInst,NULL
            );

            radioRecovery=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON,
                235,100,65,26,
                hWnd,(HMENU)16,hInst,NULL
            );
            //ƫ��
            labPreference=CreateWindow(
                TEXT("static"),TEXT("ƫ��(ѡ��)��"),
                WS_CHILD | WS_VISIBLE | SS_CENTER,
                10,130,80,26,
                hWnd,(HMENU)17,hInst,NULL
            );

            checkboxComedy=CreateWindow(
                TEXT("button"),TEXT("ϲ��"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                95,130,65,26,
                hWnd,(HMENU)18,hInst,NULL
            );

            checkboxRomance=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                165,130,65,26,
                hWnd,(HMENU)19,hInst,NULL
            );

            checkboxAction=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                235,130,65,26,
                hWnd,(HMENU)20,hInst,NULL
            );

            checkboxCartoon=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                305,130,65,26,
                hWnd,(HMENU)21,hInst,NULL
            );

            checkboxTeen=CreateWindow(
                TEXT("button"),TEXT("�ഺ"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                375,130,65,26,
                hWnd,(HMENU)22,hInst,NULL
            );

            checkboxFeature=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                95,160,65,26,
                hWnd,(HMENU)23,hInst,NULL
            );

            checkboxSci_Fic=CreateWindow(
                TEXT("button"),TEXT("�ƻ�"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                165,160,65,26,
                hWnd,(HMENU)24,hInst,NULL
            );

            checkboxThriller=CreateWindow(
                TEXT("button"),TEXT("���"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                235,160,65,26,
                hWnd,(HMENU)25,hInst,NULL
            );

            checkboxCrime=CreateWindow(
                TEXT("button"),TEXT("����"),
                WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTOCHECKBOX,
                305,160,65,26,
                hWnd,(HMENU)26,hInst,NULL
            );
            //ȷ�ϰ�ť
            btnSubmit=CreateWindow(
                TEXT("button"),TEXT("ȷ��"),
                WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT | SS_CENTER,
                210,200,80,30,
                hWnd,(HMENU)27,hInst,NULL
            );

            //�Ա�
            SendMessage(labSex,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioMale,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioFemale,WM_SETFONT,(WPARAM)hFont,NULL);
            //����
            SendMessage(labDefine,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioStudent,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioWorker,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOther,WM_SETFONT,(WPARAM)hFont,NULL);
            //����
            SendMessage(labAge,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioJuvenile,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioTeenage,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioAdult,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioOld,WM_SETFONT,(WPARAM)hFont,NULL);
            //״̬
            SendMessage(labSituation,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioHoliday,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioExam,WM_SETFONT,(WPARAM)hFont,NULL);
            SendMessage(radioRecovery,WM_SETFONT,(WPARAM)hFont,NULL);
            //ƫ��
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
            //ȷ�ϰ�ť
            SendMessage(btnSubmit,WM_SETFONT,(WPARAM)hFont,NULL);

            break;

        case WM_COMMAND:
            wmId=LOWORD(wParam);
            wmEvent=HIWORD(wParam);
//����б�ѡ�еĻ�
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
                        wsprintf(szTextBuf,TEXT("     �û���Ϣ�ύ�ɹ�"));
                        int nSelect=MessageBox(hWnd,szTextBuf,TEXT("��Ϣ����"),MB_OK);
                        ShowWindow(hWnd,SW_HIDE);
                        UpdateWindow(hWnd);
                        break;
                    default:return DefWindowProc(hWnd, message, wParam, lParam);
                }
            }

        case WM_PAINT:
            hdc=BeginPaint(hWnd,&ps);
            // TODO:  �ڴ���������ͼ����...
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
