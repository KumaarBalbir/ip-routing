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

#endif