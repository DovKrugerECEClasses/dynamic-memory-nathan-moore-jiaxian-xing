#include <string>
#include <iostream>
using namespace std;

template<typename T>
void sort(T x[], int l){
    for (int j = l-1; j > 0; j--)
        for(int i = 0; i < j; i++)
            if (x[i] > x[i+1]) swap(x[i], x[i+1]);
}

template<typename T>
void print(T x[], int l){
    for(int i=0; i <l; i++) cout << x[i];
    cout << "\r\n";
}

template<typename T>
T sum(T x[], int l){
    T s;
    for(int i =0; i < l; i++){
        s = s + x[i];
    }
    return s;
}

int main() {
	int a[] = {5, 4, 3, 1, 7, 8, 9, 2, 1};
	sort(a, sizeof(a)/sizeof(int));
	print(a, sizeof(a)/sizeof(int));
	
	double b[] = {5.5, 4.5, 1.2, 2.9, 9.2, 5.2};
	sort(b, sizeof(b)/sizeof(double));
	print(b, sizeof(b)/sizeof(double));

	cout << sum(a, sizeof(a)/sizeof(int)) << '\n';
	cout << sum(b, sizeof(b)/sizeof(double)) << '\n';

	string c[] = {"yo", "ho", "test", "foo", "bar"};
	sort(c, sizeof(c)/sizeof(string));
	print(c, sizeof(c)/sizeof(string));
	cout << sum(c, sizeof(c)/sizeof(string)) << '\n';
}
