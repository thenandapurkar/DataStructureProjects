#include <QVBoxLayout>
#include <QComboBox>
#include "multiwin.h"
#include "loginwindow.h"
#include <QString>

Loginwindow::Loginwindow(TwitEng* twit) : QWidget(NULL)
{
  //Layouts

  //main
  QVBoxLayout* mainLayout = new QVBoxLayout;
  t=twit;
  

  //QVBoxLayout* loginpassword = new QVBoxLayout;
  QHBoxLayout* username = new QHBoxLayout;
  QHBoxLayout* password = new QHBoxLayout;
  QHBoxLayout* buttons = new QHBoxLayout;

  QLabel* usern = new QLabel;
  usern->setText("Username: ");
  username->addWidget(usern);
  userentry = new QLineEdit;
  username->addWidget(userentry);

  QLabel* pass = new QLabel;
  pass->setText("Password: ");
  password->addWidget(pass);
  passwordentry = new QLineEdit;
  password->addWidget(passwordentry);

  login = new QPushButton("Login");
  register_ = new QPushButton("Register");
  QPushButton* quit = new QPushButton("Quit");

  buttons->addWidget(login);
  buttons->addWidget(register_);

  mainLayout->addLayout(username);
  mainLayout->addLayout(password);
  mainLayout->addLayout(buttons);
  mainLayout->addWidget(quit);




  
  setLayout(mainLayout);

  //Connections
  QObject::connect(register_, SIGNAL(clicked()), this, SLOT(RegisterUser()));
  QObject::connect(login, SIGNAL(clicked()), this, SLOT(LoginUser()));
  QObject::connect(quit, SIGNAL(clicked()), this, SLOT(quitProgram()));
}



void Loginwindow::RegisterUser()
{
  QString user = userentry->text();
  QString password = passwordentry->text();
  userentry->clear();
  passwordentry->clear();
  std::string user_s = user.toStdString();
  std::string password_c = password.toStdString();
  if(password_c.size()>8){
    QMessageBox::warning(this,"Login","Password must be 8 characters or shorter");
  }
  else{
    std::map<std::string,std::string>::const_iterator it;
    std::map<std::string,std::string> userchecks = t->getLoginInfo();
    it=userchecks.find(user_s);
    if(it!=userchecks.end()){
      QMessageBox::warning(this,"Login","Username is already taken");
    }
    else{
      std::string s = Hasher(password_c);
      t->addUser(user_s,s);
      multi = new Multiwin(t);
      multi->show();
      this->hide();
    }
  }
}

void Loginwindow::LoginUser(){
  QString user = userentry->text();
  QString password = passwordentry->text();
  userentry->clear();
  passwordentry->clear();
  std::string user_s = user.toStdString();
  std::string password_c = password.toStdString();
  std::string hashpass = Hasher(password_c);
  std::cout << hashpass << std::endl;

  std::map<std::string,std::string>::const_iterator it;
  std::map<std::string,std::string> userchecks = t->getLoginInfo();
  it=userchecks.find(user_s);
  if(it==userchecks.end()||hashpass!=it->second){
    QMessageBox::warning(this,"Login","Username and Password don't match");
  }
  else{
    multi = new Multiwin(t);
    multi->show();
    this->hide();
  }

}



std::string Loginwindow::Hasher(std::string password_s){
    long long passwordhash=0;
    int exponent=0;
    for(int i=password_s.size()-1; i>=0; i--){
      passwordhash=passwordhash+pow(128,exponent)*(int)password_s[i];
      exponent++;
    }

    unsigned int fournums[4];
    int i;
    for(i=3; i>=0; i--){
      fournums[i]=(passwordhash%65521);
      passwordhash=passwordhash/65521;
      // if(passwordhash<1){
      //   break;
      // }
    }
    // for(i=i;i>=0;i--){
    //   fournums[i]=0;
    // }

    int result=0; 
    result = (fournums[0]*45912+fournums[1]*35511+fournums[2]*65169+fournums[3]*4625)%65521;

    std::string result_str;          
    std::ostringstream convert;   
    convert << result;      
    result_str = convert.str();
    return result_str;
}

void Loginwindow::quitProgram() {
  QApplication::exit();
 }