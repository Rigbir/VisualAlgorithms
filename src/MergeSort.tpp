//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>
#include <iterator>

template <typename T>
void MergeSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                             std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const {
    mergeSort(vec.begin(), vec.end(), vec, delayMs, stepCallBack);
}

template <typename T>
template <typename RandomIterator>
void MergeSort<T>::mergeSort(RandomIterator begin, RandomIterator end, std::vector<T>& vec, int delayMs,
                             std::function<void(std::vector<T>&, int i, int j)> stepCallBack) {

    if (std::next(begin) == end) return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(begin, mid, vec, delayMs, stepCallBack);
    mergeSort(mid, end, vec, delayMs, stepCallBack);

    using ValueType = typename std::iterator_traits<RandomIterator>::value_type;
    std::vector<ValueType> temp;
    temp.reserve(end - begin);

    merge(begin, mid, mid, end, std::back_inserter(temp));

    std::move(temp.begin(), temp.end(), begin);

    if (stepCallBack) {
        int i = static_cast<int>(begin - vec.begin());
        int j = static_cast<int>(end - vec.begin() - 1);
        stepCallBack(vec, i, j);
        QThread::msleep(delayMs);
    }
}

template <typename T>
template <typename RandomIterator, typename OutputIterator>
void MergeSort<T>::merge(RandomIterator firstBegin, RandomIterator firstEnd,
                         RandomIterator secondBegin, RandomIterator secondEnd,
                         OutputIterator result) {
    while (firstBegin != firstEnd && secondBegin != secondEnd) {
        if (*firstBegin < *secondBegin) {
            *result = *firstBegin;
            ++firstBegin;
        } else {
            *result = *secondBegin;
            ++secondBegin;
        }
        ++result;
    }

    while (firstBegin != firstEnd) {
        *result = *firstBegin;
        ++firstBegin;
        ++result;
    }

    while (secondBegin != secondEnd) {
        *result = *secondBegin;
        ++secondBegin;
        ++result;
    }
}
