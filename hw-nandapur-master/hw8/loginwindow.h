#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <algorithm>
#include <sstream>
#include <fstream>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStringList>
#include <QScrollArea>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QRadioButton>
#include <stdio.h>
#include <stdlib.h>
#include <QMessageBox>
#include <cmath>
#include "twiteng.h"
#include "multiwin.h"
#include <stack>
#include <QApplication>



class Loginwindow : public QWidget
{
  Q_OBJECT
public:
  Loginwindow(TwitEng* twit);
  std::string Hasher(std::string password_s);
  
public slots:
  void RegisterUser();
  void LoginUser();
  void quitProgram();
  
private:
  TwitEng* t;
  Multiwin* multi;
  QLineEdit* userentry;
  QLineEdit* passwordentry;
  QPushButton* login;
  QPushButton* register_;
  

};
#endif