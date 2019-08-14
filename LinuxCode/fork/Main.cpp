#include <iostream>
#include <unistd.h>

int main(void)
{
    int ret = fork();
    if (ret < 0)
    {
        perror("fork");
    }

    if (ret == 0)
    {
        std::cout << "Hello I am child process!" << std::endl;
        std::cout << getpid() << std::endl;
    }
    else
    {
        std::cout << "Hello I am Parent process!" << std::endl;
        std::cout << getpid() << std::endl;
        std::cout << ret << std::endl;
    }

    return 0;
}
