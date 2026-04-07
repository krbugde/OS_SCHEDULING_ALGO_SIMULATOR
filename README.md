# CPU Scheduler GUI

A Qt-based desktop application for visualizing CPU scheduling algorithms, paging simulation, and memory allocation strategies.

## Overview

`CPU_Scheduler_GUI` provides an interactive graphical interface to:

- Add and simulate process scheduling using common algorithms
- Visualize Gantt charts and performance metrics
- Run a simple paging simulation with page faults tracking
- Compare memory allocation algorithms: First Fit, Best Fit, Worst Fit, and Next Fit

The project is built with C++17 and Qt Widgets using CMake.

## Features

### CPU Scheduling

The scheduler supports:

- First-Come, First-Served (FCFS)
- Shortest Job First (SJF)
- Shortest Remaining Time First (SRTF)
- Priority Scheduling
- Round Robin (with configurable time quantum)

Results include:

- Completion Time
- Waiting Time
- Turnaround Time
- Average Waiting Time
- Average Turnaround Time
- Gantt chart visualization

### Paging Simulation

The paging simulation uses a preset reference string and frame count to demonstrate:

- Page hits and faults
- Frame occupancy over each simulation step
- Total page faults count

### Memory Allocation Simulation

Memory allocation simulation supports the following strategies:

- First Fit
- Best Fit
- Worst Fit
- Next Fit

It displays:

- Assigned memory blocks
- Internal fragmentation for each process
- A visualization of block allocation

## Prerequisites

- Qt 6 or Qt 5 installed with the `Widgets` module
- CMake 3.16 or newer
- A C++ compiler supporting C++17

## Build Instructions

### Using Qt Creator

1. Open `CMakeLists.txt` in Qt Creator.
2. Configure the project using your installed Qt kit.
3. Build and run from Qt Creator.

### Using Command Line

```powershell
cd "c:\Users\Dr.Manish inamdar\OneDrive\Documents\CPU_Scheduler_GUI"
mkdir -p build
cd build
cmake ..
cmake --build .
```

If you are using Qt 6, CMake will automatically configure `qt_add_executable` and the required Qt modules.

## Run

After building, run the generated executable:

- Windows: `build\CPU_Scheduler_GUI.exe`
- Linux/macOS: `build/CPU_Scheduler_GUI`

## Usage

1. Add processes using the `Add` button.
2. Enter process arrival time, burst time, and priority.
3. Select a scheduling algorithm and click `Run`.
4. View results in the result table and inspect the Gantt chart.
5. Use `Clear` to reset the input and output tables.
6. Use the paging controls to step through the page replacement simulation.
7. Configure memory blocks and processes, then choose a memory algorithm and run the memory simulation.

## Project Structure

- `main.cpp` – Application entry point
- `mainwindow.h` – Main window declaration and algorithm definitions
- `mainwindow.cpp` – Application logic, simulation algorithms, visualization, and UI behavior
- `mainwindow.ui` – Qt Designer UI definition
- `CMakeLists.txt` – Build configuration
- `resources.qrc` – Qt resource file
- `darkstyle.qss` – Dark theme styling

## Notes

- The paging simulation uses a predefined reference string and frame count in code.
- The memory allocation simulation reads process data from the scheduler table or a dedicated memory table.
- The interface uses scrollable views and zoomable Gantt chart support.


