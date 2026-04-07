#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// ------------------ Structures ------------------

struct MemoryBlock {
    int id;
    int size;
    bool allocated;
};

struct MemoryProcess {
    int id;
    int size;
    int blockAssigned;
    int fragment;
};

struct Process {
    int pid, at, bt, pr;
    int wt, tat, ct, rem;
};

// ------------------------------------------------

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_runButton_clicked();
    void on_clearButton_clicked();
    void on_btnRunMemorySim_clicked();

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    Ui::MainWindow *ui;

    // ------------------ Data Members ------------------
    QVector<Process> processes;
    QGraphicsScene *scene;
    QVector<int> pageReferences;
    QVector<int> frames;

    QVector<MemoryProcess> memoryProcesses;
    QVector<MemoryBlock> memoryBlocks;
    QGraphicsScene *memoryScene;

    int frameCount;
    int pageFaults;
    int currentStep;


    // ------------------ Scheduling Algorithms ------------------
    void runFCFS();
    void runSJF();
    void runSRTF();
    void runPriority();
    void runRoundRobin(int tq);
    void runPagingSimulation();
    void nextPagingStep();

    // ------------------ Memory Management ------------------
    void runFirstFit();
    void runBestFit();
    void runWorstFit();
    void runNextFit();

    void displayMemoryResults(const QVector<MemoryProcess>& result);
    void visualizeMemory(const QVector<MemoryBlock>& blocks, const QVector<MemoryProcess>& processes);

    // ------------------ Common Display Functions ------------------
    void displayResults(const QVector<Process>&, const QVector<QPair<int,int>>& gantt);
    void drawGanttChart(const QVector<std::pair<int, int>> &gantt);

};

#endif // MAINWINDOW_H
