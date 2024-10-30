#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

#include <windows.h>
#include <malloc.h>
#include <stdbool.h>

struct user
{
    TCHAR Name[50],Password[50];
    int Sex,Define,Age,Condition;
    bool Preference[10];
};

struct user user[1000];


//末尾记得要加free(user)


#endif // DEFINE_H_INCLUDED
