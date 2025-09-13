//
// Created by Marat on 8.09.25.
//

#pragma once
#include <QThread>

template <typename T>
void ShellSort<T>::sortedVec(std::vector<T>& vec, int delayMs,
                             std::function<void(std::vector<T>&, int i, int j)> stepCallBack) const {

    for (int gap = vec.size() / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < vec.size(); ++i) {
            int temp = vec[i];
            int j;

            for (j = i; j >= gap && vec[j - gap] > temp; j -= gap) {
                vec[j] = vec[j - gap];
                stepCallBack(vec, j, j - gap);
                QThread::msleep(delayMs);
            }
            vec[j] = temp;
        }
    }
}
