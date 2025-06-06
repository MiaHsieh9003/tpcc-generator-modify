#pragma once

#include <cstdint>
#include <string>
#include <random>
#include <vector>

#define NODE4   1
#define NODE10  5
// #define NODE16  2
#define NODE48  3
#define NODE256 4

class TpccGenerator {
   const static uint32_t kItemCount = 100000;
   const static uint32_t kCustomerPerDistrict = 3000;
   const static uint32_t kDistrictsPerWarehouse = 10;
   const static uint32_t OrdersPerDistrict = 3000;

   // If these are different the order generation needs to be changed.
   // Right now there is a 1:1 relationship between customers and orders.
   static_assert(kCustomerPerDistrict == OrdersPerDistrict, "These should match, see comment.");

   const int64_t warehouse_count;
   const std::string folder;
   std::vector<std::vector<char>> seq4;
   std::vector<std::vector<char>> seq10;
   std::vector<std::vector<char>> seq48;
   std::mt19937 ranny;
   int type = NODE48; // Example type, can be changed to NODE10, NODE48, etc.

   uint32_t makeAlphaString(uint32_t min, uint32_t max, char *dest);
   uint32_t makeAlphaString(uint32_t min, uint32_t max, char *dest, uint32_t type);
   void initialNodeElementSource(uint32_t max, uint32_t type);
   void makeNode4ElementSource(uint32_t max);
   void makeNode10ElementSource(uint32_t max);
   void makeNode48ElementSource(uint32_t max);
   uint32_t makeNumberString(uint32_t min, uint32_t max, char *dest);
   uint32_t makeNumber(uint32_t min, uint32_t max);
   uint32_t makeNonUniformRandom(uint32_t A, uint32_t x, uint32_t y);
   std::vector<uint32_t> makePermutation(uint32_t min, uint32_t max);
   void makeAddress(char *str1, char *street2, char *city, char *state, char *zip);
   void makeLastName(int64_t num, char *name);
   void makeNow(char *str);

public:
   TpccGenerator(int64_t warehouse_count, const std::string &folder);

   void setRandomSeed(uint32_t seed) { ranny.seed(seed); }

   void generateWarehouses();
   void generateDistricts();
   void generateCustomerAndHistory();
   void generateItems();
   void generateStock();
   void generateOrdersAndOrderLines();
};