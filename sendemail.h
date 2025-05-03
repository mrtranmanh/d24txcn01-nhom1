#ifndef SENDEMAIL_H
#define SENDEMAIL_H

#include <iostream>
#include <fstream>

using namespace std;

// Ham chung de gui email
bool sendEmail(const string& recipient, const string& subject, const string& body);

// Gui email thong bao khi dang ky tai khoan
bool sendRegistrationSuccessEmail(const string& recipient, const string& username);

// Gui email dat lai mat khau khi su dung chuc nang quen mat khau
// bool sendPasswordResetEmail(const string& recipient, const string& resetToken);

#endif