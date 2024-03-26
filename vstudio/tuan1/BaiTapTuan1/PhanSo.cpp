#include "PhanSo.h"
#include <iostream>


class PhanSo
{
public:
	int tu;
	int mau;

public:
	PhanSo(const int x = 1, const int y = 1) : tu(x), mau(y) {}
	~PhanSo()
	{
		delete this;
	}

	void Nhap()
	{
		std::cout << "nhap tu: "; std::cin >> this->tu;
		std::cout << "nhap mau: "; std::cin >> this->mau;
	}
	void Xuat() const
	{
		std::cout << this->tu << "/" << this->mau;
	}

	PhanSo rutGon()
	{
		int gcd = abs(tu);
		int temp = abs(mau);

		while (temp != 0)
		{
			int remainder = gcd % temp;
			gcd = temp;
			temp = remainder;
		}

		if (gcd != 0)
		{
			return PhanSo(tu /= gcd, mau /= gcd);
		}
		return PhanSo(tu, mau);
	}

	double getValue()
	{
		return (double)this->tu / this->mau;
	}

	PhanSo operator+(const PhanSo &ps) const
	{
		return PhanSo(tu * ps.mau + mau * ps.tu, mau * ps.mau);
	}
	PhanSo operator+=(const PhanSo &ps)
	{
		this->tu *= ps.mau;
		this->tu += mau * ps.tu;
		this->mau *= ps.mau;
	}

	PhanSo operator-(const PhanSo &ps) const
	{
		return PhanSo(tu * ps.mau - mau * ps.tu, mau * ps.mau);
	}
	PhanSo operator-=(const PhanSo &ps)
	{
		this->tu *= ps.mau;
		this->tu -= mau * ps.tu;
		this->mau *= ps.mau;
	}

	PhanSo operator*(const PhanSo &ps) const
	{
		return PhanSo(tu * ps.tu, mau * ps.mau);
	}
	PhanSo operator*=(const PhanSo &ps)
	{
		this->tu *= ps.tu;
		this->mau *= ps.mau;
	}

	PhanSo operator/(const PhanSo &ps) const
	{
		return PhanSo(tu * ps.mau, mau * ps.tu);
	}
	PhanSo operator/=(const PhanSo &ps)
	{
		this->tu *= ps.mau;
		this->mau *= ps.tu;
	}
};