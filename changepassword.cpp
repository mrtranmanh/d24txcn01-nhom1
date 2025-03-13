#include "changepassword.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;

// Ham cap nhat chi mat khau trong file JSON
void updatePassword(const string& username, const string& hashedPassword) {
    string filePath = "users/" + username + "/settings.json";

    // Doc du lieu hien co
    json userData;
    ifstream inFile(filePath);
    if (inFile.is_open()) {
        inFile >> userData;
        inFile.close();
    } else {
        cerr << "Loi: Khong the mo file nguoi dung!\n";
        return;
    }

    // Cap nhat mat khau
    userData["Password"] = hashedPassword;

    // Ghi lai du lieu vao file (khong anh huong phan khac)
    ofstream outFile(filePath);
    if (outFile.is_open()) {
        outFile << userData.dump(4); // Ghi dep hon
        outFile.close();
        cout << "Doi mat khau thanh cong!\n";
    } else {
        cerr << "Loi: Khong the cap nhat mat khau!\n";
    }
}

// Ham doi mat khau
void changePassword(const string& username) {
    string oldPassword, newPassword, confirmPassword;
    string filePath = "users/" + username + "/settings.json";

    // Doc du lieu hien co
    json userData;
    ifstream inFile(filePath);
    if (inFile.is_open()) {
        inFile >> userData;
        inFile.close();
    } else {
        cerr << "Loi: Khong tim thay du lieu nguoi dung!\n";
        return;
    }

    cout << "Nhap mat khau hien tai: ";
    cin >> oldPassword;

    // Kiem tra mat khau cu
    if (userData["Password"] != hashPassword(oldPassword)) {
        cout << "Sai mat khau! Thu lai.\n";
        return;
    }

    cout << "Nhap mat khau moi: ";
    cin >> newPassword;
    cout << "Xac nhan mat khau moi: ";
    cin >> confirmPassword;

    if (newPassword != confirmPassword) {
        cout << "Mat khau xac nhan khong khop!\n";
        return;
    }

    if (newPassword.length() < 6 || newPassword.length() > 64) {
        cout << "Mat khau phai tu 6-64 ky tu!\n";
        return;
    }

    // Cap nhat mat khau moi ma khong anh huong phan khac
    updatePassword(username, hashPassword(newPassword));
}
