#include "TestCandidate.h"
#include "candidate.h"
#include <iostream>

class TestCandidate {
private:
    int size;
    candidate *dsts;

public:
    TestCandidate() {
        std::cin >> this->size;
        this->dsts = new candidate[size];
    }
    ~TestCandidate() {
        delete this;
    }

    void Nhap() {
        for (int i = 0; i < this->size; i++) {
            this->dsts[i].Nhap();
            std::cout << '\n';
        }
    }
    void Xuat() const {
        for (int i = 0; i < this->size; i++) {
            this->dsts[i].Xuat();
            std::cout << '\n';
        }
    }

    void inDSTT() {
        for (int i = 0; i < this->size; i++) {
            if (this->dsts[i].getScoreSum() > 15) {
                this->dsts[i].Xuat();
                std::cout << '\n';
            }
        }
    }
};
