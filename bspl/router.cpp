#ifndef ROUTER_CPP
#define ROUTER_CPP

#include "router.h"
#include "../util.h"

RouterBSPL::RouterBSPL(): prefixTable(IPV4_BIT_LENGTH + 1) {}

void RouterBSPL::insertPrefix(const std::string &ip, int maskLen, const std::string &routeName){
  std::string prefixIP = ipToBinary(ip).substr(0, maskLen);
  Entry entry = {prefixIP, true, prefixIP, routeName};
  prefixTable[maskLen][prefixIP] = entry;
}

void RouterBSPL::insertImgEntries(){
  std::string lastReal;
  for(int len = 1; len <= IPV4_BIT_LENGTH; ++len){
    for(int i = 0; i< (1 << len); ++i)
    {
        std::bitset<32> bits(i);
        std::string prefix = bits.to_string().substr(32-len, len);
        if(prefixTable[len].find(prefix) == prefixTable[len].end())
        {
          // no real IP having 'prefix' as prefix with length len
          if(!lastReal.empty())
          {
             Entry imaginary = {prefix, false, lastReal, ""};
             prefixTable[len][prefix] = imaginary;
          }
        }else if(prefixTable[len][prefix].isReal){
          lastReal = prefixTable[len][prefix].prefix;
        }
    }
  }
}

std::string RouterBSPL::findBSPLmatch(const std::string &ip){
  std::string binaryIP = ipToBinary(ip);
  int low = 0, high = IPV4_BIT_LENGTH;
  std::string bestMatch = "";
  std::string bestRouter = "";

  while(low <= high){
    int mid = (low + high)/2; 
    std::string prefix = binaryIP.substr(0, mid);
    if(prefixTable[mid].find(prefix) != prefixTable[mid].end())
    {
       Entry &entry = prefixTable[mid][prefix];
       if(entry.isReal)
       {
         bestMatch = entry.prefix;
         bestRouter = entry.routeName;
         low = mid + 1; // try longer match in right half
       }else{
        // imaginary entry, fallback to LSF
        if(prefixTable[entry.lsfPrefix.length()].count(entry.lsfPrefix))
        {
           Entry &lsfEntry = prefixTable[entry.lsfPrefix.length()][entry.lsfPrefix];
           bestMatch = lsfEntry.prefix;
           bestRouter = lsfEntry.routeName;
        }
        high = mid - 1;
       }
    }else{
      high = mid - 1;
    }
  }
  return bestRouter;
}

#endif