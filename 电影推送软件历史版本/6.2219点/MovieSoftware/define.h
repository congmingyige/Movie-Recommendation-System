#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct user
{
    TCHAR Name[50],Password[50];
    //Sex:�Ա�(��1/Ů2)
    //Define:���(ѧ��1��������2������3)
    //Age:����(δ������1��������2��������3������4)
    //Condition:״̬(�ż�1������2������3)
    int Sex,Define,Age,Condition;
    //Preference:ƫ��(ϲ��1������2������3������4���ഺ5������6���ƻ�7�����8������9)
    bool Preference[10];
};

struct movie
{
    TCHAR Name[50],Photo[100],Torrent[100];
    //UserNumber:���ֵ�������
    int UserNumber;
    //RatioMark:ר������ռ�ܷ����ı���(0~1)
    //OverallMark:����
    //ProfessorMark:ר������
    //UserMark:�����û����ֵķ���֮��
    float RatioMark,OverallMark,ProfessorMark,UserMark;
    //Category:ģʽ(ϲ��1������2������3������4���ഺ5������6���ƻ�7�����8������9)
    //Mood:����(����1������2���Ժ�3������4����ŭ5������6������77������8)
    bool Category[10],Mood[10];
};

extern struct user user[1000];

extern struct movie movie[1000];
//�û������
extern long pos_user;
//��Ӱ�����
extern long pos_movie;

//ĩβ�ǵ�Ҫ��free(user)
//�ǵó�ʼ��user��movie   ��������

#endif // DEFINE_H_INCLUDED
