#ifndef ROUTER_H 
#define ROUTER_H

#include <string>
#include <unordered_map> // hash table
#include <vector>

const int IPV4_BIT_LENGTH = 32;

struct Entry{
  std::string prefix; // actual binary prefix of ip
  bool isReal; // true if original prefix, false if imaginary
  std::string lsfPrefix; // holds longest so far prefix
  std::string routeName;
};







#endif 