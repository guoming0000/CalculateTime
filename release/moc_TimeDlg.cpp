/****************************************************************************
** Meta object code from reading C++ file 'TimeDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../TimeDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TimeDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CTimeDlg_t {
    QByteArrayData data[7];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTimeDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTimeDlg_t qt_meta_stringdata_CTimeDlg = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CTimeDlg"
QT_MOC_LITERAL(1, 9, 16), // "startTimeChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "text"
QT_MOC_LITERAL(4, 32, 17), // "passedTimeChanged"
QT_MOC_LITERAL(5, 50, 18), // "calculateToNowTime"
QT_MOC_LITERAL(6, 69, 8) // "pressBtn"

    },
    "CTimeDlg\0startTimeChanged\0\0text\0"
    "passedTimeChanged\0calculateToNowTime\0"
    "pressBtn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTimeDlg[] = {

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
       1,    1,   34,    2, 0x08 /* Private */,
       4,    1,   37,    2, 0x08 /* Private */,
       5,    0,   40,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CTimeDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CTimeDlg *_t = static_cast<CTimeDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startTimeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->passedTimeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->calculateToNowTime(); break;
        case 3: _t->pressBtn(); break;
        default: ;
        }
    }
}

const QMetaObject CTimeDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CTimeDlg.data,
      qt_meta_data_CTimeDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CTimeDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTimeDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CTimeDlg.stringdata0))
        return static_cast<void*>(const_cast< CTimeDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CTimeDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
