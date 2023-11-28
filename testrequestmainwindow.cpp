#include "testrequestmainwindow.h"
#include "./ui_testrequestmainwindow.h"
#include "ui/MainPage.hpp"
#include <iostream>

TestRequestMainWindow::TestRequestMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestRequestMainWindow)
{
    ui->setupUi(this);

    statusBar()->setWindowTitle("Test Request");

    mainPage = new TestRequestMainPage(this);
}

void TestRequestMainWindow::resizeEvent(QResizeEvent *event) {
  QMainWindow::resizeEvent(event);
  mainPage->resize(event->size());
  mainPage->updateGeometry();
  mainPage->update();
  std::cout << "Width: " << event->size().width() << " Height: " << event->size().height() << std::endl;
}

TestRequestMainWindow::~TestRequestMainWindow()
{
    delete ui;
    delete mainPage;
}

