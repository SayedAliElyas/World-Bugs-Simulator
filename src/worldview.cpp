#include "worldview.h"
#include <QPainter>
#include <QDebug>

WorldView::WorldView(QWidget *parent)
    : QWidget(parent)//inherit QWidget constructor
{}


void WorldView::setMap(const std::vector<std::string>& map, const std::vector<bool>& offsets)
{
    if (map.empty()) return;

    // Init traceMap first
    if (traceMap.empty() || traceMap.size() != map.size() || traceMap[0].size() != map[0].size()) {
        traceMap.assign(map.size(), std::vector<int>(map[0].size(), 0));
    }

    // Mark traces FIRST (before fading)
    if (!previousMap.empty())
    {
        for (int r = 0; r < (int)previousMap.size(); ++r)
        {
            for (int c = 0; c < (int)previousMap[r].size(); ++c)
            {
                char oldCh = previousMap[r][c];
                char newCh = map[r][c];

                if ((oldCh == 'R' || oldCh == 'r' || oldCh == 'B' || oldCh == 'b') &&
                !(newCh == 'R' || newCh == 'r' || newCh == 'B' || newCh == 'b'))
                {
                    traceMap[r][c] = traceLength;
                }
            }
        }
    }

    // Fade AFTER marking — so fresh traces stay at 5 this frame
    for (int r = 0; r < (int)traceMap.size(); ++r)
        for (int c = 0; c < (int)traceMap[r].size(); ++c)
            if (traceMap[r][c] > 0)
                traceMap[r][c]--;

    previousMap = map;
    currentMap  = map;
    offsetRows = offsets;

    update(); // trigger repaint
}

void WorldView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Background
    painter.fillRect(this->rect(), QColor(180, 180, 180));


    int rows = currentMap.size();
    int cols = rows ? currentMap[0].size() : 0;
    if (rows == 0 || cols == 0) return;

    //calculating the size of each cell in pixels
    int cellSize = std::min(width() / (cols + 1), height() / rows); // +1 for hex offset

    // Pass 1: draw base map 
    for (int r = 0; r < rows; ++r)
    {
        //horizontal shift for hexagonal rows
        int xOffset = (r < (int)offsetRows.size() && offsetRows[r]) ? cellSize / 2 : 0;

        for (int c = 0; c < (int)currentMap[r].size(); ++c)
        {
            char ch = currentMap[r][c];
            QRect rect(c * cellSize + xOffset, r * cellSize, cellSize, cellSize);

            switch (ch)
            {
                case '#':
                    painter.fillRect(rect, QColor(80, 80, 80));
                    break;
                case '.':
                    painter.fillRect(rect, QColor(220, 220, 210));
                    break;
                case '+':
                    painter.fillRect(rect, QColor(255, 180, 180));
                    break;
                case '-':
                    painter.fillRect(rect, QColor(180, 220, 180));
                    break;

                case 'R':
                case 'r':
                    painter.fillRect(rect, QColor(220, 220, 210));
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(Qt::red);
                    painter.drawEllipse(rect.adjusted(1,1,-1,-1));
                    if (ch == 'r') {
                        painter.setBrush(QColor(0, 200, 0));
                        painter.drawEllipse(rect.adjusted(cellSize/3, cellSize/3, -cellSize/3, -cellSize/3));
                    }
                    painter.setBrush(Qt::NoBrush);
                    break;

                case 'B':
                case 'b':
                    painter.fillRect(rect, QColor(220, 220, 210));
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(Qt::black);
                    painter.drawEllipse(rect.adjusted(1,1,-1,-1));
                    if (ch == 'b') {
                        painter.setBrush(QColor(0, 200, 0));
                        painter.drawEllipse(rect.adjusted(cellSize/3, cellSize/3, -cellSize/3, -cellSize/3));
                    }
                    painter.setBrush(Qt::NoBrush);
                    break;

                default:
                    if (ch >= '1' && ch <= '9') {
                        painter.fillRect(rect, QColor(220, 220, 210));
                        painter.setPen(Qt::NoPen);
                        painter.setBrush(QColor(230, 180, 0));
                        painter.drawEllipse(rect.adjusted(2,2,-2,-2));
                        painter.setBrush(Qt::NoBrush);
                    } else {
                        painter.fillRect(rect, QColor(220, 220, 210));
                    }
                    break;
            }
        }
    }

    // Pass 2: draw traces
    for (int r = 0; r < rows; ++r)
    {
        int xOffset = (r < (int)offsetRows.size() && offsetRows[r]) ? cellSize / 2 : 0;

        for (int c = 0; c < (int)traceMap[r].size(); ++c)
        {
            if (traceMap[r][c] > 0)
            {
                QRect rect(c * cellSize + xOffset, r * cellSize, cellSize, cellSize); //
                painter.fillRect(rect, QColor(255, 200, 0, traceMap[r][c] * 40)); // alpha based on trace lifespan
            }
        }
    }
}