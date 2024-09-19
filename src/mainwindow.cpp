#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    conn = new NetworkConnector(this);

    connect(conn, &NetworkConnector::dataCome, this, [=]()
    {

        ui->dataGetter->setPlainText(QString(conn->getResult().second));
        ui->headerGetter->setText(conn->getResult().first.toString());

    });
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_sendButton_clicked()
{
    QByteArray* data = nullptr;

    if( !ui->dataEdit->toPlainText().isEmpty())
    {
            data = new QByteArray(ui->dataEdit->toPlainText().toUtf8());
    }

    conn->connectToServer(ui->MethodCBox->currentIndex(),QUrl(ui->urlEdit->text()), ui->headerEdit->text(), data);

    delete data;
}

