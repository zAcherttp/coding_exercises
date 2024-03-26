#pragma once
class PhanSo
{
public:
	int tu;
	int mau;

public:
	PhanSo(const int x, const int y);
	~PhanSo();

	void Nhap();
	void Xuat() const;
	PhanSo rutGon();

	double getValue();
};

