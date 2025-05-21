#include "dashboard.h"
#include "backup.h"
#include "changepassword.h"
#include <iostream>
#include "manager.h"
#include "edit_user_info.h"
#include "wallet_manager.h"
#include <iomanip>

using namespace std;

void showDashboard(const string& username, json& userData, const json& userInfo) {
    int choice;
    bool isQuanLy = (userData.contains("Role") && userData["Role"] == "Quan_Ly");

    do {
        cout << "\n===== DASHBOARD =====\n";
        if (userInfo.contains("FullName")) {
            cout << "Xin chao, " << userInfo["FullName"] << "!\n";
        } else {
            cout << "Xin chao, " << username << "!\n";
        }

        if (isQuanLy) {
            checkAndBackup();
        }

        cout << "1. Xem thong tin ca nhan\n";
        cout << "2. Sua thong tin ca nhan\n";
        cout << "3. Doi mat khau\n";
        cout << "4. Quan ly vi dien tu\n";
        cout << "5. Dang xuat\n";
        if (isQuanLy) {
            cout << "\n6. Theo doi danh sach nguoi dung\n";
            cout << "7. Tao tai khoan nguoi dung\n";
            cout << "8. Thay doi thong tin nguoi dung\n";
            cout << "9. Backup du lieu\n";
        }
        cout << "Chon: ";

        if (!(cin >> choice)) {
            cout << "Loi: Vui long nhap so!\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        vector<UserInfo> userList;
        
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
                if (userInfo.contains("Birthday")) cout << "Ngay sinh: " << userInfo["Birthday"].get<string>() << "\n";
                cout << "=============================\n";             
                break;

            case 2:
                cin.ignore();
                editUserInfo(username);
                break;

            case 3:
                changePassword(username);
                break;

            case 4:
                showWalletMenu(username);
                break;

            case 5:
                cout << "Dang xuat...\n";
                return;

            case 6:
                if (!isQuanLy) {
                    cout << "Lua chon khong hop le!\n";
                    break;
                }
                userList = getUserList();
                cout << "\n===== USER LIST =====\n";
                for (const auto& user : userList) {
                    cout << "Username: " << user.username 
                            << " | Name: " << user.fullName 
                            << " | Role: " << user.role 
                            << " | Email: " << user.email << "\n";
                }
                break;
            
            case 7:
                if (!isQuanLy) {
                    cout << "Lua chon khong hop le!\n";
                    break;
                }
                createNewUser();
                break;
            
            case 8:
                if (!isQuanLy) {
                    cout << "Lua chon khong hop le!\n";
                    break;
                }
                modifyUserInfo(username);
                break;

            case 9:
                if (!isQuanLy) {
                    cout << "Lua chon khong hop le!\n";
                    break;
                }
                cout << "\nDang tien hanh backup du lieu...\n";
                backupUsers();
                cout << "Backup hoan thanh!\n";
                break;

            default:
                cout << "Lua chon khong hop le, vui long thu lai!\n";
        }
    } while (true);
}