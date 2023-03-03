#include <iostream>
#include <string>
using namespace std;

// Чтение вектора
float* read_vector(int n) {
	float* v = new float[n];
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	return v;
}

// Вывод вектора
void print_vector(float* v, int n) {
	for (int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
	cout << endl;
}

// Кронекеровское произведение векторов
float* tensor_vector(float* v1, int n, float* v2, int m) {
	float* res = new float[n * m];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			res[i * m + j] = v1[i] * v2[j];
		}
	}
	return res;
}

// Чтение матрицы
float** read_matrix(int n) {
	float** arr = new float* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new float[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
	return arr;
}

// Вывод матрицы
void print_matrix(float** m, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

// Кронекеровское произведение матриц
float** tensor_matrix(float** m1, int n, float** m2, int m) {
	int size = n * m;
	float** res = new float* [size];
	for (int i = 0; i < size; i++) {
		res[i] = new float[size];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < m; k++) {
				for (int l = 0; l < m; l++) {
					res[i * m + k][j * m + l] = m1[i][j] * m2[k][l];
				}
			}
		}
	}
	return res;
}