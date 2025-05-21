#include "sendemail.h"

bool sendEmail(const string& recipient, const string& subject, const string& body) {
    string email_sender = "mr.taduma@gmail.com";  // Thông tin email
    string email_password = "lrvbktjtoqhhcdig";  // Thay bằng mật khẩu ứng dụng
    string smtp_server = "smtp.gmail.com";
    string smtp_port = "587";

    // Tạo nội dung email
    ofstream emailFile("email.txt");
    emailFile << "To: " << recipient << "\n";
    emailFile << "Subject: " << subject << "\n\n";
    emailFile << body << "\n";
    emailFile.close();

    // Lệnh gửi email bằng cURL
    string command = "curl --url \"smtp://" + smtp_server + ":" + smtp_port + "\" --ssl-reqd "
                     "--mail-from \"" + email_sender + "\" "
                     "--mail-rcpt \"" + recipient + "\" "
                     "--user \"" + email_sender + ":" + email_password + "\" "
                     "-T email.txt";

    // Thực thi lệnh
    int result = system(command.c_str());

    return (result == 0);  // Trả về true nếu gửi thành công
}

// Gửi email xác nhận đăng ký
bool sendRegistrationSuccessEmail(const string& recipient, const string& username) {
    string subject = "Chào mừng bạn đã đăng ký tài khoản!";
    string body = "Xin chào " + username + ",\n\n"
                  "Chúc mừng bạn đã đăng ký tài khoản thành công!\n"
                  "Hãy sử dụng tài khoản này để đăng nhập và trải nghiệm dịch vụ của chúng tôi.\n\n"
                  "Trân trọng,\nĐội ngũ hỗ trợ";

    return sendEmail(recipient, subject, body);
}

// Gửi email OTP cho việc thay đổi thông tin
bool sendOTPForInfoChange(const string& recipient, const string& otp, const string& changes) {
    string subject = "Mã xác thực OTP cho thay đổi thông tin";
    string body = "Xin chào,\n\n"
                  "Bạn đã yêu cầu thay đổi thông tin cá nhân.\n\n"
                  + changes + "\n\n"
                  "Mã OTP của bạn là: " + otp + "\n\n"
                  "Mã này có hiệu lực trong 5 phút. Nếu bạn không thực hiện yêu cầu này, vui lòng bỏ qua email này.\n\n"
                  "Trân trọng,\nĐội ngũ hỗ trợ";
    return sendEmail(recipient, subject, body);
}
// Gửi email thông báo thay đổi thông tin thành công
bool sendInfoChangeSuccessEmail(const string& recipient, const string& username) {
    string subject = "Thay đổi thông tin tài khoản thành công";
    string body = "Xin chào " + username + ",\n\n"
                  "Thông tin tài khoản của bạn đã được cập nhật thành công!\n"
                  "Nếu bạn không thực hiện thay đổi này, vui lòng liên hệ ngay với đội hỗ trợ.\n\n"
                  "Trân trọng,\nĐội ngũ hỗ trợ";
    return sendEmail(recipient, subject, body);
}


// Gửi email đặt lại mật khẩu
// bool sendPasswordResetEmail(const string& recipient, const string& resetToken) {
//     string subject = "Yêu cầu đặt lại mật khẩu";
//     string body = "Xin chào,\n\n"
//                   "Chúng tôi nhận được yêu cầu đặt lại mật khẩu của bạn.\n"
//                   "Vui lòng nhấp vào liên kết dưới đây để đặt lại mật khẩu:\n\n"
//                   "https://yourwebsite.com/reset-password?token=" + resetToken + "\n\n"
//                   "Nếu bạn không yêu cầu, vui lòng bỏ qua email này.\n\n"
//                   "Trân trọng,\nĐội ngũ hỗ trợ";

//     return sendEmail(recipient, subject, body);
// }
