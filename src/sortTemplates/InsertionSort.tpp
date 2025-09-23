//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template<typename T>
void InsertionSort<T>::sortedVec(std::vector<T>& vec, int& delayMs,
                                 std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                                 const std::atomic_bool& stopRequested) const {

    for (size_t i = 1; i < vec.size(); ++i) {
        if (stopRequested) return;
        T key = vec[i];
        size_t j = i - 1;

        while (j >= 0 && vec[j] > key) {
            if (stopRequested) return;
            vec[j + 1] = vec[j];
            --j;
            stepCallBack(vec, j + 1, j);
            QThread::msleep(delayMs);
        }

        vec[j + 1] = key;
    }
}
