#ifndef TESTREQUESTMAINWINDOW_H
#define TESTREQUESTMAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "ui/MainPage.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class TestRequestMainWindow; }
QT_END_NAMESPACE

class TestRequestMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TestRequestMainWindow(QWidget *parent = nullptr);
    ~TestRequestMainWindow();

private:
    Ui::TestRequestMainWindow *ui;
    TestRequestMainPage *mainPage;
    void resizeEvent(QResizeEvent *event);
};
#endif // TESTREQUESTMAINWINDOW_H
