// 1. Công ty ABC là công ty sản xuất kinh doanh thú nhồi bông.
//    Công ty có nhiều nhân viên làm việc trong ba bộ phận khác
//    nhau: bộ phận quản lý, bộ phận sản xuất, bộ phận văn phòng.
//    Việc tính lương cho nhân viên dựa vào các yếu tố sau:
//    Đối với nhân viên văn phòng: Lương = Lương Cơ Bản + Số ngày làm việc * 200.000 + Trợ Cấp
//    Đối với nhân viên sản xuất: Lương = Lương Cơ Bản + Số Sản Phẩm * 2.000
//    Đối với nhân viên quản lý: Lương = Lương Cơ Bản* Hệ số chức vụ + Thưởng.
//    Ngoài ra công ty cần quản lý các thông tin về nhân viên của mình
//    như: họ tên, ngày sinh và các thông số trên để tính lương cho
//    từng nhân viên trong công ty.
//
//    Thiết kế các lớp thích hợp để thực hiện các yêu cầu sau:
//
// ▪ Nhập thông tin của các nhân viên để phục vụ cho việc tính lương.
// ▪ Thực hiện việc tính lương cho từng nhân viên.
// ▪ Xuất thông tin của các nhân viên.
// ▪ Tính tổng lương của công ty.
// ▪ Tìm kiếm một nhân viên theo họ tên.

#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

enum sex {
    NAM = 1,
    NU = 0,
    UNKNOWN = -1
};

enum phong {
    VP = 0,
    SX = 1,
    QL = 2,
    EMPTY = -1
};

struct date {
    int ngay;
    int thang;
    int nam;
    date(int _d = 0, int _m = 0, int _y = 0) : ngay(_d), thang(_m), nam(_y){};
};

class NhanVien {
public:
    phong Phong;
    string MaNhanVien;
    string HoTen;
    sex GioiTinh;
    date NgaySinh;

    explicit NhanVien(phong _p = EMPTY, string _mcb = "", string _name = "", sex _s = UNKNOWN, date _bd = {})
        : Phong(_p), MaNhanVien(move(_mcb)), HoTen(move(_name)), GioiTinh(_s), NgaySinh(_bd) {}
    ~NhanVien() = default;

    virtual void xuatThongTin() const {}

    virtual void nhapThongTin(istream &is) {}

    virtual int tinhLuong(const int _luongCB) {
        return _luongCB;
    }

    friend istream &operator>>(istream &is, NhanVien &cb) {
        cb.nhapThongTin(is);
        return is;
    }
};

class VanPhong : public NhanVien {
public:
    int SoNgayLamViec;
    int TroCap;

    explicit VanPhong(int _wd = 0, int _sub = 0) : NhanVien(VP), SoNgayLamViec(_wd), TroCap(_sub) {}
    ~VanPhong() = default;

    int tinhLuong(int _luongCB) override {
        return (_luongCB + SoNgayLamViec * 200000 + TroCap);
    }

    void xuatThongTin() const override {
        string info = "Ho ten NVVP";
        cout << setw(18) << left << info.append((GioiTinh == NAM) ? (" Nam") : (" Nu")) << ": " << HoTen << '\n';
        cout << setw(18) << left << "Ngay Sinh" << ": " << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << '\n';
        cout << setw(18) << left << "Ma Nhan Vien" << ": " << MaNhanVien << '\n';
        cout << setw(18) << left << "So Ngay Lam Viec" << ": " << SoNgayLamViec << '\n';
        cout << setw(18) << left << "Tro Cap" << ": " << TroCap << '\n';
    }

    void nhapThongTin(istream &is) override {
        Phong = VP;

        cout << "Nhap ma nhan vien: ";
        is >> MaNhanVien;

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Nu\n";
        cout << "1. Nam\n";
        is >> option;
        while (0 > option || option > 1) {
            cout << "Lua chon khong hop le!\n";
            is >> option;
        }
        (option == 0) ? (GioiTinh = NU) : (GioiTinh = NAM);

        cout << "Nhap ho va ten: ";
        is.ignore();
        getline(is, HoTen);

        cout << "Nhap ngay sinh (ngay/thang/nam): ";
        is >> NgaySinh.ngay >> NgaySinh.thang >> NgaySinh.nam;

        cout << "Nhap so ngay lam viec: ";
        is >> SoNgayLamViec;

        cout << "Nhap tro cap: ";
        is >> TroCap;
    }
};

class SanXuat : public NhanVien {
public:
    int SoSanPham;

    explicit SanXuat(int _pn = 0) : NhanVien(QL), SoSanPham(_pn) {}
    ~SanXuat() = default;

    int tinhLuong(int _luongCB) override {
        return (_luongCB + SoSanPham * 2000);
    }

    void xuatThongTin() const override {
        string info = "Ho ten NVSX";
        cout << setw(18) << left << info.append((GioiTinh == NAM) ? (" Nam") : (" Nu")) << ": " << HoTen << '\n';
        cout << setw(18) << left << "Ngay Sinh" << ": " << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << '\n';
        cout << setw(18) << left << "Ma Nhan Vien" << ": " << MaNhanVien << '\n';
        cout << setw(18) << left << "So San Pham" << ": " << SoSanPham << '\n';
    }

    void nhapThongTin(istream &is) override {
        Phong = SX;

        cout << "Nhap ma nhan vien: ";
        is >> MaNhanVien;

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Nu\n";
        cout << "1. Nam\n";
        is >> option;
        while (0 > option || option > 1) {
            cout << "Lua chon khong hop le!\n";
            is >> option;
        }
        (option == 0) ? (GioiTinh = NU) : (GioiTinh = NAM);

        cout << "Nhap ho va ten: ";
        is.ignore();
        getline(is, HoTen);

        cout << "Nhap ngay sinh (ngay/thang/nam): ";
        is >> NgaySinh.ngay >> NgaySinh.thang >> NgaySinh.nam;

        cout << "Nhap so san pham: ";
        is >> SoSanPham;
    }
};

class QuanLy : public NhanVien {
public:
    int HeSoChucVu;
    int Thuong{};

    explicit QuanLy(int _pc = 0) : NhanVien(QL), HeSoChucVu(_pc) {}
    ~QuanLy() = default;

    int tinhLuong(int _luongCB) override {
        return (_luongCB * HeSoChucVu + Thuong);
    }

    void xuatThongTin() const override {
        string info = "Ho ten NVQL";
        cout << setw(18) << left << info.append((GioiTinh == NAM) ? (" Nam") : (" Nu")) << ": " << HoTen << '\n';
        cout << setw(18) << left << "Ngay Sinh" << ": " << NgaySinh.ngay << "/" << NgaySinh.thang << "/" << NgaySinh.nam << '\n';
        cout << setw(18) << left << "Ma Nhan Vien" << ": " << MaNhanVien << '\n';
        cout << setw(18) << left << "He So Chuc Vu" << ": " << HeSoChucVu << '\n';
        cout << setw(18) << left << "Thuong" << ": " << Thuong << '\n';
    }

    void nhapThongTin(istream &is) override {
        Phong = QL;

        cout << "Nhap ma nhan vien: ";
        is >> MaNhanVien;

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Nu\n";
        cout << "1. Nam\n";
        is >> option;
        while (0 > option || option > 1) {
            cout << "Lua chon khong hop le!\n";
            is >> option;
        }
        (option == 0) ? (GioiTinh = NU) : (GioiTinh = NAM);

        cout << "Nhap ho va ten: ";
        is.ignore();
        getline(is, HoTen);

        cout << "Nhap ngay sinh (ngay thang nam): ";
        is >> NgaySinh.ngay >> NgaySinh.thang >> NgaySinh.nam;

        cout << "Nhap he so chuc vu: ";
        is >> HeSoChucVu;

        cout << "Nhap thuong: ";
        is >> Thuong;
    }
};

class DSNhanVien {
public:
    int SoLuongNhanVien;
    vector<NhanVien *> DanhSach;

    explicit DSNhanVien(int _sl = 0, const vector<NhanVien *> &_ds = {}) : SoLuongNhanVien(_sl), DanhSach({}) {}
    ~DSNhanVien() = default;

    void xoaNhanVien(int _soThuTu) {
        if (_soThuTu >= 0 && _soThuTu < DanhSach.size()) {
            auto it = DanhSach.begin() + _soThuTu;
            DanhSach.erase(it);
        } else {
            cout << "so thu tu nam ngoai danh sach!\n";
        }

        SoLuongNhanVien--;
    }

    void xuatThongTinNhanVien(int _soThuTu) const {
        if (_soThuTu < 0 || DanhSach.size() <= _soThuTu) {
            cout << "so thu tu nam ngoai danh sach!\n";
        }
        DanhSach[_soThuTu]->xuatThongTin();
    }

    void themNhanVien() {

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Nhan Vien Van Phong\n";
        cout << "1. Nhan Vien San Xuat\n";
        cout << "2. Nhan Vien Quan Ly\n";

        cin >> option;
        while (0 > option || option > 2) {
            cout << "Lua chon khong hop le!\n";
            cin >> option;
        }

        switch (option) {
        case 0: {
            auto *mau = new VanPhong;
            cin >> *mau;
            DanhSach.push_back(mau);
            break;
        }
        case 1: {
            auto *mau = new SanXuat;
            cin >> *mau;
            DanhSach.push_back(mau);
            break;
        }
        case 2: {
            auto *mau = new QuanLy;
            cin >> *mau;
            DanhSach.push_back(mau);
            break;
        }

        default:
            break;
        }

        SoLuongNhanVien++;
    }

    void chinhSuaNhanVien() {
        int _stt;
        cout << "Nhap so thu tu nhan vien can chinh sua: ";
        cin >> _stt;
        while (_stt < 0 || DanhSach.size() <= _stt) {
            cout << "so thu tu nam ngoai danh sach!\n";
            cin >> _stt;
        }

        cin >> *DanhSach[_stt];
    }

    NhanVien *operator[](const int _index) {
        if (0 <= _index <= SoLuongNhanVien)
            return DanhSach[_index];
        cout << "index out of bound!\n";
        return nullptr;
    }
};

int main(int argc, char *argv[]) {
    int cau;
    cout << "chon cau: ";
    cin >> cau;
    switch (cau) {
    case 1: {
        DSNhanVien danhsach;

        int input = 1;
        while (input > 0) {
            cout << "[";
            for (int i{}; i < danhsach.SoLuongNhanVien - 1; i++) {
                cout << i << ", ";
            }
            if (danhsach.SoLuongNhanVien > 0)
                cout << danhsach.SoLuongNhanVien - 1;
            cout << "]\n";

            cout << "Chon chuc nang:\n";
            cout << "1  - Them nhan vien\n";
            cout << "2  - Xoa nhan vien\n";
            cout << "3  - Chinh sua nhan vien\n";
            cout << "4  - In tt mot nhan vien\n";
            cout << "5  - In danh sach tt nhan vien\n";
            cout << "6  - Tinh luong mot nhan vien\n";
            cout << "-1 - Exit\n";
            cin >> input;

            switch (input) {
            case 1: {
                danhsach.themNhanVien();
                break;
            }
            case 2: {
                int stt;
                cout << "Nhap so thu tu nhan vien can xoa: ";
                cin >> stt;
                while (stt < 0 || danhsach.SoLuongNhanVien <= stt) {
                    cout << "so thu tu nam ngoai danh sach!\n";
                    cin >> stt;
                }
                danhsach.xoaNhanVien(stt);
                break;
            }
            case 3: {
                danhsach.chinhSuaNhanVien();
                break;
            }
            case 4: {
                int stt;
                cout << "Nhap so thu tu nhan vien can in: ";
                cin >> stt;
                while (stt < 0 || danhsach.SoLuongNhanVien <= stt) {
                    cout << "so thu tu nam ngoai danh sach!\n";
                    cin >> stt;
                }
                danhsach.xuatThongTinNhanVien(stt);
                break;
            }
            case 5: {
                cout << "-----------------------------------------\n";
                for (int i{}; i < danhsach.SoLuongNhanVien; i++) {
                    danhsach.xuatThongTinNhanVien(i);
                    cout << "-----------------------------------------\n";
                }
                break;
            }
            case 6: {
                int stt;
                cout << "Nhap so thu tu nhan vien can tinh luong: ";
                cin >> stt;
                while (stt < 0 || danhsach.SoLuongNhanVien <= stt) {
                    cout << "so thu tu nam ngoai danh sach!\n";
                    cin >> stt;
                }
                int dongia;
                cout << "Nhap don gia: ";
                cin >> dongia;
                cout << "-----------------------------------------\n";
                danhsach.xuatThongTinNhanVien(stt);
                cout << "-----------------------------------------\n";
                cout << "Luong: " << fixed << setprecision(3) << danhsach[stt]->tinhLuong(dongia) << " VND\n";
                cout << "-----------------------------------------\n";
                break;
            }

            default:
                break;
            }
        }
        break;
    }

    default:
        break;
    }
}