#pragma once
#include <QWidget>
#include <vector>
#include "client.h"


// simple data structure


class WorldView : public QWidget
{
    Q_OBJECT

public:
    explicit WorldView(QWidget *parent = nullptr);
    void setMap(const std::vector<std::string>& map, const std::vector<bool>& offsets);
    void setTraceLength(int n) { traceLength = n; }

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::vector<std::string> currentMap; // current world map for rendering
    std::vector<std::vector<int>> traceMap; //keeps track of how many frames are left before each trace disappears
    std::vector<std::string> previousMap; //state of the world from the last frame to detect changes for tracing
    int traceLength = 5; // sets the starting lifespan for a new trace
    std::vector<bool> offsetRows; // track which rows have offsets, used for rendering

};