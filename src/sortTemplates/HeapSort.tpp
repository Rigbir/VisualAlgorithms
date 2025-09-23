//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template <typename T>
void HeapSort<T>::sortedVec(std::vector<T>& vec, int& delayMs,
                            std::function<void(std::vector<T>&, int i, int j)> stepCallBack,
                            const std::atomic_bool& stopRequested) const {

    for (int i = vec.size() / 2 - 1; i >= 0; --i) {
        if (stopRequested) return;
        heapify(vec, i, vec.size());
    }

    for (size_t i = vec.size() - 1; i > 0; --i) {
        if (stopRequested) return;
        std::swap(vec[0], vec[i]);
        heapify(vec, 0, i);
        stepCallBack(vec, 0, i);
        QThread::msleep(delayMs);
    }
}

template<typename T>
void HeapSort<T>::heapify(std::vector<T>& vec, size_t i, size_t size) const {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < size && vec[left] > vec[largest]) {
        largest = left;
    }

    if (right < size && vec[right] > vec[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(vec[i], vec[largest]);
        heapify(vec, largest, size);
    }
}



