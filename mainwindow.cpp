#include <tesseract/baseapi.h>

#include <QImage>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    char* oldCType = strdup(setlocale(LC_ALL, NULL));
    setlocale(LC_ALL, "C");

    auto tessApi = tesseract::TessBaseAPI();
    if (tessApi.Init(TESSDATA_PREFIX, "jpn_vert")) {    // virtical text
        qDebug() << "cant load tessdata.";
        return;
    }

    tessApi.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK_VERT_TEXT);  // virtical text mode

    QImage image("jpvtext.png");
    image = image.convertToFormat(QImage::Format_RGB888);
    tessApi.SetImage(image.bits(), image.width(), image.height(), 3, image.bytesPerLine());
    char* out = tessApi.GetUTF8Text();
    ui->textEdit->setPlainText(out);

    tessApi.End();
    delete [] out;
    setlocale(LC_ALL, oldCType);
    free(oldCType);
}
