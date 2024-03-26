#include "complex.h"
#include <iostream>

class complex
{
private:
	float r;
	float i;
public:
	complex(float _real = 0.0, float _im = 1.0) : r(_real), i(_im) {}
	~complex()
	{
		delete this;
	}

	void Nhap()
	{
		std::cout << "nhap phan thuc: "; std::cin >> this->r;
		std::cout << "nhap phan ao: "; std::cin >> this->i;
	}
	void Xuat() const
	{
		std::cout << this->r << " + " << this->i << "i";
	}

	const float getReal()
	{
		return this->r;
	}

	const float getIm()
	{
		return this->i;
	}

	complex operator+(const complex &c)
	{
		return complex(r + c.r, i + c.i);
	}

	complex operator-(const complex &c)
	{
		return complex(r - c.r, i - c.i);
	}

	complex operator*(const complex &c)
	{
		return complex(r * i - c.r * c.i, r * c.i + c.r * i);
	}

	complex operator/(const complex &c)
	{
		return complex((r * i + c.r * c.i) / (i * i + c.i * c.i), (c.r * i - r * c.i) / (i * i + c.i * c.i));
	}
};