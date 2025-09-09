//
// Created by Marat on 7.09.25.
//

#include "SortCanvas.h"
#include <QPainter>

SortCanvas::SortCanvas(QWidget* parent): QWidget(parent) {}

void SortCanvas::setData(const std::vector<int>& vec, int i1, int i2, bool sorted) {
    data = vec;
    compareIndex1 = i1;
    compareIndex2 = i2;
    isSorted = sorted;
    update();
}

void SortCanvas::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.fillRect(rect(), QColor("#1E2227"));

    if (data.empty()) return;

    int w = width() / data.size();
    int maxVal = *std::max_element(data.begin(), data.end());

    for (size_t i = 0; i < data.size(); ++i) {
        int h = (height() * data[i]) / maxVal;

        QColor color = QColor("#808080");

        if (isSorted) {
            color = QColor("#A6E22E");
        } else if (i == compareIndex1 || i == compareIndex2) {
            color = QColor("#FF4444");
        }

        p.fillRect(i * w, height() - h, w - 2, h, color);
    }
}

