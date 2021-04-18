#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
int version();
using ip_str_t = std::vector<std::string>;
using ip_t = std::vector<int>;
using ip_pool_t = std::vector<ip_t>;
ip_str_t split(const std::string &str, char d);
ip_t strToInt(const ip_str_t &str_ip);

void sort(ip_pool_t &ip_pool); 
void print(const ip_pool_t &ip_pool); 

ip_pool_t filter(const ip_pool_t &ip_pool, int part); 
ip_pool_t filter(const ip_pool_t &ip_pool, int part1, int part2); 
ip_pool_t filter_any(const ip_pool_t &ip_pool, int part); 