#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

void uinkey(int ch);
void login(int argc, char *argv[]);
void printlog();
void sql_query(MYSQL *con);
MYSQL* initMySQL();
void die(MYSQL*con);

typedef struct CMDINFO {
    char *name;
    char *pawd;
} cmdinfo;

cmdinfo cmd;

void die(MYSQL*con)
{
    if (con != NULL) {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
    }
    exit(1);
}

void uinkey(int ch)
{
    switch (ch) 
    {
        case 'u':
            cmd.name = optarg;
            break;
        case 'p':
            cmd.pawd = optarg;
            break;
        case 'h':
            printf("这个玩意就是简单用用，MySQL链接的二次开发\n");
            exit(0);
            break;
        default:
            fprintf(stderr, "Unknown option: %c\n", ch);
            exit(1);
    }
}

void login(int argc, char *argv[])
{
    int ch;
    while ((ch = getopt(argc, argv, "u:p:h")) != -1)
    {
        uinkey(ch);
    }

    if (cmd.name == NULL || cmd.pawd == NULL) {
        fprintf(stderr, "用户名和密码是必需的\n");
        exit(1);
    }
}

void printlog()
{
    printf("--------------------------\n");
    printf("|                        |\n");
    printf("|     duck cli mysql     |\n");
    printf("|                        |\n");
    printf("--------------------------\n");
}

MYSQL* initMySQL()
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }
    if (mysql_real_connect(con, "localhost", cmd.name, cmd.pawd, NULL, 0, NULL, 0) == NULL)
    {
        die(con);
    }
    printf("初始化成功\n");
    return con;
}

void sql_query(MYSQL *con)
{
    using_history();
    char *sql = readline(">>>: ");
    if (sql == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        exit(1);
    }
    if (*sql)
    {
        add_history(sql);
    }

    if (mysql_query(con, sql)) {
        free(sql); // 释放内存
        die(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        free(sql); // 释放内存
        die(con);
    }

    int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD *field;

    // 打印列名
    while ((field = mysql_fetch_field(result))) {
        printf("%s\t", field->name);
    }
    printf("\n");

    // 打印每一行的结果
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    free(sql); // 释放内存
}

int main(int argc, char *argv[])
{
    printlog();
    login(argc, argv);
    MYSQL *con = initMySQL();
    while (1) {
        sql_query(con);
    }
    mysql_close(con);
    return EXIT_SUCCESS;
}
