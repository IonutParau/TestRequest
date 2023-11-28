#ifndef TR_MAINPAGE_H
#define TR_MAINPAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QPushButton>
#include <QLabel>
#include "../src/HeaderStore.hpp"
#include <QResizeEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class TestRequestMainPage; }
QT_END_NAMESPACE

class TestRequestMainPage : public QWidget {
  Q_OBJECT

public:
  TestRequestMainPage(QWidget *parent = nullptr);
  ~TestRequestMainPage();
private slots:
  void handleButton();
  void handleAddHeader();
private:
  QGridLayout *urlAndSendLayout;
  QListWidget *headersListView;
  QComboBox *requestType;
  QLineEdit *urlLine;
  QPushButton *sendButton;
  QPushButton *addHeaderButton;
  QNetworkAccessManager *manager;
  QLabel *latestResponseLabel;

  std::vector<HeaderPair> headers; // inefficient, but good enough

  void rebuildHeaders();
};

#endif
