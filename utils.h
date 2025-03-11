#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include "lib/json.hpp"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;

// Ham bam mat khau
string hashPassword(const string& password);
// Ham tao mat khau
std::string generateRandomPassword(int length = 12);

// Luu & doc du lieu nguoi dung
void saveUserInfo(const string& username, json& userData);
json loadUserInfo(const string& username);

// ✅ Them khai bao ham luu thong tin dang nhap
void saveUserCredentials(const string& username, const string& hashedPassword);
json loadUserCredentials(const string& username);

void saveUserHistory(const string& username, const json& historyData);
json loadUserHistory(const string& username);

#endif