//
// Created by czh on 18-9-20.
//

#include "command.h"

Command::Command() {
    key = Key_Defalt;
    rotate = Rotate_Defalt;
    QDBusConnection connection = QDBusConnection::sessionBus();
    while (!connection.isConnected()) {
        QThread::msleep(200);
        std::cout << "Error: sessionBus noConnected " << std::endl;
    }
    connection.connect(QString(), QString("/com/dbus/j59r/vipservice/hmi"), "local.vipservice.HmiMessage",
                       "commandRotary", this, SLOT(commandRotary(int, int)));
    connection.connect(QString(), QString("/com/dbus/j59r/vipservice/hmi"), "local.vipservice.HmiMessage", "keyEvent",
                       this, SLOT(keyEvent(int, int)));
}

void Command::commandRotary(int m, int n) {
    std::cout << "#commandRotary:[" << m << ", " << n << "]" << std::endl;
    QDBusReply<void> reply;
    if (m == 0 && n == 1) {
        rotate = Rotate_Right;
    } else if (m == 1 && n == 1) {
        rotate =  Rotate_Left;
    }
}

void Command::keyEvent(int m, int n) {
    std::cout << "#keyEvent:[" << m << ", " << n << "]" << std::endl;
    if (m == 11 && n == 1) {
        key = Key_Confirm;
    } else if (m == 17 && n == 1) {
        key = Key_Cancel;
    } else if (m == 15 && n == 1) {
        key = Key_Music;
    } else if (m == 14 && n == 1) {
        key = Key_Fly;
    } else if (m == 13 && n == 1) {
        key = Key_Homepage;
    }
}