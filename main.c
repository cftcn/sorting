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
    GetSystemInfo();
    //MergeSort_MultiThread
    clock_t start, finish;
    
    testinit(raworigin, raw);
    testinit(raworigin, result);

    struct timeval tv1,tv2;
    gettimeofday(&tv1,NULL);

    MergeSort_MultiThread(raw, result);

    gettimeofday(&tv2,NULL);
    int microseconds = (tv2.tv_sec - tv1.tv_sec) * 1000000 + ((int)tv2.tv_usec - (int)tv1.tv_usec);
    printf("MergeSort_MultiThread Time:%lf s\n", microseconds/1000000.0);

    testresult(raw);

    //MergeSort_SingleThread
    testinit(raworigin, result);
    testinit(raworigin, raw);
    
    struct timeval tv3,tv4;
    gettimeofday(&tv3,NULL);

    MergeSort_SingleThread(raw, result);
    
    gettimeofday(&tv4,NULL);
    microseconds = (tv4.tv_sec - tv3.tv_sec) * 1000000 + ((int)tv4.tv_usec - (int)tv3.tv_usec);
    printf("MergeSort_SingleThread Time:%lf s\n", microseconds/1000000.0);

    testresult(result);

    //QuickSort_SingleThread
    testinit(raworigin, result);
    testinit(raworigin, raw);
    
    struct timeval tv5,tv6;
    Copy(raw, result);
    gettimeofday(&tv5,NULL);

    MergeSort_SingleThread(raw, result);
    
    gettimeofday(&tv6,NULL);
    microseconds = (tv6.tv_sec - tv5.tv_sec) * 1000000 + ((int)tv6.tv_usec - (int)tv5.tv_usec);
    printf("QuickSort_SingleThread Time:%lf s\n", microseconds/1000000.0);

    testresult(result);

    //QuickSort_MultiThread
    testinit(raworigin, result);
    testinit(raworigin, raw);
    
    struct timeval tv7,tv8;
    gettimeofday(&tv7,NULL);

    MergeSort_SingleThread(raw, result);
    
    gettimeofday(&tv8,NULL);
    microseconds = (tv8.tv_sec - tv7.tv_sec) * 1000000 + ((int)tv8.tv_usec - (int)tv7.tv_usec);
    printf("QuickSort_MultiThread Time:%lf s\n", microseconds/1000000.0);

    testresult(result);
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