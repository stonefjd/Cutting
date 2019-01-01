#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QTreeView>
#include <QListWidget>
#include <QDebug>

#pragma execution_character_set("utf-8")
namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::Settings *ui;

};

#endif // SETTINGS_H
