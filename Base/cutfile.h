#ifndef CUTFILE_H
#define CUTFILE_H

#include <QObject>
#include "cutpage.h"
class CutFile : public QObject
{
    Q_OBJECT
private:
    QList<CutPage*> *m_qlcFile = new QList<CutPage*>;
    QString         m_qstrFileName;
    QString         m_qstrFilePath;
    int             m_nTimes;//切割次数
public:
    explicit CutFile(QObject *parent = nullptr);
    void    AddCutPage(CutPage *page,int _len);

    void    SetFilePath(QString _path);
    QString GetFilePath(void);

    void    SetFileName(QString _name);
    QString GetFileName(void);

    void    SetCutTimes(int _times);
    int     GetCutTimes(void);

    CutPage* GetPage(int _index);
    QList<CutPage*> *GetPageList();

    bool    ReduceCutTimes();//切割次数减少，减为0则返回false。
    void    ResetFileState();//重置文档状态
signals:

public slots:
};

#endif // CUTFILE_H
