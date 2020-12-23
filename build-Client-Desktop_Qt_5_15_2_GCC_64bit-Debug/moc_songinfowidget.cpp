/****************************************************************************
** Meta object code from reading C++ file 'songinfowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Client/songinfowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'songinfowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_songInfoWidget_t {
    QByteArrayData data[11];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_songInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_songInfoWidget_t qt_meta_stringdata_songInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "songInfoWidget"
QT_MOC_LITERAL(1, 15, 20), // "disconnectFromServer"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 16), // "openCommentsPage"
QT_MOC_LITERAL(4, 54, 7), // "song_id"
QT_MOC_LITERAL(5, 62, 11), // "const char*"
QT_MOC_LITERAL(6, 74, 5), // "title"
QT_MOC_LITERAL(7, 80, 21), // "on_songVoteUp_clicked"
QT_MOC_LITERAL(8, 102, 23), // "on_songVoteDown_clicked"
QT_MOC_LITERAL(9, 126, 21), // "on_songDelete_clicked"
QT_MOC_LITERAL(10, 148, 23) // "on_songComments_clicked"

    },
    "songInfoWidget\0disconnectFromServer\0"
    "\0openCommentsPage\0song_id\0const char*\0"
    "title\0on_songVoteUp_clicked\0"
    "on_songVoteDown_clicked\0on_songDelete_clicked\0"
    "on_songComments_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_songInfoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    2,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   50,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void songInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<songInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->disconnectFromServer(); break;
        case 1: _t->openCommentsPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 2: _t->on_songVoteUp_clicked(); break;
        case 3: _t->on_songVoteDown_clicked(); break;
        case 4: _t->on_songDelete_clicked(); break;
        case 5: _t->on_songComments_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (songInfoWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&songInfoWidget::disconnectFromServer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (songInfoWidget::*)(int , const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&songInfoWidget::openCommentsPage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject songInfoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_songInfoWidget.data,
    qt_meta_data_songInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *songInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *songInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_songInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int songInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void songInfoWidget::disconnectFromServer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void songInfoWidget::openCommentsPage(int _t1, const char * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
