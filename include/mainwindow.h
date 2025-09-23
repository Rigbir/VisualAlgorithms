//
// Created by Marat on 7.09.25.
//

#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QThread>

#include "SortCanvas.h"
#include "SortAlgorithm.h"
#include "BubbleSort.h"
#include "OddEvenSort.h"
#include "GnomeSort.h"
#include "ShellSort.h"
#include "RadixSort.h"
#include "CountingSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "SelectionSort.h"
#include "ShakerSort.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

    void initButtons();
    void buttonsGroup();
    void switchSorter(SortAlgorithm<int>* sorter);

    ~MainWindow();

private slots:
    void onStartButton();
    void onShuffleButton();
    void onStopButton();
    void onArraySizeChanges(size_t size);
    void onDelayChanges(size_t delay);

private:
    SortCanvas* canvas;
    QThread* sortThread = nullptr;

    SortAlgorithm<int>* currentSorter = nullptr;
    BubbleSort<int>     bubbleSorter;
    CountingSort<int>   countingSorter;
    OddEvenSort<int>    oddEvenSorter;
    GnomeSort<int>      gnomeSorter;
    ShellSort<int>      shellSorter;
    RadixSort<int>      radixSorter;
    HeapSort<int>       heapSorter;
    InsertionSort<int>  insertionSorter;
    MergeSort<int>      mergeSorter;
    QuickSort<int>      quickSorter;
    SelectionSort<int>  selectionSorter;
    ShakerSort<int>     shakerSorter;

    QPushButton* startButton;
    QPushButton* shuffleButton;
    QPushButton* stopButton;

    int delayMs = 10;
    std::atomic_bool stopRequested = false;
    std::vector<int> data;

    void updateCanvas();
    void shuffleData(size_t size);

    Ui::MainWindow* ui;
};
