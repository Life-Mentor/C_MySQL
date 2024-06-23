#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

void uinkey(int ch);
void initMySQL();

int main(int argc, char *argv[])
{
        int ch;
        printf("--------------------------\n");
        printf("|                        |\n");
        printf("|     duck cli mysql     |\n");
        printf("|                        |\n");
        printf("--------------------------\n");
        while ((ch = getopt(argc, argv, "u:p:h")) != -1)
        {
                uinkey(ch);
        }
        return EXIT_SUCCESS;
}

void uinkey(int ch)
{
       switch (ch) 
        {
                case 'u':
                        printf("HAVE option: -u \n\n");
                        printf("The argumentof -u is %s\n\n",optarg);
                        break;
                case 'p':
                        printf("HAVE option: -p \n\n");
                        printf("The argumentof -p is %s\n\n",optarg);
                        break;
                case 'h':
                        printf("这个玩意就是简单用用，MySQL链接的二次开发\n");
                        break;
        }
}


