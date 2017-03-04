#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <vector>
#include <map>

using namespace std;

class Robot: public QObject
{
     Q_OBJECT
public:
     explicit Robot(QObject *parent=0);
     ~Robot();

public slots:
     void getTask();
private:

};
#endif // ROBOT_H
