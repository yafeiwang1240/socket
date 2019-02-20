#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdatetime.h"
#include "QLineEdit"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    connect(this, SIGNAL(send(QString)), m_Socket, SLOT(m_SendMessage(QString)));
    connect(this, SIGNAL(m_Connect(QString,int)), m_Socket, SLOT(m_Connect(QString, int)));
    connect(m_Socket, SIGNAL(m_Receive(QString, QString)), this, SLOT(refreshPage(QString, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(!m_Socket){
        m_Socket->~Socket();
        delete m_Socket;
    }
}

void MainWindow::init() {
    m_Socket = new Socket();
//    ui->tedNews->setEnabled(false);
//    m_Key = new QShortcut(QKeySequence(Qt::Key_Return), this);
//    connect(m_Key, SIGNAL(activated()), this, SLOT(on_pshSend_clicked()));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        emit ui->pshSend->click();
        break;
    default:
        break;
    }
}

void MainWindow::refreshPage(QString type, QString data) {
    QString message = ui->tedNews->toPlainText();
    if(message.length() > 0){
        message.append("\n");
    }
    message.append(type);
    message.append(" ");
    message.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    message.append(": ");
    message.append(data);
    ui->tedNews->setText(message);
}


void MainWindow::on_pshSend_clicked()
{
    if(!m_Inited){
        m_Inited = true;
        m_Connect(ui->tedIP->toPlainText(), ui->tedPort->toPlainText().toInt());
    }
    QString data = ui->tedSend->toPlainText();
    if(data.length() <= 0){
        return;
    }
    send(data);
    refreshPage("send", data);
    ui->tedSend->clear();
}

void MainWindow::on_tedIP_textChanged()
{
    m_Inited = false;
}

void MainWindow::on_tedPort_textChanged()
{
    m_Inited = false;
}

void MainWindow::on_pshClear_clicked()
{
    ui->tedNews->clear();
}
