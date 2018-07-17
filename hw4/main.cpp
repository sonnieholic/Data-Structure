#include<iostream>
#include<cstdio>
#include <time.h>
#include<algorithm>


using namespace std;


void Bubble_Sort(int a[],int n)
{
    for(int p=n-1;p>=0;p--)
    {
        int flag=0;
        for(int i=0;i<p;i++)//控制排序范围
        {
            if(a[i]>a[i+1]){swap(a[i],a[i+1]);flag=1;}
        }
        if(flag==0)break;//防止多余的工作
    }
}
void Print(int a[],int n)
{
    for(int s=0;s<n;s++)
    {
        printf("%d ",a[s]);
    }
    printf("\n");
}




void quickSort(int s[], int l, int r)
{
    if (l< r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j]>= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i]< x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1); // 递归调用
        quickSort(s, i + 1, r);
    }
}



int BinSearch1(int Array[],int SizeOfArray,int key)
{
    int low=0,high=SizeOfArray-1;
    int mid;
    while (low<=high)
    {
        mid = (low+high)/2;
        if(key==Array[mid])
            return mid;
        if(key<Array[mid])
            high=mid-1;
        if(key>Array[mid])
            low=mid+1;
    }
    return -1;
}
int BinSearch(int Array[],int low,int high,int key)
{
    if (low<=high)
    {
        int mid = (low+high)/2;
        if(key == Array[mid])
            return mid;
        else if(key<Array[mid])
            return BinSearch(Array,low,mid-1,key);
        else if(key>Array[mid])
            return BinSearch(Array,mid+1,high,key);
    }
    else
        return -1;
}


clock_t start_time1,end_time1;
double avertime1=0;
clock_t start_time2,end_time2;
double avertime2=0;
clock_t start_time3,end_time3;
double avertime3=0;
clock_t start_time4,end_time4;
double avertime4=0;
int main()
{
     int position,position1;
    freopen("ans1.txt","w",stdout);
    
        for(int n=40;n<=100;n=n+10)
        {
        int array1[n];
        int array2[n];
        for(int cnt=0;cnt<1000;cnt++)
        {
            for(int i=0; i<n; i++)
            {
                //array1[i]=rand();//随机
                //array1[i]=i;//正序
                array1[i]=n-i;//倒序
                array2[i]=array1[i];
            }
            start_time1=clock();
            Bubble_Sort(array1,n);
            end_time1=clock();
            avertime1=avertime1+(double)(end_time1 - start_time1)/ CLOCKS_PER_SEC*1000;
            int len=sizeof(array2)/sizeof(int);
            start_time2=clock();
            quickSort(array2,0,len-1);
            end_time2=clock();
            avertime2=avertime2+(double)(end_time2 - start_time2)/ CLOCKS_PER_SEC*1000;

            /*int random=rand()%array2[n-1];
            start_time3=clock();
            position=BinSearch(array2, 0, n-1, random);
            end_time3=clock();
            avertime3=avertime3+(double)(end_time3 - start_time3)/ CLOCKS_PER_SEC*1000;

            start_time4=clock();
            position1=BinSearch1(array2,n,random);
            end_time4=clock();
            avertime4=avertime4+(double)(end_time4 - start_time4)/ CLOCKS_PER_SEC*1000;*/


        }
         cout<<n<<" "<<avertime1/1000<<" "<<avertime2/1000<<endl;//<<" "<<avertime3/1000<<" "<<avertime4/1000<<endl;

        }
        for(int n=250;n<=2000;n=n+300)
        {
        int array1[n];
        int array2[n];
        for(int cnt=0;cnt<1000;cnt++)
        {
            for(int i=0; i<n; i++)
            {
                 //array1[i]=rand();
                //array1[i]=i;
                array1[i]=n-i;
                array2[i]=array1[i];
            }
            start_time1=clock();
            Bubble_Sort(array1,n);
            end_time1=clock();
            avertime1=avertime1+(double)(end_time1 - start_time1)/ CLOCKS_PER_SEC*1000;
            int len=sizeof(array2)/sizeof(int);
            start_time2=clock();
            quickSort(array2,0,len-1);
            end_time2=clock();
            avertime2=avertime2+(double)(end_time2 - start_time2)/ CLOCKS_PER_SEC*1000;

            /*int random=rand()%array2[n-1];
            start_time3=clock();
            position=BinSearch(array2, 0, n-1, random);
            end_time3=clock();
            avertime3=avertime3+(double)(end_time3 - start_time3)/ CLOCKS_PER_SEC*1000;

            start_time4=clock();
            position1=BinSearch1(array2,n,random);
            end_time4=clock();
            avertime4=avertime4+(double)(end_time4 - start_time4)/ CLOCKS_PER_SEC*1000;*/

        }
         cout<<n<<" "<<avertime1/1000<<" "<<avertime2/1000<<endl;//<<" "<<avertime3/1000<<" "<<avertime4/1000<<endl;


        }
         for(int n=2000;n<=4000;n=n+600)
        {
        int array1[n];
        int array2[n];
        for(int cnt=0;cnt<1000;cnt++)
        {
            for(int i=0; i<n; i++)
            {
                 //array1[i]=rand();
                //array1[i]=i;
                array1[i]=n-i;
                array2[i]=array1[i];
            }
            start_time1=clock();
            Bubble_Sort(array1,n);
            end_time1=clock();
            avertime1=avertime1+(double)(end_time1 - start_time1)/ CLOCKS_PER_SEC*1000;
            int len=sizeof(array2)/sizeof(int);
            start_time2=clock();
            quickSort(array2,0,len-1);
            end_time2=clock();
            avertime2=avertime2+(double)(end_time2 - start_time2)/ CLOCKS_PER_SEC*1000;

            /*int random=rand()%array2[n-1];
            start_time3=clock();
            position=BinSearch(array2, 0, n-1, random);
            end_time3=clock();
            avertime3=avertime3+(double)(end_time3 - start_time3)/ CLOCKS_PER_SEC*1000;

            start_time4=clock();
            position1=BinSearch1(array2,n,random);
            end_time4=clock();
            avertime4=avertime4+(double)(end_time4 - start_time4)/ CLOCKS_PER_SEC*1000;*/

        }
         cout<<n<<" "<<avertime1/1000<<" "<<avertime2/1000<<endl;//<<" "<<avertime3/1000<<" "<<avertime4/1000<<endl;

        }
        /*for(int n=6000;n<=10000;n=n+1500)
        {
        int array1[n];
        int array2[n];
        for(int cnt=0;cnt<1000;cnt++)
        {
            for(int i=0; i<n; i++)
            {
                 //array1[i]=rand();
                array1[i]=i;
                array2[i]=array1[i];
            }
            start_time1=clock();
            Bubble_Sort(array1,n);
            end_time1=clock();
            avertime1=avertime1+(double)(end_time1 - start_time1)/ CLOCKS_PER_SEC*1000;
            int len=sizeof(array2)/sizeof(int);
            start_time2=clock();
            quickSort(array2,0,len-1);
            end_time2=clock();
            avertime2=avertime2+(double)(end_time2 - start_time2)/ CLOCKS_PER_SEC*1000;*/
            /*int random=rand()%array2[n-1];
            start_time3=clock();
            position=BinSearch(array2, 0, n-1, random);
            end_time3=clock();
            avertime3=avertime3+(double)(end_time3 - start_time3)/ CLOCKS_PER_SEC*1000;

            start_time4=clock();
            position1=BinSearch1(array2,n,random);
            end_time4=clock();
            avertime4=avertime4+(double)(end_time4 - start_time4)/ CLOCKS_PER_SEC*1000;*/

       /* }
         cout<<n<<" "<<avertime1/1000<<" "<<avertime2/1000<<endl;//<<" "<<avertime3/1000<<" "<<avertime4/1000<<endl;
        }

        for(int n=12000;n<=30000;n=n+3000)
        {
        int array1[n];
        int array2[n];
        for(int cnt=0;cnt<1000;cnt++)
        {
            for(int i=0; i<n; i++)
            {
                 //array1[i]=rand();
                array1[i]=i;
                array2[i]=array1[i];
            }
            start_time1=clock();
            Bubble_Sort(array1,n);
            end_time1=clock();
            avertime1=avertime1+(double)(end_time1 - start_time1)/ CLOCKS_PER_SEC*1000;
            int len=sizeof(array2)/sizeof(int);
            start_time2=clock();
            quickSort(array2,0,len-1);
            end_time2=clock();
            avertime2=avertime2+(double)(end_time2 - start_time2)/ CLOCKS_PER_SEC*1000;*/
           /* int random=rand()%array2[n-1];
            start_time3=clock();
            position=BinSearch(array2, 0, n-1, random);
            end_time3=clock();
            avertime3=avertime3+(double)(end_time3 - start_time3)/ CLOCKS_PER_SEC*1000;

            start_time4=clock();
            position1=BinSearch1(array2,n,random);
            end_time4=clock();
            avertime4=avertime4+(double)(end_time4 - start_time4)/ CLOCKS_PER_SEC*1000;*/

        /*}
         cout<<n<<" "<<avertime1/1000<<" "<<avertime2/1000<<endl;//" "<<avertime3/1000<<" "<<avertime4/1000<<endl;

        }
        for(int n=30000;n<=90000;n=n+30000)
        {
        int array1[n];
        int array2[n];
        for(int cnt=0;cnt<1000;cnt++)
        {
            for(int i=0; i<n; i++)
            {
                 //array1[i]=rand();
                array1[i]=i;
                array2[i]=array1[i];
            }
            start_time1=clock();
            Bubble_Sort(array1,n);
            end_time1=clock();
            avertime1=avertime1+(double)(end_time1 - start_time1)/ CLOCKS_PER_SEC*1000;
            int len=sizeof(array2)/sizeof(int);
            start_time2=clock();
            quickSort(array2,0,len-1);
            end_time2=clock();
            avertime2=avertime2+(double)(end_time2 - start_time2)/ CLOCKS_PER_SEC*1000;*/
            /*int random=rand()%array2[n-1];
            start_time3=clock();
            position=BinSearch(array2, 0, n-1, random);
            end_time3=clock();
            avertime3=avertime3+(double)(end_time3 - start_time3)/ CLOCKS_PER_SEC*1000;

            start_time4=clock();
            position1=BinSearch1(array2,n,random);
            end_time4=clock();
            avertime4=avertime4+(double)(end_time4 - start_time4)/ CLOCKS_PER_SEC*1000;*/

        /*}
         cout<<n<<" "<<avertime1/1000<<" "<<avertime2/1000<<endl;//" "<<avertime3/1000<<" "<<avertime4/1000<<endl;

        }*/
    fclose(stdout);


}
