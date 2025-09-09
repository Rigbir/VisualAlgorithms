//
// Created by Marat on 7.09.25.
//

#pragma once
#include <QThread>

template<typename T>
void BubbleSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                              std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const {

    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = 0; j < vec.size() - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                stepCallBack(vec, j, j + 1);
                QThread::msleep(delayMs);
            }
        }
    }
}
