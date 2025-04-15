#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <utility> // for std::pair
#include <bitset>
std::vector<std::pair<std::string, std::string>> read_csv(std::string filename)
{
  std::vector<std::pair<std::string, std::string>> data;
  std::ifstream file(filename);
  std::string line;
  if (!file.is_open())
  {
    std::cout << "Error opening file: " << filename << std::endl;
    return data;
  }
  // Skip the header line
  if (std::getline(file, line))
  {
  }
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    std::string ip_prefix, router_name;
    std::getline(ss, ip_prefix, ',');
    std::getline(ss, router_name, ',');
    data.push_back(std::make_pair(ip_prefix, router_name));
  }
  file.close();
  return data;
}

std::pair<std::string, std::string> split_ip_prefix(std::string ip_prefix)
{
  std::pair<std::string, std::string> result;
  std::stringstream ss(ip_prefix);
  std::string ip, mask;
  std::getline(ss, ip, '/');
  std::getline(ss, mask, '/');
  result.first = ip;
  result.second = mask;
  return result;
}

std::string decToBinary(const std::string &segment)
{
  int num = std::stoi(segment);
  std::bitset<8> bits(num);
  return bits.to_string();
}

std::string ipToBinary(const std::string &ip)
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
#endif