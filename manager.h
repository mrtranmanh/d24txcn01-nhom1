#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>
#include "lib/json.hpp"

using json = nlohmann::json;

// Struct to hold user information
struct UserInfo {
    std::string username;
    std::string fullName;
    std::string role;
    std::string email;
};

// Manager functions
std::vector<UserInfo> getUserList();
void createNewUser();
void modifyUserInfo(const std::string& managerUsername);
bool sendOTP(const std::string& email, const std::string& otp);
int getMaxUserId(const std::string& userType);
#endif