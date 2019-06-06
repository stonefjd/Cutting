#include "usermanager.h"
#include "ui_usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);



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

    if(strItem != nullptr && strLevel != nullptr)
    {
        qDebug()<<"SELECT "+strItem+" FROM userTable " +strLevel;
        query.prepare("SELECT "+strItem+" FROM userTable " +strLevel);
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
//    plainModel->setHeaderData(0, Qt::Horizontal, QObject::tr("工号"));
//    plainModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
//    plainModel->setHeaderData(2, Qt::Horizontal, QObject::tr("级别"));

    ui->tableView->setModel(plainModel);
    ui->tableView->setWindowTitle("title");
//    ui->tableView->show();
}
