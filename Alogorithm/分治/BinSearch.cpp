//折半查找要求数据有序
#include<iostream>
using namespace std;

int BinSearch(int a[],int tag,int low,int high)
{
    int mid = (low + high)/2;
    if(low <= high)//*****
    {
        if(a[mid] > tag)
            return BinSearch(a,tag,low,mid-1);
        else if(a[mid] < tag)
            return BinSearch(a,tag,mid+1,high);
        else 
            return mid;
    }
    else return -1;
    
        
}

int main()
{
    int n = 10;
    int tag = 99;//目标元素
    int a[] = {0,1,2,3,4,5,6,7,8,9};
    int i;//记录是否找到及下标
    i = BinSearch(a,tag,0,n-1);
    if(i >= 0)
    cout<<"a["<<i<<"] = "<<tag;
    else 
    cout<<"Not Found";
}