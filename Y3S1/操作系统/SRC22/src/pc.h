#ifndef INC_2_PC_H
#define INC_2_PC_H

#include <cstdio>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <cstdlib>

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

// 缓冲区的结构
struct memoryBuffer {
    char str[BUFFER_COUNT][BUFFER_LENGTH];
    // 6个缓冲区，每个缓冲区中存放一个十位以内的字符串
    int head;
    int tail;
};

LARGE_INTEGER startTime, endTime;
LARGE_INTEGER frequency;
double runningTime;

#endif // INC_2_PC_H
