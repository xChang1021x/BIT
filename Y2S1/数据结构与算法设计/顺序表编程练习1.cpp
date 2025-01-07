#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int ElemType;

typedef struct
{
    ElemType elem[LIST_INIT_SIZE]; 
    int length;
    int listsize;
    int incresize;
} SqList;

typedef int Status;

Status InitList_Sq(SqList *L)
{
    for (int i = 0; i < LIST_INIT_SIZE; i++) 
    {
        L->elem[i] = 0;
    }
    L->length = 0;
    L->listsize = LIST_INIT_SIZE;
    L->incresize = LISTINCREMENT;
    return OK;
}

Status ListInsert_Sq(SqList &L, int i, ElemType e) 
{
    if (i < 1 || i > L.length + 1)
        return ERROR;
    if (L.length >= L.listsize)
    {
        return ERROR;
    }
    int j;
    for (j = L.length - 1; j >= 0 && L.elem[j] > e; j--) 
    {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[j + 1] = e;
    L.length++;
    return OK;
}

int main()
{
    SqList L;
    InitList_Sq(&L);

    char input[100];
    fgets(input, 100, stdin);

    int numbers[100];
    int count = 0;
    char *token = strtok(input, ",");
    while (token != NULL)
    {
        numbers[count] = atoi(token);
        count++;
        token = strtok(NULL, ",");
    }
    for (int i = 0; i < count; i++)
    {
        ListInsert_Sq(L, i + 1, numbers[i]); 
    }

    int newElement;
    scanf("%d", &newElement);
    ListInsert_Sq(L, L.length + 1, newElement); 

    for (int i = 0; i < L.length; i++)
    {
        printf("%d", L.elem[i]);
        if (i != L.length - 1)
        {
            printf(",");
        }
    }
    printf("\n");

    return 0;
}
