#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), server(new MyTcpServer(this))
{
    setWindowTitle("TCP Server Control Panel");

    // Создаем кнопки и виджеты
    startButton = new QPushButton("Start Server", this);
    stopButton = new QPushButton("Stop Server", this);
    stopButton->setEnabled(false);
    clientList = new QListWidget(this);
    logWindow = new QTextEdit(this);
    logWindow->setReadOnly(true);

    // Основной Layout
    auto *layout = new QVBoxLayout;
    layout->addWidget(startButton);
    layout->addWidget(stopButton);
    layout->addWidget(new QLabel("Connected Clients:"));
    layout->addWidget(clientList);
    layout->addWidget(new QLabel("Server Logs:"));
    layout->addWidget(logWindow);

    auto *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Подключаем слоты к кнопкам
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startServer);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopServer);
    connect(server, &MyTcpServer::newConnection, this, &MainWindow::updateClientList);
    connect(server, &MyTcpServer::clientDisconnected, this, &MainWindow::updateClientList);
}

MainWindow::~MainWindow() {}

void MainWindow::startServer() {
    if (server->start(33333)) {
        logMessage("Server started on port 33333");
        startButton->setEnabled(false);
        stopButton->setEnabled(true);
    } else {
        logMessage("Failed to start server");
    }
}

void MainWindow::stopServer() {
    server->stop();
    logMessage("Server stopped");
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    updateClientList();
}

void MainWindow::updateClientList() {
    clientList->clear();
    for (const auto &client : server->getClients()) {
        clientList->addItem("Client " + QString::number(client->socketDescriptor()));
    }
}

void MainWindow::logMessage(const QString &msg) {
    logWindow->append(msg);
}
