#ifndef HEADER_STORE
#define HEADER_STORE

#include <QLineEdit>
#include <QPushButton>
#include <QtNetwork/QNetworkRequest>

QT_BEGIN_NAMESPACE
namespace Ui {struct HeaderPair; }
QT_END_NAMESPACE

struct HeaderPair {
  QLineEdit *key;
  QLineEdit *val;
  QPushButton *del;
  QWidget *owner;

public:
  HeaderPair(QLineEdit *key, QLineEdit *val, QPushButton *del, QWidget *owner) : key(key), val(val), del(del), owner(owner) {}
};

#endif // HEADER_STORE
