#include "backup.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;
using namespace std;

const string USERS_DIR = "users";
const string BACKUP_DIR = "backup";
const string LAST_BACKUP_FILE = "backup/last_backup.txt";

// Lay thoi gian hien tai duoi dang `time_t`
time_t getCurrentTime() {
    return time(nullptr);
}

// Doc thoi gian backup lan cuoi tu file
time_t getLastBackupTime() {
    ifstream file(LAST_BACKUP_FILE);
    if (!file) return 0;

    time_t lastTime;
    if (!(file >> lastTime)) {  // Kiem tra neu doc that bai
        return 0;
    }
    
    return lastTime;
}

// Cap nhat thoi gian backup moi nhat vao file
void updateLastBackupTime(time_t currentTime) {
    ofstream file(LAST_BACKUP_FILE);
    if (file) {
        file << currentTime;
    }
}

// Ham tao ten thu muc backup co dinh dang YYYY-MM-DD_HH-MM-SS
string generateBackupFolderName() {
    time_t now = getCurrentTime();
    struct tm *timeinfo = localtime(&now);
    stringstream ss;
    ss << put_time(timeinfo, "%Y-%m-%d_%H-%M-%S");
    return BACKUP_DIR + "/backup_" + ss.str();
}

// Ham thuc hien backup thu muc users
void backupUsers() {
    if (!fs::exists(USERS_DIR)) {
        cout << "Thu muc users khong ton tai! Khong the backup.\n";
        return;
    }

    // Kiem tra va tao thu muc backup
    if (!fs::exists(BACKUP_DIR)) {
        fs::create_directory(BACKUP_DIR);
    }

    string backupFolder = generateBackupFolderName();
    fs::create_directory(backupFolder);

    // Copy toan bo noi dung thu muc users
    try {
        for (const auto &entry : fs::directory_iterator(USERS_DIR)) {
            fs::copy(entry.path(), backupFolder + "/" + entry.path().filename().string(),
                     fs::copy_options::recursive);
        }

        cout << "Backup hoan thanh tai: " << backupFolder << endl;
        updateLastBackupTime(getCurrentTime()); // Cap nhat thoi gian backup
    } catch (const fs::filesystem_error &e) {
        cout << "Loi khi backup: " << e.what() << endl;
    }
}

// Kiem tra xem co can backup khong (neu da qua 7 ngay ke tu lan cuoi)
bool shouldBackup() {
    time_t lastBackup = getLastBackupTime();
    time_t now = getCurrentTime();
    double daysDiff = difftime(now, lastBackup) / (60 * 60 * 24);
    return daysDiff >= 7;
}

// Kiem tra va backup neu can thiet
void checkAndBackup() {
    if (shouldBackup()) {
        cout << "\nDa qua 7 ngay ke tu lam backup truoc. Dang tien hanh backup tu dong...\n\n";
        backupUsers();
    } else {
        cout << "\nChua can backup. Lan backup cuoi cung chua qua 7 ngay.\n\n";
    }
}