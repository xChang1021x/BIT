#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tchar.h>

// 2个生产者，每个生产者重复12次
#define PRODUCER_MAX 2
#define PRODUCER_REPETITIONS 12

// 3个消费者，每个消费者重复8次
#define CONSUMER_MAX 3
#define CONSUMER_REPETITIONS 8

// 缓冲区为6
#define BUFFER_LENGTH 11
#define BUFFER_COUNT 6

#define MEMORY_BUFFER_LEN (sizeof(struct memoryBuffer))

#define SHM_MODE 0600 // 可读可写
#define SEM_ALL_KEY 1234
#define SHM_ALL_KEY 1235
#define SEM_EMPTY 0
#define SEM_FULL 1
#define SEM_MUTEX 2

// 定义共享内存相关信息
const TCHAR sharedMemoryName[] = TEXT("PCFileMappingObject");
const TCHAR mutexName[] = TEXT("PCMutex");
const TCHAR emptySemaphoreName[] = TEXT("PCSemaphoreEmpty");
const TCHAR fullSemaphoreName[] = TEXT("PCSemaphoreFull");

// 共享缓冲区结构
struct memoryBuffer {
    char str[BUFFER_COUNT][BUFFER_LENGTH];
    int head = 0;
    int tail = 0;
};

// 随机生成一个字符串（生产者使用）
char* randomString(int length) {
    static char tempString[BUFFER_LENGTH];
    memset(tempString, 0, sizeof(tempString));
    for (int i = 0; i < length; i++)
        tempString[i] = (char)(rand() % 26 + 'A');
    return tempString;
}

// 生产者逻辑
void producer() {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, sharedMemoryName);
    struct memoryBuffer* pBuf = (struct memoryBuffer*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MEMORY_BUFFER_LEN);
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, mutexName);
    HANDLE hSemaphoreEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, emptySemaphoreName);
    HANDLE hSemaphoreFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, fullSemaphoreName);
    int SleepTime;

    for (int i = 0; i < PRODUCER_REPETITIONS; i++) {
        SleepTime = rand() % 1000;
        WaitForSingleObject(hSemaphoreEmpty, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        Sleep(SleepTime);
        strcpy_s(pBuf->str[pBuf->tail], BUFFER_LENGTH, randomString(10));
        pBuf->tail = (pBuf->tail + 1) % BUFFER_COUNT;
        printf("生产者: 推入 %-10s\n", pBuf->str[pBuf->tail]);
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphoreFull, 1, nullptr);
    }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    CloseHandle(hSemaphoreEmpty);
    CloseHandle(hSemaphoreFull);
    CloseHandle(hMutex);
}

// 消费者逻辑
void consumer() {
    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, sharedMemoryName);
    struct memoryBuffer* pBuf = (struct memoryBuffer*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MEMORY_BUFFER_LEN);
    HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, TRUE, mutexName);
    HANDLE hSemaphoreEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, emptySemaphoreName);
    HANDLE hSemaphoreFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, fullSemaphoreName);
    int SleepTime;

    for (int i = 0; i < CONSUMER_REPETITIONS; i++) {
        SleepTime = rand() % 1000;
        WaitForSingleObject(hSemaphoreFull, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        Sleep(SleepTime);
        printf("消费者: 弹出 %-10s\n", pBuf->str[pBuf->head]);
        memset(pBuf->str[pBuf->head], 0, BUFFER_LENGTH);
        pBuf->head = (pBuf->head + 1) % BUFFER_COUNT;
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphoreEmpty, 1, nullptr);
    }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    CloseHandle(hSemaphoreEmpty);
    CloseHandle(hSemaphoreFull);
    CloseHandle(hMutex);
}

// 主控制程序
int main() {
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, MEMORY_BUFFER_LEN, sharedMemoryName);
    HANDLE hMutex = CreateMutex(nullptr, FALSE, mutexName);
    HANDLE hSemaphoreEmpty = CreateSemaphore(nullptr, BUFFER_COUNT, BUFFER_COUNT, emptySemaphoreName);
    HANDLE hSemaphoreFull = CreateSemaphore(nullptr, 0, BUFFER_COUNT, fullSemaphoreName);
    struct memoryBuffer* pBuf = (struct memoryBuffer*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, MEMORY_BUFFER_LEN);
    memset(pBuf, 0, sizeof(struct memoryBuffer));
    UnmapViewOfFile(pBuf);

    PROCESS_INFORMATION processInfo[PRODUCER_MAX + CONSUMER_MAX] = {0};
    STARTUPINFO si[PRODUCER_MAX + CONSUMER_MAX] = {0};
    for (int i = 0; i < PRODUCER_MAX + CONSUMER_MAX; i++)
        si[i].cb = sizeof(STARTUPINFO);

    for (int i = 0; i < PRODUCER_MAX; i++) {
        CreateProcess(nullptr, TEXT("producer.exe"), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si[i], &processInfo[i]);
    }

    for (int i = PRODUCER_MAX; i < PRODUCER_MAX + CONSUMER_MAX; i++) {
        CreateProcess(nullptr, TEXT("consumer.exe"), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si[i], &processInfo[i]);
    }

    WaitForMultipleObjects(PRODUCER_MAX + CONSUMER_MAX, processInfo, TRUE, INFINITE);

    CloseHandle(hMapFile);
    CloseHandle(hMutex);
    CloseHandle(hSemaphoreEmpty);
    CloseHandle(hSemaphoreFull);

    printf("主进程退出!\n");
    return 0;
}
