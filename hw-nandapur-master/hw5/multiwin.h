#ifndef MULTIWIN_H
#define MULTIWIN_H
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
#include "multiwin.h"
#include "twiteng.h"
#include <QMessageBox>



class Multiwin : public QWidget
{
  Q_OBJECT
public:
  Multiwin(TwitEng* twit);
  
public slots:
  void mainButtonClicked();
  void otherButtonClicked();
  void showUserFeed(int idx);;
  void showUserMentionFeed(int idx);
  void postNewTweet();
  void showFollowers(int idx);
  void addFollowing();
  void handleAnd();
  void handleOr();
  void saveToFile();
private:
  QPushButton* mainButton;
  QWidget* otherWin;
  QPushButton* otherButton;
  QScrollArea* feed;
  QTextEdit* txt;
  QScrollArea* mentions;
  QTextEdit* mtxt;
  QLineEdit* tweetBox;
  QString tweet;
  QString followp;
  QComboBox* userbox;
  QTextEdit* followBox;
  QLineEdit* searchHash;
  QLineEdit* addFollow;
  QPushButton* andButton;
  QPushButton* orButton;
  QTextEdit* searchResults;
  QPushButton* saveButton;
  QLineEdit* fileToSave;
  TwitEng* t;
  

};
#endif