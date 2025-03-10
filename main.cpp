#include <iostream>
#include "register.h"
#include "login.h"

using namespace std;

int main() {
    int lua_chon;
    do {
        cout << "\n1. Dang ky\n2. Dang nhap\n3. Thoat\nChon: ";
        
        if (!(cin >> lua_chon)) { // Kiem tra neu nhap sai (vi du: nhap chu thay vi so)
            cout << "❌ Loi: Vui long nhap so tu 1 den 3!\n";
            cin.clear();  // Xoa trang thai loi cua cin
            cin.ignore(1000, '\n'); // Xoa du lieu sai con trong bo dem
            continue; // Quay lai vong lap de nhap lai
        }

        switch (lua_chon) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Tam biet!\n"; break;
            default: cout << "❌ Lua chon khong hop le! Vui long nhap so tu 1 den 3.\n"; break;
        }

    } while (lua_chon != 3);

    return 0;
}