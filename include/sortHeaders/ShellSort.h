//
// Created by Marat on 8.09.25.
//

#pragma once
#include "SortAlgorithm.h"

template <typename T>
class ShellSort final : public SortAlgorithm<T> {
public:
    void sortedVec(std::vector<T>& vec, int delayMs,
                   std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                   const std::atomic_bool& stopRequested) const override;
};

#include "ShellSort.tpp"
