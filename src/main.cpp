//
// Created by Marat on 7.09.25.
//

#include "mainwindow.h"
#include <QApplication>
#include <QIcon>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/appIcon/icon.png"));

    MainWindow window;
    window.setWindowTitle("Visual Algorithms");
    window.show();

    return app.exec();
}
