#include<stdio.h>
#include<pthread.h>
#define SIZE 100000

void testinit(int a[]);//生成数组
void prt(int a[]);//打印数组
int main()
{
    //test程序
    int raw[SIZE];
    testinit(raw);
    prt(raw);
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
    printf("\n");
}