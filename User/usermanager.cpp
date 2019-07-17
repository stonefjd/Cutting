#include "usermanager.h"
#include "ui_usermanager.h"

UserManager::UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
    //---open database
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("PGM");
    db.setDatabaseName("Settings\\MyDataBase.db");
    db.setUserName("STONE");
    db.setPassword("12345678");
    db.open();

    ui->lineEdit_search->setPlaceholderText(tr("查询请输入姓名或者工号"));
    ui->label_operator->setText(tr(""));
    plainModel = nullptr;
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
    this->setWindowTitle(tr("用户管理:")+user->GetUserName());

    //set button
    if(!user->GetUserPrimAdd())
        ui->pushButton_add->setEnabled(false);
    if(!user->GetUserPrimWrite())
        ui->pushButton_write->setEnabled(false);
    if(!user->GetUserPrimDelete())
        ui->pushButton_delete->setEnabled(false);
    if(!user->GetUserPrimRead())
        ui->lineEdit_search->setEnabled(false);

    //set model
    plainModel = new QSqlTableModel(this,db);
    plainModel->setTable("userTable");
    plainModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    plainModel->setFilter("userSN="+QString::number(user->GetUserSN()) +" OR userLevel >"+QString::number(user->GetUserLevel()));
    plainModel->select();
    //set view
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setModel(plainModel);

    //initial ui
    ui->buttonBox->setEnabled(false);
    ui->lineEdit_SN->setEnabled(false);
    ui->lineEdit_name->setEnabled(false);
    ui->lineEdit_passwordMd5->setEnabled(false);
    ui->comboBox_level->setEnabled(false);

    QValidator* validator = new QIntValidator(0,99999,this);
    ui->lineEdit_SN->setValidator(validator);
    QMapIterator<QString, int> i(user->GetUserPrimRoleMap());
    while (i.hasNext())
    {
        i.next();
        ui->comboBox_level->addItem(i.key());
    }
    ui->comboBox_level->setCurrentIndex(-1);

    //connect signal and slots
//    connect(ui->comboBox_level->b,SIGNAL())
}
void UserManager::SetUIByOperator()
{
    ui->lineEdit_SN->clear();
    ui->lineEdit_name->clear();
    ui->lineEdit_passwordMd5->clear();
    ui->comboBox_level->setCurrentIndex(-1);

    switch(m_operator)
    {
    case ADD:
        ui->label_operator->setText(tr("添加"));
        ui->buttonBox->setEnabled(true);
        ui->lineEdit_SN->setEnabled(true);
        ui->lineEdit_name->setEnabled(true);
        ui->lineEdit_passwordMd5->setEnabled(true);
        ui->comboBox_level->setEnabled(true);
        ui->comboBox_level->setEditable(false);
        ui->lineEdit_search->clear();
        break;
    case DELETE:
        ui->label_operator->setText(tr("删除"));
        ui->buttonBox->setEnabled(false);
        ui->lineEdit_SN->setEnabled(false);
        ui->lineEdit_name->setEnabled(false);
        ui->lineEdit_passwordMd5->setEnabled(false);
        ui->comboBox_level->setEnabled(false);
        ui->comboBox_level->setEditable(false);
        ui->lineEdit_search->clear();

        break;
    case READ:
        ui->label_operator->setText(tr("查询"));
        ui->buttonBox->setEnabled(false);
        ui->lineEdit_SN->setEnabled(false);
        ui->lineEdit_name->setEnabled(false);
        ui->lineEdit_passwordMd5->setEnabled(false);
        ui->comboBox_level->setEnabled(false);
        ui->comboBox_level->setEditable(false);

        break;
    case WRITE:
        ui->label_operator->setText(tr("修改密码"));
        ui->buttonBox->setEnabled(true);
        ui->lineEdit_SN->setEnabled(false);
        ui->lineEdit_SN  ->setText(QString::number(user->GetUserSN()));
        ui->lineEdit_name->setEnabled(false);
        ui->lineEdit_name->setText(user->GetUserName());
        ui->lineEdit_passwordMd5->setEnabled(true);
        ui->comboBox_level->setEnabled(false);
        ui->comboBox_level->setEditable(true);
        ui->comboBox_level->setCurrentText(user->GetUserRoleName());
        ui->lineEdit_search->clear();

        break;
    default:
        break;
    }
}
void UserManager::on_pushButton_add_clicked()
{
    m_operator = ADD;
    SetUIByOperator();
}

void UserManager::on_pushButton_write_clicked()
{
    m_operator = WRITE;
    SetUIByOperator();

//    qDebug()<<user->GetUserRoleName();

}

void UserManager::on_pushButton_delete_clicked()
{
    m_operator = DELETE;
    SetUIByOperator();
    int toDelRow = ui->tableView->currentIndex().row();
    if(toDelRow!=-1)
    {
        if (QMessageBox::Ok == QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("确定要删除") + plainModel->data(plainModel->index(toDelRow, 0)).toString() + QStringLiteral("吗?"), QMessageBox::Ok|QMessageBox::No))
        {
            plainModel->removeRow(toDelRow);
            plainModel->submitAll();
        }
        QString mainFilterStr = "(userSN="+QString::number(user->GetUserSN()) +" OR userLevel >"+QString::number(user->GetUserLevel())+")";
        plainModel->setFilter(mainFilterStr);
        plainModel->select();
    }
    else
    {
        QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("未选中删除对象"), QMessageBox::Ok);
    }
}
void UserManager::on_lineEdit_search_textChanged(const QString &arg1)
{
    m_operator = READ;
    SetUIByOperator();

    QString mainFilterStr = "(userSN="+QString::number(user->GetUserSN()) +" OR userLevel >"+QString::number(user->GetUserLevel())+")";
    if (arg1.isEmpty())
    {
        plainModel->setTable("userTable");	//重新关联数据库表，这样才能查询整个表
        plainModel->setFilter(mainFilterStr);
        plainModel->select();
    }
    else
    {
        QString toFind = ui->lineEdit_search->text();
        QString ID = plainModel->headerData(0, Qt::Horizontal).toString();
        QString NAME = plainModel->headerData(1, Qt::Horizontal).toString();
        QString subFilterStr = "("+ID + " LIKE \'%" + toFind + "%\' OR " + NAME +" LIKE \'%" + toFind + "%\')";

        plainModel->setFilter(mainFilterStr+" AND "+subFilterStr);
        qDebug()<<plainModel->filter();
        plainModel->select();
    }
}
void UserManager::on_buttonBox_accepted()
{


    switch(m_operator)
    {
    case ADD:
        if(ui->lineEdit_SN->text().isEmpty()
                ||ui->lineEdit_name->text().isEmpty()
                ||ui->lineEdit_passwordMd5->text().isEmpty()
                ||ui->comboBox_level->currentIndex()==-1)
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请将内容填写完整"), QMessageBox::Ok);
            return;
        }
        if (QMessageBox::Ok == QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请确定是否增加"), QMessageBox::Ok|QMessageBox::No))
        {
            int row = plainModel->rowCount();
            plainModel->insertRow(row);

            plainModel->setData(plainModel->index(row, 0), ui->lineEdit_SN->text());
            plainModel->setData(plainModel->index(row, 1), ui->lineEdit_name->text());
            plainModel->setData(plainModel->index(row, 2), QCryptographicHash::hash(ui->lineEdit_passwordMd5->text().toLatin1(),QCryptographicHash::Md5).toHex());
            plainModel->setData(plainModel->index(row, 3), user->GetUserPrimRoleMap().value(ui->comboBox_level->itemText(ui->comboBox_level->currentIndex())));

            if(!plainModel->submitAll())
                QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("工号重复"), QMessageBox::Ok);//提交修改
        }
        break;
    case WRITE:
        if(ui->lineEdit_passwordMd5->text().isEmpty())
        {
            QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请输入新密码"), QMessageBox::Ok);
            return;
        }
        if (QMessageBox::Ok == QMessageBox::warning(this, QStringLiteral("提示"), QStringLiteral("请确定是否修改"), QMessageBox::Ok|QMessageBox::No))
        {
            for(int row=0;row<plainModel->rowCount();row++)
            {
                if(plainModel->index(row, 0).data().toInt()== user->GetUserSN())
                {
                    plainModel->setData(plainModel->index(row, 2), QCryptographicHash::hash(ui->lineEdit_passwordMd5->text().toLatin1(),QCryptographicHash::Md5).toHex());
                    plainModel->submitAll();
                    break;
                }
            }
        }
        break;
    default:
        break;
    }

}

void UserManager::on_buttonBox_rejected()
{

}

void UserManager::on_tableView_clicked(const QModelIndex &index)
{
    (void)index;
}

