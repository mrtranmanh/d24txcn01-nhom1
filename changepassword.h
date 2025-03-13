#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <string>
#include "lib/json.hpp"

using json = nlohmann::json;

void changePassword(const std::string& username);

#endif
