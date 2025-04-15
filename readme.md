### IP Routing Algorithms Implementation
Implements two different approaches for IP routing table lookups:

#### 1. Longest Prefix Match (LPM) using Trie
- Uses a binary trie data structure where each node represents a bit
- Each path from root to node represents an IP prefix
- Time Complexity: O(W) where W is the length of IP address in bits (32 for IPv4)
- Space Complexity: O(N*W) where N is number of routes

#### 2. Binary Search on Prefix Length (BSPL)
- Performs binary search on possible prefix lengths
- Maintains separate tables for each prefix length
- Time Complexity: O(log W) where W is the length of IP address
- Space Complexity: O(N) where N is number of routes

### Usage
```bash
# For LPM Trie implementation
cd lpm
g++ lpm.cpp -o lpm
./lpm

# For BSPL implementation
cd bspl
g++ bspl.cpp -o bspl
./bspl
```

### Input Format
The routing table should be in CSV format:
```
ip_prefix,router_name
192.168.20.16/28,Router1
192.168.0.0/16,Router2
192.168.1.0/24,Router3
10.10.0.0/16,Router4
```
