//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template<typename T>
void CountingSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                                std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const {

    std::vector<T> temp(vec.size() + 1, 0);

    T minElement = *std::min_element(vec.begin(), vec.end());
    T maxElement = *std::max_element(vec.begin(), vec.end());

    for (const auto x : vec) {
        ++temp[x];
    }

    for (size_t i = 1; i < temp.size(); ++i) {
        temp[i] += temp[i - i];
    }

    size_t j = 0;
    for (int i = minElement; i <= maxElement; ++i) {
        while (temp[i] > 0) {
           vec[j] = i;
            ++j;
            --temp[i];
            stepCallBack(vec, i, j);
            QThread::msleep(delayMs);
        }
    }
}
