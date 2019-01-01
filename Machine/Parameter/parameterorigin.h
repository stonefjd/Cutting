#ifndef PARAMETERORIGIN_H
#define PARAMETERORIGIN_H

#include <QObject>
#include <QSettings>

class ParameterOrigin : public QObject
{
    Q_OBJECT
public:
    explicit ParameterOrigin(QObject *parent = nullptr);

signals:

public slots:

private:
    QString pathSettingFile;

};

#endif // PARAMETERORIGIN_H
