//
// Created by Marat on 7.09.25.
//

#pragma once
#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class SortAlgorithm {
public:
    virtual void sortedVec(std::vector<T>& vec, int delayMs,
                           std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const = 0;
    virtual ~SortAlgorithm() = default;
};
