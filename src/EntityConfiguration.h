#pragma once

// standard includes

#include <cstddef>
#include <bitset>
#include <memory>
#include <unordered_map>
#include <array>
#include <vector>
#include <utility>
#include <iostream>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;
using std::array;
using std::bitset;
using std::unordered_map;
using std::enable_shared_from_this;
using std::pair;
using std::make_pair;
using std::cout;
using std::endl;
using std::string;
using std::initializer_list;

// configuration
const size_t MAX_COMPONENTS = 32;

// typedefs
using ComponentBitSet = bitset<MAX_COMPONENTS>;
template<class T> using  vector_ptr = shared_ptr<vector<T>> ;