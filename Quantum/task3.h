#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ������ ������������ n+1 �����
float** oracle(int* f, int n) {
	float** uf = new float*[n];
	for (int i = 0; i < n; i++) {
		uf[i] = new float[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			uf[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		int input = i >> 1;	// |x1x2...xny> => |x1x1...xn>
		int output = (i & 1) ^ f[input]; // y + f(x) - ����� ���������
		output = (input << 1) + output;  // |x1...xn0> + (y + f(x))
		uf[i][output] = 1;
	}
	return uf;
}

// �������� �������
float** H() {
	float** H = new float* [2];
	for (int i = 0; i < 2; i++) {
		H[i] = new float[2];
	}
	float sqrtwo = sqrt(2);
	H[0][0] = H[0][1] = H[1][0] = 1.0 / sqrtwo;
	H[1][1] = -H[0][0];
	return H;
}

// �������� ����� X
float** X() {
	float** X = new float* [2];
	for (int i = 0; i < 2; i++) {
		X[i] = new float[2];
	}
	X[0][0] = X[1][1] = 0.0;
	X[0][1] = X[1][0] = 1.0;
	return X;
}

// ��������� ��������
float** I() {
	float** I = new float* [2];
	for (int i = 0; i < 2; i++) {
		I[i] = new float[2];
	}
	I[0][0] = I[1][1] = 1.0;
	I[0][1] = I[1][0] = 0.0;
	return I;
}

// �������� ������� �� n �����
float** Hn(int n) {
	int k = 2;
	float** h = H();
	float** acc = H();
	for (int i = 1; i < n; i++) {
		acc = tensor_matrix(acc, k, h, 2);
		k *= 2;
	}
	return acc;
}

// ����� � ��������� |0>
float* zero() {
	float* q = new float[2];
	q[0] = 1;
	q[1] = 0;
	return q;
}

// ������� �������
float* q_reg(int n) {
	int k = 2;
	float* q = zero();
	float* reg = zero();
	for (int i = 1; i < n; i++) {
		reg = tensor_vector(reg, k, q, 2);
		k *= 2;
	}
	return reg;
}

// �������� �����-����
// n - ���-�� �����, f - ������� ������� �������
float* deutsch_jozsa(int n, int* f) {
	int k = int_pow(2, n);	// k - ����������� ������������

	float* qreg = q_reg(n);	// ������� �� n ����� � ��������� |0>
	float* q = zero();		// n+1-�� ����� ������ ���������� � ��������� |1>
	float** x = X();		// ��� ����� � ���� ����������� �������� ����� X
	q = product(x, q, 2);
	qreg = tensor_vector(qreg, k, q, 2);	// ������������ ������ ��������

	float** hn1 = Hn(n);	// ������������ ��������� �������, ������������ �� n �����
	float** hn2 = Hn(n);
	float** h = H();
	float** im = I();
	hn1 = tensor_matrix(hn1, k, h, 2); 
	hn2 = tensor_matrix(hn2, k, im, 2);

	float** orc = oracle(f, 2 * k);	// ������������ ������� �� ������ ������� �������
	// print_matrix(orc, 2 * k);

	// ���������� ����������
	qreg = product(hn1, qreg, k * 2);
	qreg = product(orc, qreg, k * 2);
	qreg = product(hn2, qreg, k * 2);

	// ���������
	string mask = "";
	for (int i = 0; i < n; i++) {
		mask += "1";
	}
	mask += "0";
	float* res = measure(qreg, k * 2, mask);

	return res;
}

// ����������� ���� �������
int type(float* res, int n) {
	float eps = 0.0001;
	// ����������� �������
	if (abs(abs(res[0]) - 1.0) < eps) {
		return 0;
	}
	else {
		for (int i = 0; i < n; i++) {
			// ������������ �������
			if ((abs(abs(res[0]) - 1.0) >= eps) && abs(res[0]) >= eps) {
				return -1;
			}
		}
	}
	// ���������������� �������
	return 1;
}