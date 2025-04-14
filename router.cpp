#ifndef ROUTER_CPP
#define ROUTER_CPP

#include "router.h"

Route::Route(const std::string &routeName, const std::string &ip, int mask)
    : routeName(routeName), ipAddress(ip), subnetMask(mask) {}

#endif // ROUTER_CPP