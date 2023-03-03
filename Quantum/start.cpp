#include <iostream>
#include <string>
#include "task1.h"
#include "task2.h"
#include "task3.h"
using namespace std;

void task1() {
	string type;
	cin >> type;
	int n, m;
	cin >> n >> m;

	if (type == "vector") {
		float* v1 = read_vector(n);
		float* v2 = read_vector(m);
		float* res = tensor_vector(v1, n, v2, m);
		print_vector(res, n * m);
	}
	else if (type == "matrix") {
		float** m1 = read_matrix(n);
		float** m2 = read_matrix(m);
		float** res = tensor_matrix(m1, n, m2, m);
		print_matrix(res, n * m);
	}
}

void task2() {
	int k;
	cin >> k;
	string mask;
	cin >> mask;
	int n = int_pow(2, k);
	float* v = read_vector(n);
	float** m = read_matrix(n);
	float* res = product(m, v, n);
	print_vector(res, n);
	float* meas = measure(res, n, mask);
	int p = zeros(mask);
	for (int i = 0; i < p; i++) {
		n /= 2;
	}
	print_vector(meas, n);
}

void task3() {
	int k;
	cin >> k;
	int n = int_pow(2, k);
	int* f = new int[n];
	for (int i = 0; i < n; i++) { cin >> f[i]; }
	float* dg = deutsch_jozsa(k, f);
	int res = type(dg, n);
	cout << res << endl;
}


int main() {
	// task1();
	// task2();
	task3();
}