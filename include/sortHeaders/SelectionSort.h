//
// Created by Marat on 7.09.25.
//

#pragma once
#include "SortAlgorithm.h"

template <typename T>
class SelectionSort final : public SortAlgorithm<T> {
public:
    void sortedVec(std::vector<T>& vec, int delayMs,
                   std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const override;
};

#include "SelectionSort.tpp"
