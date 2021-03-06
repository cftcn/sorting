#ifndef _SORT_H_
#define _SORT_H_


#define SIZE 1000000000 //10^9
#define INITSIZE 1000000001

/*
#define SIZE 100000000 //10^8
#define INITSIZE 100000001
*/
/*
#define SIZE 90000000 //10^7
#define INITSIZE 90000001
*/
/*
#define SIZE 100
#define INITSIZE 101
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


void GetSystemInfo();
void MergeSort_SingleThread(int raw[], int result[]);
void QuickSort_SingleThread(int raw[], int result[]);
void MergeSort_MultiThread(int raw[], int result[]);
void QuickSort_MultiThread(int raw[], int result[]);
int min(int a, int b);
void Merge(int raw[], int begin, int middle, int end, int result[]);
void Copy(int des[], int ori[]);
void QuickSort(int result[], int lo, int hi);
int Partition(int result[], int lo, int hi);
void Merge_For_Multi(int a[],int low,int m,int high);
void *QuickSort_For_Multi(void *threadarg);
void *MergeSort(void *threadarg);

int partition(int a[],int left,int right);
void swap(int a[],int il, int ir);
void sort(int a[],int left,int right);

struct thread_data{
   int thread_id;
   int left;
   int right;
   int *a;
};

int ThreadNumber;
struct thread_data thread_data_array[16];

#endif