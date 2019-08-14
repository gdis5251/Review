#include <iostream>

// 查看所有环境变量
//
#if 0
int main(int argc, char* argv[], char* env[])
{
    for (int i = 0; env[i] != nullptr; i++)
    {
        std::cout << env[i] << std::endl;
    }


    return 0;
}
#endif

int main(int argc, char* argv[])
{
    extern char** environ;
    for (int i = 0; environ[i] != nullptr; i++)
    {
        std::cout << environ[i] << std::endl;
    }

    return 0;
}
