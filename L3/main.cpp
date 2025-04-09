#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
void mergeSort (int* a, int p, int q, int *temp, int &n1);
void interclasare (int* a, int p, int q, int m, int *temp, int &n1);

void Print (int *a, int n);

void QuickSort1 (int* a, int p, int q, int &n2);
void QuickSort2 (int* a, int p, int q, int &n2);

void Partition (int* a, int p, int q, int &k, int &n2);
void mergeSort (int* a, int p, int q, int *temp, int &n2)
{
    if (p < q)
    {
        int m = (p + q) / 2;
        mergeSort (a, p, m, temp, n2);
        mergeSort (a, m + 1, q, temp, n2);
        interclasare (a, p, q, m, temp, n2);
        for (int i = p; i <= q; ++i)
            a[i] = temp [i - p];
    }
}
void interclasare (int* a, int p, int q, int m, int *temp, int &n2)
{
    int i = p;
    int j = m + 1;
    int k = -1;
    while ((i <= m) && (j <= q))
    {
        k = k + 1;
        if (a[i] <= a[j])
        {
            temp[k] = a[i];
            i++;
            n2++;
        }
        else
        {
            temp[k] = a[j];
            j++;
        }
    }
    while (i <= m)
    {
        k++;
        temp[k] = a[i];
        i++;
    }
    while (j <= q)
    {
        k++;
        temp[k] = a[j];
        j++;
    }
}

void Print (int *a, int n)
{
    cout << "\nVectorul este: ";
    for (int i = 0; i < n; ++i)
        cout << a[i] << ' ';
    cout << "\n";
}


void QuickSort1 (int* a, int p, int q, int &n)
{
    if (p < q)
    {   
        int k;
        Partition (a, p, q, k, n);
        QuickSort1 (a, p, k - 1, n);
        QuickSort1 (a, k + 1, q, n);
    }
}
void QuickSort2 (int* a, int p, int q, int &n)
{
    while (p < q)
    {
        int k;
        Partition (a, p, q, k, n);
        if (k - p > q - k)
        {
            QuickSort2 (a, k + 1, q, n);
            q = k - 1;
        }
        else
        {
            QuickSort2 (a, p, k - 1, n);
            p = k + 1;
        }
    }
}

void Partition (int* a, int p, int q, int &k, int &n)
{
    int x = a[p];
    int i = p + 1;
    int j = q;
    while (i <= j)
    {
        if (a[i] <= x)
            i++, n++;
        if (a[j] >= x)
            j--, n++;
        if (i < j)
        {
            if ((a[i] > x) && (x > a[j]))
                {
                    a[i] = a[i] ^ a[j];
                    a[j] = a[j] ^ a[i];
                    a[i] = a[i] ^ a[j];
                    i++;
                    j--;
                    n += 2;
                }
        }
    }
    k = i - 1;
    a[p] = a[k];
    a[k] = x;
}

int main()
{
    int* a, *b, *c, *temp;
    int n, n1 = 0, n2 = 0, n3 = 0;
    cout << "Enter vector size: ";
    cin >> n;
    a = new int[n];
    b = new int[n];
    c = new int[n];
    temp = new int[n];

    srand(time(NULL));
    cout << "Vectorul generat aleator: ";
    for (int i = 0; i < n; ++i) {
        a[i] = rand() % 100;
        b[i] = a[i];
        c[i] = a[i];
        cout << a[i] << " ";
    }
    cout << "\n";

    mergeSort (a, 0, n - 1, temp, n1);
    QuickSort1 (b, 0, n - 1, n2);
    QuickSort2 (c, 0, n - 1, n3);


    cout << "\nMergeSort:\n";
    Print (a, n);
    cout << "n = " << n1 << '\n';

    cout << "\nQuickSort1\n";
    Print (b, n);
    cout << "n = " << n2 << '\n';

    cout << "\nQuickSort2\n";
    Print (c, n);
    cout << "n = " << n3 << '\n';
    
    int test[10000], temp2[10000];
    for (int i = 0; i < 10000; i++)
        test[i] = i;

    n1 = 0;
    QuickSort1 (test, 0, 10000 - 1, n1);
    cout << "\nPentru cazul cu 10000 de elemente crescatoare ( QuickSort) \n";
    cout << "n = " << n1;
    cout << "\n";

    n1 = 0;
    mergeSort (test, 0, 10000 - 1, temp2, n1);
    cout << "Pentru cazul cu 10000 de elemente crescatoare ( MergeSort) \n";
    cout << "n = " << n1;
    cout << "\n";
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] temp;
    return 0;
}