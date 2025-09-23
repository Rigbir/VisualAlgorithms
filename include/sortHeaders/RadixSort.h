//
// Created by Marat on 7.09.25.
//

#pragma once
#include "SortAlgorithm.h"

template <typename T>
class RadixSort final : public SortAlgorithm<T> {
public:
    void sortedVec(std::vector<T>& vec, int& delayMs,
                   std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                   const std::atomic_bool& stopRequested) const override;

private:
    void counting(std::vector<T>& vec, int exp,
                  std::function<void(std::vector<T>&, int, int)> stepCallBack,
                  int& delayMs,
                  const std::atomic_bool& stopRequested) const;
};

#include "RadixSort.tpp"
