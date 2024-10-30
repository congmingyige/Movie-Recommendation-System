#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct user
{
    long Number;
    TCHAR Name[100],Password[100];
    //Sex:�Ա�(��1��Ů2������0)
    //Define:���(ѧ��1��������2������3������0)
    //Age:����(δ������1��������2��������3������4������0)
    //Condition:״̬(�ż�1������2������3������0)
    int Sex,Define,Age,Condition;
    //Preference:ƫ��(ϲ��1������2������3������4���ഺ5������6���ƻ�7�����8������9������0)
    int Preference[10];
};

struct movie
{
    long Number;
    TCHAR Name[100],Country[100],Passage[1000],Photo[100],Torrent[100],File[100];
    int year,month,day;
    long UserNumber;
    //UserNumber:���ֵ�������
    //RatioMark:ר������ռ�ܷ����ı���(0~1)
    //OverallMark:����
    //ProfessorMark:ר������
    //UserMark:�����û����ֵķ���֮��
    float RatioMark,OverallMark,ProfessorMark,UserMark;
    //Category:ģʽ(ϲ��1������2������3������4���ഺ5������6���ƻ�7�����8������9)
    //Mood:����(����1������2���Ժ�3������4����ŭ5������6������77������8)
    //0���� 1��
    int Category[10],Mood[10];
};
//��Ӱ���û�����
extern struct user user[1000];
extern struct movie movie[1000];
//��ǰ��Ӱ���û������
extern long pos_movie,pos_user;
//��Ӱ���û����� ��ǰ��¼���û���ţ���û��Ϊ0
extern long total_movie,total_user,CurrentUser;

//ĩβ�ǵ�Ҫ��free(user)
//�ǵó�ʼ��user��movie   ��������

#endif // DEFINE_H_INCLUDED
