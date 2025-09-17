//
// Created by Marat on 7.09.25.
//

#pragma once
#include <QThread>

template <typename T>
void SelectionSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                                 std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                                 const std::atomic_bool& stopRequested) const {

    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if (stopRequested) return;
        size_t minIndex = i;

        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (stopRequested) return;
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
                QThread::msleep(delayMs);
            }
        }

        if (minIndex != i) {
            std::swap(vec[i], vec[minIndex]);
            stepCallBack(vec, i, minIndex);
        }
    }
}
