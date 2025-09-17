//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template<typename T>
void CountingSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                                std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                                const std::atomic_bool& stopRequested) const {

    T minElement = *std::min_element(vec.begin(), vec.end());
    T maxElement = *std::max_element(vec.begin(), vec.end());

    size_t range = maxElement - minElement + 1;
    std::vector<T> count(range, 0);

    for (const auto x : vec) {
        ++count[x - minElement];
    }

    size_t j = 0;
    for (int i = 0; i < range; ++i) {
        if (stopRequested) return;
        while (count[i] > 0) {
            if (stopRequested) return;
            vec[j] = i + minElement;
            stepCallBack(vec, i + minElement, j);
            QThread::msleep(delayMs);
            ++j;
            --count[i];
        }
    }
}
