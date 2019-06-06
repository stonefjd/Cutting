#include "userhandle.h"

UserHandle::UserHandle(QObject *parent) : QObject(parent)
{
    UI_userLog = new UserLog;
    UI_userManager = new UserManager;

    UI_userLog->SetUser(&user);
    UI_userManager->SetUser(&user);


    UI_userLog->setModal(true);
    UI_userLog->exec();
}
bool UserHandle::GetUserChecked()
{
    return user.GetUserIsChecked();
}
void UserHandle::ShowManagerMent()
{
    UI_userManager->InitialModel();
    UI_userManager->setModal(true);
    UI_userManager->exec();
}
