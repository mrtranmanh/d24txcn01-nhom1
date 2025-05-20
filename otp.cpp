#include "otp.h"
#include <random>
#include <ctime>
#include <algorithm>
#include "sendemail.h" // Nếu hàm sendOTP sử dụng hàm sendEmail

std::string generateOTP() {
    const std::string chars = "0123456789";
    const int length = 6;
    
    std::string otp;
    std::mt19937 rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, chars.size() - 1);
    
    for (int i = 0; i < length; ++i) {
        otp += chars[dist(rng)];
    }
    
    return otp;
}

bool verifyOTP(const std::string& generatedOTP, const std::string& userOTP) {
    return generatedOTP == userOTP;
}
/*
bool sendOTP(const std::string& recipient, const std::string& otp) {
    std::string subject = "Your OTP Code";
    std::string body = "Your OTP code is: " + otp;
    return sendEmail(recipient, subject, body);
} */

bool sendOTP(const std::string& recipient, const std::string& otp) {
    std::string subject = "Ma OTP xac nhan thay doi thong tin";
    std::string body = "Ban nhan duoc email nay vi co yeu cau thay doi thong tin tai khoan.\n"
                      "Ma OTP cua ban la: " + otp + "\n\n"
                      "Ma co hieu luc trong 5 phut. Vui long khong chia se ma nay voi bat ky ai.\n"
                      "Neu ban khong yeu cau thay doi, vui long lien he voi quan tri vien.\n";
    
    return sendEmail(recipient, subject, body);
}