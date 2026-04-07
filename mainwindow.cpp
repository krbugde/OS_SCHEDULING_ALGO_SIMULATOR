#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QDebug>
#include <algorithm>
#include <queue>
#include <QWheelEvent>
#include <QFile>
#include <QRandomGenerator>
#include <QBrush>
#include <QScrollArea>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    //Make the central widget itself scrollable
    QScrollArea *scroll = new QScrollArea(this);
    scroll->setWidget(ui->centralwidget);
    scroll->setWidgetResizable(true);
    setCentralWidget(scroll);


    //Apply dark style
    QFile styleFile(":/darkstyle.qss");
    if (styleFile.open(QFile::ReadOnly))
        this->setStyleSheet(QLatin1String(styleFile.readAll()));

    //Setup tables
    ui->processTable->setColumnCount(4);
    ui->processTable->setHorizontalHeaderLabels({"PID", "Arrival", "Burst", "Priority"});
    ui->resultTable->setColumnCount(6);
    ui->resultTable->setHorizontalHeaderLabels({"PID", "Arrival", "Burst", "Completion", "Waiting", "Turnaround"});

    ui->ganttView->setScene(scene);
    ui->ganttView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->ganttView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->ganttView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);


    ui->algoComboBox->addItems({"FCFS", "SJF", "SRTF", "Priority", "Round Robin"});

    //Paging simulation buttons
    connect(ui->runPagingButton, &QPushButton::clicked, this, &MainWindow::runPagingSimulation);
    connect(ui->nextStepButton, &QPushButton::clicked, this, &MainWindow::nextPagingStep);

    // Memory Management Initialization
    memoryScene = new QGraphicsScene(this);
    ui->memoryVisualization->setScene(memoryScene);
    ui->memoryVisualization->setDragMode(QGraphicsView::ScrollHandDrag);

    // Add memory algorithms to combo box
    ui->comboMemoryAlgo->addItems({"First Fit", "Best Fit", "Worst Fit", "Next Fit"});

    // Connect button click
    connect(ui->btnRunMemorySim, &QPushButton::clicked, this, &MainWindow::on_btnRunMemorySim_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (ui->ganttView->underMouse()) {
        const double scaleFactor = 1.15;
        if (event->angleDelta().y() > 0)
            ui->ganttView->scale(scaleFactor, scaleFactor);
        else
            ui->ganttView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
        event->accept();
    } else {
        QMainWindow::wheelEvent(event);
    }
}

void MainWindow::on_addButton_clicked()
{
    ui->processTable->insertRow(ui->processTable->rowCount());
}

void MainWindow::on_clearButton_clicked()
{
    ui->processTable->setRowCount(0);
    ui->resultTable->setRowCount(0);
    ui->avgWT->clear();
    ui->avgTAT->clear();
    scene->clear();
    processes.clear();
}

void MainWindow::on_runButton_clicked()
{
    processes.clear();
    int rows = ui->processTable->rowCount();

    for (int i = 0; i < rows; i++) {
        Process p;
        p.pid = i + 1;
        p.at = ui->processTable->item(i, 1) ? ui->processTable->item(i, 1)->text().toInt() : 0;
        p.bt = ui->processTable->item(i, 2) ? ui->processTable->item(i, 2)->text().toInt() : 0;
        p.pr = ui->processTable->item(i, 3) ? ui->processTable->item(i, 3)->text().toInt() : 0;
        p.rem = p.bt;
        processes.append(p);
    }

    QString algo = ui->algoComboBox->currentText();
    int tq = ui->timeQuantumInput->text().toInt();

    if (algo == "FCFS") runFCFS();
    else if (algo == "SJF") runSJF();
    else if (algo == "SRTF") runSRTF();
    else if (algo == "Priority") runPriority();
    else if (algo == "Round Robin") runRoundRobin(tq);
}

// ================= CPU Scheduling Algorithms ==================
void MainWindow::runFCFS()
{
    QVector<Process> p = processes;
    std::sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });
    int time = 0;
    QVector<QPair<int, int>> gantt;

    for (auto &x : p) {
        if (time < x.at) time = x.at;
        time += x.bt;
        x.ct = time;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
        gantt.append({x.pid, time});
    }
    displayResults(p, gantt);
}

void MainWindow::runSJF()
{
    QVector<Process> p = processes;
    int n = p.size(), done = 0, time = 0;
    QVector<bool> vis(n, false);
    QVector<QPair<int,int>> gantt;

    while (done < n) {
        int idx = -1, minbt = 1e9;//10^9
        for (int i = 0; i < n; i++)
            if (!vis[i] && p[i].at <= time && p[i].bt < minbt)
                minbt = p[i].bt, idx = i;

        if (idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        vis[idx] = true;
        done++;
        gantt.append({p[idx].pid, time});
    }
    displayResults(p, gantt);
}
struct GanttBlock {
    int pid;
    int start;
    int end;
};


void MainWindow::runSRTF()
{
    QVector<Process> p = processes;
    int n = p.size(), done = 0, time = 0;
    QVector<int> rem(n);
    for (int i = 0; i < n; i++) rem[i] = p[i].bt;

    struct GanttBlock { int pid, start, end; };
    QVector<GanttBlock> blocks;

    int prev = -1;
    while (done < n) {
        int idx = -1, minr = 1e9;//10^9
        for (int i = 0; i < n; i++)
            if (p[i].at <= time && rem[i] > 0 && rem[i] < minr)
                minr = rem[i], idx = i;

        if (idx == -1) { time++; continue; }

        // Start of a new execution block
        if (prev != idx)
            blocks.append({p[idx].pid, time, -1});
        prev = idx;

        rem[idx]--;
        time++;

        if (rem[idx] == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }

        // Close the current block’s end when the process changes
        if (!blocks.isEmpty())
            blocks.last().end = time;
    }

    QVector<QPair<int, int>> gantt;
    for (const auto &b : blocks)
        gantt.append({b.pid, b.end});

    displayResults(p, gantt);
}


void MainWindow::runRoundRobin(int tq)
{
    QVector<Process> p = processes;
    std::sort(p.begin(), p.end(), [](auto &a, auto &b){ return a.at < b.at; });
    int n = p.size(), time = p[0].at;

    QVector<int> rem(n);
    for (int i = 0; i < n; i++) rem[i] = p[i].bt;

    struct GanttBlock { int pid, start, end; };
    QVector<GanttBlock> blocks;

    QVector<bool> inQ(n, false);
    std::queue<int> Q;
    Q.push(0);
    inQ[0] = true;

    while (!Q.empty()) {
        int i = Q.front(); Q.pop(); inQ[i] = false;

        if (time < p[i].at) time = p[i].at;

        int start = time;
        int run = std::min(rem[i], tq);
        int end = start + run;

        // Store the CPU burst in Gantt chart
        blocks.append({p[i].pid, start, end});

        rem[i] -= run;
        time = end;

        // Add newly arrived processes
        for (int j = 0; j < n; j++) {
            if (!inQ[j] && rem[j] > 0 && p[j].at <= time) {
                Q.push(j);
                inQ[j] = true;
            }
        }

        // Requeue current process if it’s not finished
        if (rem[i] > 0) {
            Q.push(i);
            inQ[i] = true;
        } else {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }

        // Handle idle CPU case
        if (Q.empty()) {
            for (int j = 0; j < n; j++) {
                if (rem[j] > 0) {
                    time = std::max(time, p[j].at);
                    Q.push(j);
                    inQ[j] = true;
                    break;
                }
            }
        }
    }

    // Convert blocks → gantt for draw function
    QVector<QPair<int,int>> gantt;
    for (const auto &b : blocks) {
        gantt.append({b.pid, b.start});
        gantt.append({b.pid, b.end});
    }

    displayResults(p, gantt);
}


void MainWindow::runPriority()
{
    QVector<Process> p = processes;
    int n = p.size(), done = 0, time = 0;
    QVector<bool> vis(n, false);
    QVector<QPair<int,int>> gantt;

    while (done < n) {
        int idx = -1, minp = 1e9;
        for (int i = 0; i < n; i++)
            if (!vis[i] && p[i].at <= time && p[i].pr < minp)
                minp = p[i].pr, idx = i;

        if (idx == -1) { time++; continue; }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        vis[idx] = true;
        done++;
        gantt.append({p[idx].pid, time});
    }
    displayResults(p, gantt);
}


// ================= Paging Simulation ==================
void MainWindow::runPagingSimulation()
{
    ui->pageTable->setRowCount(0);
    ui->pageTable->setColumnCount(2);
    ui->pageTable->setHorizontalHeaderLabels({"Page No", "Frame No"});

    pageReferences = {1,2,3,4,1,2,5,1,2,3,4,5};
    frameCount = 3;
    frames.clear();
    pageFaults = 0;
    currentStep = 0;

    // Ensure label is visible and styled
    ui->labelPageFaults->setText(QString::number(pageFaults));
    ui->labelPageFaults->setStyleSheet("color: #FFD54F; font: bold 22px 'Segoe UI'; qproperty-alignment: 'AlignCenter';");
    ui->labelPageFaults->adjustSize();

}


void MainWindow::nextPagingStep()
{
    if (currentStep >= pageReferences.size()) {
        QMessageBox::information(this, "Simulation", "Paging simulation completed!");
        return;
    }

    int page = pageReferences[currentStep];
    bool pageFault = false;

    if (!frames.contains(page)) {
        pageFault = true;
        pageFaults++;
        if (frames.size() >= frameCount) frames.removeFirst();
        frames.append(page);
    }

    int row = ui->pageTable->rowCount();
    ui->pageTable->insertRow(row);

    QTableWidgetItem *pageItem = new QTableWidgetItem(QString::number(page));
    pageItem->setTextAlignment(Qt::AlignCenter);
    ui->pageTable->setItem(row, 0, pageItem);

    QString frameList;
    for (int f : frames) frameList += QString::number(f) + " ";
    QTableWidgetItem *frameItem = new QTableWidgetItem(frameList.trimmed());
    frameItem->setTextAlignment(Qt::AlignCenter);
    ui->pageTable->setItem(row, 1, frameItem);

    // color faults vs hits
    if (pageFault) {
        pageItem->setBackground(QColor("#e74c3c"));
        frameItem->setBackground(QColor("#f1948a"));
        pageItem->setForeground(Qt::white);
        frameItem->setForeground(Qt::white);
    } else {
        pageItem->setBackground(QColor("#1abc9c"));
        frameItem->setBackground(QColor("#48c9b0"));
        pageItem->setForeground(Qt::black);
        frameItem->setForeground(Qt::black);
    }

    // Update total page faults label and ensure it's visible
    ui->labelPageFaults->setStyleSheet("color: #FFD54F; font-weight: bold;");
    ui->labelPageFaults->setText(QString("%1").arg(pageFaults));
    ui->labelPageFaults->adjustSize();
    ui->labelPageFaults->repaint();

    ui->pageTable->scrollToBottom();
    currentStep++;
}



// ================= Display ==================
void MainWindow::displayResults(const QVector<Process>& p, const QVector<QPair<int,int>>& gantt)
{
    ui->resultTable->setRowCount(p.size());
    float totalWT = 0, totalTAT = 0;

    for (int i = 0; i < p.size(); i++) {
        totalWT += p[i].wt;
        totalTAT += p[i].tat;
        ui->resultTable->setItem(i, 0, new QTableWidgetItem(QString::number(p[i].pid)));
        ui->resultTable->setItem(i, 1, new QTableWidgetItem(QString::number(p[i].at)));
        ui->resultTable->setItem(i, 2, new QTableWidgetItem(QString::number(p[i].bt)));
        ui->resultTable->setItem(i, 3, new QTableWidgetItem(QString::number(p[i].ct)));
        ui->resultTable->setItem(i, 4, new QTableWidgetItem(QString::number(p[i].wt)));
        ui->resultTable->setItem(i, 5, new QTableWidgetItem(QString::number(p[i].tat)));
    }

    ui->avgWT->setText(QString::number(totalWT / p.size(), 'f', 2));
    ui->avgTAT->setText(QString::number(totalTAT / p.size(), 'f', 2));
    ui->avgWT->setStyleSheet("font-weight:bold; color:#00e676; background-color:#222; border-radius:4px;");
    ui->avgTAT->setStyleSheet("font-weight:bold; color:#00e676; background-color:#222; border-radius:4px;");

    drawGanttChart(gantt);
}

void MainWindow::drawGanttChart(const QVector<QPair<int,int>> &gantt)
{
    scene->clear();
    int x = 0, y = 0, height = 60, blockWidth = 40;

    QVector<QColor> colors = { QColor("#00b4d8"), QColor("#ff6f61"), QColor("#9d4edd"),
                              QColor("#00c853"), QColor("#ffb703"), QColor("#fb8500") };

    for (int i = 0; i < gantt.size(); i++) {
        int pid = gantt[i].first;
        int endTime = gantt[i].second;
        int startTime = (i == 0) ? 0 : gantt[i - 1].second;
        int width = (endTime - startTime) * blockWidth;

        QColor base = colors[pid % colors.size()];


        QGraphicsRectItem *rect = scene->addRect(x, y, width, height,
                                                 QPen(Qt::black, 0.8),
                                                 QBrush(base));
        rect->setZValue(1);

        // --- Process Label ---
        QString label = QString("P%1").arg(pid);
        QFont font("Segoe UI", 10, QFont::Bold);
        QGraphicsTextItem *text = scene->addText(label, font);
        text->setZValue(2); // make sure it’s on top of rectangle


        int brightness = (base.red() * 0.299 + base.green() * 0.587 + base.blue() * 0.114);
        QColor textColor = (brightness < 150) ? Qt::white : Qt::black;
        text->setDefaultTextColor(textColor);


        QRectF textRect = text->boundingRect();
        qreal centerX = x + (width - textRect.width()) / 2;
        qreal centerY = y + (height - textRect.height()) / 2;
        text->setPos(centerX, centerY);


        QGraphicsTextItem *startTimeText = scene->addText(QString::number(startTime),
                                                          QFont("Consolas", 8));
        startTimeText->setDefaultTextColor(QColor("#b0b0b0"));
        startTimeText->setPos(x - 3, y + height + 5);

        x += width;
    }


    if (!gantt.isEmpty()) {
        QGraphicsTextItem *endTimeText = scene->addText(QString::number(gantt.last().second),
                                                        QFont("Consolas", 8));
        endTimeText->setDefaultTextColor(QColor("#b0b0b0"));
        endTimeText->setPos(x - 3, y + height + 5);
    }


    scene->setSceneRect(scene->itemsBoundingRect());
    ui->ganttView->setScene(scene);
    ui->ganttView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

// ==================== Memory Management Simulation ====================

void MainWindow::on_btnRunMemorySim_clicked()
{

    if (ui->processTable->currentItem())
        ui->processTable->closePersistentEditor(ui->processTable->currentItem());
    if (ui->tableMemory->currentItem())
        ui->tableMemory->closePersistentEditor(ui->tableMemory->currentItem());

    // 1) Build memoryBlocks:
    QVector<MemoryBlock> blocksFromUI;

    QTableWidget *blocksTable = ui->centralwidget->findChild<QTableWidget*>("tableMemoryBlocks");

    if (blocksTable && blocksTable->rowCount() > 0) {
        for (int i = 0; i < blocksTable->rowCount(); ++i) {
            MemoryBlock b;
            b.id = i + 1;
            b.size = blocksTable->item(i, 1) ? blocksTable->item(i, 1)->text().toInt() : 0;
            b.allocated = false;
            blocksFromUI.append(b);
        }
    } else {
        // If no blocks table available, use default
        blocksFromUI = {
            {1, 300, false},
            {2, 600, false},
            {3, 350, false},
            {4, 200, false},
            {5, 750, false}
        };
    }

    if (blocksFromUI.isEmpty()) {
        QMessageBox::warning(this, "Memory Simulation", "Please add at least one memory block (tableMemoryBlocks) or provide defaults.");
        return;
    }

    // Build processes for memory simulation:
    QVector<MemoryProcess> memProcs;


    if (!processes.isEmpty()) {
        for (int i = 0; i < processes.size(); ++i) {
            MemoryProcess mp;
            mp.id = processes[i].pid;
            mp.size = processes[i].bt; // use burst as memory size
            mp.blockAssigned = -1;
            mp.fragment = -1;
            memProcs.append(mp);
        }
    } else {

        int rows = ui->tableMemory->rowCount();
        if (rows == 0) {
            QMessageBox::warning(this, "Memory Simulation", "No processes found to allocate. Add processes to the scheduler table or enter rows in tableMemory.");
            return;
        }
        for (int i = 0; i < rows; ++i) {
            MemoryProcess p;
            p.id = i + 1;
            p.size = ui->tableMemory->item(i, 1) ? ui->tableMemory->item(i, 1)->text().toInt() : 0;
            p.blockAssigned = -1;
            p.fragment = -1;
            memProcs.append(p);
        }
    }

    if (memProcs.isEmpty()) {
        QMessageBox::warning(this, "Memory Simulation", "No processes found to allocate.");
        return;
    }


    memoryBlocks = blocksFromUI;
    memoryProcesses = memProcs;


    QString algo = ui->comboMemoryAlgo->currentText().trimmed();
    if (algo == "First Fit") {
        runFirstFit();
    } else if (algo == "Best Fit") {
        runBestFit();
    } else if (algo == "Worst Fit") {
        runWorstFit();
    } else if (algo == "Next Fit") {
        runNextFit();
    } else {
        QMessageBox::warning(this, "Memory Simulation", "Select a valid memory allocation algorithm.");
        return;
    }

}


void MainWindow::runFirstFit() {
    QVector<MemoryBlock> temp = memoryBlocks;
    QVector<MemoryProcess> result = memoryProcesses;

    for (auto &proc : result) {
        for (auto &block : temp) {
            if (!block.allocated && block.size >= proc.size) {
                proc.blockAssigned = block.id;
                proc.fragment = block.size - proc.size;
                block.allocated = true;
                break;
            }
        }
    }

    displayMemoryResults(result);
    visualizeMemory(temp, result);
}

void MainWindow::runBestFit() {
    QVector<MemoryBlock> temp = memoryBlocks;
    QVector<MemoryProcess> result = memoryProcesses;

    for (auto &proc : result) {
        int bestIdx = -1;
        int bestFrag = INT_MAX;
        for (int i = 0; i < temp.size(); ++i) {
            if (!temp[i].allocated && temp[i].size >= proc.size) {
                int frag = temp[i].size - proc.size;
                if (frag < bestFrag) {
                    bestFrag = frag;
                    bestIdx = i;
                }
            }
        }
        if (bestIdx != -1) {
            temp[bestIdx].allocated = true;
            proc.blockAssigned = temp[bestIdx].id;
            proc.fragment = bestFrag;
        }
    }

    displayMemoryResults(result);
    visualizeMemory(temp, result);
}

void MainWindow::runWorstFit() {
    QVector<MemoryBlock> temp = memoryBlocks;
    QVector<MemoryProcess> result = memoryProcesses;

    for (auto &proc : result) {
        int worstIdx = -1;
        int worstFrag = -1;
        for (int i = 0; i < temp.size(); ++i) {
            if (!temp[i].allocated && temp[i].size >= proc.size) {
                int frag = temp[i].size - proc.size;
                if (frag > worstFrag) {
                    worstFrag = frag;
                    worstIdx = i;
                }
            }
        }
        if (worstIdx != -1) {
            temp[worstIdx].allocated = true;
            proc.blockAssigned = temp[worstIdx].id;
            proc.fragment = worstFrag;
        }
    }

    displayMemoryResults(result);
    visualizeMemory(temp, result);
}

void MainWindow::runNextFit() {
    QVector<MemoryBlock> temp = memoryBlocks;
    QVector<MemoryProcess> result = memoryProcesses;
    static int lastIdx = 0;

    for (auto &proc : result) {
        int i = lastIdx;
        int tried = 0;
        while (tried < temp.size()) {
            if (!temp[i].allocated && temp[i].size >= proc.size) {
                proc.blockAssigned = temp[i].id;
                proc.fragment = temp[i].size - proc.size;
                temp[i].allocated = true;
                lastIdx = (i + 1) % temp.size();
                break;
            }
            i = (i + 1) % temp.size();
            ++tried;
        }
    }

    displayMemoryResults(result);
    visualizeMemory(temp, result);
}


void MainWindow::displayMemoryResults(const QVector<MemoryProcess> &result) {
    // Show results in 'tableMemory' (Process id | Size | Block | Fragment)
    ui->tableMemory->setRowCount(result.size());
    float totalFrag = 0;
    int allocatedCount = 0;

    for (int i = 0; i < result.size(); ++i) {
        const auto &p = result[i];
        ui->tableMemory->setItem(i, 0, new QTableWidgetItem(QString::number(p.id)));
        ui->tableMemory->setItem(i, 1, new QTableWidgetItem(QString::number(p.size)));

        if (p.blockAssigned != -1) {
            ui->tableMemory->setItem(i, 2, new QTableWidgetItem(QString::number(p.blockAssigned)));
            ui->tableMemory->setItem(i, 3, new QTableWidgetItem(QString::number(p.fragment)));
            totalFrag += p.fragment;
            allocatedCount++;
        } else {
            ui->tableMemory->setItem(i, 2, new QTableWidgetItem("Not Allocated"));
            ui->tableMemory->setItem(i, 3, new QTableWidgetItem("-"));
        }
    }

    float avgFrag = allocatedCount ? (totalFrag / allocatedCount) : 0;
    ui->labelAvgFrag->setText(QString("%1 KB").arg(avgFrag, 0, 'f', 2));
    ui->labelAvgFrag->setStyleSheet("color: #00e676; font-weight: bold;");
}


void MainWindow::visualizeMemory(const QVector<MemoryBlock> &blocks, const QVector<MemoryProcess> &procs) {
    memoryScene->clear();

    // Visual layout parameters
    const int margin = 10;
    const int blockHeight = 40;
    const int spacing = 10;
    const int viewWidth = 360;
    int y = margin;
    int x = margin;

    //ui for blocks
    for (const auto &b : blocks) {
        QColor color = b.allocated ? QColor("#3498db") : QColor("#2ecc71");
        QGraphicsRectItem *rect = memoryScene->addRect(x, y, viewWidth, blockHeight, QPen(Qt::black), QBrush(color));
        QString label = QString("Block %1 - %2 KB").arg(b.id).arg(b.size);
        QGraphicsTextItem *t = memoryScene->addText(label, QFont("Segoe UI", 9));
        t->setPos(x + 8, y + 8);
        y += blockHeight + spacing;
    }

    // Draw process allocation lines to the right
    int allocX = x + viewWidth + 20;
    int idx = 0;
    for (const auto &p : procs) {
        QString tlabel;
        if (p.blockAssigned != -1)
            tlabel = QString("P%1 (%2 KB) -> Block %3").arg(p.id).arg(p.size).arg(p.blockAssigned);
        else
            tlabel = QString("P%1 (%2 KB) -> Not Allocated").arg(p.id).arg(p.size);

        QGraphicsTextItem *ta = memoryScene->addText(tlabel, QFont("Segoe UI", 9, QFont::Bold));
        ta->setDefaultTextColor(Qt::yellow);
        ta->setPos(allocX, margin + idx * (blockHeight + spacing));
        ++idx;
    }

    memoryScene->setSceneRect(memoryScene->itemsBoundingRect());
    ui->memoryVisualization->setScene(memoryScene);
}
