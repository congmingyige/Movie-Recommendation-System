#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

void fileopen_movie()
{
    int i,j,len;
    char s[1000];
    FILE *fp_movie=fopen("E:\\MovieSoftware\\movie.txt","r");
    fscanf(fp_movie,"%ld",&total_movie);
    for (i=0;i<total_movie;i++)
    {
        fscanf(fp_movie,"%ld",&movie[i].Number);
        strcpy(movie[i].Name,"");
        strcpy(movie[i].Country,"");
        strcpy(movie[i].Photo,"");
        strcpy(movie[i].Torrent,"");
        strcpy(movie[i].File,"");
        strcpy(movie[i].Passage,"");
        while (1)
        {
            fgets(s,100,fp_movie);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/name/\n")==0) break;
                else strcat(movie[i].Name,s);
        }
        len=strlen(movie[i].Name);
        while (len>0 && movie[i].Name[len-1]=='\n') len--;
        movie[i].Name[len]='\0';

        while (1)
        {
            fgets(s,100,fp_movie);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/country/\n")==0) break;
                else strcat(movie[i].Country,s);
        }
        len=strlen(movie[i].Country);
        while (len>0 && movie[i].Country[len-1]=='\n') len--;
        movie[i].Country[len]='\0';

        while (1)
        {
            fgets(s,100,fp_movie);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/photo/\n")==0) break;
                else strcat(movie[i].Photo,s);
        }
        len=strlen(movie[i].Photo);
        while (len>0 && movie[i].Photo[len-1]=='\n') len--;
        movie[i].Photo[len]='\0';

        while (1)
        {
            fgets(s,100,fp_movie);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/torrent/\n")==0) break;
                else strcat(movie[i].Torrent,s);
        }
        len=strlen(movie[i].Torrent);
        while (len>0 && movie[i].Torrent[len-1]=='\n') len--;
        movie[i].Torrent[len]=='\0';

        while (1)
        {
            fgets(s,100,fp_movie);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/file/\n")==0) break;
                else strcat(movie[i].File,s);
        }
        len=strlen(movie[i].File);
        while (len>0 && movie[i].File[len-1]=='\n') len--;
        movie[i].File[len]='\0';

        while (1)
        {
            fgets(s,1000,fp_movie);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/passage/\n")==0) break;
                else strcat(movie[i].Passage,s);
        }
        len=strlen(movie[i].Passage);
        while (len>0 && movie[i].Passage[len-1]=='\n') len--;
        movie[i].Passage[len]='\0';

        for (j=1;j<10;j++)
            fscanf(fp_movie,"%d",&movie[i].Category[j]);
        for (j=1;j<9;j++)
            fscanf(fp_movie,"%d",&movie[i].Mood[j]);
        fscanf(fp_movie,"%f%f%f%f",&movie[i].OverallMark,&movie[i].ProfessorMark,&movie[i].UserMark,&movie[i].RatioMark);
        fscanf(fp_movie,"%ld%d%d%d",&movie[i].UserNumber,&movie[i].year,&movie[i].month,&movie[i].day);
    }
    fclose(fp_movie);
}

void fileopen_user()
{
    int i,j,len;
    char s[1000];
    FILE *fp_user=fopen("user.txt","r");
    fscanf(fp_user,"%ld",&CurrentUser);
    fscanf(fp_user,"%ld",&total_user);
    for (i=0;i<total_user;i++)
    {
        fscanf(fp_user,"%ld",&user[i].Number);
        strcpy(user[i].Name,"");
        strcpy(user[i].Password,"");
        while (1)
        {
            fgets(s,100,fp_user);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/name/\n")==0) break;
                else strcat(user[i].Name,s);
        }
        len=strlen(user[i].Name);
        while (len>0 && user[i].Name[len-1]=='\n') len--;
        user[i].Name[len]='\0';

        while (1)
        {
            fgets(s,100,fp_user);
            if (strcmp(s,"\n")==0) continue;
            if (strcmp(s,"/password/\n")==0) break;
                else strcat(user[i].Password,s);
        }
        len=strlen(user[i].Password);
        while (len>0 && user[i].Password[len-1]=='\n') len--;
        user[i].Password[len]='\0';

        fscanf(fp_user,"%d%d%d%d",&user[i].Sex,&user[i].Define,&user[i].Age,&user[i].Condition);
        for (j=1;j<10;j++)
            fscanf(fp_user,"%d",&user[i].Preference[j]);
    }
    fclose(fp_user);
}
