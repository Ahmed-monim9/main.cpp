#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpserver.h"
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startServer();
    void stopServer();
    void updateClientList();
    void logMessage(const QString &msg);

private:
    MyTcpServer *server;
    QPushButton *startButton;
    QPushButton *stopButton;
    QListWidget *clientList;
    QTextEdit *logWindow;
};

#endif // MAINWINDOW_H
