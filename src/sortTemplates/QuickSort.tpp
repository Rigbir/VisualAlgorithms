//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template <typename T>
void QuickSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                             std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                             const std::atomic_bool& stopRequested) const {

    if (vec.size() <= 1) return;
    quick(vec, 0, vec.size() - 1, delayMs, stepCallBack, stopRequested);
}

template<typename T>
void QuickSort<T>::quick(std::vector<T>& vec, const int low, const int high, int delayMs,
                         std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                         const std::atomic_bool& stopRequested) const {
    if (low < high) {
        const size_t p = partition(vec, low, high, delayMs, stepCallBack, stopRequested);
        quick(vec, low, p - 1, delayMs, stepCallBack, stopRequested);
        quick(vec, p + 1, high, delayMs, stepCallBack, stopRequested);
    }
}

template <typename T>
int QuickSort<T>::partition(std::vector<T>& vec, const int low, const int high, int delayMs,
                            std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                            const std::atomic_bool& stopRequested) const {
    T pivot = vec[high];
    size_t i = low - 1;

    for (int j = low; j < high; ++j) {
        if (vec[j] <= pivot) {
            ++i;
            std::swap(vec[i], vec[j]);
            stepCallBack(vec, i, j);
        }
    }

    std::swap(vec[i + 1], vec[high]);
    stepCallBack(vec, i + 1, high);
    QThread::msleep(delayMs);
    return i + 1;
}

