#ifndef MOLE_CONSTANT_H
#define MOLE_CONSTANT_H

#include <string>
#include <unordered_map>

namespace cs {
    constexpr double amu2au = 1822.888515;  
    constexpr double temp_au2si = 3.1577464e5; 
    constexpr double coor_au2A = 0.52917721092; 
    constexpr double time_au2fs = 2.418884326505e-2; 
    const std::unordered_map<std::string, double> amu_mass = {
        {"H", 1.007947}, {"He", 4.0026022}, {"C", 12.01078}, {"N", 14.00672},
        {"O", 15.99943}, {"F", 18.9984032}, {"P", 30.9737612}, {"S", 32.0655},
        {"Cl", 35.4532}
    };
    const std::unordered_map<std::string, int> atomic_number = {
        {"H", 1}, {"He", 2}, {"Li", 3}, {"Be", 4}, {"B", 5}, {"C", 6},
        {"N", 7}, {"O", 8}, {"F", 9}, {"Ne", 10}, {"Na", 11}, {"Mg", 12},
        {"Al", 13}, {"Si", 14}, {"P", 15}, {"S", 16}, {"Cl", 17}
    };
}

#endif // !MOLE_CONSTANT_H#pragma once
