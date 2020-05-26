#include<stdio.h>
#include<pthread.h>
#include"sort.h"

void MergeSort_SingleThread(int raw[], int result[])
{
    for(int width = 1; width <= SIZE; width *= 2)
    {
        for(int i = 1; i <= SIZE; i += width * 2)
        {
            Merge(raw, i, min(i + width, SIZE), min(i + 2 * width, SIZE + 1), result);
        }
        Copy(raw, result);
    }
}
void QuickSort_SingleThread(int raw[], int result[])
{
    Copy(raw, result);
    QuickSort(result, 1, SIZE);
}
void MergeSort_MultiThread(int raw[], int result[]);
void QuickSort_MultiThread(int raw[], int result[]);

int min(int a, int b)
{
    if(a > b) return b;
    else return a;
}

void Merge(int raw[], int begin, int middle, int end, int result[])
{
    int p1 = begin, p2 = middle;
    for(int i = begin; i <= end; ++i)
    {
        if(p1 < middle && (p2 >= end || raw[p1] < raw[p2]))
        {
            result[i] = raw[p1];
            ++p1;
        }
        else
        {
            result[i] = raw[p2];
            ++p2;
        }
        
    }
}

void Copy(int des[], int ori[])
{
    for(int i = 1; i <= SIZE; ++i) des[i] = ori[i];
}
void QuickSort(int result[], int lo, int hi)
{
    int p = Partition(result, lo, hi);
    if(lo < hi)
    {
        QuickSort(result, lo, p);
        QuickSort(result, p + 1, hi);
    }
}

int Partition(int result[], int lo, int hi)
{
    int center = (lo + hi)/2;
    int pivot = result[center];
    int i = lo - 1;
    int j = hi + 1;
    while(1)
    {
        ++i;
        --j;
        while(result[i] < pivot) ++i;
        while(result[j] > pivot) --j;
        if(i >= j) return j;
        int temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}