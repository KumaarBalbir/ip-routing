#ifndef ROUTER_CPP
#define ROUTER_CPP

#include "router.h"
#include <sstream>
#include <bitset>

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

std::string IPTrie::decToBinary(const std::string &segment)
{
  int num = std::stoi(segment);
  std::bitset<8> bits(num);
  return bits.to_string();
}

std::string IPTrie::ipToBinary(const std::string &ip)
{
  std::stringstream ss(ip);
  std::string segment;
  std::string binary;

  for (int i = 0; i < 4; i++)
  {
    std::getline(ss, segment, '.');
    binary += decToBinary(segment);
  }

  return binary;
}
void IPTrie::insert(Route *route)
{
  std::string binaryIP = ipToBinary(route->getIPAddress());
  int maskLen = route->getSubnetMask();

  TrieNode *current = root;

  // Insert only up to the subnet mask length
  for (int i = 0; i < maskLen; i++)
  {
    int bit = binaryIP[i] - '0';

    if (current->children[bit] == nullptr)
    {
      current->children[bit] = new TrieNode();
    }

    current = current->children[bit];
  }

  // Store route information at the node
  current->route = route;
}
Route* IPTrie::findLongestPrefixMatch(const std::string& ip) {
    std::string binaryIP = ipToBinary(ip);
    
    TrieNode* current = root;
    Route* matchedRoute = nullptr;
    
    for (int i = 0; i < 32 && current != nullptr; i++) {
        if (current->route != nullptr) {
            matchedRoute = current->route;
        }
        int bit = binaryIP[i] - '0';
        current = current->children[bit];
    }
    
    // Check the final node
    if (current && current->route != nullptr) {
        matchedRoute = current->route;
    }
    
    return matchedRoute;
}
void IPTrie::deleteTrie()
{
  delete root;
  root = nullptr;
}
void IPTrie::deleteRoute()
{
  delete root->route;
  root->route = nullptr;
}
#endif // ROUTER_CPP