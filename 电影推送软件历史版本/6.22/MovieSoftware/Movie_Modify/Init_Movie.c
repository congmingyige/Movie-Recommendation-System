#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "E:\\Movie\\define.h"

void InitMovie(long w)
{
    int i;
    //值为0代表未填
    //当ProfessorMark,OverallMark为0,不显示分数
    movie[w].RatioMark=100;
    movie[w].UserNumber=0;
    movie[w].OverallMark=0;
    movie[w].ProfessorMark=0;
    movie[w].UserMark=0;
    for (i=1;i<=9;i++) movie[w].Category[i]=false;
    for (i=1;i<=9;i++) movie[w].Mood[i]=false;
}
