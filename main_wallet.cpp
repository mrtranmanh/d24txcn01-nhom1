#include "main_wallet.h"
#include "utils.h"
#include "otp.h"
#include "sendemail.h"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <numeric>

namespace fs = std::filesystem;

// Menu quản lý ví tổng cho admin
void showMainWalletMenu() {
    int choice;
    do {
        std::cout << "\n===== QUAN LY VI TONG =====\n";
        std::cout << "1. Xem thong tin vi tong\n";
        std::cout << "2. Nap tien vao vi tong\n";
        std::cout << "3. Rut tien tu vi tong\n";
        std::cout << "4. Chuyen tien cho nguoi dung\n";
        std::cout << "5. Xem lich su giao dich\n";
        std::cout << "6. Xem thong ke\n";
        std::cout << "7. Quay lai\n";
        std::cout << "Chon: ";

        if (!(std::cin >> choice)) {
            std::cout << "Loi: Vui long nhap so!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        double amount;
        std::string username;
        std::string otp;

        switch (choice) {
            case 1:
                viewMainWalletInfo();
                break;

            case 2:
                std::cout << "Nhap so tien muon nap: ";
                std::cin >> amount;
                if (amount <= 0) {
                    std::cout << "So tien khong hop le!\n";
                    break;
                }

                // Gửi OTP
                std::cout << "Ma OTP da duoc gui den email cua ban.\n";
                std::cout << "Nhap ma OTP: ";
                std::cin >> otp;
                
                // Kiểm tra OTP (giả định OTP đúng là "123456" - trong thực tế sẽ gửi qua email)
                if (otp == "123456") {
                    if (depositToMainWallet(amount)) {
                        std::cout << "Nap tien thanh cong!\n";
                    } else {
                        std::cout << "Nap tien that bai!\n";
                    }
                } else {
                    std::cout << "Ma OTP khong dung!\n";
                }
                break;

            case 3:
                std::cout << "Nhap so tien muon rut: ";
                std::cin >> amount;
                if (amount <= 0) {
                    std::cout << "So tien khong hop le!\n";
                    break;
                }

                // Gửi OTP
                std::cout << "Ma OTP da duoc gui den email cua ban.\n";
                std::cout << "Nhap ma OTP: ";
                std::cin >> otp;
                
                // Kiểm tra OTP
                if (otp == "123456") {
                    if (withdrawFromMainWallet(amount)) {
                        std::cout << "Rut tien thanh cong!\n";
                    } else {
                        std::cout << "Rut tien that bai!\n";
                    }
                } else {
                    std::cout << "Ma OTP khong dung!\n";
                }
                break;

            case 4:
                std::cout << "Nhap ten nguoi dung: ";
                std::cin >> username;
                std::cout << "Nhap so tien: ";
                std::cin >> amount;
                
                if (amount <= 0) {
                    std::cout << "So tien khong hop le!\n";
                    break;
                }

                // Gửi OTP
                std::cout << "Ma OTP da duoc gui den email cua ban.\n";
                std::cout << "Nhap ma OTP: ";
                std::cin >> otp;
                
                // Kiểm tra OTP
                if (otp == "123456") {
                    if (transferFromMainWallet(username, amount)) {
                        std::cout << "Chuyen tien thanh cong!\n";
                    } else {
                        std::cout << "Chuyen tien that bai!\n";
                    }
                } else {
                    std::cout << "Ma OTP khong dung!\n";
                }
                break;

            case 5:
                viewMainWalletTransactions();
                break;

            case 6:
                viewMainWalletStatistics();
                break;

            case 7:
                return;

            default:
                std::cout << "Lua chon khong hop le!\n";
        }
    } while (true);
}

// Xem thông tin ví tổng
void viewMainWalletInfo() {
    Wallet main_wallet = getMainWallet();
    std::cout << "\n===== THONG TIN VI TONG =====\n";
    std::cout << "Ma vi: " << main_wallet.wallet_id << "\n";
    std::cout << "So du: " << std::fixed << std::setprecision(2) << main_wallet.balance << "\n";
    std::cout << "Tong so tien trong he thong: " << getTotalSystemBalance() << "\n";
    std::cout << "Tong so tien trong vi nguoi dung: " << getTotalUserBalance() << "\n";
    std::cout << "===========================\n";
}

// Nạp tiền vào ví tổng
bool depositToMainWallet(double amount) {
    if (amount <= 0) return false;

    Wallet main_wallet = getMainWallet();
    if (updateWalletBalance(main_wallet.wallet_id, amount)) {
        // Tạo giao dịch nạp tiền
        Transaction trans;
        trans.transaction_id = generateTransactionId();
        trans.from_wallet_id = "DEPOSIT";
        trans.to_wallet_id = main_wallet.wallet_id;
        trans.amount = amount;
        trans.status = "completed";
        trans.created_at = getCurrentTimestamp();
        trans.completed_at = trans.created_at;
        trans.otp_verified = true;

        // Lưu giao dịch
        fs::create_directories("transactions");
        json transaction_data;
        transaction_data["transaction_id"] = trans.transaction_id;
        transaction_data["from_wallet_id"] = trans.from_wallet_id;
        transaction_data["to_wallet_id"] = trans.to_wallet_id;
        transaction_data["amount"] = trans.amount;
        transaction_data["status"] = trans.status;
        transaction_data["created_at"] = trans.created_at;
        transaction_data["completed_at"] = trans.completed_at;
        transaction_data["otp_verified"] = trans.otp_verified;

        std::ofstream file("transactions/" + trans.transaction_id + ".json");
        file << std::setw(4) << transaction_data;
        file.close();

        return true;
    }
    return false;
}

// Rút tiền từ ví tổng
bool withdrawFromMainWallet(double amount) {
    if (amount <= 0) return false;

    Wallet main_wallet = getMainWallet();
    if (main_wallet.balance < amount) return false;

    if (updateWalletBalance(main_wallet.wallet_id, -amount)) {
        // Tạo giao dịch rút tiền
        Transaction trans;
        trans.transaction_id = generateTransactionId();
        trans.from_wallet_id = main_wallet.wallet_id;
        trans.to_wallet_id = "WITHDRAW";
        trans.amount = amount;
        trans.status = "completed";
        trans.created_at = getCurrentTimestamp();
        trans.completed_at = trans.created_at;
        trans.otp_verified = true;

        // Lưu giao dịch
        fs::create_directories("transactions");
        json transaction_data;
        transaction_data["transaction_id"] = trans.transaction_id;
        transaction_data["from_wallet_id"] = trans.from_wallet_id;
        transaction_data["to_wallet_id"] = trans.to_wallet_id;
        transaction_data["amount"] = trans.amount;
        transaction_data["status"] = trans.status;
        transaction_data["created_at"] = trans.created_at;
        transaction_data["completed_at"] = trans.completed_at;
        transaction_data["otp_verified"] = trans.otp_verified;

        std::ofstream file("transactions/" + trans.transaction_id + ".json");
        file << std::setw(4) << transaction_data;
        file.close();

        return true;
    }
    return false;
}

// Chuyển tiền từ ví tổng cho user
bool transferFromMainWallet(const std::string& to_username, double amount) {
    if (amount <= 0) return false;

    // Kiểm tra user tồn tại
    if (!fs::exists("users/" + to_username)) {
        return false;
    }

    // Lấy ví của user (hoặc tạo mới nếu chưa có)
    std::vector<Wallet> user_wallets = getUserWallets(to_username);
    if (user_wallets.empty()) {
        if (!createWallet(to_username)) {
            return false;
        }
        user_wallets = getUserWallets(to_username);
    }

    Wallet main_wallet = getMainWallet();
    if (main_wallet.balance < amount) return false;

    // Chuyển tiền
    if (updateWalletBalance(main_wallet.wallet_id, -amount) &&
        updateWalletBalance(user_wallets[0].wallet_id, amount)) {
        // Tạo giao dịch chuyển tiền
        Transaction trans;
        trans.transaction_id = generateTransactionId();
        trans.from_wallet_id = main_wallet.wallet_id;
        trans.to_wallet_id = user_wallets[0].wallet_id;
        trans.amount = amount;
        trans.status = "completed";
        trans.created_at = getCurrentTimestamp();
        trans.completed_at = trans.created_at;
        trans.otp_verified = true;

        // Lưu giao dịch
        fs::create_directories("transactions");
        json transaction_data;
        transaction_data["transaction_id"] = trans.transaction_id;
        transaction_data["from_wallet_id"] = trans.from_wallet_id;
        transaction_data["to_wallet_id"] = trans.to_wallet_id;
        transaction_data["amount"] = trans.amount;
        transaction_data["status"] = trans.status;
        transaction_data["created_at"] = trans.created_at;
        transaction_data["completed_at"] = trans.completed_at;
        transaction_data["otp_verified"] = trans.otp_verified;

        std::ofstream file("transactions/" + trans.transaction_id + ".json");
        file << std::setw(4) << transaction_data;
        file.close();

        return true;
    }
    return false;
}

// Xem lịch sử giao dịch ví tổng
void viewMainWalletTransactions() {
    Wallet main_wallet = getMainWallet();
    std::vector<Transaction> transactions = getWalletTransactions(main_wallet.wallet_id);

    std::cout << "\n===== LICH SU GIAO DICH VI TONG =====\n";
    if (transactions.empty()) {
        std::cout << "Chua co giao dich nao!\n";
        return;
    }

    for (const auto& trans : transactions) {
        std::cout << "Ma giao dich: " << trans.transaction_id << "\n";
        if (trans.from_wallet_id == "DEPOSIT") {
            std::cout << "Loai giao dich: Nap tien\n";
        } else if (trans.to_wallet_id == "WITHDRAW") {
            std::cout << "Loai giao dich: Rut tien\n";
        } else {
            std::cout << "Tu vi: " << trans.from_wallet_id << "\n";
            std::cout << "Den vi: " << trans.to_wallet_id << "\n";
        }
        std::cout << "So tien: " << std::fixed << std::setprecision(2) << trans.amount << "\n";
        std::cout << "Trang thai: " << trans.status << "\n";
        std::cout << "------------------------\n";
    }
}

// Xem thống kê ví tổng
void viewMainWalletStatistics() {
    Wallet main_wallet = getMainWallet();
    std::vector<Transaction> transactions = getWalletTransactions(main_wallet.wallet_id);

    double total_deposit = 0;
    double total_withdraw = 0;
    double total_transfer = 0;
    int num_deposit = 0;
    int num_withdraw = 0;
    int num_transfer = 0;

    for (const auto& trans : transactions) {
        if (trans.from_wallet_id == "DEPOSIT") {
            total_deposit += trans.amount;
            num_deposit++;
        } else if (trans.to_wallet_id == "WITHDRAW") {
            total_withdraw += trans.amount;
            num_withdraw++;
        } else {
            total_transfer += trans.amount;
            num_transfer++;
        }
    }

    std::cout << "\n===== THONG KE VI TONG =====\n";
    std::cout << "So du hien tai: " << std::fixed << std::setprecision(2) << main_wallet.balance << "\n";
    std::cout << "\nTong so tien nap: " << total_deposit << "\n";
    std::cout << "So lan nap: " << num_deposit << "\n";
    std::cout << "\nTong so tien rut: " << total_withdraw << "\n";
    std::cout << "So lan rut: " << num_withdraw << "\n";
    std::cout << "\nTong so tien chuyen: " << total_transfer << "\n";
    std::cout << "So lan chuyen: " << num_transfer << "\n";
    std::cout << "===========================\n";
}

// Tổng số tiền trong hệ thống
double getTotalSystemBalance() {
    double total = 0;
    for (const auto& user_entry : fs::directory_iterator("users")) {
        if (user_entry.is_directory()) {
            std::string walletDir = user_entry.path().string() + "/wallets";
            if (fs::exists(walletDir)) {
                for (const auto& entry : fs::directory_iterator(walletDir)) {
                    if (entry.path().extension() == ".json") {
                        std::ifstream ifs(entry.path());
                        if (ifs.is_open()) {
                            json walletJson;
                            ifs >> walletJson;
                            total += walletJson["balance"].get<double>();
                        }
                    }
                }
            }
        }
    }
    return total;
}

// Tổng số tiền trong ví người dùng (không tính ví tổng)
double getTotalUserBalance() {
    double total = 0;
    for (const auto& user_entry : fs::directory_iterator("users")) {
        if (user_entry.is_directory()) {
            std::string username = user_entry.path().filename().string();
            if (username != "system") {  // Không tính ví của system
                std::string walletDir = user_entry.path().string() + "/wallets";
                if (fs::exists(walletDir)) {
                    for (const auto& entry : fs::directory_iterator(walletDir)) {
                        if (entry.path().extension() == ".json") {
                            std::ifstream ifs(entry.path());
                            if (ifs.is_open()) {
                                json walletJson;
                                ifs >> walletJson;
                                total += walletJson["balance"].get<double>();
                            }
                        }
                    }
                }
            }
        }
    }
    return total;
} 