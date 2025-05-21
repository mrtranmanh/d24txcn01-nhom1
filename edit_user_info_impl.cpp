#include "edit_user_info.h"
#include "utils.h"
#include "sendemail.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
#include <random>
#include <iomanip>
#include <sstream>

using namespace std;

// Hàm tạo mã OTP
string generateOTP() {
    // Tạo số ngẫu nhiên gồm 6 chữ số
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(100000, 999999);
    
    return to_string(dis(gen));
}

// Hàm kiểm tra email có tồn tại hay không
bool isEmailValid(const string& email) {
    // Biểu thức chính quy kiểm tra email
    regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, emailPattern);
}

// Kiểm tra ngày hợp lệ
bool isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false; // Giới hạn năm

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Kiểm tra năm nhuận
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    // Kiểm tra tháng & ngày
    return (month >= 1 && month <= 12) && (day >= 1 && day <= daysInMonth[month]);
}

// Hàm gửi OTP qua email
bool sendOTPEmail(const string& email, const string& otp, const string& changeDescription) {
    string subject = "Mã xác thực OTP cho thay đổi thông tin";
    string body = "Xin chào,\n\n"
                  "Bạn đã yêu cầu thay đổi thông tin cá nhân: \n\n" + 
                  changeDescription + "\n\n" +
                  "Mã OTP của bạn là: " + otp + "\n\n"
                  "Mã này có hiệu lực trong 5 phút.\n"
                  "Nếu bạn không thực hiện yêu cầu này, vui lòng bỏ qua email này.\n\n"
                  "Trân trọng,\nĐội ngũ hỗ trợ";

    return sendEmail(email, subject, body);
}

// Xác thực OTP đã nhập
bool verifyOTP(const string& inputOTP, const string& correctOTP) {
    return inputOTP == correctOTP;
}

// Chức năng chỉnh sửa thông tin cá nhân
void editUserInfo(const string& username) {
    json userInfo = loadUserInfo(username);
    json newInfo = userInfo; // Tạo bản sao để chỉnh sửa
    
    if (userInfo.empty()) {
        cout << "Không thể tải thông tin người dùng. Vui lòng thử lại sau!\n";
        return;
    }

    // Hiển thị thông tin hiện tại
    cout << "\n===== THÔNG TIN CÁ NHÂN HIỆN TẠI =====\n";
    
    string fullName = userInfo.contains("FullName") ? userInfo["FullName"].get<string>() : "";
    string gender = userInfo.contains("Gender") ? userInfo["Gender"].get<string>() : "";
    string email = userInfo.contains("Email") ? userInfo["Email"].get<string>() : "";
    string phone = userInfo.contains("Phone") ? userInfo["Phone"].get<string>() : "";
    string address = userInfo.contains("Address") ? userInfo["Address"].get<string>() : "";
    string birthday = userInfo.contains("Birthday") ? userInfo["Birthday"].get<string>() : "";
    
    cout << "Họ và tên: " << fullName << endl;
    cout << "Giới tính: " << gender << endl;
    cout << "Email: " << email << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Địa chỉ: " << address << endl;
    cout << "Ngày sinh: " << birthday << endl;
    
    cout << "\n===== CHỈNH SỬA THÔNG TIN =====\n";
    cout << "Nhấn Enter để giữ nguyên thông tin cũ\n\n";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // String để lưu mô tả các thay đổi
    string changeDescription = "Các thay đổi thông tin của bạn:\n";
    bool hasChanges = false;

    // Chỉnh sửa họ tên
    string newFullName;
    cout << "Họ và tên mới: ";
    getline(cin, newFullName);
    
    if (!newFullName.empty()) {
        regex fullNamePattern("^[A-Za-zÀ-Ỹà-ỹ\\s]{2,50}$");
        if (!regex_match(newFullName, fullNamePattern)) {
            cout << "Họ tên không hợp lệ! Chỉ chứa chữ cái và dấu cách, từ 2-50 ký tự.\n";
        } else {
            changeDescription += "- Họ và tên: " + fullName + " -> " + newFullName + "\n";
            newInfo["FullName"] = newFullName;
            hasChanges = true;
        }
    }

    // Chỉnh sửa giới tính
    cout << "Giới tính mới (Nam/Nữ): ";
    string newGender;
    getline(cin, newGender);
    
    if (!newGender.empty()) {
        if (newGender != "Nam" && newGender != "Nữ") {
            cout << "Giới tính không hợp lệ! Chỉ chấp nhận 'Nam' hoặc 'Nữ'.\n";
        } else {
            changeDescription += "- Giới tính: " + gender + " -> " + newGender + "\n";
            newInfo["Gender"] = newGender;
            hasChanges = true;
        }
    }

    // Chỉnh sửa số điện thoại
    cout << "Số điện thoại mới: ";
    string newPhone;
    getline(cin, newPhone);
    
    if (!newPhone.empty()) {
        regex phonePattern("^[0-9]{0,16}$");
        if (!regex_match(newPhone, phonePattern)) {
            cout << "Số điện thoại không hợp lệ! Chỉ chứa số, tối đa 16 ký tự.\n";
        } else {
            changeDescription += "- Số điện thoại: " + phone + " -> " + newPhone + "\n";
            newInfo["Phone"] = newPhone;
            hasChanges = true;
        }
    }

    // Chỉnh sửa địa chỉ
    cout << "Địa chỉ mới: ";
    string newAddress;
    getline(cin, newAddress);
    
    if (!newAddress.empty()) {
        if (newAddress.length() > 255) {
            cout << "Địa chỉ không hợp lệ! Tối đa 255 ký tự.\n";
        } else {
            changeDescription += "- Địa chỉ: " + address + " -> " + newAddress + "\n";
            newInfo["Address"] = newAddress;
            hasChanges = true;
        }
    }

    // Chỉnh sửa ngày sinh
    cout << "Ngày sinh mới (dd/mm/yyyy): ";
    string newBirthday;
    getline(cin, newBirthday);
    
    if (!newBirthday.empty()) {
        regex datePattern(R"(^\d{2}/\d{2}/\d{4}$)");
        if (!regex_match(newBirthday, datePattern)) {
            cout << "Định dạng ngày sinh không hợp lệ! Vui lòng nhập theo định dạng dd/mm/yyyy.\n";
        } else {
            // Tách ngày, tháng, năm
            int day, month, year;
            if (sscanf(newBirthday.c_str(), "%d/%d/%d", &day, &month, &year) != 3 || !isValidDate(day, month, year)) {
                cout << "Ngày sinh không hợp lệ! Vui lòng nhập lại.\n";
            } else {
                changeDescription += "- Ngày sinh: " + birthday + " -> " + newBirthday + "\n";
                newInfo["Birthday"] = newBirthday;
                hasChanges = true;
            }
        }
    }

    // Email không được phép thay đổi vì là định danh chính
    cout << "Email không thể thay đổi vì đây là định danh chính của tài khoản.\n";

    // Nếu không có thay đổi, thông báo và thoát
    if (!hasChanges) {
        cout << "Không có thông tin nào được thay đổi!\n";
        return;
    }

    // Nếu có thay đổi, gửi OTP để xác nhận
    cout << "\nĐể xác nhận thay đổi thông tin, chúng tôi cần gửi mã OTP đến email của bạn.\n";
    cout << "Gửi OTP đến " << email << "? (y/n): ";
    
    string confirm;
    getline(cin, confirm);
    
    if (confirm != "y" && confirm != "Y") {
        cout << "Bạn đã hủy quá trình cập nhật thông tin.\n";
        return;
    }

    // Tạo và gửi OTP
    string otp = generateOTP();
    cout << "Đang gửi mã OTP...\n";
    
    if (!sendOTPEmail(email, otp, changeDescription)) {
        cout << "Không thể gửi mã OTP. Vui lòng thử lại sau!\n";
        return;
    }
    
    cout << "Mã OTP đã được gửi đến email của bạn.\n";
    cout << "Vui lòng nhập mã OTP để hoàn tất cập nhật thông tin: ";
    
    string inputOTP;
    getline(cin, inputOTP);
    
    if (verifyOTP(inputOTP, otp)) {
        // Cập nhật thông tin
        if (updateUserInfo(username, newInfo)) {
            cout << "Cập nhật thông tin thành công!\n";
        } else {
            cout << "Đã xảy ra lỗi khi cập nhật thông tin. Vui lòng thử lại sau!\n";
        }
    } else {
        cout << "Mã OTP không chính xác. Quá trình cập nhật đã bị hủy.\n";
    }
}

// Cập nhật thông tin người dùng sau khi xác thực OTP thành công
bool updateUserInfo(const string& username, const json& newInfo) {
    try {
        saveUserInfo(username, const_cast<json&>(newInfo));
        return true;
    } catch (const exception& e) {
        cerr << "Lỗi khi cập nhật thông tin: " << e.what() << endl;
        return false;
    }
}