#include <iostream>
#include <unistd.h>
#include <cstdlib>

int main(void)
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    int ret = fork();
    if (ret < 0)
    {
        perror("fork");
        return 1;
    }
    else if (ret == 0) // child
    {
        close(pipefd[0]);
        write(pipefd[1], "Hello", 5);
        close(pipefd[1]);

        exit(EXIT_SUCCESS);
    }
    else // parent
    {
        close(pipefd[1]);
        char buf[1024] = {0};
        read(pipefd[0], buf, 1023);

        printf("child said: %s\n", buf);
    }


    return 0;
}
