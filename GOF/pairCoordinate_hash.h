#pragma once
#include <functional>
namespace std {
    template<>
    struct hash<pair<size_t, size_t>>
    {
        size_t operator()(const std::pair<size_t, size_t>& pair) const
        {
            return ((pair.first + pair.second) * (pair.first + pair.second + 1) / 2) + pair.second;
        }
    };

    template<>
    struct equal_to<pair<size_t, size_t>>
    {
        bool operator()(const std::pair<size_t, size_t>& fpair, const std::pair<size_t, size_t>& spair) const
        {
            return fpair.first == spair.first && fpair.second == spair.second;
        }
    };
}