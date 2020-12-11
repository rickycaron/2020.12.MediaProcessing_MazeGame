/****************************************************************************
** Meta object code from reading C++ file 'tenemy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../final/tenemy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tenemy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TEnemy_t {
    QByteArrayData data[9];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TEnemy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TEnemy_t qt_meta_stringdata_TEnemy = {
    {
QT_MOC_LITERAL(0, 0, 6), // "TEnemy"
QT_MOC_LITERAL(1, 7, 7), // "collide"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 5), // "index"
QT_MOC_LITERAL(4, 22, 3), // "isP"
QT_MOC_LITERAL(5, 26, 12), // "indicateDead"
QT_MOC_LITERAL(6, 39, 12), // "checkCollide"
QT_MOC_LITERAL(7, 52, 1), // "x"
QT_MOC_LITERAL(8, 54, 1) // "y"

    },
    "TEnemy\0collide\0\0index\0isP\0indicateDead\0"
    "checkCollide\0x\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TEnemy[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   34,    2, 0x0a /* Public */,
       6,    2,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,

       0        // eod
};

void TEnemy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TEnemy *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->collide((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->indicateDead(); break;
        case 2: _t->checkCollide((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TEnemy::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TEnemy::collide)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TEnemy::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsTextItem::staticMetaObject>(),
    qt_meta_stringdata_TEnemy.data,
    qt_meta_data_TEnemy,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TEnemy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TEnemy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TEnemy.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsTextItem::qt_metacast(_clname);
}

int TEnemy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsTextItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TEnemy::collide(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
