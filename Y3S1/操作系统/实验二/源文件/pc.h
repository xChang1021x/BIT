#ifndef INC_2_PC_H
#define INC_2_PC_H

#include <cstdio>
#include <windows.h>
#include <ctime>
#include <cstring>
#include <cstdlib>

#define BUFFER_LENGTH 11            //缓冲区长度
#define BUFFER_COUNT 6              //6个缓冲区
#define PRODUCER_COUNT 2            //2个生产者
#define PRODUCER_REPEAT 12     //生产者重复12次
#define CONSUMER_COUNT 3            //3个消费者
#define CONSUMER_REPEAT 8           //消费者重复8次

#define MEMORY_BUFFER_LEN (sizeof(struct BufferPool))

// 定义共享内存相关信息
const TCHAR sharedMemoryName[] = TEXT("PCFileMappingObject");
const TCHAR mutexName[] = TEXT("PCMutex");
const TCHAR emptySemaphoreName[] = TEXT("PCSemaphoreEmpty");
const TCHAR fullSemaphoreName[] = TEXT("PCSemaphoreFull");

// 缓冲区的结构
struct BufferPool {
    char str[BUFFER_COUNT][BUFFER_LENGTH];
    int head;
    int tail;
};

LARGE_INTEGER startTime, endTime;
LARGE_INTEGER frequency;
double runningTime;

#endif // INC_2_PC_H
