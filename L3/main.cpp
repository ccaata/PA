#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;

void quickSort1(int a[], int p, int q);
void partitioneaza(int a[], int p, int q, int &k);
void mergeSort(int a[],int p, int q);
void interclasare(int a[], int p,int q, int m, int temp[]);

int main()
{
    int v[10000], p = 0, q = 10000;
    
    //  generez numerele random
    for(int i=p;i<=q;++i)
    {
        v[i] = rand() %10000;
    }
  
    // START TIMER
    auto start = std::chrono::high_resolution_clock::now();

    quickSort1(v,p,q);
    
    // STOP TIMER
    auto end = std::chrono::high_resolution_clock::now();    
    auto duration = (end - start);    
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)    
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration); // Milliseconds (as int)    
    const float ms_fractional = static_cast<float>(us.count()) / 1000;         // Milliseconds (as float)    
    std::cout << "Duration = " << us.count() << "µs (" << ms_fractional << "ms)" << std::endl<<std::endl;
    
    // cout<<" Vectorul sortat: ";
    // for(int i=p;i<=q;++i)
    //     cout<<v[i]<<" ";
    // cout<<endl<<endl;

    int v2[10000], p2 = 0, q2 = 10000;
    
    //  generez numerele random
    for(int i = p2; i <= q2; ++i)
    {
        v2[i] = rand() % 10000;
    }
  
    // START TIMER
    auto start2 = std::chrono::high_resolution_clock::now();

    mergeSort(v2, p2, q2);
    
    // STOP TIMER
    auto end2 = std::chrono::high_resolution_clock::now();    
    auto duration2 = (end2 - start2);    
    auto us2 = std::chrono::duration_cast<std::chrono::microseconds>(duration2); // Microsecond (as int)    
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(duration2); // Milliseconds (as int)    
    const float ms_fractional2 = static_cast<float>(us2.count()) / 1000;         // Milliseconds (as float)    
    std::cout << "Duration = " << us2.count() << "µs (" << ms_fractional2 << "ms)" << std::endl << std::endl;
    
    // cout << " Vectorul sortat: ";
    // for(int i = p2; i <= q2; ++i)
    //     cout << v2[i] << " ";
    // cout << endl << endl;

    return 0;
}

void quickSort1(int a[], int p, int q)
{
    if(p<q)
    {
        int k;
        partitioneaza(a,p,q,k);
        quickSort1(a,p,k-1);
        quickSort1(a,k+1,q);
    }
}

void partitioneaza(int a[], int p, int q, int &k)
{
    int x=a[p];
    int i=p+1;
    int j=q;

    while(i<=j)
    {
        if(a[i]<=x) ++i;
        if(a[j]>=x) --j;
        if(i<j)
        {
            if( (a[i]>x) && (x>a[j]) )
            {
                swap(a[i],a[j]);
                ++i;
                --j;
            }
        }
    }
    k=i-1;
    a[p]=a[k];
    a[k]=x;
}

void mergeSort(int a[],int p, int q)
{
    if(p<q)
    {
        int m = ceil((p+q)/2);
        mergeSort(a,p,m);
        mergeSort(a,m+1,q);
        int temp[10000]={0};
        interclasare(a,p,q,m,temp);
        for(int i=p;i<=q;++i)
        {
            a[i] = temp[i-p];
        }
    }
}

void interclasare(int a[], int p,int q, int m, int temp[])
{
    int i=p, j=m+1, k=-1;

    while((i<=m) && (j<=q))
    {
        k = k+1;
        if( a[i] <= a[j] )
        {
            temp[k] = a[i];
            ++i;
        }
        else
        {
            temp[k] = a[j];
            ++j;
        }
    }

    while(i<=m)
    {
        ++k;
        temp[k] = a[i];
        ++i;
    }
    while(j<=q)
    {
        ++k;
        temp[k] = a[j];
        ++j;
    }
}