#include "dashboard.h"
#include <iostream>

using namespace std;

void showDashboard(const string& username, const json& userData, const json& userInfo) {
    int choice;
    bool isQuanLy = (userData.contains("Role") && userData["Role"] == "Quan_Ly"); //Kiem tra loai tai khoan

    do {
        cout << "\n===== DASHBOARD =====\n";
        if (userInfo.contains("FullName")) {
            cout << "Xin chao, " << userInfo["FullName"] << "!\n";
        } else {
            cout << "Xin chao, " << username << "!\n";
        }

        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Sua thong tin ca nhan\n";
        cout << "3. Doi mat khau\n";
        cout << "4. Dang xuat\n";
        if (isQuanLy) {
            cout << "\n5. Theo doi danh sach nguoi dung\n";
            cout << "6. Tao tai khoan nguoi dung\n";
            cout << "7. Thay doi thong tin nguoi dung\n";
        }
        cout << "Chon: ";

        if (!(cin >> choice)) {
            cout << "Loi: Vui long nhap so!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\n===== THONG TIN CA NHAN =====\n";
                cout << "Username: " << username << "\n";
                if (userData.contains("Role")) cout << "Loai tai khoan: " << userData["Role"].get<string>() << "\n";  
                if (userInfo.contains("FullName")) cout << "Ho va ten: " << userInfo["FullName"].get<string>() << "\n";
                if (userInfo.contains("Gender")) cout << "Gioi tinh: " << userInfo["Gender"].get<string>() << "\n";
                if (userInfo.contains("Email")) cout << "Email: " << userInfo["Email"].get<string>() << "\n";
                if (userInfo.contains("Phone")) cout << "So dien thoai: " << userInfo["Phone"].get<string>() << "\n";
                if (userInfo.contains("Address")) cout << "Dia chi: " << userInfo["Address"].get<string>() << "\n";
                cout << "=============================\n";             
                break;

            case 2:
                cout << "Chuc nang dang cap nhat...\n";
                break;

            case 3:
                cout << "Chuc nang dang cap nhat...\n";
                break;

            case 4:
                cout << "Dang xuat...\n";
                return;

            case 5:
                cout << "Chuc nang dang cap nhat...\n";
                break;
            
            case 6:
                cout << "Chuc nang dang cap nhat...\n";
                break;
            
            case 7:
                cout << "Chuc nang dang cap nhat...\n";
                break;

            default:
                cout << "Lua chon khong hop le, vui long thu lai!\n";
        }
    } while (true);
}
