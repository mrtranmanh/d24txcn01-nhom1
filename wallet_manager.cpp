#include "wallet_manager.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <ctime>

// Hiển thị menu ví cho người dùng
void showWalletMenu(const std::string& username) {
    std::vector<Wallet> wallets = getUserWallets(username);
    int choice;
    
    do {
        std::cout << "\n===== QUAN LY VI DIEN TU =====\n";
        std::cout << "1. Xem danh sach vi\n";
        std::cout << "2. Tao vi moi\n";
        std::cout << "3. Chuyen tien\n";
        std::cout << "4. Xem lich su giao dich\n";
        std::cout << "5. Quay lai\n";
        std::cout << "Chon: ";

        if (!(std::cin >> choice)) {
            std::cout << "Loi: Vui long nhap so!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                std::cout << "\n===== DANH SACH VI =====\n";
                if (wallets.empty()) {
                    std::cout << "Ban chua co vi nao!\n";
                } else {
                    for (const auto& wallet : wallets) {
                        std::cout << "Ma vi: " << wallet.wallet_id << "\n";
                        std::cout << "So du: " << std::fixed << std::setprecision(2) << wallet.balance << "\n";
                        std::cout << "------------------------\n";
                    }
                }
                break;
            }
            case 2: {
                if (createWallet(username)) {
                    std::cout << "Tao vi moi thanh cong!\n";
                    wallets = getUserWallets(username); // Cập nhật danh sách ví
                } else {
                    std::cout << "Tao vi that bai!\n";
                }
                break;
            }
            case 3: {
                if (wallets.empty()) {
                    std::cout << "Ban chua co vi nao! Vui long tao vi truoc.\n";
                    break;
                }

                std::string from_wallet_id, to_wallet_id;
                double amount;

                std::cout << "\nDanh sach vi cua ban:\n";
                for (const auto& wallet : wallets) {
                    std::cout << "Ma vi: " << wallet.wallet_id << " - So du: " << wallet.balance << "\n";
                }

                std::cout << "Nhap ma vi gui: ";
                std::cin >> from_wallet_id;
                std::cout << "Nhap ma vi nhan: ";
                std::cin >> to_wallet_id;
                std::cout << "Nhap so tien: ";
                std::cin >> amount;

                if (amount <= 0) {
                    std::cout << "So tien khong hop le!\n";
                    break;
                }

                // Kiểm tra số dư
                if (getWalletBalance(from_wallet_id) < amount) {
                    std::cout << "So du khong du!\n";
                    break;
                }

                // Tạo giao dịch
                Transaction trans = createTransaction(from_wallet_id, to_wallet_id, amount);
                std::cout << "Ma giao dich: " << trans.transaction_id << "\n";
                std::cout << "Ma OTP da duoc gui den email cua ban.\n";
                
                std::string otp;
                std::cout << "Nhap ma OTP: ";
                std::cin >> otp;

                if (verifyTransactionOTP(trans.transaction_id, otp)) {
                    if (completeTransaction(trans.transaction_id)) {
                        std::cout << "Chuyen tien thanh cong!\n";
                    } else {
                        std::cout << "Chuyen tien that bai!\n";
                    }
                } else {
                    std::cout << "Ma OTP khong dung!\n";
                }
                break;
            }
            case 4: {
                std::vector<Transaction> transactions = getUserTransactions(username);
                std::cout << "\n===== LICH SU GIAO DICH =====\n";
                if (transactions.empty()) {
                    std::cout << "Chua co giao dich nao!\n";
                } else {
                    for (const auto& trans : transactions) {
                        std::cout << "Ma giao dich: " << trans.transaction_id << "\n";
                        std::cout << "Tu vi: " << trans.from_wallet_id << "\n";
                        std::cout << "Den vi: " << trans.to_wallet_id << "\n";
                        std::cout << "So tien: " << std::fixed << std::setprecision(2) << trans.amount << "\n";
                        std::cout << "Trang thai: " << trans.status << "\n";
                        std::cout << "------------------------\n";
                    }
                }
                break;
            }
            case 5:
                return;
            default:
                std::cout << "Lua chon khong hop le!\n";
        }
    } while (true);
}

// Hiển thị thông tin ví
void showWalletInfo(const std::string& username) {
    std::vector<Wallet> wallets = getUserWallets(username);
    if (wallets.empty()) {
        std::cout << "Ban chua co vi nao. Dang tao vi moi...\n";
        createWallet(username);
        wallets = getUserWallets(username);
    }

    std::cout << "\n===== THONG TIN VI =====\n";
    for (const auto& wallet : wallets) {
        std::cout << "Ma vi: " << wallet.wallet_id << "\n";
        std::cout << "So du: " << wallet.balance << " diem\n";
        std::cout << "Ngay tao: " << std::ctime(&wallet.created_at);
        std::cout << "------------------------\n";
    }
}

// Hiển thị lịch sử giao dịch
void showTransactionHistory(const std::string& username) {
    std::vector<Transaction> transactions = getUserTransactions(username);
    
    std::cout << "\n===== LICH SU GIAO DICH =====\n";
    if (transactions.empty()) {
        std::cout << "Chua co giao dich nao.\n";
        return;
    }

    for (const auto& transaction : transactions) {
        std::cout << "Ma giao dich: " << transaction.transaction_id << "\n";
        std::cout << "Tu vi: " << transaction.from_wallet_id << "\n";
        std::cout << "Den vi: " << transaction.to_wallet_id << "\n";
        std::cout << "So diem: " << transaction.amount << "\n";
        std::cout << "Trang thai: " << transaction.status << "\n";
        std::cout << "Thoi gian tao: " << std::ctime(&transaction.created_at);
        if (transaction.completed_at > 0) {
            std::cout << "Thoi gian hoan thanh: " << std::ctime(&transaction.completed_at);
        }
        std::cout << "------------------------\n";
    }
}

// Chuyển điểm
void transferPoints(const std::string& username) {
    std::string to_wallet_id;
    double amount;

    // Hiển thị danh sách ví của người dùng
    std::vector<Wallet> user_wallets = getUserWallets(username);
    std::cout << "\n===== DANH SACH VI CUA BAN =====\n";
    for (const auto& wallet : user_wallets) {
        std::cout << "Ma vi: " << wallet.wallet_id << " - So du: " << wallet.balance << " diem\n";
    }

    // Chọn ví gửi
    std::string from_wallet_id;
    std::cout << "Nhap ma vi gui: ";
    std::cin >> from_wallet_id;

    // Kiểm tra ví gửi
    bool valid_wallet = false;
    for (const auto& wallet : user_wallets) {
        if (wallet.wallet_id == from_wallet_id) {
            valid_wallet = true;
            break;
        }
    }
    if (!valid_wallet) {
        std::cout << "Ma vi khong hop le!\n";
        return;
    }

    // Nhập ví nhận và số điểm
    std::cout << "Nhap ma vi nhan: ";
    std::cin >> to_wallet_id;
    if (!isWalletExists(to_wallet_id)) {
        std::cout << "Vi nhan khong ton tai!\n";
        return;
    }

    std::cout << "Nhap so diem muon chuyen: ";
    std::cin >> amount;
    if (amount <= 0) {
        std::cout << "So diem khong hop le!\n";
        return;
    }

    // Kiểm tra số dư
    if (getWalletBalance(from_wallet_id) < amount) {
        std::cout << "So du khong du!\n";
        return;
    }

    // Tạo giao dịch
    Transaction transaction = createTransaction(from_wallet_id, to_wallet_id, amount);
    std::cout << "Giao dich da duoc tao. Vui long nhap ma OTP de xac nhan.\n";
    std::cout << "Ma OTP da duoc gui qua email cua ban.\n";
}

// Xác thực OTP chuyển điểm
void verifyTransferOTP(const std::string& username) {
    std::string transaction_id, otp_code;
    std::cout << "Nhap ma giao dich: ";
    std::cin >> transaction_id;
    std::cout << "Nhap ma OTP: ";
    std::cin >> otp_code;

    if (verifyTransactionOTP(transaction_id, otp_code)) {
        if (completeTransaction(transaction_id)) {
            std::cout << "Giao dich thanh cong!\n";
        } else {
            std::cout << "Giao dich that bai!\n";
        }
    } else {
        std::cout << "Ma OTP khong hop le!\n";
    }
}

// Menu quản lý ví cho admin
void showAdminWalletMenu() {
    int choice;
    do {
        std::cout << "\n===== QUAN LY VI (ADMIN) =====\n";
        std::cout << "1. Xem danh sach vi\n";
        std::cout << "2. Xem lich su giao dich\n";
        std::cout << "3. Them diem vao vi tong\n";
        std::cout << "4. Rut diem tu vi tong\n";
        std::cout << "5. Quay lai\n";
        std::cout << "Chon: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                showAllWallets();
                break;
            case 2:
                showAllTransactions();
                break;
            case 3:
                double add_amount;
                std::cout << "Nhap so diem muon them: ";
                std::cin >> add_amount;
                addPointsToMainWallet(add_amount);
                break;
            case 4:
                double remove_amount;
                std::cout << "Nhap so diem muon rut: ";
                std::cin >> remove_amount;
                removePointsFromMainWallet(remove_amount);
                break;
            case 5:
                return;
            default:
                std::cout << "Lua chon khong hop le!\n";
        }
    } while (true);
}

// Hiển thị tất cả ví
void showAllWallets() {
    std::cout << "\n===== DANH SACH VI =====\n";
    for (const auto& entry : fs::directory_iterator("wallets")) {
        if (entry.path().extension() == ".json") {
            std::ifstream file(entry.path());
            json wallet_data;
            file >> wallet_data;
            std::cout << "Ma vi: " << wallet_data["wallet_id"] << "\n";
            std::cout << "Chu so huu: " << wallet_data["owner_username"] << "\n";
            std::cout << "So du: " << wallet_data["balance"] << " diem\n";
            std::cout << "Loai vi: " << (wallet_data["is_main_wallet"] ? "Vi tong" : "Vi thuong") << "\n";
            std::cout << "------------------------\n";
        }
    }
}

// Hiển thị tất cả giao dịch
void showAllTransactions() {
    std::cout << "\n===== LICH SU GIAO DICH =====\n";
    for (const auto& entry : fs::directory_iterator("transactions")) {
        if (entry.path().extension() == ".json") {
            std::ifstream file(entry.path());
            json transaction_data;
            file >> transaction_data;
            std::cout << "Ma giao dich: " << transaction_data["transaction_id"] << "\n";
            std::cout << "Tu vi: " << transaction_data["from_wallet_id"] << "\n";
            std::cout << "Den vi: " << transaction_data["to_wallet_id"] << "\n";
            std::cout << "So diem: " << transaction_data["amount"] << "\n";
            std::cout << "Trang thai: " << transaction_data["status"] << "\n";
            std::cout << "------------------------\n";
        }
    }
}

// Thêm điểm vào ví tổng
void addPointsToMainWallet(double amount) {
    if (amount <= 0) {
        std::cout << "So diem khong hop le!\n";
        return;
    }

    Wallet main_wallet = getMainWallet();
    if (updateWalletBalance(main_wallet.wallet_id, amount)) {
        std::cout << "Them diem thanh cong!\n";
    } else {
        std::cout << "Them diem that bai!\n";
    }
}

// Rút điểm từ ví tổng
void removePointsFromMainWallet(double amount) {
    if (amount <= 0) {
        std::cout << "So diem khong hop le!\n";
        return;
    }

    Wallet main_wallet = getMainWallet();
    if (getWalletBalance(main_wallet.wallet_id) < amount) {
        std::cout << "So du khong du!\n";
        return;
    }

    if (updateWalletBalance(main_wallet.wallet_id, -amount)) {
        std::cout << "Rut diem thanh cong!\n";
    } else {
        std::cout << "Rut diem that bai!\n";
    }
} 