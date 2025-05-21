#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <ctime>
#include "lib/json.hpp"
#include "timestamp.h"

using json = nlohmann::json;

// Cấu trúc ví
struct Wallet {
    std::string wallet_id;      // Mã định danh ví
    std::string username;       // Tên người sở hữu
    double balance;            // Số dư
    bool is_main_wallet;       // Có phải ví tổng không
    time_t created_at;         // Thời gian tạo
    time_t updated_at;         // Thời gian cập nhật
};

// Cấu trúc giao dịch
struct Transaction {
    std::string transaction_id;    // Mã giao dịch
    std::string from_wallet_id;    // Ví gửi
    std::string to_wallet_id;      // Ví nhận
    double amount;                 // Số điểm
    std::string status;           // Trạng thái: pending, completed, failed
    time_t created_at;            // Thời gian tạo
    time_t completed_at;          // Thời gian hoàn thành
    std::string otp_code;         // Mã OTP
    bool otp_verified;            // Đã xác thực OTP chưa
};

// Các hàm quản lý ví
bool createWallet(const std::string& username, bool is_main_wallet = false);
Wallet getWallet(const std::string& wallet_id);
std::vector<Wallet> getUserWallets(const std::string& username);
bool updateWalletBalance(const std::string& wallet_id, double amount);
Wallet getMainWallet();

// Các hàm quản lý giao dịch
Transaction createTransaction(const std::string& from_wallet_id, 
                            const std::string& to_wallet_id, 
                            double amount);
bool verifyTransactionOTP(const std::string& transaction_id, 
                         const std::string& otp_code);
bool completeTransaction(const std::string& transaction_id);
std::vector<Transaction> getWalletTransactions(const std::string& wallet_id);
std::vector<Transaction> getUserTransactions(const std::string& username);

// Các hàm tiện ích
std::string generateWalletId();
std::string generateTransactionId();
std::string generateOTP();
bool isWalletExists(const std::string& wallet_id);
double getWalletBalance(const std::string& wallet_id);

#endif 