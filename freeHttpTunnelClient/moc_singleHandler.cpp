/****************************************************************************
** Meta object code from reading C++ file 'singleHandler.h'
**
** Created: Sun May 1 20:27:22 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "singleHandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'singleHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_singlehandler[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   14,   14,   14, 0x0a,
      61,   14,   14,   14, 0x0a,
      80,   14,   14,   14, 0x0a,
     104,   14,   14,   14, 0x0a,
     128,   15,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_singlehandler[] = {
    "singlehandler\0\0message\0someError(QString)\0"
    "dataFromInternal()\0dataFromExternal()\0"
    "internalDiscounnected()\0externalDiscounnected()\0"
    "slotErrorHandler(QString)\0"
};

const QMetaObject singlehandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_singlehandler,
      qt_meta_data_singlehandler, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &singlehandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *singlehandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *singlehandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_singlehandler))
        return static_cast<void*>(const_cast< singlehandler*>(this));
    return QObject::qt_metacast(_clname);
}

int singlehandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: someError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: dataFromInternal(); break;
        case 2: dataFromExternal(); break;
        case 3: internalDiscounnected(); break;
        case 4: externalDiscounnected(); break;
        case 5: slotErrorHandler((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void singlehandler::someError(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
