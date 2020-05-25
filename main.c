#include<stdio.h>
#include<pthread.h>
#include<sort.h>
#define SIZE 100000

void testinit(int a[]);//生成数组
void prt(int a[]);//打印数组
void testresult(int a[]);//判断排序是否完成

int main()
{
    //test程序
    int raw[SIZE];
    testinit(raw);
    prt(raw);
    int out[SIZE];
    testresult(raw);
}

void testinit(int a[])
{
    for(int i = 1; i <= SIZE; ++i) a[i] = rand()%(SIZE+1);
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
    //printf("\n");
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