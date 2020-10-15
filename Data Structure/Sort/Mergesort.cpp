#include<iostream>
#include<malloc.h>
using namespace std;

void Merge(int a[],int low,int mid,int high)
{
    int *tmp;
    int i = low,j = mid + 1,k = 0;
    tmp = (int *)malloc((high - low + 1)*sizeof(int));
//分配临时储存两组数据的空间
    while(i <= mid && j <= high)
        if(a[i] <= a[j])
        {
            tmp[k] = a[i];
            i++,k++;
        }
        else
        {
            tmp[k] = a[j];
            j++,k++;
        }
//当两组数据都未扫描完时
    while(i <= mid)
    {
        tmp[k] = a[i];
        k++;i++;
    }
    while(j <= high)
    {
        tmp[k] = a[j];
        k++;j++;
    } 
//将未扫完的那一组数据排在末尾
    for(k = 0,i = low;i <= high;i++,k++)
    {
        a[i] = tmp[k];
    }   
//转入a[]
    free(tmp);
}

void MergeSort(int a[],int low,int high)
{
    int mid;
    if(low < high)
    {
        mid = (low + high)/2;
        MergeSort(a,low,mid);
        MergeSort(a,mid+1,high);
        Merge(a,low,mid,high);
    }
}//递归二路归并

int main()
{
    int n = 10;
    int a[] = {2,3,4,7,5,8,9,0,1,6};
    MergeSort(a,0,n);
    for(int i = 0;i < 10 ; i++)
    cout<<a[i]<<' ';
}