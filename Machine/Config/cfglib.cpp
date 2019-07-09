#include "cfglib.h"
CfgLib::CfgLib()
{
    m_sLibCfgPath = KNIFETOOLLIB_PATH;
//    ReadCutToolLib();
//    SaveCutToolLib();
}


CfgLib::~CfgLib(void)
{
    FreeCutTools();
}


void CfgLib::FreeCutTools()
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        delete m_stvCutTools.at(i);
    }
    m_stvCutTools.clear();
}
bool CfgLib::ReadCutToolLib()
{
    FreeCutTools();

    QString strSect = ("");
    QString strKey = ("");
    QString *szBuf = new QString;
    QString strConfigPath = m_sLibCfgPath;

    QList<QString> vCutToolIdArray;
    strSect = ("CuttingToolId");
    strKey = ("CuttingToolIds");
    if(GetPrivateProfileString(strSect,strKey,szBuf,strConfigPath))
    {
        vCutToolIdArray = (*szBuf).split(',');
    }

    QString strTemp = ("");
    //读取刀具大类
    for(int i = 0; i < vCutToolIdArray.size(); i++)
    {
        CfgCutTool* pCutTool = new CfgCutTool();

        short nCutToolId = vCutToolIdArray[i].toShort();

        strSect = ("CuttingTool");
        strTemp = QString::number(nCutToolId);
        strSect += strTemp;

        //刀具Id
        strKey = ("CuttingToolId");
        if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath) > 0)
        {
            KnifeId nValue = static_cast<KnifeId>((*szBuf).toShort());
            pCutTool->SetCutToolId(nValue);
        }

        //刀具名
        strKey = ("CuttingToolName");
        if (GetPrivateProfileString(strSect, strKey, szBuf, strConfigPath) > 0)
        {

            pCutTool->SetCutToolName(*szBuf);
        }

        //子刀具最大Id
        strKey = ("MaxKnifeId");
        if (GetPrivateProfileString(strSect, strKey,   szBuf, strConfigPath) > 0)
        {
            short nValue = (*szBuf).toShort();
            pCutTool->SetMaxKnifeId(nValue);
        }

        //子刀具最大Id
        strKey = ("MaxKnifeId1");
        if (GetPrivateProfileString(strSect, strKey,   szBuf, strConfigPath) > 0)
        {
            short nValue = (*szBuf).toShort();
            pCutTool->SetMaxKnifeId(nValue,1);
        }


        //子刀具最大Id
        strKey = ("MaxKnifeId2");
        if (GetPrivateProfileString(strSect, strKey,   szBuf, strConfigPath) > 0)
        {
            short nValue = (*szBuf).toShort();
            pCutTool->SetMaxKnifeId(nValue,2);
        }

        //加载刀具名关键字
        pCutTool->LoadCutToolKey();

        //刀具Guid队列信息
        QList<QString> vKnifeSpArray;
        strKey = ("KnifeGuids");
        if (GetPrivateProfileString(strSect, strKey,   szBuf, strConfigPath) > 0)
        {
            vKnifeSpArray = (*szBuf).split(',');
        }

        QString sConfigPath = strConfigPath;
        for(int j = 0; j < vKnifeSpArray.size(); j++)
        {
            CfgKnife* pKnife = new CfgKnife();

            pKnife->SetCutToolKey(pCutTool->GetCutToolKey());
            pKnife->SetCutToolName(pCutTool->GetCutToolName());
            pKnife->SetGuid(vKnifeSpArray.at(j).toInt());

            QString sKnifeSect = "Knife";
            sKnifeSect += pKnife->GetGuidString();

            pKnife->ReadKnifeInfo(sConfigPath,sKnifeSect);//待修改确认

            pCutTool->AddKnifePro(pKnife);
        }

        m_stvCutTools.push_back(pCutTool);
    }


    return true;
}
bool CfgLib::SaveCutToolLib()
{
    //方案2 ini格式
    QString strConfigPath = m_sLibCfgPath;


    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");

    strSect = ("CuttingToolId");

    //配置刀具大类信息
    int nCutToolCount = m_stvCutTools.size();
    QString strTemp = ("");
    strText = ("");
    int i = 0;
    for(i = 0; i < nCutToolCount; i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);

        //strTemp.Format(("%hd"),pCutTool->GetCutToolId());
        strTemp = QString::number(pCutTool->GetCutToolId());
        strText += strTemp;
        if (i < (nCutToolCount-1))
        {
            strText += (",");
        }
    }
    strKey = ("CuttingToolIds");
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    //保存刀具大类
    for(i = 0; i < nCutToolCount; i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);

        strSect = ("CuttingTool");
        //strTemp.Format(("%hd"),pCutTool->GetCutToolId());
        strTemp = QString::number(pCutTool->GetCutToolId());
        strSect += strTemp;

        //刀具Id
        strKey = ("CuttingToolId");
        //strText.Format(("%hd"),pCutTool->GetCutToolId());
        strText = QString::number(pCutTool->GetCutToolId());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //刀具名
        strKey = ("CuttingToolName");
        //strText = SDConvert::stringToCString(pCutTool->GetCutToolName());
        strText = pCutTool->GetCutToolName();
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具最大Id【第一梯段】
        strKey = ("MaxKnifeId");
        //strText.Format(_T("%hd"),pCutTool->GetMaxKnifeId(0));
        strText = QString::number(pCutTool->GetMaxKnifeId(0));
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具最大Id【第二梯段】
        strKey = ("MaxKnifeId1");
        //strText.Format(("%hd"),pCutTool->GetMaxKnifeId(1));
        strText = QString::number(pCutTool->GetMaxKnifeId(1));
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具最大Id【第三梯段】
        strKey = ("MaxKnifeId2");
        //strText.Format(("%hd"),pCutTool->GetMaxKnifeId(2));
        strText = QString::number(pCutTool->GetMaxKnifeId(2));
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //子刀具SP值队列
        QList<CfgKnife*> *pSubKnifes = pCutTool->GetSubKnifes();
        int nKnifeCount = pSubKnifes->size();
        int j = 0;
        strText = ("");
        for(j = 0; j < nKnifeCount; j++)
        {
            CfgKnife* pKnife = pSubKnifes->at(j);

            //strTemp.Format(("%d"),pKnife->GetGuid());
            strTemp = QString::number(pKnife->GetGuid());
            strText += strTemp;
            if (j < (nKnifeCount-1))
            {
                strText += (",");
            }
        }
        strKey = ("KnifeGuids");
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //保存子刀具
        QString sConfigPath = (strConfigPath);
        for(j = 0; j < nKnifeCount; j++)
        {
            CfgKnife* pKnife = pSubKnifes->at(j);

            QString sSect = "Knife";
            sSect += pKnife->GetGuidString();


            pKnife->WriteKnifeInfo(sConfigPath,sSect);
        }
    }
    return true;
}
bool CfgLib::AddCutTool(CfgCutTool* pCutTool)
{
    if (pCutTool == nullptr)
        return false;

    m_stvCutTools.push_back(pCutTool);

    return true;
}
QList<CfgCutTool*>*	CfgLib::GetCutTools()
{
    return &m_stvCutTools;
}
void CfgLib::GetAllKnifes(QList<CfgKnife*> &vKnifes)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);

        QList<CfgKnife*>* pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            CfgKnife* pKnife = pKnifes->at(j);
            vKnifes.push_back(pKnife);
        }
    }
}
void CfgLib::GetAllKnifeNames(QList<QString> &vNames)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);

        QList<CfgKnife*>* pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            CfgKnife* pKnife = pKnifes->at(j);

            vNames.push_back(pKnife->GetKnifeName());
        }
    }
}
void CfgLib::GetAllKnifeKeys(QList<QString> &vKeys)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);

        QList<CfgKnife*>* pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            CfgKnife* pKnife = pKnifes->at(j);

            vKeys.push_back(pKnife->GetKnifeKey());
        }
    }
}
CfgCutTool* CfgLib::GetCutToolById(short nCutToolId)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);
        if (static_cast<short>(pCutTool->GetCutToolId()) == nCutToolId)
            return pCutTool;
    }

    return nullptr;
}
CfgCutTool* CfgLib::GetCutToolByIndex(int nIndex)
{
    if (nIndex < m_stvCutTools.size() && nIndex >= 0)
    {
        return m_stvCutTools.at(nIndex);
    }

    return nullptr;
}

CfgCutTool* CfgLib::GetCutToolByKey(QString sKey)
{
    for(int i = 0; i < m_stvCutTools.size(); i++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(i);
        if (pCutTool->GetCutToolKey() == sKey)
            return pCutTool;
    }

    return nullptr;
}
CfgKnife*   CfgLib::GetKnifeById(short nCutToolId, short nKnifeId)
{
    CfgCutTool* pCutTool = GetCutToolById(nCutToolId);
    if (pCutTool != nullptr)
    {
        CfgKnife* pKnife = pCutTool->GetKnifeById(nKnifeId);
        return pKnife;
    }
    return nullptr;
}
CfgKnife*   CfgLib::GetKnifeByGuid(int nGuid)
{
    short nCutToolId = GUID2CUTTOOLID(nGuid);
    short nKnifeId = GUID2KNIFEID(nGuid);
    return GetKnifeById(nCutToolId,nKnifeId);
}
CfgKnife*   CfgLib::GetKnifeByName(QString sName)
{
    QString knifeName = sName;
    sName.remove(QRegExp("[123456789]"));
    CfgCutTool* pCutTool = GetCutToolByKey(sName);
    return pCutTool->GetKnifeByName(knifeName);
}

CfgKnife*   CfgLib::GetFirstCModeKnife(short nCModeId)
{
    for(int k = 0; k < m_stvCutTools.size(); k++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(k);

        CfgKnife* pKnife = pCutTool->GetKnifeByIndex(0);
        if (pKnife != nullptr && pKnife->GetApronCMode() == nCModeId)
        {
            return pKnife;
        }
    }
    return nullptr;
}
void CfgLib::GetAllKnifesOnCMode(short nCModeId,QList<CfgKnife*> &vKnifes)
{
    for(int k = 0; k < m_stvCutTools.size(); k++)
    {
        CfgCutTool* pCutTool = m_stvCutTools.at(k);

        QList<CfgKnife*> *pKnifes = pCutTool->GetSubKnifes();
        for(int j = 0; j < pKnifes->size(); j++)
        {
            CfgKnife* pKnife = pKnifes->at(j);
            if (pKnife->GetApronCMode() == nCModeId)
            {
                vKnifes.push_back(pKnife);
            }
        }
    }
}
void CfgLib::UpdateKnifeInfo(CfgKnife* pKinfe)
{
    if (pKinfe == nullptr)
        return;

    CfgKnife* pDesKnife = this->GetKnifeById(pKinfe->GetCutToolId(),pKinfe->GetKnifeId());
    if (pDesKnife != nullptr)
    {
        pDesKnife->Copy(pKinfe);
    }
}
void CfgLib::UpdateKnifeInfo(QList<CfgKnife*> *pKnifes)
{
    for(int i = 0; i < pKnifes->size(); i++)
    {
        UpdateKnifeInfo(pKnifes->at(i));
    }
}



