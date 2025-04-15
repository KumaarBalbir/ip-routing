#include <iostream>
#include <string>

#include "router.cpp"
#include "util.h"
using namespace std;
int main()
{
  IPTrie trie;

  std::string filename = "data.csv";
  std::vector<std::pair<std::string, std::string>> data = read_csv(filename);
  for (const auto &entry : data)
  {
    std::string ip_prefix = entry.first;
    std::string router_name = entry.second;

    // Split the IP prefix into IP and subnet mask
    std::pair<std::string, std::string> ip_mask = split_ip_prefix(ip_prefix);
    std::string ip = ip_mask.first;
    std::string mask = ip_mask.second;

    Route *route = new Route(router_name, ip, std::stoi(mask));
    trie.insert(route);
  }
  Route *match = trie.findLongestPrefixMatch("192.168.20.191");
  if (match)
  {
    std::cout << "192.168.20.191 routes to: " << match->getRouteName() << std::endl;
  }
  else
  {
    std::cout << "No route found for IP" << std::endl;
  }
}