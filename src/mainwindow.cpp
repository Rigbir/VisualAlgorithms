//
// Created by Marat on 7.09.25.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QButtonGroup>
#include <random>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    canvas = new SortCanvas(ui->sortCanvasContainer);
    ui->sortCanvasContainer->layout()->addWidget(canvas);

    initButtons();
    buttonsGroup();
}

void MainWindow::updateCanvas() {
    canvas->setData(data);
    canvas->update();
}

void MainWindow::shuffleData(size_t size) {
    data.resize(size);
    std::iota(data.begin(), data.end(), 1);

    std::mt19937 rng(std::random_device{}());
    std::shuffle(data.begin(), data.end(), rng);

    ui->arrSizeLabel->setText(QString::number(size) + " bars");

    updateCanvas();
}

void MainWindow::onStartButton() {
    if (!currentSorter || data.empty()) return;

    stopRequested = false;
    ui->startBtn->setChecked(true);
    ui->stopBtn->setChecked(false);

    if (sortThread) return;

    sortThread = QThread::create([this]{
        currentSorter->sortedVec(data, delayMs,
            [this](const std::vector<int>& step, int i, int j) {
                QMetaObject::invokeMethod(canvas, [this, step, i, j]{
                    canvas->setData(step, i, j);
                });
            },
            stopRequested
        );

        if (!stopRequested) {
            QMetaObject::invokeMethod(canvas, [this]{
                canvas->setData(data, -1, -1, true);
            });
        }
    });

    connect(sortThread, &QThread::finished, sortThread, &QObject::deleteLater);
    connect(sortThread, &QThread::finished, [this]{ sortThread = nullptr; });

    sortThread->start();
}

void MainWindow::onShuffleButton() {
    shuffleData(ui->arrSizeSlider->value());
}

void MainWindow::onStopButton() {
    stopRequested = true;
    ui->stopBtn->setChecked(true);
    ui->startBtn->setChecked(false);
}

void MainWindow::onArraySizeChanges(size_t size) {
    shuffleData(size);
}

void MainWindow::onDelayChanges(size_t delay) {
    ui->delayLabel->setText(QString::number(delay) + " ms");
    this->delayMs = delay;
}

void MainWindow::initButtons() {
    connect(ui->startBtn,       &QPushButton::clicked,  this, &MainWindow::onStartButton);
    connect(ui->shuffleBtn,     &QPushButton::clicked,  this, &MainWindow::onShuffleButton);
    connect(ui->stopBtn,        &QPushButton::clicked,  this, &MainWindow::onStopButton);
    connect(ui->arrSizeSlider,  &QSlider::valueChanged, this, &MainWindow::onArraySizeChanges);
    connect(ui->delaySlider,    &QSlider::valueChanged, this, &MainWindow::onDelayChanges);

    connect(ui->bubbleBtn,      &QPushButton::clicked, this, [this](){ switchSorter(&bubbleSorter);    });
    connect(ui->selectionBtn,   &QPushButton::clicked, this, [this](){ switchSorter(&selectionSorter); });
    connect(ui->insertionBtn,   &QPushButton::clicked, this, [this](){ switchSorter(&insertionSorter); });
    connect(ui->shakerBtn,      &QPushButton::clicked, this, [this](){ switchSorter(&shakerSorter);    });
    connect(ui->gnomeBtn,       &QPushButton::clicked, this, [this](){ switchSorter(&gnomeSorter);     });
    connect(ui->oddEvenBtn,     &QPushButton::clicked, this, [this](){ switchSorter(&oddEvenSorter);   });
    connect(ui->mergeBtn,       &QPushButton::clicked, this, [this](){ switchSorter(&mergeSorter);     });
    connect(ui->quickBtn,       &QPushButton::clicked, this, [this](){ switchSorter(&quickSorter);     });
    connect(ui->heapBtn,        &QPushButton::clicked, this, [this](){ switchSorter(&heapSorter);      });
    connect(ui->countingBtn,    &QPushButton::clicked, this, [this](){ switchSorter(&countingSorter);  });
    //connect(ui->radixBtn,       &QPushButton::clicked, this, [this](){ switchSorter(&); });
    connect(ui->shellBtn,       &QPushButton::clicked, this, [this](){ switchSorter(&shellSorter);     });
}

void MainWindow::switchSorter(SortAlgorithm<int>* sorter) {
    ui->startBtn->setChecked(false);
    stopRequested = true;

    if (sortThread) {
        connect(sortThread, &QThread::finished, this, [this, sorter]{
            sortThread = nullptr;
            currentSorter = sorter;
            shuffleData(ui->arrSizeSlider->value());
        }, Qt::QueuedConnection);
    } else {
        currentSorter = sorter;
        shuffleData(ui->arrSizeSlider->value());
    }
}

void MainWindow::buttonsGroup() {
    QButtonGroup* group = new QButtonGroup(this);
    group->setExclusive(true);

    QList<QPushButton*> buttons = {
        ui->bubbleBtn,   ui->selectionBtn, ui->insertionBtn,
        ui->shakerBtn,   ui->gnomeBtn,     ui->oddEvenBtn,
        ui->mergeBtn,    ui->quickBtn,     ui->heapBtn,
        ui->countingBtn, ui->radixBtn,     ui->shellBtn
    };

    for (auto btn : buttons) {
        btn->setCheckable(true);
        group->addButton(btn);
    }
}

MainWindow::~MainWindow() {
    delete canvas;
    delete ui;
}
