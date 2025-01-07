#include "pc.h"

int main()
{
    HANDLE hMapFile; // 共享内存句柄
    struct BufferPool* pBuf; // 共享内存缓冲区指针
    int pid = GetCurrentProcessId(); // 获取当前进程ID
    srand(pid); // 使用进程ID初始化随机数生成器

    // 连接共享内存
    hMapFile = OpenFileMapping(
            FILE_MAP_ALL_ACCESS, // 读写访问
            FALSE,               // 不继承名称
            sharedMemoryName);   // 映射对象名称
    if (hMapFile == nullptr)
    {
        printf("共享内存映射失败!\n");
        return 1;
    }

    pBuf = (struct BufferPool*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MEMORY_BUFFER_LEN);
    if (pBuf == nullptr)
    {
        printf("共享内存映射视图失败!\n");
        CloseHandle(hMapFile);
        return 1;
    }

    // 打开互斥量
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, mutexName);
    if (hMutex == nullptr)
    {
        printf("互斥量打开失败!\n");
        return 1;
    }

    // 打开空信号量
    HANDLE hSemaphoreEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, emptySemaphoreName);
    if (hSemaphoreEmpty == nullptr)
    {
        printf("空信号量打开失败!\n");
        return 1;
    }

    // 打开满信号量
    HANDLE hSemaphoreFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, fullSemaphoreName);
    if (hSemaphoreFull == nullptr)
    {
        printf("满信号量打开失败!\n");
        return 1;
    }

    int SleepTime; // 休眠时间
    for (int i = 0; i < CONSUMER_REPEAT; i++)
    {
        QueryPerformanceCounter(&startTime); // 记录开始时间
        SleepTime = rand() % 2000; 

        Sleep(SleepTime);
        // P(满信号量)：等待满信号量g
        WaitForSingleObject(hSemaphoreFull, INFINITE);
        // P(互斥量)：等待互斥量
        WaitForSingleObject(hMutex, INFINITE);

        // 从共享内存中消费一个字符串
        char* s = pBuf->str[pBuf->head]; // 获取缓冲区头部的字符串指针
        // 休眠
        

        printf("消费者: 弹出 %-10s ", pBuf->str[pBuf->head]); // 打印消费的字符串
        memset(s, 0, sizeof(pBuf->str[pBuf->head])); // 清空消费的字符串

        pBuf->head = (pBuf->head + 1) % BUFFER_COUNT; // 更新头部索引

        // 打印缓冲区内容
        for (int cnt = 0; cnt < BUFFER_COUNT; cnt++)
            printf("|%-10s", pBuf->str[cnt]);
        printf("|");

        QueryPerformanceCounter(&endTime); // 记录结束时间
        QueryPerformanceFrequency(&frequency); // 获取性能计数器频率
        runningTime = (double)(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart; // 计算运行时间
        printf(" 运行时间:%lf ms\n", runningTime); // 打印运行时间

        // V(互斥量)：释放互斥量
        ReleaseMutex(hMutex);
        // V(空信号量)：释放空信号量
        ReleaseSemaphore(hSemaphoreEmpty, 1, nullptr);
    }

    // 释放资源
    CloseHandle(hSemaphoreEmpty); // 关闭空信号量
    CloseHandle(hSemaphoreFull); // 关闭满信号量
    CloseHandle(hMutex); // 关闭互斥量
    UnmapViewOfFile(pBuf); // 解除共享内存映射
    CloseHandle(hMapFile); // 关闭共享内存句柄
    return 0;
}
