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
    QSqlQuery query;
    query.prepare("SELECT * FROM parameterTable");
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
    QHBoxLayout *TotalHBoxLayout = new QHBoxLayout();
    QFormLayout *UserSelectFormLayout = new QFormLayout();
    while(query.next())
    {
        //get query value from table
        QString key         = query.value("key").toString();
        QString group       = query.value("group").toString();
        QString widgetName  = query.value("widgetName").toString();
        QString range       = query.value("range").toString();
        QString editableLevel = query.value("editableLevel").toString();
        QString lableName  = query.value("lableName").toString();

        //get setting value from .ini file
        QString *value = new QString;
        this->GetPrivateProfileString(group,key,value,cPath);

        //set lable widget
        QLabel *lable = new QLabel(this);
        QByteArray qByteArray = lableName.toUtf8();
        const char* cStr = qByteArray.data();
        lable->setText(tr(cStr));

        //----set content widget
        QWidget *widget = new QWidget;
        if(widgetName == "QLineEdit")
        {
            //new widget
            QLineEdit *lineEdit = new QLineEdit(this);
            //set value
            lineEdit->setText(*value);
            //set layout
            UserSelectFormLayout->addRow(lable,lineEdit);
            //connect slot
            connect(lineEdit,SIGNAL(textChanged(const QString )),this,SLOT(SlotLineEditTextChanged(const QString)));
            //return widget
            widget = lineEdit;
        }
        else if(widgetName == "QComboBox")
        {
            //new widget
            QComboBox *comboBox = new QComboBox(this);
            //set value and index
            QStringList indexTextList = range.split(',');
            for(int i=0;i<indexTextList.count();i++)
            {
                QByteArray qByteArray = indexTextList.at(i).toUtf8();
                const char* cStr = qByteArray.data();
                comboBox->addItem(cStr);
            }
            comboBox->setCurrentIndex((*value).toInt()?1:0);
            //set layout
            UserSelectFormLayout->addRow(lable,comboBox);
            //connect slot
            connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(SlotComboBoxCurrentIndexChanged(int)));
            //return widget
            widget = comboBox;
        }

        //----bind lable and content widget
        lable->setBuddy(widget);
        widget->setProperty("key",key);
        widget->setProperty("group",group);
        widget->setProperty("widgetName",widgetName);
        widget->setProperty("changed","0");
        //----set widget proprety
        if(userHandle == nullptr ||userHandle->GetUser()->GetUserLevel()>editableLevel.toInt())
        {
            lable->buddy()->setDisabled(true);
        }
        else
            lable->buddy()->setDisabled(false);
    }

    //setting the layout
    TotalHBoxLayout->addLayout(UserSelectFormLayout);
    TotalHBoxLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    UserSelectFormLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(TotalHBoxLayout);

//    //机械固化参数
//    ui->lEdtHwVersion->setText(cMach->GetVersionHw());
//    ui->lEdtSwVersion->setText(cMach->GetVersionSw());
//    ui->lEdtType->setText(QString::number(cMach->GetType()));
//    ui->lEdtSizeX->setText(QString::number(cMach->GetSizeX()));
//    ui->lEdtSizeY->setText(QString::number(cMach->GetSizeY()));
//    ui->lEdtFeltThick->setText(QString::number(cMach->GetFeltThick()));
//    ui->lEdtHeadCount->setText(QString::number(cMach->GetHeadCount()));
//    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);
//    //ui->tabWidget->setTabEnabled(0,false);
//    ui->tabWidget->setStyleSheet("QTabBar::tab:disabled {width: 0; color: transparent;}");

//    //机械配置参数
//    ui->cbEffctLvLimit->setCurrentIndex(cMach->GetEffctLvLimit()?0:1);
//    ui->cbEffctLvSwage->setCurrentIndex(cMach->GetEffctLvSwage()?0:1);
//    ui->cbEffctLvPuase->setCurrentIndex(cMach->GetEffctLvPuase()?0:1);
//    ui->cbEffctLvPump ->setCurrentIndex(cMach->GetEffctLvPump ()?0:1);

//    ui->cbEnFanZone   ->setCurrentIndex(cMach->GetEnFanZone()?0:1);
//    ui->cbEnBlow      ->setCurrentIndex(cMach->GetEnBlow()?0:1);
//    ui->cbEnInhale    ->setCurrentIndex(cMach->GetEnInhal()?0:1);

//    ui->lEdtFreqBlow  ->setValidator(new QIntValidator(0,5000,this));
//    ui->lEdtFreqInhale->setValidator(new QIntValidator(0,5000,this));
//    ui->lEdtFreqBlow  ->setText(QString::number(cMach->GetFreqBlow()));
//    ui->lEdtFreqInhale->setText(QString::number(cMach->GetFreqInhale()));

//    ui->lEdtTimeSwage      ->setValidator(new QIntValidator(0,500,this));
//    ui->lEdtTimeBlow       ->setValidator(new QIntValidator(0,500,this));
//    ui->lEdtTimeLoadBefore ->setValidator(new QIntValidator(0,500,this));
//    ui->lEdtTimeLoadAfter  ->setValidator(new QIntValidator(0,500,this));
//    ui->lEdtTimeInhaleDelay->setValidator(new QIntValidator(0,500,this));
//    ui->lEdtTimeSwage      ->setText(QString::number(cMach->GetTimeSwage()));
//    ui->lEdtTimeBlow       ->setText(QString::number(cMach->GetTimeBlow()));
//    ui->lEdtTimeLoadBefore ->setText(QString::number(cMach->GetTimeLoadBefore()));
//    ui->lEdtTimeLoadAfter  ->setText(QString::number(cMach->GetTimeLoadAfter()));
//    ui->lEdtTimeInhaleDelay->setText(QString::number(cMach->GetTimeInhaleDelay()));

//    ui->cbAlignEn      ->setCurrentIndex(cMach->GetAlignEn()?0:1);
//    ui->lEdtAlignMaxZ  ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtAlignStartZ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtAlignAbsX  ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtAlignAbsY  ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtAlignMaxZ  ->setText(QString::number(cMach->GetAlignMaxZ()));
//    ui->lEdtAlignStartZ->setText(QString::number(cMach->GetAlignStartZ()));
//    ui->lEdtAlignAbsX  ->setText(QString::number(cMach->GetAlignAbsX()));
//    ui->lEdtAlignAbsY  ->setText(QString::number(cMach->GetAlignAbsY()));

//    //机头配置参数
//    ui->lEdtPosOrgX         ->setText(QString::number(cHead->GetPosOrg().x()));
//    ui->lEdtPosOrgY         ->setText(QString::number(cHead->GetPosOrg().y()));
//    ui->lEdtPosLimitX       ->setText(QString::number(cHead->GetPosLimit().x()));
//    ui->lEdtPosLimitY       ->setText(QString::number(cHead->GetPosLimit().y()));
//    ui->lEdtPosMaxX         ->setText(QString::number(cHead->GetPosMax().x()));
//    ui->lEdtPosMaxY         ->setText(QString::number(cHead->GetPosMax().y()));
//    ui->lEdtPosToPulseScaleX->setText(QString::number(cHead->GetPosToPulseScale().x()));
//    ui->lEdtPosToPulseScaleY->setText(QString::number(cHead->GetPosToPulseScale().y()));
//    ui->lEdtPulseMaxX       ->setText(QString::number(cHead->GetPulseMax().x()));
//    ui->lEdtPulseMaxY       ->setText(QString::number(cHead->GetPulseMax().y()));
//    ui->lEdtRealToCutScaleX ->setText(QString::number(cHead->GetRealToCutScale().x()));
//    ui->lEdtRealToCutScaleY ->setText(QString::number(cHead->GetRealToCutScale().y()));
//    ui->lEdtPosOrgX         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosOrgY         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosLimitX       ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosLimitY       ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosMaxX         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosMaxY         ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosToPulseScaleX->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtPosToPulseScaleY->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtRealToCutScaleX ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtRealToCutScaleY ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000

//    ui->lEdtFeedLen    ->setText(QString::number(cHead->GetFeedLen()));
//    ui->lEdtFeedSpd    ->setText(QString::number(cHead->GetFeedSpd()));
//    ui->lEdtFeedAcc    ->setText(QString::number(cHead->GetFeedAcc()));
//    ui->lEdtIdleMoveSpd->setText(QString::number(cHead->GetIdleMoveSpd()));
//    ui->lEdtIdleMoveAcc->setText(QString::number(cHead->GetIdleMoveAcc()));
//    ui->lEdtFeedLen    ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtFeedSpd    ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtFeedAcc    ->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtIdleMoveSpd->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000
//    ui->lEdtIdleMoveAcc->setValidator(new QRegExpValidator(QRegExp("^(5000|[1-4]?[0-9]?\\d?\\d(\\.\\d+)?)$"), this));//0-5000

//    QList<QLineEdit*> lEditList;
//    lEditList.append(ui->tab->findChildren<QLineEdit*>());

//    qDebug()<<lEditList;
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

void CfgMachSettings::on_pBtnOK_clicked()
{
    on_pBtnApply_clicked();
    this->close();
}

void CfgMachSettings::on_pBtnCancle_clicked()
{
    this->close();
}

void CfgMachSettings::on_pBtnApply_clicked()
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
            WritePrivateProfileString(lEdit->property("group").toString(),lEdit->property("key").toString(),lEdit->text(),cPath);
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
            WritePrivateProfileString(cbBox->property("group").toString(),cbBox->property("key").toString(),cbBox->currentIndex()==0?"0":"1",cPath);
        }
    }
}
