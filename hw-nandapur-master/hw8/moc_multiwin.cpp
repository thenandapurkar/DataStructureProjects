/****************************************************************************
** Meta object code from reading C++ file 'multiwin.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "multiwin.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'multiwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Multiwin[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      30,    9,    9,    9, 0x0a,
      55,   51,    9,    9, 0x0a,
      73,   51,    9,    9, 0x0a,
      98,    9,    9,    9, 0x0a,
     113,   51,    9,    9, 0x0a,
     132,    9,    9,    9, 0x0a,
     147,    9,    9,    9, 0x0a,
     159,    9,    9,    9, 0x0a,
     170,    9,    9,    9, 0x0a,
     183,    9,    9,    9, 0x0a,
     194,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Multiwin[] = {
    "Multiwin\0\0mainButtonClicked()\0"
    "otherButtonClicked()\0idx\0showUserFeed(int)\0"
    "showUserMentionFeed(int)\0postNewTweet()\0"
    "showFollowers(int)\0addFollowing()\0"
    "handleAnd()\0handleOr()\0saveToFile()\0"
    "saveSCCs()\0displayTrendingHashTags()\0"
};

void Multiwin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Multiwin *_t = static_cast<Multiwin *>(_o);
        switch (_id) {
        case 0: _t->mainButtonClicked(); break;
        case 1: _t->otherButtonClicked(); break;
        case 2: _t->showUserFeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->showUserMentionFeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->postNewTweet(); break;
        case 5: _t->showFollowers((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->addFollowing(); break;
        case 7: _t->handleAnd(); break;
        case 8: _t->handleOr(); break;
        case 9: _t->saveToFile(); break;
        case 10: _t->saveSCCs(); break;
        case 11: _t->displayTrendingHashTags(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Multiwin::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Multiwin::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Multiwin,
      qt_meta_data_Multiwin, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Multiwin::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Multiwin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Multiwin::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Multiwin))
        return static_cast<void*>(const_cast< Multiwin*>(this));
    return QWidget::qt_metacast(_clname);
}

int Multiwin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
