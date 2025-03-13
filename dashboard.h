#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include "lib/json.hpp"

using json = nlohmann::json;

void showDashboard(const std::string& username, json& userData, const json& userInfo);

#endif
