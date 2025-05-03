#include <iostream>
#include <omp.h>

using namespace std;

void bubble(int*, int);
void swap(int&, int&);

void bubble(int* a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;

        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int n;
    cout << "\nEnter total number of elements => ";
    cin >> n;

    int* a = new int[n];

    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bubble(a, n);

    cout << "\nSorted array is => ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a; // free memory
    return 0;
}
// OUTPUT 
//Enter total number of elements => 6

//Enter elements => 23 45 23 22 10 45

//Sorted array is => 10 22 23 23 45 45
