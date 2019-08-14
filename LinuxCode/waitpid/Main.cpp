#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int ret = fork();
    if (ret < 0)
    {
        perror("fork");
        return -1;
    }

    if (ret == 0) // child
    {
        std::cout << "I am child, my NO. " << getpid() << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "I am parent, my NO. " << getpid() << std::endl;

        int status;
        int r = waitpid(ret, &status, 0);

        if (WIFEXITED(status) && r == ret)
        {
            std::cout << "child process success exit, and the return code is " << WEXITSTATUS(status) << std::endl;

        }
        else
        {
            std::cout << "wait child failed!" << std::endl;
            return 1;
        }
    }

    return 0;
}
