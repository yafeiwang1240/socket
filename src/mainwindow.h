#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "utils/socket.h"
#include "QKeyEvent"
#include "qshortcut.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void init();
    void keyPressEvent(QKeyEvent *event);

signals:
    void send(QString data);
    void m_Connect(QString ip, int port);

private slots:

    void on_pshSend_clicked();

    void refreshPage(QString type, QString data);

    void on_tedIP_textChanged();

    void on_tedPort_textChanged();

    void on_pshClear_clicked();

private:
    Ui::MainWindow *ui;
    Socket *m_Socket = 0;
//    QShortcut *m_Key = 0;
    bool m_Inited = false;
};

#endif // MAINWINDOW_H
