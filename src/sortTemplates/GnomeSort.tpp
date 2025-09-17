//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template<typename T>
void GnomeSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                             std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                             const std::atomic_bool& stopRequested) const {

    size_t i = 0;
    while (i < vec.size()) {
        if (stopRequested) return;
        if (i == 0) {
            ++i;
        } else if (vec[i] >= vec[i - 1]) {
            ++i;
        } else {
            std::swap(vec[i], vec[i - 1]);
            stepCallBack(vec, i, i - 1);
            QThread::msleep(delayMs);
            --i;
        }
    }
}
