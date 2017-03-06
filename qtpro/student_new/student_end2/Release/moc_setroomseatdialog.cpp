/****************************************************************************
** Meta object code from reading C++ file 'setroomseatdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VM_Code/setroomseatdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'setroomseatdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SetRoomSeatDialog_t {
    QByteArrayData data[7];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SetRoomSeatDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SetRoomSeatDialog_t qt_meta_stringdata_SetRoomSeatDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SetRoomSeatDialog"
QT_MOC_LITERAL(1, 18, 23), // "on_OKpushButton_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 27), // "on_CancelpushButton_clicked"
QT_MOC_LITERAL(4, 71, 30), // "on_RoomNumlineEdit_textChanged"
QT_MOC_LITERAL(5, 102, 4), // "arg1"
QT_MOC_LITERAL(6, 107, 30) // "on_SeatNumlineEdit_textChanged"

    },
    "SetRoomSeatDialog\0on_OKpushButton_clicked\0"
    "\0on_CancelpushButton_clicked\0"
    "on_RoomNumlineEdit_textChanged\0arg1\0"
    "on_SeatNumlineEdit_textChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SetRoomSeatDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    1,   36,    2, 0x08 /* Private */,
       6,    1,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void SetRoomSeatDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SetRoomSeatDialog *_t = static_cast<SetRoomSeatDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_OKpushButton_clicked(); break;
        case 1: _t->on_CancelpushButton_clicked(); break;
        case 2: _t->on_RoomNumlineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_SeatNumlineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SetRoomSeatDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SetRoomSeatDialog.data,
      qt_meta_data_SetRoomSeatDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SetRoomSeatDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SetRoomSeatDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SetRoomSeatDialog.stringdata0))
        return static_cast<void*>(const_cast< SetRoomSeatDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SetRoomSeatDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
