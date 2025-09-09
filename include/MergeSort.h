//
// Created by Marat on 8.09.25.
//

#pragma once
#include "SortAlgorithm.h"

template <typename T>
class MergeSort final : public SortAlgorithm<T> {
public:
    void sortedVec(std::vector<T>& vec, int delayMs,
                   std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const override;

private:
    template <typename RandomIterator>
    static void mergeSort(RandomIterator begin, RandomIterator end, std::vector<T>& vec, int delayMs,
                          std::function<void(std::vector<T>&, int i, int j)> stepCallBack);

    template <typename RandomIterator, typename OutputIterator>
    static void merge(RandomIterator firstBegin, RandomIterator firstEnd,
                      RandomIterator secondBegin, RandomIterator secondEnd,
                      OutputIterator result);
};

#include "MergeSort.tpp"
