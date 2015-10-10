//
// Created by roberts on 2015-10-09.
//

#ifndef ENTITY_FRAMEWORK_BITSETUTILITY_H
#define ENTITY_FRAMEWORK_BITSETUTILITY_H

#include <bitset>

using std::bitset;

class BitSetUtility
{
private:
    BitSetUtility() {}

public:
    static bool containsAll(bitset<32>& source, bitset<32>& other)
    {
        size_t count = other.count();
        bitset<32> result = source & other;

        return result.count() == count;
    }

    static bool intersects(bitset<32>& source, bitset<32>& other)
    {
        bitset<32> result = source & other;
        return result.any();
    }
};


#endif //ENTITY_FRAMEWORK_BITSETUTILITY_H

