#ifndef __POLYNOMIAL_CPP__
#define __POLYNOMIAL_CPP__
#include <iostream>
#include <cmath>
#include <list>
#include "Polynomial.h"

using namespace std;

template<typename NumberType>
const Polynomial <NumberType> & Polynomial<NumberType>::operator=(const Polynomial<NumberType> & rhs) {
	if ((*this) != rhs) {
		term_list = rhs.term_list;
		number_of_terms = rhs.number_of_terms;
		highest_degree = rhs.highest_degree;
	}
	return *this;
}

template<typename NumberType>
const Polynomial<NumberType> & Polynomial<NumberType>::operator=(const Monomial<NumberType> & rhs) {
	if (this != rhs) {
		term_list = rhs;
		number_of_terms = 1;
		highest_degree = rhs.degree;
	}
	return *this;
}

//start math funct
template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator+=(const Monomial<NumberType> &m) {
	insert_in_poly(*this, m);
	return *this;
}

template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator+=(const Polynomial<NumberType> & rhs) {
	Polynomial<NumberType> temp(*this);
	//temp = *this;
	for (typename list<Monomial<NumberType> >::const_iterator itr = rhs.term_list.begin();
		itr != rhs.term_list.end();
		itr++)
	{
		insert_in_poly(temp, *itr);
	}
	*this = temp;
	return *this;

}

template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator+ (const Monomial<NumberType> &m)const {
	return Polynomial(*this) += m;
}

template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator+ (const Polynomial<NumberType> & rhs) const {
	return Polynomial(*this) += rhs;
}

template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator-=(const Monomial<NumberType> &m) {
	Monomial<NumberType> m_temp;
	m_temp = m;
	m_temp.assign_coefficient(-(m->coefficient()));
	insert_in_poly(*this, m_temp);
	return *this;
}

template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator-=(const Polynomial<NumberType> & rhs) {

	Polynomial<NumberType> temp(*this);
	Monomial<NumberType> m_temp;
	for (typename list<Monomial<NumberType> >::const_iterator itr = rhs.term_list.begin();
		itr != rhs.term_list.end();
		itr++)
	{
		m_temp = *itr;
		m_temp.assign_coefficient(-(itr->coefficient()));
		insert_in_poly(temp, m_temp);
	}
	*this = temp;
	return *this;
}

template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator- (const Monomial<NumberType> &m)const {
	return Polynomial(*this) -= m;
}

template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator- (const Polynomial<NumberType> & rhs) const {
	Polynomial<NumberType> result(*this); //result goes 2 the stack
	result -= rhs;
	return result;
}

template<typename NumberType>
Polynomial<NumberType> Polynomial<NumberType>::operator*=(const Monomial<NumberType> &m) {

	Polynomial<NumberType> result;
	Monomial<NumberType> m_temp;
	int m_degree;
	NumberType m_coefficient;
	m_degree = m.degree();
	m_coefficient = m.coefficient();
	for (typename list<Monomial<NumberType> >::const_iterator itr = (*this).term_list.begin();
		itr != (*this).term_list.end();
		itr++)
	{
		m_temp.assign_coefficient((*itr).coefficient()*m_coefficient);
		m_temp.assign_degree((*itr).degree() + m_degree);
		insert_in_poly(result, m_temp);
	}
	*this = result;
	return *this;
}

template<typename NumberType> //poly with poly
Polynomial<NumberType> Polynomial<NumberType>::operator*=(const Polynomial<NumberType> & rhs) {


	Polynomial<NumberType> temp, result;
	for (typename list<Monomial<NumberType> >::const_iterator itr = rhs.term_list.begin();
		itr != rhs.term_list.end();
		itr++)
	{
		temp = (*this)*(*itr);
		result += temp;
	}
	*this = result;
	return *this;

}

template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator*(const Monomial<NumberType> &m) const {
	Polynomial<NumberType> result(*this);
	result *= m;
	return result;
}

template<typename NumberType>
const Polynomial<NumberType> Polynomial<NumberType>::operator*(const Polynomial<NumberType> &rhs)const {
	return Polynomial(*this) *= rhs;
}
//end math functs

//const NumberType evaluate(NumberType x) const;          //neeeds work
template<typename NumberType>
bool Polynomial<NumberType>::operator==(const Polynomial<NumberType> &p) const {
	bool flag = true;
	typename list<Monomial<NumberType> >::const_iterator itr1 = (*this).term_list.begin();
	for (typename list<Monomial<NumberType> >::const_iterator itr2 = p.term_list.begin();
		itr2 != p.term_list.end();
		itr1++, itr2++)
	{
		if (*itr1 != *itr2)
			flag = false;
	}
	return flag;
}

template<typename NumberType>
bool Polynomial<NumberType>::operator!=(const Polynomial<NumberType> &p) const {
	if ((*this) == p)
		return false;
	else
		return true;
}

template<typename NumberType>
void Polynomial<NumberType>::insert_in_poly(Polynomial<NumberType> & p, const Monomial<NumberType> & m) {

	Monomial<NumberType> small;
	int m_degree = m.degree();
	typename list<Monomial<NumberType> >::iterator itr = p.term_list.begin();
	for (;
		itr != p.term_list.end();
		itr++)
	{
		Monomial<NumberType> current_m = *itr;
		if (current_m.degree() <= m_degree)
			break;
		small = *itr;
	}
	if (itr != p.term_list.end() && (*itr).degree() == m_degree) {

		if (((*itr).coefficient() + m.coefficient()) == 0) {
			itr = p.term_list.erase(itr);
			p.number_of_terms--;
			if (p.number_of_terms == 0) {
				p.highest_degree = 0;
				p.term_list.push_back(Monomial<NumberType>(0, 0));
			}
			else {
				if (p.highest_degree == m_degree) {
					p.highest_degree = (*itr).degree();
				}
			}
		}
		else
			(*itr).assign_coefficient((*itr).coefficient() + m.coefficient());
	}
	else
		p.term_list.insert(itr, m);


}

template<typename NumberType>
const NumberType Polynomial<NumberType>::evaluate(NumberType x) const
{
	NumberType result = 0;
	for (typename list<Monomial<NumberType> >::const_iterator itr = (*this).term_list.begin();
		itr != (*this).term_list.end();
		itr++)
	{
		result += itr->coefficient() * power(x, itr->degree());

	}

	return result;
}

template <typename NumberType>
NumberType Polynomial<NumberType>::power(NumberType x, int n) const {
	NumberType result;
	result = 1.0;
	if (n == 0) {
		return result = 1;
	}
	for (int i = 1; i <= n; i++) {
		result = result*x;
	}
	return (result);
}


template<typename NumberType>
istream& operator >> (istream &in, Polynomial<NumberType>& rhs) {
	rhs.read(in);
	return in;

}
template<typename NumberType>
ostream& operator << (ostream &out, const Polynomial<NumberType> & rhs)
{
	rhs.print(out);
	return out;
}

template<typename NumberType> 
void Polynomial<NumberType>::read(istream & in) { //may be the problem
//cin>>c
//while (c != 0) {
//	cin >> d
//		construct a monomial(c, d)
//		insert monomial into polynomial
//		cin >> c
//}
	NumberType c;
	int d;
	Monomial<NumberType> m;
	in >> c;
	while (c!=0) {
		in >> d;
		if (d < 0) {
			cout << "Negative degree" << endl;
			exit(1);
		}
		Monomial<NumberType> m(c , d );
		this->insert_in_poly(*this, m);
		in >> c;
	}
	return;
}

template<typename NumberType>
void Polynomial<NumberType>::print(ostream & out) const { //needs work
	NumberType result;
	for (typename list<Monomial<NumberType> >::const_iterator itr = (*this).term_list.begin();
		itr != (*this).term_list.end();
		itr++)
	{
		if (itr == (*this).term_list.begin()) {
			if (itr->coefficient() == 0)
				out << 0;
			else
				out << itr->coefficient() << "x^" << itr->degree() << " ";
		}
		else if (itr->coefficient() > 0)
			out << "+" << itr->coefficient() << "x^" << itr->degree() << " ";
		else if (itr->coefficient() < 0)
			out << itr->coefficient() << "x^" << itr->degree() << " ";
	}
	return;
}




#endif
