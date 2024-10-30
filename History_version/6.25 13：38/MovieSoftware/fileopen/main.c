#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

long total_movie;
struct movie movie[1000];
long total_user;
struct user user[1000];
long CurrentUser;

int main()
{
    fileopen_movie();
    fileopen_user();
    fileclose_movie();
    fileclose_user();
}
