#ifndef RECORDS_H
#define RECORDS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <QTranslator>
class Records : public QObject
{
    Q_OBJECT

private:
    QStringList recordsFileDir;

public:
    explicit Records(QObject *parent = nullptr);
    void        fileDir_Chose();
    QStringList fileDir_Get();

signals:

public slots:
};

#endif // RECORDS_H
