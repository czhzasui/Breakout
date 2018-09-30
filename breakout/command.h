//
// Created by czh on 18-9-20.
//

#ifndef OPENGL_ES_COMMAND_H
#define OPENGL_ES_COMMAND_H

#include <QObject>
#include <QCoreApplication>
#include <QtDBus>
#include <iostream>
#include <tiff.h>

enum Key {
    Key_Defalt,
    Key_Confirm,
    Key_Cancel,
    Key_Music,
    Key_Fly,
    Key_Homepage
};

enum Rotate {
    Rotate_Defalt,
    Rotate_Right,
    Rotate_Left
};

class Command : public QObject {
Q_OBJECT
public:
    Key key;

    Rotate rotate;

    Command();

public slots:

    void commandRotary(int m, int n);

    void keyEvent(int m, int n);
};


#endif //OPENGL_ES_COMMAND_H
