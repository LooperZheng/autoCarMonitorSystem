/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 11),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 18),
QT_MOC_LITERAL(4, 43, 18),
QT_MOC_LITERAL(5, 62, 18),
QT_MOC_LITERAL(6, 81, 18),
QT_MOC_LITERAL(7, 100, 12),
QT_MOC_LITERAL(8, 113, 28),
QT_MOC_LITERAL(9, 142, 11),
QT_MOC_LITERAL(10, 154, 12),
QT_MOC_LITERAL(11, 167, 11),
QT_MOC_LITERAL(12, 179, 2),
QT_MOC_LITERAL(13, 182, 12),
QT_MOC_LITERAL(14, 195, 11),
QT_MOC_LITERAL(15, 207, 12),
QT_MOC_LITERAL(16, 220, 11),
QT_MOC_LITERAL(17, 232, 12),
QT_MOC_LITERAL(18, 245, 11)
    },
    "MainWindow\0sendFortune\0\0acceptConnection_1\0"
    "acceptConnection_2\0acceptConnection_3\0"
    "acceptConnection_4\0DisplayError\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "ReadMyData_1\0ShowImage_1\0ba\0ReadMyData_2\0"
    "ShowImage_2\0ReadMyData_3\0ShowImage_3\0"
    "ReadMyData_4\0ShowImage_4\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a,
       3,    0,   85,    2, 0x0a,
       4,    0,   86,    2, 0x0a,
       5,    0,   87,    2, 0x0a,
       6,    0,   88,    2, 0x0a,
       7,    1,   89,    2, 0x0a,
      10,    0,   92,    2, 0x0a,
      11,    1,   93,    2, 0x0a,
      13,    0,   96,    2, 0x0a,
      14,    1,   97,    2, 0x0a,
      15,    0,  100,    2, 0x0a,
      16,    1,  101,    2, 0x0a,
      17,    0,  104,    2, 0x0a,
      18,    1,  105,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   12,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->sendFortune(); break;
        case 1: _t->acceptConnection_1(); break;
        case 2: _t->acceptConnection_2(); break;
        case 3: _t->acceptConnection_3(); break;
        case 4: _t->acceptConnection_4(); break;
        case 5: _t->DisplayError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->ReadMyData_1(); break;
        case 7: _t->ShowImage_1((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->ReadMyData_2(); break;
        case 9: _t->ShowImage_2((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 10: _t->ReadMyData_3(); break;
        case 11: _t->ShowImage_3((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 12: _t->ReadMyData_4(); break;
        case 13: _t->ShowImage_4((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
