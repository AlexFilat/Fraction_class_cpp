#include <iostream>
using namespace std;

class Fraction {
private:
	int num, den;
public:
	Fraction() { set(0, 1); }
	Fraction(int n, int d) { set(n, d); }
	Fraction(int n) { set(n, 1); }
	Fraction(const Fraction& src);

	void set(int n, int d) { num = n; den = d; normalize(); }
	int get_num() const { return num; }
	int get_den() const { return den; }
	Fraction add(const Fraction& other);
	Fraction mult(const Fraction& other);
	Fraction operator+(const Fraction& other)
	{
		return add(other);
	}
	Fraction operator*(const Fraction& other) { return mult(other); }
	int operator==(const Fraction& other);
	friend ostream& operator<<(ostream& os, Fraction& fr);
private:
	void normalize();

	int gcf(int a, int b);
	int lcm(int a, int b);
};

int main() {
	Fraction f1(1, 2);
	Fraction f2(1, 3);

	Fraction f3 = f1 + f2 + 1;
	cout << "1/2 + 1/3 + 1 = " << f3 << endl;

	return 0;
}

Fraction::Fraction(const Fraction& src) {
	num = src.num;
	den = src.den;
}

void Fraction::normalize() {
	if (den == 0 || num == 0) {
		num = 0;
		den = 1;
	}

	if (den < 0) {
		num *= -1;
		den *= -1;
	}

	int n = gcf(num, den);
	num = num / n;
	den = den / n;
}

int Fraction::gcf(int a, int b) {
	if (a % b == 0)
		return abs(b);
	else
		return gcf(b, a % b);
}

int Fraction::lcm(int a, int b) {
	return (a / gcf(a, b)) * b;
}

Fraction Fraction::add(const Fraction& other) {
	Fraction fract;
	int lcd = lcm(den, other.den);
	int qout1 = lcd / den;
	int qout2 = lcd / other.den;
	fract.set(num * qout1 + other.num * qout2, lcd);
	fract.normalize();
	return fract;
}

Fraction Fraction::mult(const Fraction& other) {
	Fraction fract;
	fract.set(num * other.num, den * other.den);
	fract.normalize();
	return fract;
}

int Fraction::operator==(const Fraction& other) {
	return (num == other.num && den == other.den);
}

ostream& operator<<(ostream& os, Fraction& fr) {
	os << fr.num << "/" << fr.den;
	return os;
}

