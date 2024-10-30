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
    //Sex:性别(男1、女2、不填0)
    //Define:类别(学生1、工作者2、其它3、不填0)
    //Age:年龄(未成年人1、青年人2、成年人3、老人4、不填0)
    //Condition:状态(放假1、考试2、康复3、不填0)
    int Sex,Define,Age,Condition;
    //Preference:偏好(喜剧1、爱情2、动作3、动画4、青春5、剧情6、科幻7、惊悚8、犯罪9、不填0)
    int Preference[10];
};

struct movie
{
    long Number;
    TCHAR Name[100],Country[100],Passage[1000],Photo[100],Torrent[100],File[100];
    int year,month,day;
    long UserNumber;
    //UserNumber:评分的总人数
    //RatioMark:专家评分占总分数的比例(0~1)
    //OverallMark:总评
    //ProfessorMark:专家评分
    //UserMark:所有用户评分的分数之和
    float RatioMark,OverallMark,ProfessorMark,UserMark;
    //Category:模式(喜剧1、爱情2、动作3、动画4、青春5、剧情6、科幻7、惊悚8、犯罪9)
    //Mood:心情(高兴1、激动2、自豪3、伤心4、愤怒5、害怕6、羞愧77、忐忑8)
    //0不是 1是
    int Category[10],Mood[10];
};
//电影、用户数据
extern struct user user[1000];
extern struct movie movie[1000];
//当前电影、用户的序号
extern long pos_movie,pos_user;
//电影、用户总数 当前登录的用户编号，若没有为0
extern long total_movie,total_user,CurrentUser;

//末尾记得要加free(user)
//记得初始化user和movie   在主程序

#endif // DEFINE_H_INCLUDED
