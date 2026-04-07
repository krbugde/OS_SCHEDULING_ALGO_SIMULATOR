/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *addButton;
    QLabel *label_6;
    QComboBox *algoComboBox;
    QLabel *label_7;
    QLineEdit *timeQuantumInput;
    QPushButton *runButton;
    QTableWidget *resultTable;
    QTableWidget *processTable;
    QGroupBox *groupBoxPaging;
    QTableWidget *pageTable;
    QLabel *label_2;
    QLabel *labelPageFaults;
    QPushButton *clearButton;
    QPushButton *runPagingButton;
    QPushButton *nextStepButton;
    QGroupBox *groupBox;
    QLabel *avgTAT;
    QLabel *label_9;
    QGroupBox *groupMemoryManagement;
    QLabel *label;
    QComboBox *comboMemoryAlgo;
    QPushButton *btnRunMemorySim;
    QTableWidget *tableMemory;
    QLabel *label_3;
    QLabel *labelAvgFrag;
    QGroupBox *groupBox_3;
    QGraphicsView *memoryVisualization;
    QTableWidget *tableMemoryBlocks;
    QLabel *avgWT;
    QGraphicsView *ganttView;
    QLabel *label_8;
    QMenuBar *menubar;
    QMenu *menuOSPROCESS_SIMULATOR;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1696, 949);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(20, 50, 101, 29));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(550, 90, 201, 20));
        algoComboBox = new QComboBox(centralwidget);
        algoComboBox->setObjectName("algoComboBox");
        algoComboBox->setGeometry(QRect(550, 130, 201, 28));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(550, 180, 121, 21));
        timeQuantumInput = new QLineEdit(centralwidget);
        timeQuantumInput->setObjectName("timeQuantumInput");
        timeQuantumInput->setGeometry(QRect(680, 180, 113, 28));
        runButton = new QPushButton(centralwidget);
        runButton->setObjectName("runButton");
        runButton->setGeometry(QRect(550, 230, 181, 29));
        resultTable = new QTableWidget(centralwidget);
        if (resultTable->columnCount() < 6)
            resultTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        resultTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        resultTable->setObjectName("resultTable");
        resultTable->setGeometry(QRect(20, 290, 761, 191));
        processTable = new QTableWidget(centralwidget);
        if (processTable->columnCount() < 4)
            processTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        processTable->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        processTable->setObjectName("processTable");
        processTable->setGeometry(QRect(20, 90, 501, 191));
        groupBoxPaging = new QGroupBox(centralwidget);
        groupBoxPaging->setObjectName("groupBoxPaging");
        groupBoxPaging->setGeometry(QRect(1220, 30, 321, 711));
        pageTable = new QTableWidget(groupBoxPaging);
        if (pageTable->columnCount() < 2)
            pageTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        pageTable->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        pageTable->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        pageTable->setObjectName("pageTable");
        pageTable->setGeometry(QRect(20, 30, 251, 541));
        label_2 = new QLabel(groupBoxPaging);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 590, 131, 20));
        labelPageFaults = new QLabel(groupBoxPaging);
        labelPageFaults->setObjectName("labelPageFaults");
        labelPageFaults->setGeometry(QRect(150, 590, 101, 31));
        clearButton = new QPushButton(groupBoxPaging);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(20, 670, 111, 29));
        runPagingButton = new QPushButton(groupBoxPaging);
        runPagingButton->setObjectName("runPagingButton");
        runPagingButton->setGeometry(QRect(120, 630, 181, 29));
        nextStepButton = new QPushButton(groupBoxPaging);
        nextStepButton->setObjectName("nextStepButton");
        nextStepButton->setGeometry(QRect(20, 630, 90, 29));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(0, 10, 1211, 721));
        avgTAT = new QLabel(groupBox);
        avgTAT->setObjectName("avgTAT");
        avgTAT->setGeometry(QRect(570, 470, 101, 41));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(370, 470, 161, 41));
        groupMemoryManagement = new QGroupBox(groupBox);
        groupMemoryManagement->setObjectName("groupMemoryManagement");
        groupMemoryManagement->setGeometry(QRect(800, 30, 401, 701));
        label = new QLabel(groupMemoryManagement);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 81, 31));
        comboMemoryAlgo = new QComboBox(groupMemoryManagement);
        comboMemoryAlgo->setObjectName("comboMemoryAlgo");
        comboMemoryAlgo->setGeometry(QRect(100, 30, 141, 28));
        btnRunMemorySim = new QPushButton(groupMemoryManagement);
        btnRunMemorySim->setObjectName("btnRunMemorySim");
        btnRunMemorySim->setGeometry(QRect(260, 30, 121, 29));
        tableMemory = new QTableWidget(groupMemoryManagement);
        if (tableMemory->columnCount() < 4)
            tableMemory->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableMemory->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableMemory->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableMemory->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableMemory->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        if (tableMemory->rowCount() < 5)
            tableMemory->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableMemory->setVerticalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableMemory->setVerticalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableMemory->setVerticalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableMemory->setVerticalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableMemory->setVerticalHeaderItem(4, __qtablewidgetitem20);
        tableMemory->setObjectName("tableMemory");
        tableMemory->setGeometry(QRect(20, 240, 381, 192));
        tableMemory->setEditTriggers(QAbstractItemView::EditTrigger::AnyKeyPressed|QAbstractItemView::EditTrigger::CurrentChanged|QAbstractItemView::EditTrigger::DoubleClicked|QAbstractItemView::EditTrigger::SelectedClicked);
        label_3 = new QLabel(groupMemoryManagement);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 450, 161, 20));
        labelAvgFrag = new QLabel(groupMemoryManagement);
        labelAvgFrag->setObjectName("labelAvgFrag");
        labelAvgFrag->setGeometry(QRect(190, 440, 63, 31));
        groupBox_3 = new QGroupBox(groupMemoryManagement);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(10, 480, 361, 211));
        memoryVisualization = new QGraphicsView(groupBox_3);
        memoryVisualization->setObjectName("memoryVisualization");
        memoryVisualization->setGeometry(QRect(10, 30, 341, 171));
        tableMemoryBlocks = new QTableWidget(groupMemoryManagement);
        if (tableMemoryBlocks->columnCount() < 2)
            tableMemoryBlocks->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableMemoryBlocks->setHorizontalHeaderItem(0, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableMemoryBlocks->setHorizontalHeaderItem(1, __qtablewidgetitem22);
        if (tableMemoryBlocks->rowCount() < 9)
            tableMemoryBlocks->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(3, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(4, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(5, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(6, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(7, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableMemoryBlocks->setVerticalHeaderItem(8, __qtablewidgetitem31);
        tableMemoryBlocks->setObjectName("tableMemoryBlocks");
        tableMemoryBlocks->setGeometry(QRect(80, 70, 251, 161));
        avgWT = new QLabel(groupBox);
        avgWT->setObjectName("avgWT");
        avgWT->setGeometry(QRect(170, 470, 61, 41));
        ganttView = new QGraphicsView(groupBox);
        ganttView->setObjectName("ganttView");
        ganttView->setGeometry(QRect(10, 512, 781, 192));
        ganttView->setMinimumSize(QSize(771, 192));
        ganttView->setStyleSheet(QString::fromUtf8("border: 1px solid gray; background-color: white;"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(30, 480, 161, 20));
        MainWindow->setCentralWidget(centralwidget);
        groupBox->raise();
        addButton->raise();
        label_6->raise();
        algoComboBox->raise();
        label_7->raise();
        timeQuantumInput->raise();
        runButton->raise();
        resultTable->raise();
        processTable->raise();
        groupBoxPaging->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1696, 25));
        menuOSPROCESS_SIMULATOR = new QMenu(menubar);
        menuOSPROCESS_SIMULATOR->setObjectName("menuOSPROCESS_SIMULATOR");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuOSPROCESS_SIMULATOR->menuAction());
        menuOSPROCESS_SIMULATOR->addSeparator();
        menuOSPROCESS_SIMULATOR->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "+Add Process", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Select scheduling algorithms</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt;\">Time quantum: </span></p></body></html>", nullptr));
        runButton->setText(QCoreApplication::translate("MainWindow", "Run Simulation", nullptr));
        QTableWidgetItem *___qtablewidgetitem = resultTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Process Id", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = resultTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Arrival time", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = resultTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Burst Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = resultTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Completion Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = resultTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Waiting time", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = resultTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Turn around time", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = processTable->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Process id", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = processTable->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Arrival Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = processTable->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Burst Time", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = processTable->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Priority", nullptr));
        groupBoxPaging->setTitle(QCoreApplication::translate("MainWindow", "\360\237\222\276 Paging Simulation ", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = pageTable->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Page No", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = pageTable->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Frame No", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Total Page Faults: </span></p></body></html>", nullptr));
        labelPageFaults->setText(QString());
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear/Reset", nullptr));
        runPagingButton->setText(QCoreApplication::translate("MainWindow", "Run Paging Simulation", nullptr));
        nextStepButton->setText(QCoreApplication::translate("MainWindow", "Next step", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 CPU Scheduling Simulation ", nullptr));
        avgTAT->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "Average Turn around time:-", nullptr));
        groupMemoryManagement->setTitle(QCoreApplication::translate("MainWindow", "\360\237\247\240Memory Management", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Algorithm: </span></p></body></html>", nullptr));
        btnRunMemorySim->setText(QCoreApplication::translate("MainWindow", "Run simulation", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableMemory->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Process id", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableMemory->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tableMemory->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "Block", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tableMemory->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Fragments", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Average Fragmentation", nullptr));
        labelAvgFrag->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Memory Visualization", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tableMemoryBlocks->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Block id", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tableMemoryBlocks->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        avgWT->setText(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "Average waiting time:-", nullptr));
        menuOSPROCESS_SIMULATOR->setTitle(QCoreApplication::translate("MainWindow", "OSPROCESS SIMULATOR ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
