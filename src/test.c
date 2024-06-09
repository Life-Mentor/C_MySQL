#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>


struct sockaddr_un addr;
char *mysql_sock = "/run/mysqld/mysqld.sock";

int
main (int argc, char *argv[])
{
        int sock_res = socket (AF_UNIX, SOCK_STREAM, 0);
        if (sock_res < 0)
        {
                perror ("SOCK ERROR!!!;");
                exit (1);
        }
        memset (&addr, 0, sizeof (addr));
        addr.sun_family = AF_UNIX;
        strcpy (addr.sun_path, mysql_sock);
        int date = connect (sock_res, (struct sockaddr *)&addr, sizeof (addr));
        if (date < 0)
        {
                printf ("ERROR");
                close (sock_res);
        }
        printf ("%d OK\n", date);
        close (sock_res);

        return 0;
}
