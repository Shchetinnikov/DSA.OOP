#pragma once

#include <iostream>

#include "Exception.h"
#include "Complex.h"

using namespace std;

struct Complex
{
	double re;
	double im;
public:
	Complex(const double re = 0, const double im = 0)
	{
		this->re = re;
		this->im = im;
	}
	Complex(const Complex& ob)
	{
		this->re = ob.re;
		this->im = ob.im;
	}
public:
	double AbsoluteValue() const
	{
		return sqrt(pow(this->re, 2) + pow(this->im, 2));
	}
public:
	friend Complex& operator+(const Complex& value1, const double& value2);
	friend Complex& operator+(const Complex& value1, const Complex& value2);
	friend Complex& operator-(const Complex& value1, const double& value2);
	friend Complex& operator-(const Complex& value1, const Complex& value2);
	friend Complex& operator*(const Complex& value1, const double& value2);
	friend Complex& operator*(const Complex& value1, const Complex& value2);
	friend Complex& operator/(const Complex& value1, const double& value2);
	friend Complex& operator/(const Complex& value1, const Complex& value2);
	Complex& operator++();
	Complex& operator++(int);
	Complex& operator--();
	Complex& operator--(int);
	Complex& operator=(const double& value2);
	Complex& operator=(const Complex& value2);
	friend bool operator==(const Complex& value1, const Complex& value2);
	friend bool operator!=(const Complex& value1, const Complex& value2);
	friend ostream& operator<<(ostream& out, const Complex& value);
	friend void operator>>(istream& in, const Complex& value);
};


Complex& operator+(const Complex& value1, const double& value2)
{
	Complex* temp = new Complex();
	temp->re = value1.re + value2;
	temp->im = value1.im;
	return *temp;
};


Complex& operator+(const Complex& value1, const Complex& value2)
{
	Complex* temp = new Complex();
	temp->re = value1.re + value2.re;
	temp->im = value1.im + value2.im;
	return *temp;
};


Complex& operator-(const Complex& value1, const double& value2)
{
	Complex* temp = new Complex();
	temp->re = value1.re - value2;
	temp->im = value1.im;
	return *temp;
};


Complex& operator-(const Complex& value1, const Complex& value2)
{
	Complex* temp = new Complex();
	temp->re = value1.re - value2.re;
	temp->im = value1.im - value2.im;
	return *temp;
};


Complex& operator*(const Complex& value1, const double& value2)
{
	Complex* temp = new Complex();
	temp->re = value1.re * value2;
	temp->im = value1.re * value2;
	return *temp;
};


Complex& operator*(const Complex& value1, const Complex& value2)
{
	Complex* temp = new Complex();
	temp->re = value1.re * value2.re - value1.im * value2.im;
	temp->im = value1.re * value2.im + value1.im * value2.re;
	return *temp;
};


Complex& operator/(const Complex& value1, const double& value2)
{
	if (!value2)
	{
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	Complex* temp = new Complex();
	temp->re = value1.re / value2;
	temp->im = value1.im / value2;
	return *temp;
};


Complex& operator/(const Complex& value1, const Complex& value2)
{
	if (!value2.re && !value2.im)
	{
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
	Complex* temp = new Complex();
	temp->re = (value1.re * value1.re + value2.im * value1.im) / (pow(value2.re, 2) + pow(value2.im, 2));
	temp->im = (value2.re * value2.im - value2.re * value2.im) / (pow(value2.re, 2) + pow(value2.im, 2));
	return *temp;
};


Complex& Complex::operator++() // префикс
{
	++this->re;
	return *this;
};


Complex& Complex::operator++(int) // постфикс
{
	this->re++;
	return *this;
};


Complex& Complex::operator--() // префикс
{
	--this->re;
	return *this;
};


Complex& Complex::operator--(int) // постфикс
{
	this->re--;
	return *this;
};


Complex& Complex::operator=(const double& value2)
{
	this->re = value2;
	this->im = 0;
	return *this;
}


Complex& Complex::operator=(const Complex& ob)
{
	this->re = ob.re;
	this->im = ob.im;
	return *this;
}


bool operator==(const Complex& value1, const Complex& value2)
{
	return (value1.re == value2.re) && (value1.im == value2.im);
};


bool operator!=(const Complex& value1, const Complex& value2)
{
	return !((value1.re == value2.re) && (value1.im == value2.im));
};



ostream& operator<<(ostream& out, const Complex& ob)
{
	out << "( " << ob.re << ", " << ob.im << " )";
	return out;
}


void operator>>(istream& in, Complex& ob)
{
	char flag;
	double data;
	in >> flag;
	if (flag == '(')
	{
		if (in.peek() == ')')
		{
			ob.re = 0;
			ob.im = 0;
		}
		else
		{
			while (in.peek() == ' ')
			{
				in.ignore(1);
			}
			if (in.peek() == ')')
			{
				ob.re = 0;
				ob.im = 0;
			}
			else
			{
				cin >> data;
				ob.re = data;
				while (in.peek() == ' ')
				{
					in.ignore(1);
				}
				if (in.peek() == ')')
				{
					ob.im = 0;
				}
				else
				{
					in >> data;
					ob.im = data;
					while (in.peek() == ' ')
					{
						in.ignore(1);
					}
					if (in.peek() != ')')
					{
						while (in.peek() != ')')
						{
							in.ignore(1);
						}
						in.ignore(1);
						throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
					}
				}
			}
		}
		in.ignore(1);
	}
	else
	{
		throw InvalidArguments("***InvalidArguments: invalid meanings of arguments***", __FILE__, __LINE__);
	}
}
