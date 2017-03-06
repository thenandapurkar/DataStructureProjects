#include <QVBoxLayout>
#include <QComboBox>
#include "multiwin.h"
#include <QString>

Multiwin::Multiwin(TwitEng* twit) : QWidget(NULL)
{
  //Layouts

  //main
  QVBoxLayout* mainLayout = new QVBoxLayout;

  //Layouts for feeds
  QHBoxLayout* feedLabels = new QHBoxLayout;
  QHBoxLayout* feedLayout = new QHBoxLayout;

  //Layout for tweet and textbox
  QHBoxLayout* tweetBarLayout = new QHBoxLayout;
  QHBoxLayout* chooseUserWriteTweetLayout = new QHBoxLayout;
  
  //Layout for the save area
  QHBoxLayout* saveAreaLayout = new QHBoxLayout;
  saveButton = new QPushButton("Save File: ");
  fileToSave = new QLineEdit();
  stronglyConnected = new QPushButton("Write SCC's to file: ");
  strongFileToSave = new QLineEdit();
  saveAreaLayout->addWidget(saveButton);
  saveAreaLayout->addWidget(fileToSave);
  saveAreaLayout->addWidget(stronglyConnected);
  saveAreaLayout->addWidget(strongFileToSave);


  //Labels
  QLabel* feedLabel = new QLabel;
  feedLabel->setText("Main Feed");
  QLabel* mentionLabel = new QLabel;
  mentionLabel->setText("Mentions");
  QLabel* tweetInd = new QLabel;
  tweetInd->setText("Tweet: ");
  QLabel* fLabel = new QLabel;
  fLabel->setText("Followers");
  QLabel* addFollowLabel = new QLabel;
  addFollowLabel->setText("Follow Another User Here: ");


  //member declarations
  t=twit;
  mainButton = new QPushButton("HashTag Search");
  txt = new QTextEdit();
  txt->setReadOnly(true);
  mtxt = new QTextEdit();
  mtxt->setReadOnly(true);
  feed = new QScrollArea();
  mentions = new QScrollArea();
  
  
  //Drop Down List of Users
  userbox = new QComboBox();
  for(unsigned int i=0; i<t->getUsers().size(); i++){
    std::string l = t->getUsers()[i];
    QString temp = QString::fromStdString(l);
    userbox->addItem(temp);
  }

  //Text Box for tweets
  tweetBox = new QLineEdit();

  //Text Box to add a follower
  addFollow = new QLineEdit();

  
  

  
  //List of followers
  followBox = new QTextEdit();
  followBox->setReadOnly(true);
  QScrollArea* followscroller = new QScrollArea();


  


  //Widgets & Layouts
  feed->setWidget(txt);
  mentions->setWidget(mtxt);
  followscroller->setWidget(followBox);

  //Top Button
  mainLayout->addWidget(mainButton);

  //UserBox and TweetBar
  chooseUserWriteTweetLayout->addWidget(userbox);
  tweetBarLayout->addWidget(tweetInd);
  tweetBarLayout->addWidget(tweetBox);
  chooseUserWriteTweetLayout->addLayout(tweetBarLayout);
  chooseUserWriteTweetLayout->addWidget(addFollowLabel);
  chooseUserWriteTweetLayout->addWidget(addFollow);
  mainLayout->addLayout(chooseUserWriteTweetLayout);

  //Feed Area
  feedLabels->addWidget(fLabel);
  feedLabels->addWidget(feedLabel);
  feedLabels->addWidget(mentionLabel);
  mainLayout->addLayout(feedLabels);
  feedLayout->addWidget(followscroller);
  feedLayout->addWidget(feed);
  feedLayout->addWidget(mentions);
  mainLayout->addLayout(feedLayout);
  mainLayout->addLayout(saveAreaLayout);

  setLayout(mainLayout);
  otherWin = new QWidget;
  //Other Box Layouts
  QVBoxLayout* otherLayout = new QVBoxLayout;
  QHBoxLayout* searchLayout = new QHBoxLayout;
  QVBoxLayout* andorButtonLayout = new QVBoxLayout;
  QVBoxLayout* searchFunctionLayout = new QVBoxLayout;

  //Push Buttons
  andButton = new QPushButton("AND Search", otherWin);
  orButton = new QPushButton("OR Search", otherWin);
  
  // //Add to the Layout
  andorButtonLayout->addWidget(andButton);
  andorButtonLayout->addWidget(orButton);
  
  // //Search Widgets
  QLabel* searchQueryLabel = new QLabel;
  searchQueryLabel->setText("Search: ");
  searchHash = new QLineEdit();
  searchFunctionLayout->addWidget(searchQueryLabel);
  searchFunctionLayout->addWidget(searchHash);

  searchResults = new QTextEdit();
  searchResults->setReadOnly(true);



  
  
  otherButton = new QPushButton("Close");
  
  searchLayout->addLayout(andorButtonLayout);
  searchLayout->addLayout(searchFunctionLayout);
  otherLayout->addLayout(searchLayout);
  otherLayout->addWidget(searchResults);
  otherLayout->addWidget(otherButton);
  otherWin->setLayout(otherLayout);

  //Connections
  QObject::connect(mainButton, SIGNAL(clicked()), this, SLOT(mainButtonClicked()));
  QObject::connect(userbox, SIGNAL(currentIndexChanged(int)), this, SLOT(showUserFeed(int)));
  QObject::connect(userbox, SIGNAL(currentIndexChanged(int)), this, SLOT(showUserMentionFeed(int)));
  QObject::connect(tweetBox, SIGNAL(returnPressed()), this, SLOT(postNewTweet()));
  QObject::connect(userbox, SIGNAL(currentIndexChanged(int)), this, SLOT(showFollowers(int)));
  QObject::connect(addFollow, SIGNAL(returnPressed()), this, SLOT(addFollowing()));
  QObject::connect(otherButton, SIGNAL(clicked()), this, SLOT(otherButtonClicked()));
  QObject::connect(andButton, SIGNAL(clicked()), this, SLOT(handleAnd()));
  QObject::connect(orButton, SIGNAL(clicked()), this, SLOT(handleOr()));
  QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
  QObject::connect(stronglyConnected, SIGNAL(clicked()), this, SLOT(saveSCCs()));
}



void Multiwin::mainButtonClicked()
{
  otherWin->show();
}
void Multiwin::otherButtonClicked()
{
  otherWin->hide();
}

void Multiwin::showUserFeed(int idx){
  txt->clear();
  User* u = t->getUsers2()[idx];
  for(int i=u->getFeed().size()-1; i>=0; i--){
    std::string temp;
    std::ostringstream j(temp);
    j << *(u)->getFeed()[i];
    //temp = j.str();
    QString t = QString::fromStdString(j.str());
    txt->append(t);
 }
}

void Multiwin::showUserMentionFeed(int idx){
  mtxt->clear();
  User* u = t->getUsers2()[idx];
  for(int i=u->getMentions().size()-1; i>=0; i--){
    std::string temp;
    std::ostringstream j(temp);
    j << *(u)->getMentions()[i];
    //temp = j.str();
    QString t = QString::fromStdString(j.str());
    mtxt->append(t);
  }
}

void Multiwin::postNewTweet(){
  tweet = tweetBox->text();
  tweetBox->clear();
  std::string content = tweet.toStdString();
  DateTime dt;
  int idx = userbox->currentIndex();
  
  std::string person = t->getUsers()[idx];
  t->addTweet(person, dt, content);
  t->dumpFeeds();
  showUserFeed(idx);
  showUserMentionFeed(idx);
}

void Multiwin::showFollowers(int idx){
  //Display for Followers
  followBox->clear();
  idx = userbox->currentIndex();
  User* p = t->getUsers2()[idx];
  std::set<User*> f = p->followers();
  for(std::set<User*>::iterator it=f.begin(); 
      it!=f.end(); ++it){
    std::string temp = ((*it)->name());
    QString name = QString::fromStdString(temp);
    followBox->append(name);
  }
}

void Multiwin::addFollowing(){
  followp = addFollow->text();
  addFollow->clear();
  std::string content = followp.toStdString();
  int idx = userbox->currentIndex();
  QString temp5 = userbox->currentText();
  std::string username = temp5.toStdString();
  User* n = t->getUserMap().find(username)->second;
  User* n2 = t->getUserMap().find(content)->second;
  n->addFollowing(n2);
  n2->addFollower(n);
  t->dumpFeeds();
  showUserFeed(idx);
  showUserMentionFeed(idx);
}

void Multiwin::handleAnd(){
  QString qline = searchHash->text();
  searchHash->clear();
  searchResults->clear();
  std::string tags = qline.toStdString();
  std::vector<std::string> hashtags;
  std::vector<Tweet*> tweets;
  std::stringstream line(tags);
  while(!line.eof()){
    std::string temp;
    line >> temp;
    hashtags.push_back(temp);
  }
  tweets = t->search(hashtags, 0);
  if(tweets.size()==0){
    searchResults->append("No matches found.");
  }
  else{
    if(tweets.size()==1){
      std::string intro_s;
      std::stringstream intro(intro_s);
      intro << tweets.size() << " match: ";
      QString intro_q = QString::fromStdString(intro_s);
      searchResults->append(intro_q);
    }
    else{
      std::string intro_s;
      std::stringstream intro(intro_s);
      intro << tweets.size() << " matches: ";
      QString intro_q = QString::fromStdString(intro_s);
      searchResults->append(intro_q);  
    }
    for(unsigned int i=0; i<tweets.size(); i++){
      //cout << *tweets[i] << endl;
      std::string temp;
      std::ostringstream j(temp);
      j << *tweets[i];
      //temp = j.str();
      QString t = QString::fromStdString(j.str());
      searchResults->append(t);
    }
  }
}

void Multiwin::handleOr(){
  QString qline = searchHash->text();
  searchHash->clear();
  searchResults->clear();
  std::string tags = qline.toStdString();
  std::vector<std::string> hashtags;
  std::vector<Tweet*> tweets;
  std::stringstream line(tags);
  while(!line.eof()){
    std::string temp;
    line >> temp;
    hashtags.push_back(temp);
  }
  tweets = t->search(hashtags, 1);
  if(tweets.size()==0){
    searchResults->append("No matches found.");
  }
  else{
    if(tweets.size()==1){
      std::string intro_s;
      std::stringstream intro(intro_s);
      intro << tweets.size() << " match: ";
      QString intro_q = QString::fromStdString(intro_s);
      searchResults->append(intro_q);
    }
    else{
      std::string intro_s;
      std::stringstream intro(intro_s);
      intro << tweets.size() << " matches: ";
      QString intro_q = QString::fromStdString(intro_s);
      searchResults->append(intro_q);  
    }
    for(unsigned int i=0; i<tweets.size(); i++){
      //cout << *tweets[i] << endl;
      std::string temp;
      std::ostringstream j(temp);
      j << *tweets[i];
      //temp = j.str();
      QString t = QString::fromStdString(j.str());
      searchResults->append(t);
    }
  }
}

void Multiwin::saveToFile(){
  QString qfilename = fileToSave->text();
  fileToSave->clear();
  std::string filename = qfilename.toStdString();
  std::ofstream ofile(filename.c_str());

  int numUsers = t->getUsers().size();
  ofile << numUsers << std::endl;

  for(unsigned int i=0; i<t->getUsers().size(); i++){
    ofile << t->getUsers()[i];
    std::set<User*> tfollowing = t->getUsers2()[i]->following();
    for(std::set<User*>::iterator it = tfollowing.begin(); it!=tfollowing.end(); ++it){
      ofile << " " << (*it)->name();
    }
    ofile << std::endl;
  }

  for(unsigned int i=0; i<t->getUsers().size(); i++){
    std::list<Tweet*> tempTweets = t->getUsers2()[i]->tweets();
    for(std::list<Tweet*>::iterator it = tempTweets.begin(); it!=tempTweets.end(); ++it){
      ofile << *(*it) << std::endl;
    }
  }

}

void Multiwin::saveSCCs(){
  //change types
  QString qfilename = strongFileToSave->text();
  strongFileToSave->clear();
  std::string filename = qfilename.toStdString();
  //std::ofstream ofile(filename.c_str());
  t->tarjanAlgorithm();
  t->outputToFile(filename.c_str());
}
    
  



