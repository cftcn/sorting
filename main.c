#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include"sort.h"

int raworigin[INITSIZE], raw[INITSIZE], result[INITSIZE];//因为过大需要放在外面

void testinit(int a[], int b[]);//生成数组
void prt(int a[]);//打印数组
void testresult(int a[]);//判断排序是否完成
void ismatch(int a[], int b[]);//判断两个数组是否相等

int main()
{
    clock_t start, finish;
    testinit(raworigin, raw);
    start = clock();
    MergeSort_SingleThread(raw, result);
    finish = clock();
    testresult(result);
    testinit(raworigin, result);
    printf("MergeSort_SingleThread Time: %f s\n", (double)(finish-start)/CLOCKS_PER_SEC);

    testinit(raworigin, raw);
    start = clock();
    QuickSort_SingleThread(raw, result);
    finish = clock();
    testresult(result);
    printf("QuickSort_SingleThread Time: %f s\n", (double)(finish-start)/CLOCKS_PER_SEC);
    
}

void testinit(int raworigin[], int raw[])
{
    if(raworigin[0] == 0) 
    {
        srand((unsigned)time(NULL)); //不同电脑之间对比时先删去
        for(int i = 1; i <= SIZE; ++i) raworigin[i] = raw[i] = rand()%(SIZE+1);
    }
    else 
    {
        for(int i = 1; i <= SIZE; ++i) raw[i] = raworigin[i];
    }
}

void prt(int a[])
{
    int count = 0;
    for(int i = 1; i <= SIZE; ++i)
    {
        printf("%10d ", a[i]);
        ++count;
        if(count == 10)
        {
            printf("\n");
            count = 0;
        }
    }
    for(int i = 1; i <= 110; ++i) printf("-");
    printf("\n");
}

void testresult(int a[])
{
    int flag = 0;
    for(int i = 1; i < SIZE; ++i)
    {
        if(a[i] > a[i+1])
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0) printf("Success!\n");
    else printf("Failed!\n");
}

void ismatch(int a[], int b[])
{
    int temp = 0;
    for(int i = 1; i <= SIZE; ++i)
    {
        if(a[i] != b[i])
        {
            temp = 1;
            break;
        }
    }
    if(temp == 0) printf("is match\n");
    else printf("isn't match \n");
}