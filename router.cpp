#ifndef ROUTER_CPP
#define ROUTER_CPP

#include "router.h"

Route::Route(const std::string &routeName, const std::string &ip, int mask)
    : routeName(routeName), ipAddress(ip), subnetMask(mask) {}

std::string Route::getRouteName() const
{
  return routeName;
}

std::string Route::getIPAddress() const
{
  return ipAddress;
}
int Route::getSubnetMask() const
{
  return subnetMask;
}
#endif // ROUTER_CPP