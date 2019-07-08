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
    int             m_qstrTimes;//切割次数
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

signals:

public slots:
};

#endif // CUTFILE_H
