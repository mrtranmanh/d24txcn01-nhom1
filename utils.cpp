#include "utils.h"

// Ham ma hoa mat khau
string hashPassword(const string& password) {
    return to_string(hash<string>{}(password));
}

// Ham tim ID lon nhat trong cac tep info.json
int getMaxUserId(const std::string& usersDir) {
    int maxId = 0;
    
    // Duyet qua tat ca cac thu muc con trong thu muc users
    for (const auto& entry : fs::directory_iterator(usersDir)) {
        if (entry.is_directory()) {
            std::string filePath = entry.path().string() + "/info.json";
            if (fs::exists(filePath)) {
                std::ifstream file(filePath);
                json userData;
                file >> userData;
                
                // Kiem tra xem tep co truong "id" hay khong
                if (userData.contains("user_id")) {
                    int userId = userData["user_id"];
                    maxId = std::max(maxId, userId);  // Cap nhat ID lon nhat
                }
            }
        }
    }
    
    return maxId;
}

// Luu thong tin dang nhap vao settings.json
void saveUserCredentials(const string& username, const string& hashedPassword) {
    string filePath = "users/" + username + "/settings.json";
    fs::create_directories("users/" + username);  // Tao thu muc neu chua co

    json settings;
    settings["Role"] = "Nguoi_Dung";
    settings["Username"] = username;
    settings["Password"] = hashedPassword;

    ofstream file(filePath);
    if (file.is_open()) {
        file << settings.dump(4); // Ghi du lieu voi format dep
        file.close();
    } else {
        cerr << "❌ Loi: Khong the luu thong tin dang nhap!\n";
    }
}

// Doc thong tin dang nhap tu settings.json
json loadUserCredentials(const string& username) {
    string filePath = "users/" + username + "/settings.json";
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "❌ Loi: Khong tim thay tai khoan!\n";
        return {};
    }

    json credentials;
    file >> credentials;
    file.close();
    return credentials;
}

// Luu thong tin ca nhan vao info.json
void saveUserInfo(const std::string& username, json& userData) {
    // Duong dan toi thu muc nguoi dung
    std::string usersDir = "./users/";
    std::string userDir = usersDir + username;
    fs::create_directories(userDir);  // Tao thu muc nguoi dung neu chua co

    // Them truong Diem Thuong neu chua co
    if (!userData.contains("Points")) {
        userData["Points"] = 0;
    }

    // Lay ID lon nhat tu cac tep info.json
    int maxId = getMaxUserId(usersDir);

    // Neu chua co nguoi dung, bat dau tu ID = 1
    if (!userData.contains("user_id")) {
        userData["user_id"] = maxId + 1;
    }

    std::string filePath = userDir + "/info.json";

    // Luu du lieu vao file
    std::ofstream file(filePath);
    if (file.is_open()) {
        file << userData.dump(4);
        file.close();
    } else {
        std::cerr << "Loi: Khong the luu du lieu!\n";
    }
}

// Doc thong tin ca nhan tu info.json
json loadUserInfo(const string& username) {
    string filePath = "users/" + username + "/info.json";
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "❌ Loi: Khong tim thay thong tin ca nhan!\n";
        return {};
    }

    json userData;
    file >> userData;
    file.close();
    return userData;
}