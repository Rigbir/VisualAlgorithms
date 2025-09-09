//
// Created by Marat on 7.09.25.
//

#pragma once
#include <QWidget>
#include <vector>

class SortCanvas : public QWidget {
    Q_OBJECT

public:
    explicit SortCanvas(QWidget* parent = nullptr);

    void setData(const std::vector<int>& vec, int i1 = -1, int i2 = -1, bool sorted = false);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    std::vector<int> data;
    int compareIndex1 = -1;
    int compareIndex2 = -1;
    bool isSorted = false;
};

