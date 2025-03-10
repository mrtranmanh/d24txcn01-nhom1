#include "login.h"
#include "utils.h"

void loginUser() {
    string username, password;
    cout << "Nhap ten dang nhap: ";
    cin >> username;

    json userData = loadUserCredentials(username);
    if (userData.empty()) {
        cout << "Tai khoan khong ton tai!\n";
        return;
    }

    cout << "Nhap mat khau: ";
    cin >> password;

    if (userData["Password"] == hashPassword(password)) {
        cout << "Dang nhap thanh cong!\n";
        cout << "Xin chao, " << userData["HoTen"] << "!\n";
    } else {
        cout << "Sai mat khau!\n";
    }
}