#pragma once

// standard includes

#include <cstddef>
#include <bitset>
#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::vector;
using std::bitset;
using std::unordered_map;
using std::enable_shared_from_this;

// configuration
const size_t MAX_COMPONENTS = 32;

// typedefs
typedef bitset<MAX_COMPONENTS> ComponentBitSet;
