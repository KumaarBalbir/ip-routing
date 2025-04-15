#include <iostream>
#include "../util.h"
#include "router.cpp"
#include <chrono>

using namespace std;
int main()
{ 

  RouterBSPL router;
  std::string filename = "../data.csv";
  std::vector<std::pair<std::string, std::string>> data = read_csv(filename);
  for(const auto &entry : data){
    std::string ip_prefix = entry.first;
    std::string router_name = entry.second;
    
    // Split the IP prefix into IP and subnet mask
    std::pair<std::string, std::string> ip_mask = split_ip_prefix(ip_prefix);
    std::string ip = ip_mask.first;
    std::string mask = ip_mask.second;
    
    router.insertPrefix(ip, std::stoi(mask), router_name);
  }
  cout<<"before insert img entries"<<endl;
  router.insertImgEntries();
  cout<<"after insert img entries"<<endl;

  std::string testIP = "192.168.20.191";
  // timer start
  auto start = std::chrono::high_resolution_clock::now();
  std::string routerName = router.findBSPLmatch(testIP);
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  if(!routerName.empty()){
    std::cout << "Best router for IP " << testIP << " is: " << routerName << std::endl;
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
  }else{
    std::cout << "No route found for IP " << testIP << std::endl;
  }
   
}