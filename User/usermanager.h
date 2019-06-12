#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDialog>
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
#include "user.h"
enum OperatorType
{
    NOOP,WRITE,READ,DELETE,ADD,
};

namespace Ui {
class UserManager;
}

class UserManager : public QDialog
{
    Q_OBJECT

public:
    explicit UserManager(QWidget *parent = nullptr);
    ~UserManager();

private:
    Ui::UserManager *ui;
    User *user;
    QSqlTableModel *plainModel;

//    QList<QLabel*> m_infoLabelList;
//    QList<QWidget*> m_infoEditList;
    OperatorType m_operator= NOOP;
private:
    void SetUIByOperator();
public:
    void SetUser(User *_user);
    void InitialModel();

public:

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_write_clicked();
    void on_pushButton_delete_clicked();
    void on_lineEdit_search_textChanged(const QString &arg1);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_tableView_clicked(const QModelIndex &index);
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // USERMANAGER_H
