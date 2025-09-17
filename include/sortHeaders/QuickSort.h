//
// Created by Marat on 8.09.25.
//

#pragma once
#include "SortAlgorithm.h"

template <typename T>
class QuickSort final : public SortAlgorithm<T> {
public:
    void sortedVec(std::vector<T>& vec, int delayMs,
                   std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                   const std::atomic_bool& stopRequested) const override;

private:
    void quick(std::vector<T>& vec, int low, int high, int delayMs,
               std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
               const std::atomic_bool& stopRequested) const;

    int partition(std::vector<T>& vec, int low, int high, int delayMs,
                  std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const;
};

#include "QuickSort.tpp"
