# World-Bugs-Simulator

Bug World Visual Frontend (C++)
Description

This project is a C++ frontend client for the Bug World simulator.
It visualizes the bug world in real-time, including trace lines showing previous bug positions. The trace length is configurable, and older positions fade over time.

Features
Real-time visualization of red and black bugs
Trace lines for past N positions with fading effect
Configurable trace length and display speed
Works with the Bug World simulator

Requirements
Qt / qmake build system (for automatic build)
External simulator tools (not included):
. sim (simulator executable)
. asm (assembler for bug programs)
These tools are provided by Constructor University and must be obtained separately.

How to Build and Run
Build the project using qmake and make:
qmake
make
Run the compiled frontend client:
./project-26 <world_map> <bug1> <bug2> [ticks_per_frame_] [fps]

Arguments:
<world_map> → path to a .world map file
<bug1> → Red team bug program
<bug2> → Black team bug program
[ticks_per_frame] → optional, default 50
[fps] → optional, default 10

Example:
./project-26 worlds/tiny.world bugs/simple.bug bugs/simple.bug
./project-26 worlds/cross.world bugs/beetle.bug bugs/firefly.bug 20 5

Simulator Communication
The frontend communicates with sim via named pipes (FIFOs).
Commands sent to the simulator:
FETCH\n → Get current world state
STEP N\n → Advance N ticks, return state
QUIT\n → Terminate simulator
