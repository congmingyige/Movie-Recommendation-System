#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

void fileclose_movie()
{
    long i,j;
    char s[1000];
    FILE *fp_movie=fopen("movie.txt","w");
    fprintf(fp_movie,"%ld\n",total_movie);
    for (i=0;i<total_movie;i++)
    {
        fprintf(fp_movie,"\n");
        fprintf(fp_movie,"%ld\n",movie[i].Number);
        fprintf(fp_movie,"%s\n",movie[i].Name);
        fprintf(fp_movie,"/name/\n");
        fprintf(fp_movie,"%s\n",movie[i].Country);
        fprintf(fp_movie,"/country/\n");
        fprintf(fp_movie,"%s\n",movie[i].Photo);
        fprintf(fp_movie,"/photo/\n");
        fprintf(fp_movie,"%s\n",movie[i].Torrent);
        fprintf(fp_movie,"/torrent/\n");
        fprintf(fp_movie,"%s\n",movie[i].File);
        fprintf(fp_movie,"/file/\n");
        fprintf(fp_movie,"%s\n",movie[i].Passage);
        fprintf(fp_movie,"/passage/\n");
        for (j=1;j<10;j++)
            fprintf(fp_movie,"%d ",movie[i].Category[j]);
        fprintf(fp_movie,"\n");
        for (j=1;j<9;j++)
            fprintf(fp_movie,"%d ",movie[i].Mood[j]);
        fprintf(fp_movie,"\n");
        fprintf(fp_movie,"%f %f %f %f\n",movie[i].OverallMark,movie[i].ProfessorMark,movie[i].UserMark,movie[i].RatioMark);
        fprintf(fp_movie,"%ld %d %d %d\n",movie[i].UserNumber,movie[i].year,movie[i].month,movie[i].day);
    }
    fclose(fp_movie);
}

void fileclose_user()
{
    long i,j;
    char s[1000];
    FILE *fp_user=fopen("user.txt","w");
    fprintf(fp_user,"%ld\n",CurrentUser);
    fprintf(fp_user,"%ld\n",total_user);
    for (i=0;i<total_user;i++)
    {
        fprintf(fp_user,"\n");
        fprintf(fp_user,"%ld\n",user[i].Number);
        fprintf(fp_user,"%s\n",user[i].Name);
        fprintf(fp_user,"/name/\n");
        fprintf(fp_user,"%s\n",user[i].Password);
        fprintf(fp_user,"/password/\n");
        fprintf(fp_user,"%d %d %d %d\n",user[i].Sex,user[i].Define,user[i].Age,user[i].Condition);
        for (j=1;j<10;j++)
            fprintf(fp_user,"%d ",user[i].Preference[j]);
        fprintf(fp_user,"\n");
    }
    fclose(fp_user);
}
