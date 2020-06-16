/****************************************************************************
** Meta object code from reading C++ file 'Widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../widget/Widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[17];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 16), // "onBtnShowClicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "onBtnHideClicked"
QT_MOC_LITERAL(4, 42, 19), // "onSystemTrayClicked"
QT_MOC_LITERAL(5, 62, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(6, 96, 6), // "reason"
QT_MOC_LITERAL(7, 103, 22), // "onBtnFullScreenClicked"
QT_MOC_LITERAL(8, 126, 22), // "onBtnRectScreenClicked"
QT_MOC_LITERAL(9, 149, 15), // "onBtnMinClicked"
QT_MOC_LITERAL(10, 165, 17), // "onBtnCloseClicked"
QT_MOC_LITERAL(11, 183, 17), // "onBtnPasteClicked"
QT_MOC_LITERAL(12, 201, 11), // "switchSlots"
QT_MOC_LITERAL(13, 213, 6), // "vkCode"
QT_MOC_LITERAL(14, 220, 12), // "initFileList"
QT_MOC_LITERAL(15, 233, 6), // "isInit"
QT_MOC_LITERAL(16, 240, 14) // "rollbackOffset"

    },
    "Widget\0onBtnShowClicked\0\0onBtnHideClicked\0"
    "onSystemTrayClicked\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0onBtnFullScreenClicked\0"
    "onBtnRectScreenClicked\0onBtnMinClicked\0"
    "onBtnCloseClicked\0onBtnPasteClicked\0"
    "switchSlots\0vkCode\0initFileList\0isInit\0"
    "rollbackOffset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    1,   76,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    0,   82,    2, 0x0a /* Public */,
      11,    0,   83,    2, 0x0a /* Public */,
      12,    1,   84,    2, 0x0a /* Public */,
      14,    1,   87,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x2a /* Public | MethodCloned */,
      16,    0,   91,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onBtnShowClicked(); break;
        case 1: _t->onBtnHideClicked(); break;
        case 2: _t->onSystemTrayClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 3: _t->onBtnFullScreenClicked(); break;
        case 4: _t->onBtnRectScreenClicked(); break;
        case 5: _t->onBtnMinClicked(); break;
        case 6: _t->onBtnCloseClicked(); break;
        case 7: _t->onBtnPasteClicked(); break;
        case 8: _t->switchSlots((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->initFileList((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->initFileList(); break;
        case 11: _t->rollbackOffset(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
