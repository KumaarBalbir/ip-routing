#ifndef ROUTER_H
#define ROUTER_H

#include <string>
class Route
{
private:
  std::string routeName;
  std::string ipAddress;
  int subnetMask;

public:
  Route(const std::string &routeName, const std::string &ip, int mask);
  std::string getRouteName() const;
  std::string getIPAddress() const;
  int getSubnetMask() const;
};

class TrieNode
{
public:
  TrieNode *children[2];
  Route *route;
  TrieNode();
  ~TrieNode();
};

class IPTrie
{
private:
  TrieNode *root;
  std::string ipToBinary(const std::string &ip);

public:
  IPTrie();
  ~IPTrie();
  void insert(Route *route);
  Route *findLongestPrefixMatch(const std::string &ip);
  void deleteTrie();
  void deleteRoute();
};

#endif