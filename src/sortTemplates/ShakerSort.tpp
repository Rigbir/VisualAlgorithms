//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template <typename T>
void ShakerSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                              std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                              const std::atomic_bool& stopRequested) const {

    bool sort = true;
    size_t left = 0;
    size_t right = vec.size() - 1;

    while (sort) {
        if (stopRequested) return;
        sort = false;

        for (size_t i = left; i < right; ++i) {
            if (stopRequested) return;
            if (vec[i] > vec[i + 1]) {
                std::swap(vec[i], vec[i + 1]);
                sort = true;
                stepCallBack(vec, i, i + 1);
                QThread::msleep(delayMs);
            }
        }
        --right;

        if (!sort) break;
        sort = false;

        for (size_t i = right; i > left; --i) {
            if (stopRequested) return;
            if (vec[i - 1] > vec[i]) {
                std::swap(vec[i - 1], vec[i]);
                sort = true;
                stepCallBack(vec, i - 1, i);
                QThread::msleep(delayMs);
            }
        };
        ++left;
    }
}
