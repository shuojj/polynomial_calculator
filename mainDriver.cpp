#include "Polynomial.h"
#include <iostream>
#include <cmath>

using namespace std;

int main() {
	Monomial<int> m(9, 3);
	// a = 9x^3
	//a.print();

	// a = 9 * 5^3 = 
	Polynomial<int> a, b, c, d;
	Polynomial<double> p;
	int x;
	double y;

	cout << "Enter Polynomial: ";
	cin >> a;
	cout << "Polynomial entered a = ";
	a.print();
	cout << endl;

	cout << "Enter value of integer x: " << endl;
	cin >> x;
	cout << "Value of a = ";
	a.print();
	cout << " at x = " << x << " is: ";
	cout << a.evaluate(x) << endl;


	cout << "Enter Polynomial: ";
	cin >> p;
	cout << "Enter value of floating integer x: " << endl;
	cin >> y;
	cout << "Value of p = ";
	p.print();
	cout << " at x = " << y << " is: ";
	cout << p.evaluate(y) << endl;


	cout << "Enter Polynomial: ";
	cin >> b;
	cout << "Polynomial entered b = ";
	b.print();
	cout << endl;

	cout << "a + b = ";
	c = a + b;
	c.print();
	cout << endl;

	cout << "2a + b = ";
	c += a;
	c.print();
	cout << endl;

	cout << "a - b = ";
	c = a - b;
	c.print();
	cout << endl;

	cout << "a - 2b = ";
	c -= b;
	c.print();
	cout << endl;

	cout << "Polynomial a * Monomial m = 9x^3: ";
	c = a * m;
	c.print();
	cout << endl;

	cout << "a * b = ";
	c = a * b;
	c.print();
	cout << endl;

	m.assign_coefficient(2);
	m.assign_degree(0);
	c = a * m;
	c.print();
	cout << endl;
	d = a + a;
	d.print();
	cout << endl;
	if (c == d)
		cout << "2a is equal to a+a" << endl;
	return 0;
}
