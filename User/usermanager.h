#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDialog>
#include "user.h"
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
public:
    void SetUser(User *_user);
    void InitialModel();

public:

};

#endif // USERMANAGER_H
