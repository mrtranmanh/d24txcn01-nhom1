#include "wallet.h"
#include "utils.h"
#include "sendemail.h"
#include "otp.h"
#include <fstream>
#include <filesystem>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

// Tạo mã ví ngẫu nhiên
std::string generateWalletId() {
    static const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string wallet_id = "W";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    
    for (int i = 0; i < 9; ++i) {
        wallet_id += chars[dis(gen)];
    }
    return wallet_id;
}

// Tạo mã giao dịch ngẫu nhiên
std::string generateTransactionId() {
    static const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string transaction_id = "T";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, chars.size() - 1);
    
    for (int i = 0; i < 9; ++i) {
        transaction_id += chars[dis(gen)];
    }
    return transaction_id;
}

// Kiểm tra ví tồn tại
bool isWalletExists(const std::string& wallet_id) {
    // Tìm trong tất cả thư mục users
    for (const auto& user_entry : fs::directory_iterator("users")) {
        if (user_entry.is_directory()) {
            std::string wallet_path = user_entry.path().string() + "/wallets/" + wallet_id + ".json";
            if (fs::exists(wallet_path)) {
                return true;
            }
        }
    }
    return false;
}

// Tạo ví mới
bool createWallet(const std::string& username, bool is_main_wallet) {
    // Tao thư mục wallets trong thư mục user nếu chưa tồn tại
    std::string walletDir = "users/" + username + "/wallets";
    if (!fs::exists(walletDir)) {
        fs::create_directories(walletDir);
    }

    // Tao vi moi
    Wallet wallet;
    wallet.wallet_id = generateWalletId();
    wallet.username = username;
    wallet.balance = 0;
    wallet.is_main_wallet = is_main_wallet;
    wallet.created_at = getCurrentTimestamp();
    wallet.updated_at = wallet.created_at;

    // Luu vi vao file
    std::string walletPath = walletDir + "/" + wallet.wallet_id + ".json";
    std::ofstream ofs(walletPath);
    if (!ofs.is_open()) {
        return false;
    }

    json walletJson;
    walletJson["wallet_id"] = wallet.wallet_id;
    walletJson["username"] = wallet.username;
    walletJson["balance"] = wallet.balance;
    walletJson["is_main_wallet"] = wallet.is_main_wallet;
    walletJson["created_at"] = wallet.created_at;
    walletJson["updated_at"] = wallet.updated_at;

    ofs << std::setw(4) << walletJson;
    ofs.close();

    return true;
}

// Lấy thông tin ví
Wallet getWallet(const std::string& wallet_id) {
    Wallet wallet;
    // Tìm trong tất cả thư mục users
    for (const auto& user_entry : fs::directory_iterator("users")) {
        if (user_entry.is_directory()) {
            std::string wallet_path = user_entry.path().string() + "/wallets/" + wallet_id + ".json";
            if (fs::exists(wallet_path)) {
                std::ifstream ifs(wallet_path);
                if (ifs.is_open()) {
                    json walletJson;
                    ifs >> walletJson;
                    wallet.wallet_id = walletJson["wallet_id"];
                    wallet.username = walletJson["username"];
                    wallet.balance = walletJson["balance"];
                    wallet.created_at = walletJson["created_at"];
                    wallet.updated_at = walletJson["updated_at"];
                    return wallet;
                }
            }
        }
    }
    return wallet;
}

// Lấy danh sách ví của người dùng
std::vector<Wallet> getUserWallets(const std::string& username) {
    std::vector<Wallet> wallets;
    std::string walletDir = "users/" + username + "/wallets";
    
    if (!fs::exists(walletDir)) {
        return wallets;
    }

    for (const auto& entry : fs::directory_iterator(walletDir)) {
        if (entry.path().extension() == ".json") {
            std::ifstream ifs(entry.path());
            if (ifs.is_open()) {
                json walletJson;
                ifs >> walletJson;
                
                Wallet wallet;
                wallet.wallet_id = walletJson["wallet_id"];
                wallet.username = walletJson["username"];
                wallet.balance = walletJson["balance"];
                wallet.created_at = walletJson["created_at"];
                wallet.updated_at = walletJson["updated_at"];
                
                wallets.push_back(wallet);
            }
        }
    }
    
    return wallets;
}

// Cập nhật số dư ví
bool updateWalletBalance(const std::string& wallet_id, double amount) {
    // Tìm trong tất cả thư mục users
    for (const auto& user_entry : fs::directory_iterator("users")) {
        if (user_entry.is_directory()) {
            std::string wallet_path = user_entry.path().string() + "/wallets/" + wallet_id + ".json";
            if (fs::exists(wallet_path)) {
                // Đọc dữ liệu ví
                std::ifstream file(wallet_path);
                if (!file.is_open()) return false;
                
                json wallet_data;
                file >> wallet_data;
                file.close();

                // Cập nhật số dư
                wallet_data["balance"] = wallet_data["balance"].get<double>() + amount;
                wallet_data["updated_at"] = getCurrentTimestamp();

                // Lưu lại dữ liệu
                std::ofstream outFile(wallet_path);
                if (!outFile.is_open()) return false;
                
                outFile << std::setw(4) << wallet_data;
                outFile.close();
                
                return true;
            }
        }
    }
    return false;
}

// Lấy ví tổng
Wallet getMainWallet() {
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
                            if (walletJson["is_main_wallet"]) {
                                Wallet wallet;
                                wallet.wallet_id = walletJson["wallet_id"];
                                wallet.username = walletJson["username"];
                                wallet.balance = walletJson["balance"];
                                wallet.is_main_wallet = walletJson["is_main_wallet"];
                                wallet.created_at = walletJson["created_at"];
                                wallet.updated_at = walletJson["updated_at"];
                                return wallet;
                            }
                        }
                    }
                }
            }
        }
    }
    // Nếu chưa có ví tổng, tạo mới
    if (createWallet("system", true)) {
        return getMainWallet();
    }
    return Wallet(); // Trả về ví rỗng nếu không tạo được
}

// Lấy số dư ví
double getWalletBalance(const std::string& wallet_id) {
    // Tìm trong tất cả thư mục users
    for (const auto& user_entry : fs::directory_iterator("users")) {
        if (user_entry.is_directory()) {
            std::string wallet_path = user_entry.path().string() + "/wallets/" + wallet_id + ".json";
            if (fs::exists(wallet_path)) {
                std::ifstream file(wallet_path);
                if (!file.is_open()) return 0.0;
                
                json wallet_data;
                file >> wallet_data;
                file.close();
                
                return wallet_data["balance"].get<double>();
            }
        }
    }
    return 0.0;
}

// Tạo giao dịch mới
Transaction createTransaction(const std::string& from_wallet_id, 
                            const std::string& to_wallet_id, 
                            double amount) {
    Transaction transaction;
    transaction.transaction_id = generateTransactionId();
    transaction.from_wallet_id = from_wallet_id;
    transaction.to_wallet_id = to_wallet_id;
    transaction.amount = amount;
    transaction.status = "pending";
    transaction.created_at = getCurrentTimestamp();
    transaction.completed_at = 0;
    transaction.otp_code = generateOTP();
    transaction.otp_verified = false;

    // Tạo thư mục transactions nếu chưa tồn tại
    fs::create_directories("transactions");

    // Lưu thông tin giao dịch
    json transaction_data;
    transaction_data["transaction_id"] = transaction.transaction_id;
    transaction_data["from_wallet_id"] = transaction.from_wallet_id;
    transaction_data["to_wallet_id"] = transaction.to_wallet_id;
    transaction_data["amount"] = transaction.amount;
    transaction_data["status"] = transaction.status;
    transaction_data["created_at"] = transaction.created_at;
    transaction_data["completed_at"] = transaction.completed_at;
    transaction_data["otp_code"] = transaction.otp_code;
    transaction_data["otp_verified"] = transaction.otp_verified;

    std::ofstream file("transactions/" + transaction.transaction_id + ".json");
    file << transaction_data.dump(4);
    file.close();

    // Gửi OTP qua email
    Wallet from_wallet = getWallet(from_wallet_id);
    json user_info = loadUserInfo(from_wallet.username);
    if (user_info.contains("Email")) {
        std::string email = user_info["Email"];
        std::string subject = "Xác nhận giao dịch chuyển điểm";
        std::string message = "Mã OTP của bạn là: " + transaction.otp_code;
        sendEmail(email, subject, message);
    }

    return transaction;
}

// Xác thực OTP giao dịch
bool verifyTransactionOTP(const std::string& transaction_id, 
                         const std::string& otp_code) {
    // Kiểm tra thư mục transactions tồn tại
    if (!fs::exists("transactions")) {
        return false;
    }

    std::string transaction_path = "transactions/" + transaction_id + ".json";
    if (!fs::exists(transaction_path)) {
        return false;
    }

    std::ifstream file(transaction_path);
    if (!file.is_open()) return false;

    try {
        json transaction_data;
        file >> transaction_data;
        file.close();

        if (transaction_data["otp_code"] == otp_code) {
            transaction_data["otp_verified"] = true;
            std::ofstream outFile(transaction_path);
            if (!outFile.is_open()) return false;
            
            outFile << std::setw(4) << transaction_data;
            outFile.close();
            return true;
        }
    } catch (const json::exception& e) {
        return false;
    }
    return false;
}

// Hoàn thành giao dịch
bool completeTransaction(const std::string& transaction_id) {
    // Kiểm tra thư mục transactions tồn tại
    if (!fs::exists("transactions")) {
        return false;
    }

    std::string transaction_path = "transactions/" + transaction_id + ".json";
    if (!fs::exists(transaction_path)) {
        return false;
    }

    std::ifstream file(transaction_path);
    if (!file.is_open()) return false;

    try {
        json transaction_data;
        file >> transaction_data;
        file.close();

        if (!transaction_data["otp_verified"]) return false;

        // Cập nhật số dư ví
        double amount = transaction_data["amount"];
        std::string from_wallet_id = transaction_data["from_wallet_id"];
        std::string to_wallet_id = transaction_data["to_wallet_id"];

        if (getWalletBalance(from_wallet_id) < amount) {
            transaction_data["status"] = "failed";
            std::ofstream outFile(transaction_path);
            if (!outFile.is_open()) return false;
            
            outFile << std::setw(4) << transaction_data;
            outFile.close();
            return false;
        }

        if (!updateWalletBalance(from_wallet_id, -amount) || 
            !updateWalletBalance(to_wallet_id, amount)) {
            transaction_data["status"] = "failed";
            std::ofstream outFile(transaction_path);
            if (!outFile.is_open()) return false;
            
            outFile << std::setw(4) << transaction_data;
            outFile.close();
            return false;
        }

        transaction_data["status"] = "completed";
        transaction_data["completed_at"] = getCurrentTimestamp();

        std::ofstream outFile(transaction_path);
        if (!outFile.is_open()) return false;
        
        outFile << std::setw(4) << transaction_data;
        outFile.close();
        return true;
    } catch (const json::exception& e) {
        return false;
    }
}

// Lấy lịch sử giao dịch của ví
std::vector<Transaction> getWalletTransactions(const std::string& wallet_id) {
    std::vector<Transaction> transactions;
    
    // Kiểm tra thư mục transactions tồn tại
    if (!fs::exists("transactions")) {
        return transactions;
    }
    
    for (const auto& entry : fs::directory_iterator("transactions")) {
        if (entry.path().extension() == ".json") {
            std::ifstream file(entry.path());
            if (!file.is_open()) continue;
            
            try {
                json transaction_data;
                file >> transaction_data;
                file.close();
                
                if (transaction_data["from_wallet_id"] == wallet_id || 
                    transaction_data["to_wallet_id"] == wallet_id) {
                    Transaction transaction;
                    transaction.transaction_id = transaction_data["transaction_id"];
                    transaction.from_wallet_id = transaction_data["from_wallet_id"];
                    transaction.to_wallet_id = transaction_data["to_wallet_id"];
                    transaction.amount = transaction_data["amount"];
                    transaction.status = transaction_data["status"];
                    transaction.created_at = transaction_data["created_at"];
                    transaction.completed_at = transaction_data["completed_at"];
                    transaction.otp_code = transaction_data["otp_code"];
                    transaction.otp_verified = transaction_data["otp_verified"];
                    transactions.push_back(transaction);
                }
            } catch (const json::exception& e) {
                // Bỏ qua file JSON không hợp lệ
                continue;
            }
        }
    }
    return transactions;
}

// Lấy lịch sử giao dịch của người dùng
std::vector<Transaction> getUserTransactions(const std::string& username) {
    std::vector<Transaction> transactions;
    std::vector<Wallet> user_wallets = getUserWallets(username);
    
    for (const auto& wallet : user_wallets) {
        std::vector<Transaction> wallet_transactions = getWalletTransactions(wallet.wallet_id);
        transactions.insert(transactions.end(), 
                          wallet_transactions.begin(), 
                          wallet_transactions.end());
    }
    return transactions;
} 