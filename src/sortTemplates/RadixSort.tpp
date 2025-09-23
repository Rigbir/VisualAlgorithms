//
// Created by Marat on 7.09.25.
//

#pragma once
#include <QThread>
#include <climits>
#include <algorithm>
#include <atomic>

template<typename T>
void RadixSort<T>::sortedVec(std::vector<T>& vec, int& delayMs,
                              std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                              const std::atomic_bool& stopRequested) const {

    T maxEl = *std::max_element(vec.begin(), vec.end());

    for (int exp = 1; maxEl / exp > 0; exp *= 10) {
        counting(vec, exp, stepCallBack, delayMs, stopRequested);
        if (stopRequested) return;
    }
}

template<typename T>
void RadixSort<T>::counting(std::vector<T>& vec, int exp,
                            std::function<void(std::vector<T>&, int, int)> stepCallBack,
                            int& delayMs,
                            const std::atomic_bool& stopRequested) const {

    std::vector<T> output(vec.size());
    int count[10] = {0};

    for (int i = 0; i < vec.size(); ++i){
        int digit = (vec[i] / exp) % 10;
        ++count[digit];
        if (stopRequested) return;
    }

    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = vec.size() - 1; i >= 0; --i){
        int digit = (vec[i] / exp) % 10;
        output[count[digit] - 1] = vec[i];
        --count[digit];

        stepCallBack(output, i, count[digit]);
        QThread::msleep(delayMs);
        if (stopRequested) return;
    }

    vec = output;
}
