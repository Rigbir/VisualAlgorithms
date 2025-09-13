//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template<typename T>
void OddEvenSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                               std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const {

    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        for (size_t i = 1; i + 1 < vec.size(); i += 2) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                isSorted = false;
                stepCallBack(vec, i, i + 1);
                QThread::msleep(delayMs);
            }
        }

        for (size_t i = 0; i + 1 < vec.size(); i += 2) {
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                isSorted = false;
                stepCallBack(vec, i, i + 1);
                QThread::msleep(delayMs);
            }
        }
    }
}
