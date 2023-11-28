#include "MainPage.hpp"
#include <QtNetwork/qnetworkaccessmanager.h>
#include <iostream>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QMessageBox>
#include <QBoxLayout>
#include <QWidgetItem>
#include <qboxlayout.h>
#include <qnamespace.h>
#include <QLayout>
#include <QScrollArea>

TestRequestMainPage::TestRequestMainPage(QWidget *parent) : QWidget(parent) {
  sendButton = new QPushButton("Send"); 
  connect(sendButton, &QPushButton::clicked, this, &TestRequestMainPage::handleButton);

  sendButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  sendButton->update();

  urlLine = new QLineEdit();
  urlLine->setText("http://localhost:8080/");

  requestType = new QComboBox();
  requestType->addItem("GET");
  requestType->addItem("POST");
  requestType->addItem("DELETE");
  requestType->addItem("PUT");
  requestType->addItem("CONNECT");
  requestType->addItem("OPTIONS");
  requestType->addItem("HEAD");
  requestType->addItem("TRACE");
  requestType->addItem("PATH");
  requestType->setFocusPolicy(Qt::FocusPolicy::NoFocus);

  headersListView = new QListWidget();
  rebuildHeaders();

  addHeaderButton = new QPushButton("Add Header");
  connect(addHeaderButton, &QPushButton::clicked, this, &TestRequestMainPage::handleAddHeader);

  addHeaderButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  addHeaderButton->update();

  latestResponseLabel = new QLabel("No request made.");
  latestResponseLabel->setAlignment(Qt::Alignment::enum_type::AlignCenter);

  QHBoxLayout *scrollAreaLayout = new QHBoxLayout();
  scrollAreaLayout->addWidget(latestResponseLabel);

  QScrollArea *scrollArea = new QScrollArea;
  scrollArea->setWidget(latestResponseLabel);
  scrollArea->setAlignment(Qt::Alignment::enum_type::AlignCenter);
  scrollArea->setLayout(scrollAreaLayout);

  QWidget *layoutContainer = new QWidget(this);

  urlAndSendLayout = new QGridLayout(this);
  urlAndSendLayout->addWidget(sendButton, 0, 0);
  urlAndSendLayout->addWidget(requestType, 0, 1);
  urlAndSendLayout->addWidget(urlLine, 0, 2, 1, 4);
  urlAndSendLayout->addWidget(addHeaderButton, 1, 0);
  urlAndSendLayout->addWidget(headersListView, 3, 0, 3, 3);
  urlAndSendLayout->addWidget(scrollArea, 3, 3, 3, 3);
  urlAndSendLayout->setMargin(10);

  manager = new QNetworkAccessManager();
  QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
    sendButton->setText("Send");

    if(reply->error()) {
      QMessageBox msgBox;
      msgBox.setWindowTitle("Network Error");
      msgBox.setText(reply->errorString());
      msgBox.exec();
      latestResponseLabel->setText("Latest request failed.");
      return;
    }

    QString answer = reply->readAll();
    latestResponseLabel->setText(answer);
    if(answer.length() == 0) {
      latestResponseLabel->setText("No response was able to be read");
    }
  });
}

void TestRequestMainPage::handleAddHeader() {
  QWidget *owner = new QWidget();
  headers.push_back(HeaderPair(new QLineEdit(owner), new QLineEdit(owner), new QPushButton(owner), owner));

  rebuildHeaders();
}

void TestRequestMainPage::rebuildHeaders() {
  headersListView->clear(); // bye bye old headers

  int l = headers.size();
  for(int i = 0; i < l; i++) {
    QBoxLayout *row = new QBoxLayout(QBoxLayout::Direction::LeftToRight);
   
    HeaderPair old = headers[i];

    QWidget *widget = new QWidget();

    QLineEdit *keyField = new QLineEdit(widget);
    QLineEdit *valField = new QLineEdit(widget);
    QPushButton *removeButton = new QPushButton("Remove", widget);
    removeButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    connect(removeButton, &QPushButton::clicked, widget, [=]() {
      headers.erase(headers.begin() + i);
      rebuildHeaders();
    });

    keyField->setText(old.key->text());
    valField->setText(old.val->text());

    delete old.owner;

    row->addWidget(keyField);
    row->addWidget(valField);
    row->addWidget(removeButton);

    headers[i] = HeaderPair(keyField, valField, removeButton, widget);

    QListWidgetItem *item = new QListWidgetItem();

    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);

    widget->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    
    widget->setLayout(row);
    item->setSizeHint(widget->sizeHint());

    headersListView->addItem(item);
    headersListView->setItemWidget(item, widget);
  }

  headersListView->update();
}

void TestRequestMainPage::handleButton() {
  // If we send a request while waiting for another, then it is hard to figure out who's response is which.
  // It is best we wait.
  if(sendButton->text() != "Send") return;

  QNetworkRequest request;

  request.setUrl(QUrl(urlLine->text()));

  for(auto &pair : headers) {
    request.setRawHeader(pair.key->text().toUtf8(), pair.val->text().toUtf8());
  }
  manager->sendCustomRequest(request, requestType->currentText().toUtf8());
  sendButton->setText("Sending...");
}

TestRequestMainPage::~TestRequestMainPage() {
  delete urlLine;
  delete urlAndSendLayout;
  delete requestType;
  delete manager;
}
