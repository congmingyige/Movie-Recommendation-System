#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <windows.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

struct user
{
    TCHAR Name[50],Password[50];
    //Sex:性别(男1/女2)
    //Define:类别(学生1、工作者2、其它3)
    //Age:年龄(未成年人1、青年人2、成年人3、老人4)
    //Condition:状态(放假1、考试2、康复3)
    int Sex,Define,Age,Condition;
    //Preference:偏好(喜剧1、爱情2、动作3、动画4、青春5、剧情6、科幻7、惊悚8、犯罪9)
    bool Preference[10];
};

struct movie
{
    TCHAR Name[50],Photo[100],Torrent[100];
    //UserNumber:评分的总人数
    int UserNumber;
    //RatioMark:专家评分占总分数的比例(0~1)
    //OverallMark:总评
    //ProfessorMark:专家评分
    //UserMark:所有用户评分的分数之和
    float RatioMark,OverallMark,ProfessorMark,UserMark;
    //Category:模式(喜剧1、爱情2、动作3、动画4、青春5、剧情6、科幻7、惊悚8、犯罪9)
    //Mood:心情(高兴1、激动2、自豪3、伤心4、愤怒5、害怕6、羞愧77、忐忑8)
    bool Category[10],Mood[10];
};

extern struct user user[1000];

extern struct movie movie[1000];
//用户的序号
extern long pos_user;
//电影的序号
extern long pos_movie;

//末尾记得要加free(user)
//记得初始化user和movie   在主程序

#endif // DEFINE_H_INCLUDED
