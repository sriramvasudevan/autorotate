/****************************************************************************
** Meta object code from reading C++ file 'tesqprocess.h'
**
** Created: Mon Jul 15 14:50:33 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tesqprocess.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tesqprocess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_tesQProcess[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      28,   12,   12,   12, 0x08,
      43,   12,   12,   12, 0x08,
      67,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_tesQProcess[] = {
    "tesQProcess\0\0rightMessage()\0wrongMessage()\0"
    "on_btnProcess_clicked()\0"
    "on_btnProcess2_clicked()\0"
};

void tesQProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        tesQProcess *_t = static_cast<tesQProcess *>(_o);
        switch (_id) {
        case 0: _t->rightMessage(); break;
        case 1: _t->wrongMessage(); break;
        case 2: _t->on_btnProcess_clicked(); break;
        case 3: _t->on_btnProcess2_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData tesQProcess::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject tesQProcess::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_tesQProcess,
      qt_meta_data_tesQProcess, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &tesQProcess::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *tesQProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *tesQProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_tesQProcess))
        return static_cast<void*>(const_cast< tesQProcess*>(this));
    return QDialog::qt_metacast(_clname);
}

int tesQProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
