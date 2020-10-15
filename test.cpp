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
    int n;
    int tag = 99;//目标元素
    int m;
    int i;//记录是否找到及下标
    cin>>n;
    int a[n];
    for(int j =0;j < n;j++)
        cin>>a[j];
    cin>>m;
    int b[n];
    for(int j = 0;j < m;j++)
    cin>>b[j];
    for(int j = 0;j < m;j++)
    {
    i = BinSearch(a,b[j],0,n-1);
    if(i >= 0)
    cout<<"Yes"<<endl;
    else 
    cout<<"No"<<endl;
    i = 0;
    }
}