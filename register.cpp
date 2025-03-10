#include "register.h"
#include "utils.h"
#include <regex> // kiem tra dinh dang

bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false; // Gioi han nam

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Kiem tra nam nhuan
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    // Kiem tra thang & ngay
    return (month >= 1 && month <= 12) && (day >= 1 && day <= daysInMonth[month]);
}

void registerUser() {
    string username, password, confirmPassword;
    json userData;

    // Ten dang nhap (username)
    do {
        cout << "Nhap ten dang nhap (bat buoc): ";
        cin >> username;

        // Bieu thuc chinh quy kiem tra ten dang nhap hop le
        regex usernamePattern("^[a-zA-Z0-9_.]{4,32}$");

        if (!regex_match(username, usernamePattern)) {
            cout << "❌ Ten dang nhap khong hop le! 4-32 ky tu, chi gom chu, so, dau . hoac _ .\n";
        } else {
            break; // Hop le thi thoat vong lap
        }

    } while (true);

    if (fs::exists("users/" + username + "/settings.json")) {
        cout << "❌ Tai khoan da ton tai! Dang ky that bai.\n";
        return;
    }

    // Nhap va xac nhan mat khau
    do {
        cout << "Nhap mat khau (6-64 ky tu): ";
        cin >> password;
        cout << "Nhap lai mat khau: ";
        cin >> confirmPassword;

        if (password != confirmPassword) {
            cout << "❌ Mat khau khong khop, vui long nhap lai!\n";
        } else if (password.length() < 6 || password.length() > 64) {
            cout << "❌ Mat khau phai tu 6-64 ky tu!\n";
        } else {
            break;
        }
    } while (true);

    string hashedPassword = hashPassword(password);

    // Luu thong tin dang nhap vao settings.json
    saveUserCredentials(username, hashedPassword);
    // XOA BO NHO DEM TRUOC KHI DUNG getline()
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    // Nhap thong tin ca nhan
    // Ho ten
    cout << "Nhap ho ten (khong bat buoc): ";
    string hoTen;
    do {
        getline(cin, hoTen);

        // Neu nguoi dung khong nhap gi (nhan Enter), cho phep bo qua
        if (hoTen.empty()) {
            break;
        }

        // Bieu thuc chinh quy kiem tra ho ten hop le
        regex hoTenPattern("^[A-Za-zÀ-Ỹà-ỹ\\s]{2,50}$");

        if (!regex_match(hoTen, hoTenPattern)) {
            cout << "❌ Ho ten khong hop le! Chi chua chu cai va dau cach, tu 2-50 ky tu.\n";
        } else {
            break; // Hop le thi thoat vong lap
        }

    } while (true);
    userData["HoTen"] = hoTen;

    // Gioi tinh
    int choice;
    string gioiTinh;
    do {
        cout << "Chon gioi tinh (khong bat buoc):\n";
        cout << "1. Nam\n";
        cout << "2. Nu\n";
        cout << "Chon (1/2 hoac Enter de bo qua): ";

        string input;
        getline(cin, input); // Doc ca dong de kiem tra nguoi dung co nhap khong

        if (input.empty()) { 
            gioiTinh = ""; // Cho phep bo qua
            break;
        }

        // Kiem tra neu input co dung 1 ky tu va la so 1 hoac 2
        if (input == "1") {
            gioiTinh = "Nam";
            break;
        } else if (input == "2") {
            gioiTinh = "Nu";
            break;
        } else {
            cout << "❌ Lua chon khong hop le! Vui long nhap 1, 2 hoac Enter de bo qua.\n";
        }

    } while (true);
    userData["GioiTinh"] = gioiTinh;

    // Dia chi
    cout << "Nhap dia chi (khong bat buoc): ";
    string diaChi;

    do {
        getline(cin, diaChi);
        
        if (diaChi.length() > 255) {
            cout << "❌ Dia chi khong hop le! Toi da 255 ky tu";
        } else {
            break; // Dia chi hop le, thoat vong lap
        }

    } while (true);
    userData["DiaChi"] = diaChi;

    // Dien thoai
    cout << "Nhap so dien thoai (khong bat buoc): ";
    string dienThoai;
    regex phonePattern("^[0-9]{0,16}$"); // Bieu thuc chinh quy chi cho phep so (tu 1 den 16 ky tu)
    do {
        getline(cin, dienThoai);

        if (!regex_match(dienThoai, phonePattern)) {
            cout << "❌ So dien thoai khong hop le! Chi chua so, toi da 16 ky tu ";
        } else {
            break; // Hop le thi thoat vong lap
        }

    } while (true);
    userData["DienThoai"] = dienThoai;

    // Email
    cout << "Nhap email (khong bat buoc): ";
    string email;
    regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)"); // Regex kiem tra email

    while (true) {
        getline(cin, email);

        // Neu nguoi dung bam Enter (khong nhap gi), cho phep bo qua
        if (email.empty()) {
            break;
        }

        // Kiem tra email hop le
        if (!regex_match(email, emailPattern)) {
            cout << "❌ Email khong hop le! Vui long nhap lai (vi du: example@gmail.com): ";
        } else {
            break; // Hop le thi thoat vong lap
        }
    }
    userData["Email"] = email;

    // Ngay sinh
    string ngaySinh;
    regex datePattern(R"(^\d{2}/\d{2}/\d{4}$)"); // Dinh dang dd//mm//yyyy
    do {
        cout << "Nhap ngay sinh (dd/mm/yyyy) (khong bat buoc): ";
        getline(cin, ngaySinh);

        // Neu nguoi dung bam Enter (khong nhap gi), cho phep bo qua
        if (ngaySinh.empty()) {
            break;
        }

        if (!regex_match(ngaySinh, datePattern)) {
            cout << "❌ Dinh dang ngay sinh khong hop le! Vui long nhap lai.\n";
            continue;
        }

        // Tach ngay, thang, nam
        int day, month, year;
        if (sscanf(ngaySinh.c_str(), "%d/%d/%d", &day, &month, &year) != 3) {
            cout << "❌ Dinh dang ngay sinh khong hop le! Vui long nhap lai.\n";
            continue;
        }

        // Kiem tra ngay hop le
        if (!isValidDate(day, month, year)) {
            cout << "❌ Ngay sinh khong hop le! Vui long nhap lai.\n";
        } else {
            break; // Thoat vong lap neu hop le
        }

    } while (true);
    userData["NgaySinh"] = ngaySinh;

    saveUserInfo(username, userData);
    cout << "Dang ky thanh cong!\n";
}