#include "rucsac.cpp"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int M, n;
    cout << "Introduceti capacitatea rucsacului (M): ";
    cin >> M;
    cout << "Introduceti numarul de obiecte (n): ";
    cin >> n;

    vector<int> w(n), p(n), x(n);
    cout << "Introduceti greutatile obiectelor: ";
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    cout << "Introduceti valorile obiectelor: ";
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    rucsac(M, n, w, p, x);

    cout << "Solutia optima este: \n";
    for (int i = 0; i < n; ++i) {
        cout << "Obiectul " << i + 1 << ": " << (x[i] ? "Ales" : "Neales") << "\n";
    }

    return 0;
}