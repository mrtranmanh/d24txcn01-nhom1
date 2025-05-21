#ifndef EDITINFO_H
#define EDITINFO_H

#include <string>
#include "lib/json.hpp"

using json = nlohmann::json;

// Hiển thị form chỉnh sửa thông tin cá nhân
void editUserInfo(const std::string& username);

// Gửi OTP qua email cho người dùng
bool sendOTPEmail(const std::string& email, const std::string& otp, const std::string& changeDescription);

// Xác thực OTP đã nhập
bool verifyOTPEditUserInfo(const std::string& inputOTP, const std::string& correctOTP);

// Cập nhật thông tin người dùng sau khi xác thực OTP thành công
bool updateUserInfo(const std::string& username, const json& newInfo);

#endif