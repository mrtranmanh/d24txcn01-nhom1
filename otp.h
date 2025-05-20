#ifndef OTP_H
#define OTP_H

#include <string>

std::string generateOTP();
bool verifyOTP(const std::string& generatedOTP, const std::string& userOTP);
bool sendOTP(const std::string& recipient, const std::string& otp);

#endif