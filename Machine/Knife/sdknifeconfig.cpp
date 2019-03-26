#include "sdknifeconfig.h"

SDKnifeConfig::SDKnifeConfig(QObject *parent) : QObject(parent)
{
    m_sLocalDir = "";
    m_dbMaterialThick = 30;
}
SDKnifeConfig::~SDKnifeConfig(void)
{
    FreeKnifes();
}

bool SDKnifeConfig::InitDefaultKnifeLib()
{
    FreeKnifes();

    QList<SDApron*> vAprons;
    m_stMachineInfo.GetAllAprons(vAprons);

    for(int i = 0; i < vAprons.size(); i++)
    {
        SDApron* pApron = vAprons.at(i);
        SDKnife* pKnife = m_stCutToolLib.GetFirstCModeKnife(pApron->GetApronCMode());

        if (pKnife != nullptr)
        {
            m_stvKnifes.push_back(pKnife);
            pApron->SetKnifeGuid(pKnife->GetGuid());//刀具Guid设置到刀座上
        }
    }

    return true;
}

bool SDKnifeConfig::ReadConfigFile()
{
    if (!m_stCutToolLib.ReadCutToolLib(m_sLocalDir))
    {
        return false;
    }

//    if (!ReadMachineInfo())
//        return false;

//    if (!ReadKnifeLib())
//        return false;

//    //默认切割参数
//    ReadCutInfo();

//    m_stKPDesignLib.Read(); //刀具切割参数方案库

//    //刀具和刀座的匹配性检测
//    CheckKnifeConfig();

//    //test
    return true;
}
bool SDKnifeConfig::ReadKnifeLib()
{
    FreeKnifes();

    QString strConfigPath = m_sLocalDir;
    strConfigPath += ("\\TooSet\\CutterSet.ini");

    QString strSect = ("CutTool");
    QString strKey = ("KnifeGuids");

    QString *pData = nullptr;

    QString  strDefault = ("");
    int nRet = GetPrivateProfileString(strSect, strKey, strDefault, pData,strConfigPath);

    QString strKnifeSps = *pData;

    QStringList arrOut;
    //SDConvert::MSG_SplitCString(strKnifeSps,',',arrOut);
    arrOut = strKnifeSps.split(',');


    for(int i = 0; i < arrOut.size(); i++)
    {
        int nGuid = arrOut.at(i).toInt();

        SDKnife* pKnife = new SDKnife();//g_sCutToolLib.GetKnifeBySp(nSp);
        pKnife->SetGuid(nGuid);

        this->AddKnife(pKnife);
    }

    for(int j = 0; j < m_stvKnifes.size(); j++)
    {
        SDKnife* pKnife = m_stvKnifes.at(j);
        //strKey.Format(("%d"),pKnife->GetGuid());
        strKey = QString::number(pKnife->GetGuid());

        GetPrivateProfileString(strSect, strKey, strDefault, pData,strConfigPath);

        strKey = *pData;
        pKnife->SetColor(strKey.toInt());
    }
    //释放内存
    free(pData);

    //如果配置刀具队列为空，就自动产生一个
    if (m_stvKnifes.empty())
    {
        InitDefaultKnifeLib();
    }

    return true;
}
bool SDKnifeConfig::SaveKnifeLib()
{
    QString strConfigPath = m_sLocalDir;
    strConfigPath += ("\\TooSet\\CutterSet.ini");

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");

    strSect = ("CutTool");
    strKey = ("KnifeGuids");

    QString strTemp = ("");
    strText = ("");
    int nKnifeCount = m_stvKnifes.size();
    for(int i = 0; i < nKnifeCount; i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);

        //strTemp.Format(("%d"),pKnife->GetGuid());
        strTemp = QString::number(pKnife->GetGuid());
        strText += strTemp;
        if (i < (nKnifeCount-1))
        {
            strText += (",");
        }
    }
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    for(int j = 0; j < nKnifeCount; j++)
    {
        SDKnife* pKnife = m_stvKnifes.at(j);

        //strKey.Format(("%d"),pKnife->GetGuid());
        strKey = QString::number(pKnife->GetGuid());
        //strText.Format(("%d"),pKnife->GetColor());
        strText = QString::number(pKnife->GetColor());

        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);
    }

    return true;
}
void SDKnifeConfig::CheckKnifeConfig()
{
    int i = 0;
    int j = 0;

    //1 加载可用刀具
    LoadActiveKnifes();

    //检查可用刀具和联机刀座是否一致 [可用刀具是重新加载的，就不用检测和刀座是否一致了]
    //for(j = 0; j < (int)m_stvActiveKnifes.size(); j++)
    //{
    //	SDKnife* pKnife = m_stvActiveKnifes.at(j);

    //	short nApronCMode = pKnife->GetApronCMode();
    //	if (!FindApronByApronCMode(nApronCMode))
    //	{
    //		m_stvActiveKnifes.erase(m_stvActiveKnifes.begin()+j);
    //		j--;
    //	}
    //}

    //2 去除不可用的配置刀具
    for(j = 0; j < m_stvKnifes.size(); j++)
    {
        SDKnife* pKnife = m_stvKnifes.at(j);

        if (!GetActiveKnifeByGuid(pKnife->GetGuid()))
        {
            m_stvKnifes.erase(m_stvKnifes.begin()+j);
            j--;
        }
    }

    //3 去除重复刀座的配置刀具
    QList<SDApron*> vAprons;
    m_stMachineInfo.GetAllAprons(vAprons);

    QList<SDKnife*> vFitKnifes;
    for(i = 0; i < vAprons.size(); i++)
    {
        SDApron* pApron = vAprons.at(i);
        for(j = 0; j < m_stvKnifes.size(); j++)
        {
            SDKnife* pKnife = m_stvKnifes.at(j);
            if (pKnife->GetApronIndex() == pApron->GetApronIndex() && pKnife->GetApronCMode() == pApron->GetApronCMode())
            {
                vFitKnifes.push_back(pKnife);
                m_stvKnifes.erase(m_stvKnifes.begin()+j);
                break;
            }
        }
    }
    this->FreeKnifes();

    if (!vFitKnifes.empty())
    {
        //m_stvKnifes.assign(vFitKnifes.begin(),vFitKnifes.end());
        m_stvKnifes = vFitKnifes;
    }

    //4  恢复被禁用的刀具.对于既没有配置刀具，也没有禁用刀具的刀座，那么就添加一个默认的刀具。
    for(i = 0; i < vAprons.size(); i++)
    {
        SDApron* pApron = vAprons.at(i);

        SDKnife* pFindKnife = GetKnifeByApronGuid(pApron->GetApronGuid());
        if (pFindKnife != nullptr)
            continue;

        SDKnife* pApronKnife = m_stCutToolLib.GetKnifeByGuid(pApron->GetKnifeGuid());
        if (pApronKnife == nullptr)//如果根据刀座上的刀具SP，从刀具库中找不到刀具指针
        {
            //那么就从刀具库中找一个默认的刀具
            pApronKnife = m_stCutToolLib.GetFirstCModeKnife(pApron->GetApronCMode());
            if (pApronKnife != nullptr)
            {
                pApron->SetKnifeGuid(pApronKnife->GetGuid());

                SDKnife* pNewKnife = pApronKnife;
                pNewKnife->SetApronGuid(pApron->GetApronGuid());
                pNewKnife->UpdateOffsetFromApron(pApron->GetXOffset(),pApron->GetYOffset());//同步刀座偏移量
                this->AddKnife(pNewKnife);
            }
        }
        else //根据刀座上的刀具SP，从刀具库中找到刀具指针
        {
            //判断，刀具控制模式是否和刀座控制模式相同
            if (pApron->GetApronCMode() == pApronKnife->GetApronCMode()) //如果相同，就添加到刀具队列
            {

                //if (this->GetActiveKnifeBySp(pApronKnife->GetSp()) != NULL)//可用刀具队列也有此刀具，那么就恢复
                {
                    //添加到配置刀具队列
                    SDKnife* pNewKnife = pApronKnife;//pApronKnife->Copied();
                    pNewKnife->SetApronGuid(pApron->GetApronGuid());
                    pNewKnife->UpdateOffsetFromApron(pApron->GetXOffset(),pApron->GetYOffset());//同步刀座偏移量
                    this->AddKnife(pNewKnife);
                }
                //else
                //{
                //	//可用刀具队列没有，那么就保持禁用
                //}
            }
            else //刀具控制模式是和刀座控制模式不相同
            {
                pApron->SetKnifeGuid(-1);

                //那么就从刀具库中找一个默认的刀具
                pApronKnife = m_stCutToolLib.GetFirstCModeKnife(pApron->GetApronCMode());
                if (pApronKnife != nullptr)
                {
                    pApron->SetKnifeGuid(pApronKnife->GetGuid());

                    SDKnife* pNewKnife = pApronKnife;//pApronKnife->Copied();
                    pNewKnife->SetApronGuid(pApron->GetApronGuid());
                    pNewKnife->UpdateOffsetFromApron(pApron->GetXOffset(),pApron->GetYOffset());//同步刀座偏移量
                    this->AddKnife(pNewKnife);
                }

            }

        }
    }
}

void SDKnifeConfig::SetLocalDir(QString sDir)
{
    m_sLocalDir = sDir;
}

int SDKnifeConfig::GetKnifesCount()
{
    return m_stvKnifes.size();
}
void SDKnifeConfig::FreeKnifes()
{
    m_stvKnifes.clear();
}
QList<SDKnife*>*	SDKnifeConfig::GetKnifes()
{
    return &m_stvKnifes;
}

bool SDKnifeConfig::AddKnife(SDKnife* pKnife)
{
    if (pKnife == nullptr)
        return false;

    SDKnife* pFindKnife = GetKnifeByGuid(pKnife->GetGuid());
    if (pFindKnife != nullptr)
    {
        return false;
    }

    //pKnife->CreateGuid();
    m_stvKnifes.push_back(pKnife);

    return true;
}

SDKnife* SDKnifeConfig::GetKnifeByGuid(int nGuid)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetGuid() == nGuid)
        {
            return pKnife;
        }
    }
    return nullptr;
}

SDKnife* SDKnifeConfig::GetKnifeByName(QString sName)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetKnifeName() == sName)
        {
            return pKnife;
        }
    }
    return nullptr;
}

SDKnife* SDKnifeConfig::GetKnifeByApronGuid(short nApronGuid)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetApronGuid() == nApronGuid)
        {
            return pKnife;
        }
    }
    return nullptr;
}
SDKnife* SDKnifeConfig::GetKnifeByIndex(int nIndex)
{
    if (nIndex < m_stvKnifes.size() && nIndex >= 0)
    {
        return m_stvKnifes.at(nIndex);
    }


    return nullptr;
}

SDKnife* SDKnifeConfig::GetKnife_Pen()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetCutToolId() == CUTTINGTOOL_PEN)
        {
            return pKnife;
        }
    }
    return nullptr;
}
SDKnife* SDKnifeConfig::GetKnife_Mill()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetCutToolId() == CUTTINGTOOL_MILL)
        {
            return pKnife;
        }
    }
    return nullptr;
}
SDKnife* SDKnifeConfig::GetKnife_VCut()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetCutToolId() == CUTTINGTOOL_VCUT)
        {
            return pKnife;
        }
    }
    return nullptr;
}

SDKnife* SDKnifeConfig::GetKnife_VPunch()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        int nCutToolId = pKnife->GetCutInfoId();
        if (nCutToolId == CUTTINGTOOL_VPUNCH)
        {
            short nKnifeId = pKnife->GetKnifeId();
            if (nKnifeId >= 0 && nKnifeId<= 20) //1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
            {
                return pKnife;
            }
        }
    }
    return nullptr;
}

SDKnife* SDKnifeConfig::GetKnife_SPunch()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        int nCutToolId = pKnife->GetCutInfoId();
        if (nCutToolId == CUTTINGTOOL_SPUNCH)
        {
            return pKnife;
        }
        else if (nCutToolId == CUTTINGTOOL_VPUNCH)
        {
            short nKnifeId = pKnife->GetKnifeId();
            if (nKnifeId >= 21 && nKnifeId<= 40) //1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
            {
                return pKnife;
            }
        }
    }

    return nullptr;
}

SDKnife* SDKnifeConfig::GetKnife_RPunch()
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        int nCutToolId = pKnife->GetCutInfoId();
        if (nCutToolId == CUTTINGTOOL_RPUNCH)
        {
            return pKnife;
        }
        else if (nCutToolId == CUTTINGTOOL_VPUNCH)
        {
            short nKnifeId = pKnife->GetKnifeId();
            if (nKnifeId >= 41 && nKnifeId<= 60) //1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
            {
                return pKnife;
            }
        }
    }

    return nullptr;
}

bool     SDKnifeConfig::DeleteKnifeFromKnifes(SDKnife* pKnife)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pSrcKnife = m_stvKnifes.at(i);
        if (pKnife == pSrcKnife)
        {
            m_stvKnifes.erase(m_stvKnifes.begin()+i);
            return true;
        }
    }

    return false;
}

int      SDKnifeConfig::GetKnifeIndexByGuid(int nGuid)
{
    for(int i = 0; i < m_stvKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvKnifes.at(i);
        if (pKnife->GetGuid() == nGuid)
        {
            return i;
        }
    }
    return -1;
}

short    SDKnifeConfig::GetCutToolTypeByGuid(int nGuid)
{
    return static_cast<short>(nGuid&0xff);
}
bool     SDKnifeConfig::IsCutToolType(int nGuid,short nCutToolType)
{
    return (static_cast<short>(nGuid&0xff)==nCutToolType);
}

bool     SDKnifeConfig::IsCutToolType_Punch(int nGuid)
{
    short nCutTool = GUID2CUTTOOLID(nGuid);//(short)(nGuid&0xff);
    if (nCutTool == CUTTINGTOOL_VPUNCH || nCutTool == CUTTINGTOOL_RPUNCH || nCutTool == CUTTINGTOOL_SPUNCH)
        return true;
    return false;
}

bool     SDKnifeConfig::IsKnifeTool_SPunch(int nGuid)
{
    short nCutTool = GUID2CUTTOOLID(nGuid);//(short)(nGuid&0xff);
    if (nCutTool == CUTTINGTOOL_SPUNCH )
    {
        return true;
    }
    else if (nCutTool == CUTTINGTOOL_VPUNCH)
    {
        short nKnifeId = GUID2KNIFEID(nGuid);

        if (nKnifeId >= 21 && nKnifeId <= 40) //1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
        {
            return true;
        }
    }

    return false;
}

bool     SDKnifeConfig::IsKnifeTool_RPunch(int nGuid)
{
    short nCutTool = GUID2CUTTOOLID(nGuid);//(short)(nGuid&0xff);
    if (nCutTool == CUTTINGTOOL_RPUNCH )
    {
        return true;
    }
    else if (nCutTool == CUTTINGTOOL_VPUNCH)
    {
        short nKnifeId = GUID2KNIFEID(nGuid);//(short)((nGuid>>8)&0xff);

        if (nKnifeId >= 41 && nKnifeId <= 60) //1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
        {
            return true;
        }
    }

    return false;
}
bool     SDKnifeConfig::IsKnifeTool_VPTPunch(int nGuid)
{
    short nCutTool = GUID2CUTTOOLID(nGuid);//(short)(nGuid&0xff);

    if (nCutTool == CUTTINGTOOL_VPUNCH)
    {
        short nKnifeId = GUID2KNIFEID(nGuid);//(short)((nGuid>>8)&0xff);

        if (nKnifeId >= 0 && nKnifeId <= 20) //1--20 VPUNCH, 21--40 SPUNCH,41-60 RPUNCH
        {
            return true;
        }
    }
    return false;
}

double   SDKnifeConfig::GetMaxKnifeEtc()
{
    double lfMaxOffset = 0;

    return lfMaxOffset; //

}


//SDKPDesignLib* SDKnifeConfig::GetKPDesignLib()
//{
//    return &m_stKPDesignLib;
//}

//void SDKnifeConfig::GetKPDesignNames(int nSp,CStringArray &arrDesignNames)
//{
//    QList<SDCutInfo*> vCutInfos;
//    m_stKPDesignLib.GetCutInfos(nSp,vCutInfos);

//    CString strName = "";
//    if(!vCutInfos.empty())
//    {
//        for(int i = 0; i < vCutInfos.size(); i++)
//        {
//            SDCutInfo* pCutInfo = vCutInfos.at(i);
//            strName = SDConvert::stringToCString(pCutInfo->GetName());
//            arrDesignNames.Add(strName);
//        }

//    }
//    arrDesignNames.Add("NULL");
//}
//QString SDKnifeConfig::GetKPDesignName(int nDesignId)
//{
//    SDCutInfo* pCutInfo = m_stKPDesignLib.GetCutInfoById(nDesignId);
//    if (pCutInfo == nullptr)
//    {
//        return "NULL";
//    }
//    else
//    {
//        return pCutInfo->GetName();
//    }
//}

SDCutToolLib* SDKnifeConfig::GetCutToolLib()
{
    return &m_stCutToolLib;
}

//////////////////ActiveKnife//////////////////////////////////
void     SDKnifeConfig::LoadActiveKnifes()
{
    FreeActiveKnifes();

    QList<SDApron*> vAprons;
    m_stMachineInfo.GetAllAprons(vAprons);

    for(int i = 0; i < vAprons.size(); i++)
    {
        SDApron* pApron = vAprons.at(i);

        QList<SDKnife*> vKnifes;
        m_stCutToolLib.GetAllKnifesOnCMode(pApron->GetApronCMode(),vKnifes);

        if (!vKnifes.empty())
        {
            for(int j = 0; j < vKnifes.size(); j++)
            {
                m_stvActiveKnifes.push_back(vKnifes[j]);
            }
        }
    }
}
void     SDKnifeConfig::FreeActiveKnifes()
{
    m_stvActiveKnifes.clear();
}
SDKnife* SDKnifeConfig::GetActiveKnifeByGuid(int nGuid)
{
    for(int i = 0; i < m_stvActiveKnifes.size(); i++)
    {
        SDKnife* pKnife = m_stvActiveKnifes.at(i);
        if (pKnife->GetGuid() == nGuid)
        {
            return pKnife;
        }
    }
    return nullptr;
}
//////////////////////MachineInfo//////////////////

SDMachine* SDKnifeConfig::GetMachineInfo()
{
    return &m_stMachineInfo;
}
void SDKnifeConfig::SetMachineInfo(SDMachine* pMachineInfo)
{
    if (pMachineInfo == nullptr)
        return;

    m_stMachineInfo.Copy(pMachineInfo);
}
int SDKnifeConfig::GetPrivateProfileString(QString strSect,QString strKey,QString strDefault,QString *szBuf,QString strConfigPath)
{
    return true;
}
bool SDKnifeConfig::ReadMachineInfo()
{
    //方案2 采用ini格式
    QString strConfigPath = m_sLocalDir;
    strConfigPath += ("\\ToolSet\\CutterSet.ini");

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");

    strSect = ("MachInfo");

    QString strDefault = ("");
    QString sInfo = ("");
    QString *szBuf = nullptr;
    QString sDefault = "";

    m_stMachineInfo.Free();

    int nValue = 0;
    double dbValue = 0;

    //机器类型
    strKey = ("MachType");
    int nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        short nMachineType = sInfo.toShort();
        m_stMachineInfo.SetMachineType(nMachineType);
    }

    //机器子类型
    strKey = ("MachType1");
    nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        short nMachineType = sInfo.toShort();
        m_stMachineInfo.SetSubMachineType(nMachineType);
    }

    //裁床长度
    strKey = ("MachLength");
    nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        dbValue = sInfo.toDouble();
        m_stMachineInfo.SetMachineLength(dbValue);
    }

    //裁床门幅
    strKey = ("MachWidth");
    nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        dbValue = sInfo.toDouble();
        m_stMachineInfo.SetMachineHeight(dbValue);
    }

    //机头数量
    int nHeadCount = 0;
    strKey = ("MachHeadCount");
    nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
    if (nRet > 0)
    {
        sInfo = *szBuf;
        nHeadCount = sInfo.toInt();
    }

    QString strTemp = ("");
    QList<SDMachineHead*>* pHeads = m_stMachineInfo.GetMachineHeads();
    for(int i = 0; i < nHeadCount; i++)
    {
        SDMachineHead* pHead = new SDMachineHead();

        //strSect.Format(("%s%d"),("MachHead"),i);
        strSect = "MachHead" + QString::number(i);

        //横梁序号
        strKey = ("MachBeamIndex");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toShort();
            pHead->SetMachineBeamIndex(static_cast<short>(nValue));
        }

        //机头序号
        strKey = ("MachHeadIndex");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toShort();
            pHead->SetMachineHeadIndex(static_cast<short>(nValue));
        }

        //机头原点X
        strKey = ("MachHeadXOrigon");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetHeadXOrigin(dbValue);
        }

        //机头原点Y
        strKey = ("MachHeadYOrigon");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetHeadYOrigin(dbValue);
        }

        //机头位置X
        strKey = ("MachHeadXPos");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetHeadXPos(dbValue);
        }

        //机头位置Y
        strKey = ("MachHeadYPos");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetHeadYPos(dbValue);
        }

        //实测长度
        strKey = ("ActualLen");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetActualLen(dbValue);
        }
        //预测长度
        strKey = ("ExpectLen");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetExpectLen(dbValue);
        }

        //实测宽度
        strKey = ("ActualWidth");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetActualWidth(dbValue);
        }

        //预测宽度
        strKey = ("ExpectWidth");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetExpectWidth(dbValue);
        }

        //X向比例
        strKey = ("XScale");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetXScale(dbValue);
        }

        //Y向比例
        strKey = ("YScale");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetYScale(dbValue);
        }

        //实测长度[喷墨]
        strKey = ("PlotActualLen");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPlotActualLen(dbValue);
        }

        //预测长度[喷墨]
        strKey = ("PlotExpectLen");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPlotExpectLen(dbValue);
        }

        //实测宽度[喷墨]
        strKey = ("PlotActualWidth");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPlotActualWidth(dbValue);
        }

        //预测宽度[喷墨]
        strKey = ("PlotExpectWidth");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPlotExpectWidth(dbValue);
        }

        //X向比例[喷墨]
        strKey = ("PlotXScale");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPlotXScale(dbValue);
        }

        //Y向比例[喷墨]
        strKey = ("PlotYScale");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPlotYScale(dbValue);
        }


        //笔偏移X
        strKey = ("PenOffsetX");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPenXOffset(dbValue);
        }

        //笔偏移Y
        strKey = ("PenOffsetY");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetPenYOffset(dbValue);
        }

        //红光定位 X偏移
        strKey = ("GlowOffsetX");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetGlowXOffset(dbValue);
        }

        //红光定位 Y偏移
        strKey = ("GlowOffsetY");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetGlowYOffset(dbValue);
        }

        //摄像头 X偏移
        strKey = ("CameraOffsetX");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetCameraXOffset(dbValue);
        }

        //摄像头 Y偏移
        strKey = ("CameraOffsetY");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetCameraYOffset(dbValue);
        }

        //摄像头 高度
        strKey = ("CameraHeight");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetCameraHeight(dbValue);
        }

        //切割模式
        strKey = ("CuttingMode");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toInt();
            pHead->SetCuttingMode(static_cast<short>(nValue));
        }

        //减震模式
        strKey = ("DecoupleMode");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toInt();
            pHead->SetDecoupleMode(static_cast<short>(nValue));
        }
        //送料长度
        strKey = ("FeedLen");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetFeedLen(dbValue);
        }

        //送料速度(m/s)
        strKey = ("FeedSpeed");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetFeedSpeed(dbValue);
        }

        //压料时间(s)
        strKey = ("SwagingTime");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetSwagingTime(dbValue);
        }

        //空走速度 (m/s)
        strKey = ("IdleMoveSpeed");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetIdleMoveSpeed(dbValue);
        }

        //空走加速度(G)
        strKey = ("IdleMoveAcc");//Acceleration
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetIdleMoveAcceleration(dbValue);
        }

        //减速边界
        strKey = ("ReducerEdge");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetReducerEdge(dbValue);
        }

        //吸气延迟时间(ms)
        strKey = ("InhaleDelayTime");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetInhaleDelayTime(dbValue);
        }

        //最后一条切割的直线段id
        strKey = ("LastCutLineId");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toInt();
            pHead->SetLastcutLineId(static_cast<long>(nValue));
        }

        //最后一条打印的直线段id
        strKey = ("LastPlotLineId");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toInt();
            pHead->SetLastPlotLineId(static_cast<long>(nValue));
        }

        //打印标记
        strKey = ("LastPlotFlag");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            nValue = sInfo.toInt();
            pHead->SetLastPlotFlag(nValue);
        }

        //扫描长度
        strKey = ("ScanLen");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetScanLen(dbValue);
        }

        //扫描速度(m/s)
        strKey = ("ScanSpeed");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetScanSpeed(dbValue);
        }

        //扫描加速度(G)
        strKey = ("ScanAcc");
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szBuf;
            dbValue = sInfo.toDouble();
            pHead->SetScanAcceleration(dbValue);
        }

        //刀座和刀座信息
        QList<QString> vApronsIndex;
        strKey = ("Aprons");

        QString *szApronsBuf = nullptr;
        nRet = GetPrivateProfileString(strSect, strKey, strDefault, szApronsBuf, strConfigPath);
        if (nRet > 0)
        {
            sInfo = *szApronsBuf;
            //SDString::Splitstring(sInfo,',',vApronsIndex);
            vApronsIndex = sInfo.split(',');
            short nTempValue = 0;
            int nApronsSize = vApronsIndex.size();
            for(int h = 0; h < vApronsIndex.size(); h+=1)
            {
                SDApron* pApron = new SDApron();

                nTempValue = static_cast<short>(vApronsIndex.at(h).toInt());
                pApron->SetApronIndex(nTempValue);

                pHead->AddApron(pApron);
            }

            //刀座信息
            QList<SDApron*>* pAprons = pHead->GetAprons();
            for(int k = 0; k < pAprons->size(); k++)
            {
                SDApron* pApron = pAprons->at(k);
                //strKey.Format(("Apron%d"),pApron->GetApronIndex());
                strKey = "Apron" + QString::number(pApron->GetApronIndex());
                QString *szApronsBuf1 = nullptr;
                int nRet1 = GetPrivateProfileString(strSect, strKey, strDefault, szApronsBuf1, strConfigPath);
                if (nRet1 > 0)
                {
                    QList<QString> vApronInfos;
                    sInfo = *szApronsBuf1;
                    //SDString::Splitstring(sInfo,',',vApronInfos);
                    vApronInfos = sInfo.split(',');
                    short nTempValue = 0;
                    int nInfoSize = vApronInfos.size();
                    if (nInfoSize >= 5)
                    {
                        nTempValue = static_cast<short>(vApronInfos.at(0).toInt());
                        pApron->SetApronCMode(nTempValue);

                        //
                        int nCutToolId = vApronInfos.at(1).toInt();
                        int nKnifeId = vApronInfos.at(2).toInt();
                        int nGuid = KNIFETOOLID2GUID(nCutToolId,nKnifeId);
                        pApron->SetKnifeGuid(nGuid);

                        pApron->SetXOffset(vApronInfos[3].toDouble());
                        pApron->SetYOffset(vApronInfos[4].toDouble());
                    }
                }
            }
        }

        if (pHead->GetApronsCount() <=0 )
        {
            pHead->InitApron();
        }

        //机头
        m_stMachineInfo.AddMachineHead(pHead);
    }

    //保证至少有一个机头结构
    if (nHeadCount <= 0)
    {
        SDMachineHead* pHead = new SDMachineHead();
        pHead->InitApron();
        m_stMachineInfo.AddMachineHead(pHead);
    }

    return true;
}
void SDKnifeConfig::WritePrivateProfileString(QString strSect,QString strKey,QString strText,QString strConfigPath)
{

}
bool SDKnifeConfig::SaveMachineInfo()
{
    //方案2 采用ini格式保存
    QString strConfigPath = m_sLocalDir;
    strConfigPath += ("\\ToolSet\\CutterSet.ini");

    QString strSect = ("");
    QString strKey = ("");
    QString strText = ("");

    strSect = ("MachInfo");

    //机器类型
    strKey = ("MachType");
    //strText.Format(("%hd"),m_stMachineInfo.GetMachineType());
    strText = QString::number(m_stMachineInfo.GetMachineType());
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    //机器子类型
    strKey = ("MachType1");
    //strText.Format(("%hd"),m_stMachineInfo.GetSubMachineType());
    strText = QString::number(m_stMachineInfo.GetSubMachineType());
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    //裁床长度
    strKey = ("MachLength");
    //strText.Format(("%.4lf"),m_stMachineInfo.GetMachineLength());
    strText = QString::number(m_stMachineInfo.GetMachineLength());
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    //裁床门幅
    strKey = ("MachWidth");
    //strText.Format(("%.4lf"),m_stMachineInfo.GetMachineHeight());
    strText = QString::number(m_stMachineInfo.GetMachineHeight());
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    //机头数量
    strKey = ("MachHeadCount");
    //strText.Format(("%d"),m_stMachineInfo.GetMachineHeadCount());
    strText = QString::number(m_stMachineInfo.GetMachineHeadCount());
    WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

    QString strTemp = ("");
    QList<SDMachineHead*>* pHeads = m_stMachineInfo.GetMachineHeads();
    for(int i = 0; i < pHeads->size(); i++)
    {
        SDMachineHead* pHead = pHeads->at(i);

        //strSect.Format(("%s%d"),("MachHead"),i);
        strSect = "MachHead" + QString::number(i);

        //机头序号
        strKey = ("MachBeamIndex");
        //strText.Format(("%hd"),pHead->GetMachineBeamIndex());
        strText = QString::number(pHead->GetMachineBeamIndex());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //机头序号
        strKey = ("MachHeadIndex");
        //strText.Format(("%hd"),pHead->GetMachineHeadIndex());
        strText = QString::number(pHead->GetMachineHeadIndex());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //机头原点X
        strKey = ("MachHeadXOrigon");
        //strText.Format(("%.4lf"),pHead->GetHeadXOrigin());
        strText = QString::number(pHead->GetHeadXOrigin());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //机头原点Y
        strKey = ("MachHeadYOrigon");
        //strText.Format(("%.4lf"),pHead->GetHeadYOrigin());
        strText = QString::number(pHead->GetHeadYOrigin());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //机头位置X
        strKey = ("MachHeadXPos");
        //strText.Format(("%.4lf"),pHead->GetHeadXPos());
        strText = QString::number(pHead->GetHeadXPos());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //机头位置Y
        strKey = ("MachHeadYPos");
        //strText.Format(("%.4lf"),pHead->GetHeadYPos());
        strText = QString::number(pHead->GetHeadYPos());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //实测长度
        strKey = ("ActualLen");
        //strText.Format(("%.4lf"),pHead->GetActualLen());
        strText = QString::number(pHead->GetActualLen());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //预测长度
        strKey = ("ExpectLen");
        //strText.Format(("%.4lf"),pHead->GetExpectLen());
        strText = QString::number(pHead->GetExpectLen());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //实测宽度
        strKey = ("ActualWidth");
        //strText.Format(("%.4lf"),pHead->GetActualWidth());
        strText = QString::number(pHead->GetActualWidth());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //预测宽度
        strKey = ("ExpectWidth");
        //strText.Format(("%.4lf"),pHead->GetExpectWidth());
        strText = QString::number(pHead->GetExpectWidth());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //X向比例
        strKey = ("XScale");
        //strText.Format(("%.4lf"),pHead->GetXScale());
        strText = QString::number(pHead->GetXScale());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //Y向比例
        strKey = ("YScale");
        //strText.Format(("%.4lf"),pHead->GetYScale());
        strText = QString::number(pHead->GetYScale());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //实测长度[喷墨]
        strKey = ("PlotActualLen");
        //strText.Format(("%.4lf"),pHead->GetPlotActualLen());
        strText = QString::number(pHead->GetPlotActualLen());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //预测长度[喷墨]
        strKey = ("PlotExpectLen");
        //strText.Format(("%.4lf"),pHead->GetPlotExpectLen());
        strText = QString::number(pHead->GetPlotExpectLen());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //实测宽度[喷墨]
        strKey = ("PlotActualWidth");
        //strText.Format(("%.4lf"),pHead->GetPlotActualWidth());
        strText = QString::number(pHead->GetPlotActualWidth());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //预测宽度[喷墨]
        strKey = ("PlotExpectWidth");
        //strText.Format(("%.4lf"),pHead->GetPlotExpectWidth());
        strText = QString::number(pHead->GetPlotExpectWidth());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //X向比例[喷墨]
        strKey = ("PlotXScale");
        //strText.Format(("%.4lf"),pHead->GetPlotXScale());
        strText = QString::number(pHead->GetPlotXScale());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //Y向比例[喷墨]
        strKey = ("PlotYScale");
        //strText.Format(("%.4lf"),pHead->GetPlotYScale());
        strText = QString::number(pHead->GetPlotYScale());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //笔偏移X
        strKey = ("PenOffsetX");
        //strText.Format(("%.4lf"),pHead->GetPenXOffset());
        strText = QString::number(pHead->GetPenXOffset());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //笔偏移Y
        strKey = ("PenOffsetY");
        //strText.Format(("%.4lf"),pHead->GetPenYOffset());
        strText = QString::number(pHead->GetPenYOffset());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //红光定位 X偏移
        strKey = ("GlowOffsetX");
        //strText.Format(("%.4lf"),pHead->GetGlowXOffset());
        strText = QString::number(pHead->GetGlowXOffset());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //红光定位 Y偏移
        strKey = ("GlowOffsetY");
        //strText.Format(("%.4lf"),pHead->GetGlowYOffset());
        strText = QString::number(pHead->GetGlowYOffset());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //摄像头 X偏移
        strKey = ("CameraOffsetX");
        //strText.Format(("%.4lf"),pHead->GetCameraXOffset());
        strText = QString::number(pHead->GetCameraXOffset());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //摄像头 Y偏移
        strKey = ("CameraOffsetY");
        //strText.Format(("%.4lf"),pHead->GetCameraYOffset());
        strText = QString::number(pHead->GetCameraYOffset());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //摄像头 高度
        strKey = ("CameraHeight");
        //strText.Format(("%.6lf"),pHead->GetCameraHeight());
        strText = QString::number(pHead->GetCameraHeight());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //切割模式
        strKey = ("CuttingMode");
        //strText.Format(("%hd"),pHead->GetCuttingMode());
        strText = QString::number(pHead->GetCuttingMode());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //减震模式
        strKey = ("DecoupleMode");
        //strText.Format(("%hd"),pHead->GetDecoupleMode());
        strText = QString::number(pHead->GetDecoupleMode());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //送料长度
        strKey = ("FeedLen");
        //strText.Format(("%.4lf"),pHead->GetFeedLen());
        strText = QString::number(pHead->GetFeedLen());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //送料速度(m/s)
        strKey = ("FeedSpeed");
        //strText.Format(("%.4lf"),pHead->GetFeedSpeed());
        strText = QString::number(pHead->GetFeedSpeed());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //压料时间(s)
        strKey = ("SwagingTime");
        //strText.Format(("%.4lf"),pHead->GetSwagingTime());
        strText = QString::number(pHead->GetSwagingTime());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //空走速度 (m/s)
        strKey = ("IdleMoveSpeed");
        //strText.Format(("%.4lf"),pHead->GetIdleMoveSpeed());
        strText = QString::number(pHead->GetIdleMoveSpeed());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //空走加速度(G)
        strKey = ("IdleMoveAcc");
        //strText.Format(("%.4lf"),pHead->GetIdleMoveAcceleration());
        strText = QString::number(pHead->GetIdleMoveAcceleration());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //减速边界
        strKey = ("ReducerEdge");
        //strText.Format(("%.4lf"),pHead->GetReducerEdge());
        strText = QString::number(pHead->GetReducerEdge());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //吸气延迟时间(ms)
        strKey = ("InhaleDelayTime");
        //strText.Format(("%.4lf"),pHead->GetInhaleDelayTime());
        strText = QString::number(pHead->GetInhaleDelayTime());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //最后一条切割的直线段id
        strKey = ("LastCutLineId");
        //strText.Format(("%ld"),pHead->GetLastCutLineId());
        strText = QString::number(pHead->GetLastCutLineId());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //最后一条打印的直线段id
        strKey = ("LastPlotLineId");
        //strText.Format(("%ld"),pHead->GetLastPlotLineId());
        strText = QString::number(pHead->GetLastPlotLineId());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //打印标记
        strKey = ("LastPlotFlag");
        //strText.Format(("%d"),pHead->GetLastPlotFlag());
        strText = QString::number(pHead->GetLastPlotFlag());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //扫描长度
        strKey = ("ScanLen");
        //strText.Format(("%.4lf"),pHead->GetScanLen());
        strText = QString::number(pHead->GetScanLen());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //扫描速度(m/s)
        strKey = ("ScanSpeed");
        //strText.Format(("%.4lf"),pHead->GetScanSpeed());
        strText = QString::number(pHead->GetScanSpeed());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //扫描加速度(G)
        strKey = ("ScanAcc");
        //strText.Format(("%.4lf"),pHead->GetScanAcceleration());
        strText = QString::number(pHead->GetScanAcceleration());
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        //刀座信息
        QList<SDApron*> *pAprons = pHead->GetAprons();
        strText = ("");
        for(int j = 0; j < pAprons->size(); j++)
        {
            SDApron* pApron = pAprons->at(j);
            if (j == 0)
            {
                //strTemp.Format(("%hd"),pApron->GetApronIndex());
                strTemp = QString::number(pApron->GetApronIndex());
            }
            else
            {
                //strTemp.Format((",%hd"),pApron->GetApronIndex());
                strTemp = ',' + QString::number(pApron->GetApronIndex());
            }
            strText += strTemp;
        }
        strKey = ("Aprons");
        WritePrivateProfileString(strSect, strKey, strText, strConfigPath);

        QString strIndex = "";
        for(int k = 0; k < pAprons->size(); k++)
        {
            SDApron* pApron = pAprons->at(k);

            //strKey.Format(("Apron%hd"),pApron->GetApronIndex());
            strKey = "Apron" + QString::number(pApron->GetApronIndex());

            int nGuid = pApron->GetKnifeGuid();
            int nCutToolId = GUID2CUTTOOLID(nGuid);
            int nKnifeId = GUID2KNIFEID(nGuid);
            //strText.Format(("%hd,%d,%d,%.4lf,%.4lf"),
            //pApron->GetApronCMode(),nCutToolId,nKnifeId,pApron->GetXOffset(),pApron->GetYOffset());
            strText = QString::number(pApron->GetApronCMode()) +',' +
                    QString::number(nCutToolId) + ',' +
                    QString::number(nKnifeId) + ',' +
                    QString::number(pApron->GetXOffset()) + ',' +
                    QString::number(pApron->GetYOffset());
            WritePrivateProfileString(strSect, strKey, strText, strConfigPath);
        }
    }

    return true;
}

void SDKnifeConfig::GetAllAprons(QList<SDApron*> &vAprons)
{
    m_stMachineInfo.GetAllAprons(vAprons);
}

void SDKnifeConfig::SaveLastCutLine()
{
    QString strFile = m_sLocalDir;
    strFile += ("\\ToolSet\\CutterSet.ini");

    QString strSect = ("Apron");
    QString strKey = ("LastLineId");
    QString strValue = ("");
    QList<SDMachineHead*>* pHeads = m_stMachineInfo.GetMachineHeads();
    for(int j = 0; j < pHeads->size(); j++)
    {
        SDMachineHead* pHead = pHeads->at(j);

        //strSect.Format(("Apron%d"),j);
        strSect = "Apron" + QString::number(j);

        //strValue.Format(("%ld"),pHead->GetLastCutLineId());
        strValue = QString::number(pHead->GetLastCutLineId());
        WritePrivateProfileString(strSect, strKey, strValue, strFile);
    }
}

void SDKnifeConfig::SaveLastPlotLine()
{
    QString strFile = m_sLocalDir;
    strFile += ("\\ToolSet\\CutterConfig.ini");

    QString strSect = ("Apron");
    QString strKey = ("LastPlotLineId");
    QString strKey1 = ("LastPlotFlag");
    QString strValue = ("");
    QList<SDMachineHead*>* pHeads = m_stMachineInfo.GetMachineHeads();
    for(int j = 0; j < pHeads->size(); j++)
    {
        SDMachineHead* pHead = pHeads->at(j);

        //strSect.Format(("Apron%d"),j);
        strSect = "Apron" + QString::number(j);

        //strValue.Format(("%ld"),pHead->GetLastPlotLineId());
        strValue = QString::number(pHead->GetLastPlotLineId());

        WritePrivateProfileString(strSect, strKey, strValue, strFile);

        //strValue.Format(("%ld"),pHead->GetLastPlotFlag());
        strValue = QString::number(pHead->GetLastPlotFlag());

        WritePrivateProfileString(strSect, strKey1, strValue, strFile);
    }
}

void SDKnifeConfig::LoadLastCutLine()
{
    QString strFile = m_sLocalDir;
    strFile += ("\\ToolSet\\CutterSet.ini");

    QString strSect = ("Apron");
    QString strKey = ("LastLineId");
    QString strValue = ("");
    QString strKey1 = ("LastPlotLineId");
    QString strKey2 = ("LastPlotFlag");

    QString *pData = nullptr;

    QList<SDMachineHead*>* pHeads = m_stMachineInfo.GetMachineHeads();
    for(int j = 0; j < pHeads->size(); j++)
    {
        SDMachineHead* pHead = pHeads->at(j);

        //strSect.Format(("Apron%d"),j);
        strSect = "Apron" + QString::number(j);


        int nRet = GetPrivateProfileString(strSect, strKey, ("0"), pData,strFile);

        strValue = *pData;
        pHead->SetLastcutLineId(strValue.toLong());

        nRet = GetPrivateProfileString(strSect, strKey1, ("-1"), pData,strFile);

        strValue = *pData;
        pHead->SetLastPlotLineId(strValue.toLong());

        nRet = GetPrivateProfileString(strSect, strKey2, ("0"), pData,strFile);

        strValue = *pData;
        pHead->SetLastPlotFlag(strValue.toLong());
    }

    //释放内存
    free(pData);
}

int SDKnifeConfig::GetLastCuttingLineId()
{
    //暂时 获取第一个机头的最后一条切割线id号
    SDMachineHead* pHead = m_stMachineInfo.GetFirstHead();
    if (pHead != nullptr)
    {
        return pHead->GetLastCutLineId();
    }

    return -1;
}
int SDKnifeConfig::GetLastPlottingLineId()
{
    //暂时 获取第一个机头的最后一条打印id号
    SDMachineHead* pHead = m_stMachineInfo.GetFirstHead();
    if (pHead != nullptr)
    {
        return pHead->GetLastPlotLineId();
    }

    return -1;
}
int SDKnifeConfig::GetLastPlottingFlag()
{
    //暂时 获取第一个机头的最后一条打印id号
    SDMachineHead* pHead = m_stMachineInfo.GetFirstHead();
    if (pHead != nullptr)
    {
        return pHead->GetLastPlotFlag();
    }

    return -1;
}
int SDKnifeConfig::GetLastCuttingLineSp()
{
    int nSp = -1;
    //SJPolyline* pLine = g_sTaskLib.GetLastCuttingLine(GetLastCuttingLineId());
    //if (pLine != nullptr)
    //{
    //	return pLine->GetSpValue();
    //}
    return nSp;
}
//////////////////////DefaultCutInfo//////////////////

void	   SDKnifeConfig::SetMateriaThick(double dbValue)
{
    m_dbMaterialThick = dbValue;
}
double     SDKnifeConfig::GetMateriaThick()
{
    return m_dbMaterialThick;
}

//SDCutInfo* SDKnifeConfig::GetCutInfo()
//{
//    return &m_stCutInfo;
//}
//void       SDKnifeConfig::SetCutInfo(SDCutInfo* pCutInfo)
//{
//    if (pCutInfo == nullptr)
//        return;

//    m_stCutInfo.Copy(pCutInfo);
//}

bool       SDKnifeConfig::ReadCutInfo()
{
    QString sPath = m_sLocalDir;
    sPath += "\\DConfig\\Config.ini";

    QString sSect = "DefaultInfo";
//    m_stCutInfo.ReadEx(sPath,sSect,0);

    return true;
}
//bool       SDKnifeConfig::SaveCutInfo()
//{
//    QString sPath = m_sLocalDir;
//    sPath += "\\DConfig\\Config.ini";

//    QString sSect = "DefaultInfo";
//    m_stCutInfo.SaveEx(sPath,sSect,0);

//    return true;
//}


//////////////////////DefaultKnife//////////////////
SDKnife* SDKnifeConfig::GetDefaultKnife()
{
    return &m_stDefaultknife;
}
void     SDKnifeConfig::SetDefaultKnife(SDKnife* pTestKnife)
{
    if (pTestKnife == nullptr)
        return;

    m_stDefaultknife.SetDefaultKnifeInfo(pTestKnife);
}
