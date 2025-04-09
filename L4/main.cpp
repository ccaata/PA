#include <iostream>
#include <chrono>

using namespace std;

void BatcherSort(double a[], int i, int d, int s);
void ComparaSiSchimba(double &a, double &b, int s);
void SortareSecventaBitona(double a[], int i, int d, int s);
void AfisareVector(double a[], int d);

int main()
{
    double v[16384];

    //============================================================================================================================================================================
    //      CAZUL I - Elementele sunt sortate deja crescator
    for(int i=0; i<16384; ++i)
    {
        v[i] = i;
    }

    // TIMER START
    auto start = chrono::high_resolution_clock::now();   
    BatcherSort(v,0,16384,0);
    // TIMER STOP
    auto end = chrono::high_resolution_clock::now();    
    auto duration = (end - start);    
    auto us = chrono::duration_cast<chrono::microseconds>(duration); // Microsecond (as int)    
    auto ms = chrono::duration_cast<chrono::milliseconds>(duration); // Milliseconds (as int)    
    const float ms_fractional = static_cast<float>(us.count()) / 1000;         // Milliseconds (as float)    s
    cout << "\n Timpul pentru cazul Vectorului Sortat Crescator = " << us.count() << "µs (" << ms_fractional << "ms)" << endl;
   
       //============================================================================================================================================================================
    //      CAZUL II - Elementele sunt sortate descrescator
    //double x[16384];
    int n = 16384;
    for(int i=0; i<n; i++)
    {
        v[i] = n-i;
    }

    // TIMER START
    auto start1 = chrono::high_resolution_clock::now();   
    BatcherSort(v,0,16384,0);
    // TIMER STOP
    auto end1 = chrono::high_resolution_clock::now();    
    auto duration1 = (end1 - start1);    
    auto us1 = chrono::duration_cast<chrono::microseconds>(duration1); // Microsecond (as int)    
    auto ms1 = chrono::duration_cast<chrono::milliseconds>(duration1); // Milliseconds (as int)    
    const float ms_fractional1 = static_cast<float>(us1.count()) / 1000;         // Milliseconds (as float)    s
    cout << "\n Timpul pentru cazul Vectorului Sortat Desrescator = " << us1.count() << "µs (" << ms_fractional1 << "ms)" << endl;
    
    //============================================================================================================================================================================
    // CAZUL III - Elementele sunt generate random
    for(int i=0; i<n; i++)
    {
        v[i] = rand () % 16384;
    }

    // TIMER START
    auto start2 = chrono::high_resolution_clock::now();   
    BatcherSort(v,0,16384,0);
    // TIMER STOP
    auto end2 = chrono::high_resolution_clock::now();    
    auto duration2 = (end2 - start2);    
    auto us2 = chrono::duration_cast<chrono::microseconds>(duration2); // Microsecond (as int)    
    auto ms2 = chrono::duration_cast<chrono::milliseconds>(duration2); // Milliseconds (as int)    
    const float ms_fractional2 = static_cast<float>(us2.count()) / 1000;         // Milliseconds (as float)    s
    cout << "\n Timpul pentru cazul Vectorului Randomizat = " << us2.count() << "µs (" << ms_fractional2 << "ms)" << endl<<endl;
    return 0;
}


void BatcherSort(double a[], int i, int d, int s)
{
    if(d==2)
    {
        ComparaSiSchimba(a[i], a[i+1], s);
    }
    else
    {
        BatcherSort(a,i,d/2,0);
        BatcherSort(a,i+d/2,d/2,1);
        SortareSecventaBitona(a,i,d,s);
    }
}

void SortareSecventaBitona(double a[], int i, int d, int s)
{
    if(d==2)
    {
        ComparaSiSchimba(a[i],a[i+1],s);
    }
    else
    {
        for(int j=0; j<=(d/2)-1 ;++j)
        {
            ComparaSiSchimba(a[i+j],a[i+j+d/2],s);
        }
        SortareSecventaBitona(a,i,d/2,s);
        SortareSecventaBitona(a,i+d/2,d/2,s);
    }
}

void ComparaSiSchimba(double &a, double &b, int s)
{
    // avem sortare crescatoare
    if(s==0)
    {
        if(a>b)
        {
            swap(a,b);
        }
    }

    // avem sortare descrescatoare
    if(s==1)
    {
        if(a<b)
        {
            swap(a,b);
        }
    }
}

void AfisareVector(double a[], int d)
{
    for(int i=0;i<d;++i)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;

}