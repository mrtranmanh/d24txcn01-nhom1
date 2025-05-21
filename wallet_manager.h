#ifndef WALLET_MANAGER_H
#define WALLET_MANAGER_H

#include <string>
#include <vector>
#include "wallet.h"

// Các hàm quản lý ví cho người dùng
void showWalletMenu(const std::string& username);
void showWalletInfo(const std::string& username);
void showTransactionHistory(const std::string& username);
void transferPoints(const std::string& username);
void verifyTransferOTP(const std::string& username);

// Các hàm quản lý ví cho admin
void showAdminWalletMenu();
void showAllWallets();
void showAllTransactions();
void addPointsToMainWallet(double amount);
void removePointsFromMainWallet(double amount);

#endif 