#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// ��������� ������������ ��������
float dot_product(float* v1, float* v2, int n) {
	float p = 0.0;
	for (int i = 0; i < n; i++) {
		p += v1[i] * v2[i];
	}
	return p;
}

// ��������� ������� �� ������
float* product(float** m, float* v, int n) {
	float* res = new float[n];
	for (int i = 0; i < n; i++) {
		res[i] = dot_product(m[i], v, n);
	}
	return res;
}

// ���������� � �������
int int_pow(int x, int n) {
	int p = 1;
	for (int i = 0; i < n; i++) {
		p *= x;
	}
	return p;
}

// �������� �� ��������� ��� ���������
bool correct(int mask, int number) {
	int res = mask & number;
	return res == number;
}

// ������� ��������� ���� � ����� �����
int bin_to_int(string mask) {
	int s = 0;
	int p = 1;
	for (int i = mask.size() - 1; i >= 0; i--) {
		int d = mask[i] - '0';
		s += d * p;
		p *= 2;
	}
	return s;
}

// ������� ���-�� �����
int zeros(string mask) {
	int p = 0;
	for (int i = 0; i < mask.size(); i++) {
		if (mask[i] == '0') { p++; }
	}
	return p;
}

// ����� �������
float length(float* v, int n) {
	float s = 0.0;
	for (int i = 0; i < n; i++) {
		s += v[i] * v[i];
	}
	s = sqrt(s);
	return s;
}

// ������������ �������
float* norm(float* v, int n) {
	float l = length(v, n);
	float* res = new float[n];
	for (int i = 0; i < n; i++) {
		res[i] = v[i] / l;
	}
	return res;
}

// �������� ���������
float* measure(float* v, int n, string mask) {
	int msk = bin_to_int(mask);
	int p = zeros(mask);
	int k = n;
	for (int i = 0; i < p; i++) {
		k /= 2;
	}
	float* res = new float[k];
	int l = 0;
	for (int i = 0; i < n; i++) {
		if (l == k) { break; }
		if (correct(msk, i)) {
			res[l] = v[i];
			l++;
		}
	}
	return norm(res, k);
}