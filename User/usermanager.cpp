#include "usermanager.h"
#include "ui_usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
    ui->lineEdit_search->setPlaceholderText(tr("请输入姓名或者工号查找"));


}

UserManager::~UserManager()
{
    delete ui;
}

void UserManager::SetUser(User *_user)
{
    this->user = _user;
}
void UserManager::InitialModel()
{
    QString strItem  = user->GetUserPrimItemStr();
    QString strLevel = user->GetUserPrimLevelStr();
    QSqlQueryModel *plainModel = new QSqlQueryModel;
    QSqlQuery query;

//    if(strItem != nullptr && strLevel != nullptr)
    {
        qDebug()<<"SELECT * FROM userTable WHERE userSN="+QString::number(user->GetUserSN()) +" OR userLevel >"+QString::number(user->GetUserLevel());
        query.prepare("SELECT * FROM userTable WHERE userSN="+QString::number(user->GetUserSN()) +" OR userLevel >"+QString::number(user->GetUserLevel()));
//        query.prepare("SELECT "+strItem+" FROM userTable " +strLevel);
    }
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    plainModel->setQuery(query);
    if (plainModel->lastError().isValid())
    {
        qDebug() << plainModel->lastError();
    }

    ui->tableView->setModel(plainModel);
    ui->tableView->setWindowTitle("title");
//    ui->tableView->show();
}
