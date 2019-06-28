#include "cfgmachsettings.h"
#include "ui_cfgmachsettings.h"

CfgMachSettings::CfgMachSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CfgMachSettings)
{
    ui->setupUi(this);
    cPath = SETTING_PATH;
    //set up database
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("PGM");
    db.setDatabaseName("Settings\\MyDataBase.db");
    db.setUserName("STONE");
    db.setPassword("12345678");
    db.open();
}

CfgMachSettings::~CfgMachSettings()
{
    delete ui;
}
void CfgMachSettings::SetCfgMach(CfgMach *_cMach)
{
    this->cMach = _cMach;
}
void CfgMachSettings::SetCfgHead(CfgHead *_cHead)
{
    this->cHead = _cHead;
}
void CfgMachSettings::SetMachUser(UserHandle *_userHandle)
{
    this->userHandle = _userHandle;
}
void CfgMachSettings::LoadData()
{
    QSqlQuery queryGroup;
    //[BEGIN]---query groupName from the groupTable
    QStringList groupList;
    QTabWidget *tabWidget = new QTabWidget(this);
//    tabWidget->setGeometry(QRect(510, 90, 441, 351));
    queryGroup.prepare("SELECT * FROM groupTable");
    if(!queryGroup.exec())
    {
        qDebug() << queryGroup.lastError();
    }
    while(queryGroup.next())
    {
        //get group name
        QString groupName   = queryGroup.value("groupName").toString();
        QString text    = queryGroup.value("text").toString();
        QString comment = queryGroup.value("comment").toString();
        QByteArray qByteArray = text.toUtf8();
        const char* cStr = qByteArray.data();
        //new sub tab
        QWidget *tab = new QWidget();
        tab->setProperty("groupName",groupName);
        tabWidget->addTab(tab,QString(tr(cStr)));

        //[BEGIN]---query parameter from the parameterTable
        QSqlQuery queryParam;
        queryParam.prepare("SELECT * FROM parameterTable WHERE groupName = \'" +groupName+"\'");
        if(!queryParam.exec())
        {
            qDebug() << queryParam.lastError();
        }
        QFormLayout *buffLayout = new QFormLayout(tab);
        QHBoxLayout *hrzlLayout = new QHBoxLayout(tab);
        while(queryParam.next())
        {
            //get query value from table
            QString key         = queryParam.value("key").toString();
            QString groupName   = queryParam.value("groupName").toString();
            QString widgetAble  = queryParam.value("widgetAble").toString();
            QString widgetName  = queryParam.value("widgetName").toString();
            QString range       = queryParam.value("range").toString();
            QString editLevel   = queryParam.value("editLevel").toString();
            QString text        = queryParam.value("text").toString();
            //get setting value from .ini file
            QString *value = new QString;
            this->GetPrivateProfileString(groupName,key,value,cPath);

            //set lable widget
            if(widgetAble !="N")
            {
                QLabel *lable = new QLabel(tab);
                QByteArray qByteArray = text.toUtf8();
                const char* cStr = qByteArray.data();
                lable->setText(tr(cStr));

                //----set content widget
                QWidget *widget = new QWidget;
                if(widgetName == "QLineEdit")
                {
                    //new widget
                    QLineEdit *lineEdit = new QLineEdit(tab);
                    //set value
                    lineEdit->setText(*value);
                    //connect slot
                    connect(lineEdit,SIGNAL(textChanged(const QString )),this,SLOT(SlotLineEditTextChanged(const QString)));
                    //return widget
                    widget = lineEdit;
                }
                else if(widgetName == "QComboBox")
                {
                    //new widget
                    QComboBox *comboBox = new QComboBox(tab);
                    //set value and index
                    QStringList indexTextList = range.split(',');
                    for(int i=0;i<indexTextList.count();i++)
                    {
                        QByteArray qByteArray = indexTextList.at(i).toUtf8();
                        const char* cStr = qByteArray.data();
                        comboBox->addItem(cStr);
                    }
                    comboBox->setCurrentIndex((*value).toInt()?1:0);
                    //connect slot
                    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(SlotComboBoxCurrentIndexChanged(int)));
                    //return widget
                    widget = comboBox;
                }
                //----bind lable and content widget
                lable->setBuddy(widget);
                buffLayout->addRow(lable,lable->buddy());
                buffLayout->setSizeConstraint(QLayout::SetFixedSize);
                widget->setProperty("key",key);
                widget->setProperty("groupName",groupName);
                widget->setProperty("widgetName",widgetName);
                widget->setProperty("changed","0");
                //----set widget proprety
                if(userHandle == nullptr ||userHandle->GetUser()->GetUserLevel()>editLevel.toInt())
                {
                    lable->buddy()->setDisabled(true);
                }
                else
                {
                    lable->buddy()->setDisabled(false);
                }
            }
        }
        hrzlLayout->addLayout(buffLayout);
        hrzlLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        tab->setLayout(hrzlLayout);
        //[END]---query group from the parameterTable
    }
    //[END]---query groupName from the groupTable

    QVBoxLayout *TotalVBoxLayout = new QVBoxLayout(this);
    QHBoxLayout *buttonLayout    = new QHBoxLayout(this);
    QPushButton *btnOk     = new QPushButton(tr("确认"),this);
    QPushButton *btnApply  = new QPushButton(tr("应用"),this);
    QPushButton *btnCancle = new QPushButton(tr("取消"),this);
    connect(btnOk,    SIGNAL(clicked()),this,SLOT(SlotBtnOkClicked()));
    connect(btnApply, SIGNAL(clicked()),this,SLOT(SlotBtnApplyClicked()));
    connect(btnCancle,SIGNAL(clicked()),this,SLOT(SlotBtnCancleClicked()));
    buttonLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    buttonLayout->addWidget(btnOk);
    buttonLayout->addWidget(btnApply);
    buttonLayout->addWidget(btnCancle);

    TotalVBoxLayout->addWidget(tabWidget);
    TotalVBoxLayout->addLayout(buttonLayout);
    setLayout(TotalVBoxLayout);
}

void CfgMachSettings::SlotBtnOkClicked()
{
    SlotBtnApplyClicked();
    this->close();
}

void CfgMachSettings::SlotBtnCancleClicked()
{
    this->close();
}

void CfgMachSettings::SlotBtnApplyClicked()
{
    //set lineEdit value
    QList<QLineEdit*> lEditList;
    QLineEdit *lEdit;
    lEditList.append(this->findChildren<QLineEdit*>());
    foreach (lEdit, lEditList)
    {
        if(lEdit->property("changed") == "1")
        {
            lEdit->setProperty("changed","0");
            QFont font = lEdit->font();
            font.setBold(false);
            lEdit->setFont(font);
            WritePrivateProfileString(lEdit->property("groupName").toString(),lEdit->property("key").toString(),lEdit->text(),cPath);
        }
    }

    //set comboBox value
    QList<QComboBox*> cbBoxList;
    QComboBox *cbBox;
    cbBoxList.append(this->findChildren<QComboBox*>());
    foreach (cbBox,cbBoxList)
    {
        if(cbBox->property("changed") == "1")
        {
            cbBox->setProperty("changed","0");
            QFont font = cbBox->font();
            font.setBold(false);
            cbBox->setFont(font);
            WritePrivateProfileString(cbBox->property("groupName").toString(),cbBox->property("key").toString(),cbBox->currentIndex()==0?"0":"1",cPath);
        }
    }
    cMach->GetMachineBaseInfo();
    cHead->GetHeadInfo();
//    this->LoadData();
}



void CfgMachSettings::SlotLineEditTextChanged(const QString &text)
{
    QLineEdit *lEdt = qobject_cast<QLineEdit*>(sender());
    QFont font = lEdt->font();
    font.setBold(true);
    lEdt->setFont(font);
    lEdt->setProperty("changed","1");
}
void CfgMachSettings::SlotComboBoxCurrentIndexChanged(int index)
{
    QComboBox *cbBox = qobject_cast<QComboBox*>(sender());
    QFont font = cbBox->font();
    font.setBold(true);
    cbBox->setFont(font);
    cbBox->setProperty("changed","1");

}



bool CfgMachSettings::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(strConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(strSect);
        settingsObj.setValue(strKey,strText);
        settingsObj.endGroup();
    }
    return true;
}
bool CfgMachSettings::GetPrivateProfileString(QString strSect,QString strKey,QString *szBuf,QString strConfigPath)
{
    QFile file(strConfigPath);
    if(!file.exists())
    {
        QMessageBox::information(this,QObject::tr("提示"),QObject::tr("初始化配置文件不存在"),QObject::tr("确定"));//setText(QObject::tr("软件配置文件不存在，以默认文件进行创建"))
        return false;
    }
    else
    {
        QSettings settingsObj(strConfigPath,QSettings::IniFormat);

        settingsObj.beginGroup(strSect);
        QString tpstr= (settingsObj.value(strKey)).toString();
        if(tpstr == nullptr)
        {
            QStringList tpstrl = (settingsObj.value(strKey)).toStringList();
            tpstr = tpstrl.join(',');
        }
        *szBuf = tpstr;
        settingsObj.endGroup();
    }
    return true;
}

