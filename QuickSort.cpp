#include<iostream>
#include<algorithm>
using namespace std;

int Partition(int a[],int first,int last)
{
    int i = first, j = last;
    int tmp = a[first];
    while(i != j)
    {
        while(j>i && a[j] >= tmp)
            j--;
        a[i] = a[j];
        while(j>i && a[i] <=tmp)
            i++;
        a[j] = a[i];
    }
    a[i] = tmp;
    return i;
}

void QuickSort(int a[],int first,int last)
{
    if(first < last)
    {
        int i = Partition(a,first,last);
        
        QuickSort(a,first,i-1);
        
        QuickSort(a,i+1,last);
        
    }
}
int main()
{
    int n = 10;//元素个数
    int a[10] = {1,9,2,3,4,5,11,8,6,10};
    QuickSort(a,0,n-1);
    for(int i =0;i < n;i++)
    cout<<a[i]<<" ";
}