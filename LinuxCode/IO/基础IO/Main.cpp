#include <iostream>
#include <cstdio>
#include <cstring>

#if 0 
写文件
int main(void)
{
    FILE* fp = fopen("TestIO.txt", "w");
    if (fp == nullptr)
    {
        perror("fopen");
    }

    const char* msg = "Test IO.";
    int count = 5;
    while (count--)
    {
        fwrite(msg, strlen(msg), 1, fp);
    }

    fclose(fp);

    return 0;
}
#endif 

// 读文件
#if 1
int main(void)
{
    FILE* fp = fopen("TestIO.txt", "r");
    if (fp == nullptr)
    {
        perror("fopen");
        return 1;
    }

    char buf[1024] = {0};
    const char* msg = "Test IO.";

    while (true)
    {
        ssize_t s = fread(buf, 1, strlen(msg), fp);
        if (s > 0)
        {
            buf[s] = 0;
            std::cout << buf << std::endl;
        }

        if (feof(fp))
        {
            break;
        }
    }

    fclose(fp);

    return 0;
}
#endif
