#include<stdio.h>
#include<pthread.h>
#include<sort.h>

int * MergeSort_SingleThread(int raw[]);
int * QuickSort_SingleThread(int raw[]);
int * MergeSort_MultiThread(int raw[]);
int * QuickSort_MultiThread(int raw[]);