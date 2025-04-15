#include <iostream>
#include <string>

#include "router.cpp"
#include "../util.h"
#include <chrono>
using namespace std;
int main()
{
  IPTrie trie;

  std::string filename = "../data.csv";
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
  std::string testIP = "192.168.20.191";
  // timer start
  auto start = std::chrono::high_resolution_clock::now();
  Route *match = trie.findLongestPrefixMatch(testIP);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  if(match){
    std::cout<< "Best router for IP " << testIP << " is: " << match->getRouteName() << std::endl;
    std::cout<< "Time taken: " << duration.count() << " microseconds" << std::endl;
  }else{
    std::cout<< "No route found for IP " << testIP << std::endl;
  }
}