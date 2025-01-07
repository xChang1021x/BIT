#include <windows.h>
#include <cstdio>
#include "pc.h"

int main() {
    HANDLE sharedMemoryHandle; // 共享内存句柄
    BOOL operationResult; // 操作结果
    // 创建共享内存
    sharedMemoryHandle = CreateFileMapping(
            INVALID_HANDLE_VALUE,  // 使用分页文件
            nullptr,               // 默认安全属性
            PAGE_READWRITE,        // 读写访问
            0,                     // 最大对象大小（高32位）
            sizeof(struct memoryBuffer), // 最大对象大小（低32位）
            sharedMemoryName);     // 映射对象名称
    if (sharedMemoryHandle == nullptr) {
        printf("共享内存映射失败!\n");
        return 1;
    }

    // 创建互斥量
    HANDLE mutexHandle = CreateMutex(nullptr, FALSE, mutexName);
    if (mutexHandle == nullptr) {
        printf("互斥量创建失败!\n");
        return 1;
    }

    // 创建空信号量
    HANDLE emptySemaphoreHandle = CreateSemaphore(nullptr, 3, 3, emptySemaphoreName);
    if (emptySemaphoreHandle == nullptr) {
        printf("空信号量创建失败!\n");
        return 1;
    }

    // 创建满信号量
    HANDLE fullSemaphoreHandle = CreateSemaphore(nullptr, 0, 3, fullSemaphoreName);
    if (fullSemaphoreHandle == nullptr) {
        printf("满信号量创建失败!\n");
        return 1;
    }

    // 映射共享内存并清零
    struct memoryBuffer *sharedBuffer = (struct memoryBuffer *) MapViewOfFile(sharedMemoryHandle, FILE_MAP_ALL_ACCESS, 0, 0, MEMORY_BUFFER_LEN);
    if (sharedBuffer == nullptr) {
        printf("共享内存映射视图失败\n");
        CloseHandle(sharedMemoryHandle);
        return 1;
    }
    memset(sharedBuffer, 0, sizeof(struct memoryBuffer)); // 清零共享内存
    UnmapViewOfFile(sharedBuffer); // 解除映射
    sharedBuffer = nullptr;

    // 进程信息数组
    PROCESS_INFORMATION processInfoArray[PRODUCER_MAX + CONSUMER_MAX] = {0};
    STARTUPINFO startupInfoArray[PRODUCER_MAX + CONSUMER_MAX] = {0};
    for (int i = 0; i < PRODUCER_MAX + CONSUMER_MAX; i++) {
        startupInfoArray[i].cb = sizeof(STARTUPINFO); // 设置启动信息结构体大小
    }

    TCHAR producerExecutableName[] = TEXT("producer.exe"); // 生产者可执行文件名
    TCHAR consumerExecutableName[] = TEXT("consumer.exe"); // 消费者可执行文件名

    // 创建生产者进程
    for (int i = 0; i < PRODUCER_MAX; i++) {
        operationResult = CreateProcess(nullptr, producerExecutableName,
                                        nullptr, nullptr, TRUE,
                                        NORMAL_PRIORITY_CLASS,
                                        nullptr, nullptr, &startupInfoArray[i], &processInfoArray[i]);
        if (!operationResult) // 失败
        {
            printf("无法创建生产者进程.\n");
            return 1;
        }
    }

    // 创建消费者进程
    for (int i = PRODUCER_MAX; i < PRODUCER_MAX + CONSUMER_MAX; i++) {
        operationResult = CreateProcess(nullptr, consumerExecutableName,
                                        nullptr, nullptr, TRUE,
                                        NORMAL_PRIORITY_CLASS,
                                        nullptr, nullptr, &startupInfoArray[i], &processInfoArray[i]);
        if (!operationResult) // 失败
        {
            printf("无法创建消费者进程.\n");
            return 1;
        }
    }

    HANDLE processHandles[PRODUCER_MAX + CONSUMER_MAX];
    DWORD exitCode;
    for (int i = 0; i < PRODUCER_MAX + CONSUMER_MAX; i++) {
        processHandles[i] = processInfoArray[i].hProcess; // 存储进程句柄
    }
    // 等待所有子进程结束
    WaitForMultipleObjects(PRODUCER_MAX + CONSUMER_MAX, processHandles, TRUE, INFINITE); // 等待所有进程结束
    printf("主进程退出!\n");
    for (int i = 0; i < PRODUCER_MAX + CONSUMER_MAX; i++) {
        if (processInfoArray[i].hProcess == 0)
            exit(-1);
        operationResult = GetExitCodeProcess(processInfoArray[i].hProcess, &exitCode); // 获取进程退出码
        CloseHandle(processInfoArray[i].hProcess); // 关闭进程句柄
        CloseHandle(processInfoArray[i].hThread); // 关闭线程句柄
    }
    CloseHandle(sharedMemoryHandle); // 关闭共享内存句柄
    return 0;
}
