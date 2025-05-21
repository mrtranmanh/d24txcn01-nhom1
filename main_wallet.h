#ifndef MAIN_WALLET_H
#define MAIN_WALLET_H

#include <string>
#include "wallet.h"
#include "lib/json.hpp"

using json = nlohmann::json;

// Menu quản lý ví tổng cho admin
void showMainWalletMenu();

// Các chức năng quản lý ví tổng
void viewMainWalletInfo();                    // Xem thông tin ví tổng
bool depositToMainWallet(double amount);      // Nạp tiền vào ví tổng
bool withdrawFromMainWallet(double amount);   // Rút tiền từ ví tổng
bool transferFromMainWallet(                  // Chuyển tiền từ ví tổng cho user
    const std::string& to_username,
    double amount
);
void viewMainWalletTransactions();           // Xem lịch sử giao dịch ví tổng
void viewMainWalletStatistics();             // Xem thống kê ví tổng

// Các hàm tiện ích
double getTotalSystemBalance();              // Tổng số tiền trong hệ thống
double getTotalUserBalance();                // Tổng số tiền trong ví người dùng

#endif 