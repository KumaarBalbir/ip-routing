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
TrieNode::TrieNode()
{
  children[0] = nullptr;
  children[1] = nullptr;
  route = nullptr;
}
TrieNode::~TrieNode()
{
  delete children[0];
  delete children[1];
}
IPTrie::IPTrie()
{
  root = new TrieNode();
}
IPTrie::~IPTrie()
{
  delete root;
}
#endif // ROUTER_CPP