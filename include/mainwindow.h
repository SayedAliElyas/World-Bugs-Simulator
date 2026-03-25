#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "worldview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setSimulationParameters(const std::string &world,
                                 const std::string &bug1,
                                 const std::string &bug2,
                                 int ticksPerFrame,
                                 int fps);

private slots:
void on_sendButton_clicked();

private:
    Client client; // handles communication with the simulator
    WorldView *view;// custom widget to render the world and bugs
    QTimer *timer = nullptr;// timer to control simulation steps
    std::string world;// simulation world file
    std::string bug1;// red bug file
    std::string bug2;// black bug file
    int ticks_per_frame;// how many simulation ticks to advance per frame
    int fps;// frames per second for the GUI update
};

#endif