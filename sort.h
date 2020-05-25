#ifndef _SORT_H_
#define _SORT_H_
#define SIZE 1000000000 //10^9
#define INITSIZE 1000000001
#include<stdio.h>
#include<pthread.h>

void MergeSort_SingleThread(int raw[], int result[]);
void QuickSort_SingleThread(int raw[], int result[]);
void MergeSort_MultiThread(int raw[], int result[]);
void QuickSort_MultiThread(int raw[], int result[]);
int min(int a, int b);
void Merge(int raw[], int begin, int middle, int end, int result[]);
void Copy(int des[], int ori[]);

#endif