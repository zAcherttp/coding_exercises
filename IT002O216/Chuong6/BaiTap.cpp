
//// check ✓

// 1. Xây dựng chương trình quản lý cán bộ viên chức
//    trường Đại học CNTT, giả sử trường gồm 2 loại
//    CBVC:
// ▪ Giảng Viên gồm các thông tin: mã cán bộ, họ tên, giới
//   tính, số giờ dạy, số giờ nghiên cứu
// ▪ Lương = (số giờ dạy + số giờ nghiên cứu ) * đơn giá
// ▪ Nhân viên hành chính: mã cán bộ, họ tên, giới tính, số
//   ngày làm việc, số giờ làm them.
// ▪ Lương = số ngày làm việc * tiền công 1 ngày + số giờ làm
//   thêm * đơn giá

// 2. Giả sử Trường ĐH CNTT TP.HCM đào tạo sinh viên theo 2 hệ là hệ cao đẳng và hệ
//    đại học. Thông tin cần quản lí của một sinh viên cao đẳng bao gồm: mã số sinh viên,
//    họ tên, địa chỉ, tổng số tín chỉ, điểm trung bình, điểm thi tốt nghiệp. Thông tin cần
//    quản lí của một sinh viên đại học bao gồm: mã số sinh viên, họ tên, địa chỉ, tổng số
//    tín chỉ, điểm trung bình, tên luận văn, điểm luận văn.
// Cách xét tốt nghiệp của sinh viên mỗi hệ là khác nhau:
// ▪ Sinh viên hệ cao đẳng tốt nghiệp khi có tổng số tín chỉ từ 120 trở lên, điểm trung bình từ 5
//   trở lên và điểm thi tốt nghiệp phải đạt từ 5 trở lên.
// ▪ Sinh viên hệ đại học tốt nghiệp khi có tổng số tín chỉ từ 170 trở lên, điểm trung bình từ 5
//   trở lên và phải bảo vệ luận văn với điểm số đạt được từ 5 điểm trở lên.
// Hãy viết chương trình bằng C++ cho phép thực hiện các yêu cầu sau:
// ▪ Nhập vào một sinh viên cao đẳng và một sinh viên đại học
// ▪ Cho biết sinh viên đủ điều kiện tốt nghiệp?
// ▪ Xuất thông tin 2 sinh viên trên

// 3. CT phần mềm Hoàn cầu 2 loại nhân viên. Các lập trình viên là những người sẽ viết
//    mã nguồn cho các ứng dụng. Các kiểm chứng viên có nhiệm vụ kiểm tra mã nguồn
//    và chương trình mà lập trình viên viết ra, để tìm các lỗi trước khi giao sản phẩm cho
//    khách hàng. Hiện tại, Công ty phần mềm Hoàn cầu lưu trữ các thông tin sau:
// ▪ Đối với lập trình viên: mã nhân viên, họ tên, tuổi, số điện thoại, email, lương cơ bản, số giờ overtime.
// ▪ Đối với kiểm chứng viên: mã nhân viên, họ tên, tuổi, số điện thoại, email, lương cơ bản, số lỗi phát hiện
//   được.
// Do tính chất công việc khác nhau, nên lương hàng tháng của lập trình viên và kiểm
// chứng viên cũng khác nhau. Cụ thể:
// ▪ Lương (lập trình viên) = lương cơ bản + số giờ làm thêm * 200.000
// ▪ Lương (kiểm chứng viên) = lương cơ bản + số lỗi * 50.000
// Bạn hãy đề xuất thiết kế các lớp đối tượng cần thiết để quản lý danh sách các nhân
// viên của Công ty và hỗ trợ tính lương cho nhân viên theo tiêu chí đặt ra như trên.
// Hãy viết chương trình bằng C++ cho phép thực hiện các yêu cầu sau:
// ▪ Nhập vào danh sách nhân viên
// ▪ Xuất danh sách nhân viên
// ▪ Liệt kê danh sách nhân viên có lương thấp hơn mức lương trung bình của các nhân viên trong công ty

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

/////////////////////////// cau 1.
enum sex
{
    NAM = 1,
    NU = 0,
    UNKNOWN = -1
};

enum phong
{
    GV = 0,
    HC = 1,
    EMPTY = -1,
};

class CanBo
{
public:
    phong Phong;
    string MaCanBo;
    string HoTen;
    sex GioiTinh;

    CanBo(phong _p = EMPTY, string _mcb = "", string _name = "", sex _s = UNKNOWN) : Phong(_p), MaCanBo(_mcb), HoTen(_name), GioiTinh(_s) {}
    ~CanBo() {}

    virtual void xuatThongTin() const
    {
        cout << setw(18) << left << "Ho ten:" << HoTen << '\n';
        cout << setw(18) << left << "Ma Can Bo:" << MaCanBo << '\n';
    }

    virtual void nhapThongTin(istream &is)
    {
        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Giang Vien\n";
        cout << "1. Nhan Vien Hanh Chinh\n";
        cin >> option;
        while (0 > option || option > 1)
        {
            cout << "Lua chon khong hop le!\n";
            cin >> option;
        }
        (option == 0) ? (Phong = GV) : (Phong = HC);

        cout << "Nhap ma can bo: ";
        cin >> MaCanBo;

        cout << "Chon de nhap:\n";
        cout << "0. Nu\n";
        cout << "1. Nam\n";
        cin >> option;
        while (0 > option || option > 1)
        {
            cout << "Lua chon khong hop le!\n";
            cin >> option;
        }
        (option == 0) ? (GioiTinh = NU) : (GioiTinh = NAM);

        cout << "Nhap ho va ten: ";
        cin.ignore();
        getline(cin, HoTen);
    }

    friend istream &operator>>(istream &is, CanBo &cb)
    {
        cb.nhapThongTin(is);
        return is;
    }
};

class GiangVien : public CanBo
{
public:
    int SoGioDay;
    int SoGioNghienCuu;

    GiangVien(int _th = 0, int _rh = 0) : CanBo(GV), SoGioDay(_th), SoGioNghienCuu(_rh) {}
    ~GiangVien() {}

    int tinhLuong(int _donGia)
    {
        return ((SoGioDay + SoGioNghienCuu) * _donGia);
    }

    void xuatThongTin() const
    {
        string info = "Ho ten GV";
        cout << setw(18) << left << info.append((GioiTinh == NAM) ? (" Nam") : (" Nu")) << ": " << HoTen << '\n';
        cout << setw(18) << left << "Ma Can Bo" << ": " << MaCanBo << '\n';
        cout << setw(18) << left << "So Gio Day" << ": " << SoGioDay << '\n';
        cout << setw(18) << left << "So Gio NC" << ": " << SoGioNghienCuu << '\n';
    }

    void nhapThongTin(istream &is) override
    {
        Phong = GV;

        cout << "Nhap ma can bo: ";
        cin >> MaCanBo;

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Nu\n";
        cout << "1. Nam\n";
        cin >> option;
        while (0 > option || option > 1)
        {
            cout << "Lua chon khong hop le!\n";
            cin >> option;
        }
        (option == 0) ? (GioiTinh = NU) : (GioiTinh = NAM);

        cout << "Nhap ho va ten: ";
        cin.ignore();
        getline(cin, HoTen);

        cout << "Nhap so gio day: ";
        cin >> SoGioDay;

        cout << "Nhap so gio nghien cuu: ";
        cin >> SoGioNghienCuu;
    }
};

class NVHanhChinh : public CanBo
{
public:
    int SoNgayLamViec;
    int SoGioLamThem;

    NVHanhChinh(int _th = 0, int _rh = 0) : CanBo(HC), SoNgayLamViec(_th), SoGioLamThem(_rh) {}
    ~NVHanhChinh() {}

    int tinhLuong(int _donGia, int _tienCongMotNgay)
    {
        return (SoNgayLamViec * _tienCongMotNgay + SoGioLamThem * _donGia);
    }

    void xuatThongTin() const
    {
        string info = "Ho ten NVHC";
        cout << setw(18) << left << info.append((GioiTinh == NAM) ? (" Nam") : (" Nu")) << ": " << HoTen << '\n';
        cout << setw(18) << left << "Ma Can Bo" << ": " << MaCanBo << '\n';
        cout << setw(18) << left << "So Gio Lam Them" << ": " << SoGioLamThem << '\n';
        cout << setw(18) << left << "So Ngay Lam Viec" << ": " << SoNgayLamViec << '\n';
    }

    void nhapThongTin(istream &is) override
    {
        Phong = HC;

        cout << "Nhap ma can bo: ";
        cin >> MaCanBo;

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Nu\n";
        cout << "1. Nam\n";
        cin >> option;
        while (0 > option || option > 1)
        {
            cout << "Lua chon khong hop le!\n";
            cin >> option;
        }
        (option == 0) ? (GioiTinh = NU) : (GioiTinh = NAM);

        cout << "Nhap ho va ten: ";
        cin.ignore();
        getline(cin, HoTen);

        cout << "Nhap so ngay lam viec: ";
        cin >> SoNgayLamViec;

        cout << "Nhap so lam them: ";
        cin >> SoGioLamThem;
    }
};

class DSCanBo
{
public:
    int SoLuongCanBo;
    vector<CanBo *> DanhSach;

    DSCanBo(int _sl = 0, vector<CanBo *> _ds = {}) : SoLuongCanBo(_sl), DanhSach({}) {}
    ~DSCanBo() {}

    void xoaCanBo(int _soThuTu)
    {
        if (_soThuTu >= 0 && _soThuTu < DanhSach.size())
        {
            auto it = DanhSach.begin() + _soThuTu;
            DanhSach.erase(it);
        }
        else
        {
            cout << "so thu tu nam ngoai danh sach!\n";
        }

        SoLuongCanBo--;
    }

    void xuatThongTinCanBo(int _soThuTu) const
    {
        if (_soThuTu < 0 || DanhSach.size() <= _soThuTu)
        {
            cout << "so thu tu nam ngoai danh sach!\n";
        }
        DanhSach[_soThuTu]->xuatThongTin();
    }

    void themCanBo()
    {

        int option;
        cout << "Chon de nhap:\n";
        cout << "0. Giang Vien\n";
        cout << "1. Nhan Vien Hanh Chinh\n";

        cin >> option;
        while (0 > option || option > 1)
        {
            cout << "Lua chon khong hop le!\n";
            cin >> option;
        }

        switch (option)
        {
        case 0:
        {
            GiangVien *mau = new GiangVien;
            cin >> *mau;
            DanhSach.push_back(mau);
            break;
        }

        case 1:
        {
            NVHanhChinh *mau = new NVHanhChinh;
            cin >> *mau;
            DanhSach.push_back(mau);
            break;
        }

        default:
            break;
        }

        SoLuongCanBo++;
    }

    void chinhSuaCanBo()
    {
        int _stt;
        cout << "Nhap so thu tu can bo can chinh sua: ";
        cin >> _stt;
        while (_stt < 0 || DanhSach.size() <= _stt)
        {
            cout << "so thu tu nam ngoai danh sach!\n";
            cin >> _stt;
        }

        switch (DanhSach[_stt]->Phong)
        {
        case GV:
        {
            cout << "Nhap ma can bo: ";
            cin >> DanhSach[_stt]->MaCanBo;

            int option;
            cout << "Chon de sua:\n";
            cout << "0. Nu\n";
            cout << "1. Nam\n";
            cin >> option;
            while (0 > option || option > 1)
            {
                cout << "Lua chon khong hop le!\n";
                cin >> option;
            }
            (option == 0) ? (DanhSach[_stt]->GioiTinh = NU) : (DanhSach[_stt]->GioiTinh = NAM);

            cout << "Nhap ho va ten: ";
            cin.ignore();
            getline(cin, DanhSach[_stt]->HoTen);

            cout << "Nhap so gio day: ";
            cin >> static_cast<GiangVien *>(DanhSach[_stt])->SoGioDay;

            cout << "Nhap so gio nghien cuu: ";
            cin >> static_cast<GiangVien *>(DanhSach[_stt])->SoGioNghienCuu;
        }
        break;

        case HC:
        {
            cout << "Nhap ma can bo: ";
            cin >> DanhSach[_stt]->MaCanBo;

            int option;
            cout << "Chon de sua:\n";
            cout << "0. Nu\n";
            cout << "1. Nam\n";
            cin >> option;
            while (0 > option || option > 1)
            {
                cout << "Lua chon khong hop le!\n";
                cin >> option;
            }
            (option == 0) ? (DanhSach[_stt]->GioiTinh = NU) : (DanhSach[_stt]->GioiTinh = NAM);

            cout << "Nhap ho va ten: ";
            cin.ignore();
            getline(cin, DanhSach[_stt]->HoTen);

            cout << "Nhap so ngay lam viec: ";
            cin >> static_cast<NVHanhChinh *>(DanhSach[_stt])->SoNgayLamViec;

            cout << "Nhap so gio lam them: ";
            cin >> static_cast<NVHanhChinh *>(DanhSach[_stt])->SoGioLamThem;
        }
        break;

        default:
            break;
        }
    }
};

int main(int argc, char *argv[])
{
    int i{};
    cout << "chon cau: ";
    cin >> i;
    switch (i)
    {
    case 1:
    {
        DSCanBo danhsach;

        int input = 1;
        while (input > 0)
        {
            cout << "[";
            for (int i{}; i < danhsach.SoLuongCanBo - 1; i++)
            {
                cout << i << ", ";
            }
            if (danhsach.SoLuongCanBo > 0)
                cout << danhsach.SoLuongCanBo - 1;
            cout << "]\n";

            cout << "Chon chuc nang:\n";
            cout << "1  - Them can bo\n";
            cout << "2  - Xoa can bo\n";
            cout << "3  - Chinh sua can bo\n";
            cout << "4  - In tt mot can bo\n";
            cout << "5  - In danh sach tt can bo\n";
            cout << "-1 - Exit\n";
            cin >> input;

            switch (input)
            {
            case 1:
            {
                danhsach.themCanBo();
            }
            break;
            case 2:
            {
                int stt;
                cout << "Nhap so thu tu can bo can xoa: ";
                cin >> stt;
                while (stt < 0 || danhsach.SoLuongCanBo <= stt)
                {
                    cout << "so thu tu nam ngoai danh sach!\n";
                    cin >> stt;
                }
                danhsach.xoaCanBo(stt);
            }
            break;
            case 3:
            {
                danhsach.chinhSuaCanBo();
            }
            break;
            case 4:
            {
                int stt;
                cout << "Nhap so thu tu can bo can in: ";
                cin >> stt;
                while (stt < 0 || danhsach.SoLuongCanBo <= stt)
                {
                    cout << "so thu tu nam ngoai danh sach!\n";
                    cin >> stt;
                }
                danhsach.xuatThongTinCanBo(stt);
            }
            break;
            case 5:
            {
                for (int i{}; i < danhsach.SoLuongCanBo; i++)
                {
                    danhsach.xuatThongTinCanBo(i);
                    cout << "-----------------------------------------\n";
                }
            }
            break;

            default:
                break;
            }
        }
    }
    break;
    case 2:
        break;
    case 3:
        break;

    default:
        break;
    }
}