#ifndef _SORT_H_
#define _SORT_H_

#include<stdio.h>
#include<pthread.h>

int * MergeSort_SingleThread(int raw[]);
int * QuickSort_SingleThread(int raw[]);
int * MergeSort_MultiThread(int raw[]);
int * QuickSort_MultiThread(int raw[]);

#endif