#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include"sort.h"

void GetSystemInfo()
{
    #ifdef __APPLE__
        ThreadNumber = sysconf(_SC_NPROCESSORS_CONF);
        printf("The number of threads available: %d\n", ThreadNumber);
        ThreadNumber = 8;
    #endif
}

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

void Merge_For_Multi(int raw[],int begin,int middle,int end)
{
	int p1 = begin, p2 = middle;
    int *temp = (int *)malloc(sizeof (int) * (end - begin + 1));
    for(int i = 0; i <= end - begin; ++i)
    {
        if(p1 < middle && (p2 >= end || raw[p1] < raw[p2]))
        {
            temp[i] = raw[p1];
            ++p1;
        }
        else
        {
            temp[i] = raw[p2];
            ++p2;
        }
    }
    for(int i = 0; i <= end - begin; ++i) raw[i + begin] = temp[i];
    free(temp);
}

void *MergeSort(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    int taskid = my_data->thread_id;
    int left = my_data->left, right = my_data->right;
    int *raw = my_data->a;
    //printf("this is thread %d\n", taskid);
    for(int width = 1; width <= (right - left); width *= 2)
    {
        for(int i = left; i <= right; i += width * 2)
        {
            Merge_For_Multi(raw, i, min(i + width, right), min(i + 2 * width, right + 1));
        }
    }
    //printf("thread %d complete\n", taskid);
    return NULL;
}

void MergeSort_MultiThread(int raw[], int result[])
{
    pthread_t threads[ThreadNumber];
    int rc;
    int part = SIZE/ThreadNumber;
    //prt(raw);
    for(int t = 0; t < ThreadNumber; t++)
    {
        //printf("In main: creating thread %ld\n", t);
        thread_data_array[t].thread_id = t;
        thread_data_array[t].left = part * t + 1;
        if(t != ThreadNumber - 1)thread_data_array[t].right = part * (t + 1);
        else thread_data_array[t].right = SIZE;
        thread_data_array[t].a = raw;
        rc = pthread_create(&threads[t], NULL, MergeSort, (void *) &thread_data_array[t]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    int number = ThreadNumber;
    for(int i = 0; i < number; i++) 
    {
        //printf("%d\n", i);
        pthread_join(threads[i], NULL);
    }
    //printf("%d\n", ThreadNumber); 不知道为什么ThreadNumber会为0
    /*
    for(int t = 0; t < number; ++t)
    {
        for(int i = part * t + 1; i <= part * (t + 1); ++i) printf("%4d", raw[i]);
        printf("\n");
    }
    for(int i = part * 8; i <= SIZE; ++i)printf("%4d", raw[i]);
    printf("\n\n");
    */
    for(int i = 1; i <= 4; ++i) 
    {
        if(i != 4)Merge_For_Multi(raw, part * (i - 1) * 2 + 1, part * (2 * i - 1) + 1, part * 2 * i + 1);
        else Merge_For_Multi(raw, part * (i - 1) * 2 + 1, part * (2 * i - 1) + 1, SIZE + 1);
    }
    Merge_For_Multi(raw, 1, part * 2 + 1, part * 4 + 1);
    Merge_For_Multi(raw, part * 4 + 1, part * 6 + 1, SIZE + 1);
    Merge_For_Multi(raw, 1, part * 4 + 1, SIZE + 1);
}

void QuickSort_MultiThread(int raw[], int result[])
{
    GetSystemInfo();
    pthread_t threads[ThreadNumber];
    int rc;
    int part = SIZE/ThreadNumber;
    for(int t = 0; t < ThreadNumber; t++)
    {
        thread_data_array[t].thread_id = t;
        thread_data_array[t].left = part * t + 1;
        if(t != ThreadNumber - 1)thread_data_array[t].right = part * (t + 1);
        else thread_data_array[t].right = SIZE;
        thread_data_array[t].a = raw;
        rc = pthread_create(&threads[t], NULL, QuickSort_For_Multi, (void *) &thread_data_array[t]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    int number = ThreadNumber;
    for(int i = 0; i < number; i++) pthread_join(threads[i], NULL);
    for(int i = 1; i <= 4; ++i) 
    {
        if(i != 4)Merge_For_Multi(raw, part * (i - 1) * 2 + 1, part * (2 * i - 1) + 1, part * 2 * i + 1);
        else Merge_For_Multi(raw, part * (i - 1) * 2 + 1, part * (2 * i - 1) + 1, SIZE + 1);
    }
    Merge_For_Multi(raw, 1, part * 2 + 1, part * 4 + 1);
    Merge_For_Multi(raw, part * 4 + 1, part * 6 + 1, SIZE + 1);
    Merge_For_Multi(raw, 1, part * 4 + 1, SIZE + 1);
}

void QuickSort_SingleThread(int raw[], int result[])
{
    QuickSort(result, 1, SIZE);
}

void *QuickSort_For_Multi(void *threadarg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    int taskid = my_data->thread_id;
    int left = my_data->left, right = my_data->right;
    int *raw = my_data->a;
    //QuickSort(raw, left, right);
    sort(raw, left, right);
    return NULL;
}

void swap(int a[],int il, int ir){
	int temp=a[il];
	a[il]=a[ir];
	a[ir]=temp;
}

int partition(int a[],int left,int right)
{
	int i;i=rand()%(right-left+1);i+=left;
	swap(a,i,left);
	int temp=a[left];
    while(left<right){
        while(left<right&&a[right]>=temp) right--;
        a[left]=a[right];
        while(left<right&&a[left]<=temp) left++;
        a[right]=a[left];
    }
    a[left]=temp;
    return left;
}

void sort(int a[],int left,int right){
	if(left>right){
		return;
	}
	int pivot=partition(a,left,right);
	sort(a,left,pivot-1);
	sort(a,pivot+1,right);
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