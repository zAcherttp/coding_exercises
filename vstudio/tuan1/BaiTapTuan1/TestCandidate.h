#pragma once
#include "candidate.h"
class TestCandidate
{
private:
	int size;
	candidate *dsts;
public:
	TestCandidate();
	~TestCandidate();

	void Nhap();
	void Xuat() const;

	void inDSTT();
};

