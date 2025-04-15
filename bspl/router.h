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

class RouterBSPL{
  private:
  std::vector<std::unordered_map<std::string, Entry>> prefixTable;
  public:
  RouterBSPL();
  void insertPrefix(const std::string &ip, int maskLen, const std::string &routeName);
  void insertImgEntries();
  std::string findBSPLmatch(const std::string &ip);
};

#endif 