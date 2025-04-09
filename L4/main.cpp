#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void batcherSort (int *a, int i, int d, int s, int &cnt);

void afisareVector (int *a, int n);

void compara_si_schimba (int &x, int &y, int s, int &cnt){
    cnt += 2;
    if (s == 0)
    {
        if (x > y)
            swap (x, y);
    }
    else
        if (x < y)
            swap (x, y);
}


void sortare_secventa_bitona (int *a, int i, int d, int s, int &cnt){
    cnt++;
    if (d < 2) return;
    if (d == 2)
        compara_si_schimba (a[i], a[i + 1], s, cnt);
    else{
        for (int j = 0; j < d / 2; ++j)
            compara_si_schimba (a[i + j], a[i + j + d / 2], s, cnt);
        sortare_secventa_bitona (a, i, d / 2, s, cnt);
        sortare_secventa_bitona (a, i + d / 2, d / 2, s, cnt);
    }
}

void batcherSort (int *a, int i, int d, int s, int &cnt){
    cnt++;
    if (d < 2) return;
    if (d == 2)
    {
        compara_si_schimba(a[i], a[i + 1], s, cnt);
    }
    else{
        batcherSort (a, i, d / 2, 0, cnt);
        batcherSort (a, i + d / 2, d / 2, 1, cnt);
        sortare_secventa_bitona (a, i, d, s, cnt);
    }
}



void afisareVector (int *a, int n){
    cout << "--------------------\n";
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << "\n";
}
int main(){
    
    cout << "Intrduceti numarul: ";
    int n;
    cin >> n;
    int *a = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; ++i)
        a[i] = rand() % 100;
    
    int cnt = 0;
    batcherSort (a, 0, n, 0, cnt);

    afisareVector (a, n);
    cout << "Elemente distribuite aleator_cnt " << cnt << "\n";

    cnt = 0;
    batcherSort (a, 0, n, 0, cnt);
    cout << "Elemente sortate crescator_cnt: " << cnt << "\n";

    cnt = 0;
    batcherSort (a, 0, n, 1, cnt);
    cnt = 0;
    afisareVector (a, n);
    batcherSort (a, 0, n, 1, cnt);
    cout << "Elemente sortate descrescator_cnt: " << cnt << "\n";

    // int *b = new int[16325];
    // for (int i = 0; i < 16324; ++i)
    //     b[i] = i;
    
    // cnt = 0;
    // batcherSort (b, 0, 16324, 0, cnt);
    // cout << "\nCrescator, sortam crescator: " << cnt << '\n';

    return 0;
}