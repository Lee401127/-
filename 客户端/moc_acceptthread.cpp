/****************************************************************************
** Meta object code from reading C++ file 'acceptthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "acceptthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'acceptthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AcceptThread_t {
    QByteArrayData data[81];
    char stringdata0[1140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AcceptThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AcceptThread_t qt_meta_stringdata_AcceptThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "AcceptThread"
QT_MOC_LITERAL(1, 13, 12), // "loginsuccess"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 6), // "nouser"
QT_MOC_LITERAL(4, 34, 12), // "passwordwarn"
QT_MOC_LITERAL(5, 47, 8), // "codewarn"
QT_MOC_LITERAL(6, 56, 13), // "loginsuccess1"
QT_MOC_LITERAL(7, 70, 13), // "loginsuccess2"
QT_MOC_LITERAL(8, 84, 17), // "loginRoleMismatch"
QT_MOC_LITERAL(9, 102, 3), // "msg"
QT_MOC_LITERAL(10, 106, 16), // "phonehasbeenused"
QT_MOC_LITERAL(11, 123, 8), // "sendwarn"
QT_MOC_LITERAL(12, 132, 13), // "registerswarn"
QT_MOC_LITERAL(13, 146, 8), // "password"
QT_MOC_LITERAL(14, 155, 4), // "code"
QT_MOC_LITERAL(15, 160, 16), // "sendvideosuccess"
QT_MOC_LITERAL(16, 177, 13), // "sendvideowarn"
QT_MOC_LITERAL(17, 191, 15), // "sendfilesuccess"
QT_MOC_LITERAL(18, 207, 12), // "sendfilewarn"
QT_MOC_LITERAL(19, 220, 18), // "sendpicturesuccess"
QT_MOC_LITERAL(20, 239, 15), // "sendpicturewarn"
QT_MOC_LITERAL(21, 255, 19), // "getvideolistsuccess"
QT_MOC_LITERAL(22, 275, 6), // "Video*"
QT_MOC_LITERAL(23, 282, 22), // "getDateTimeListSuccess"
QT_MOC_LITERAL(24, 305, 14), // "QList<QString>"
QT_MOC_LITERAL(25, 320, 16), // "getvideolistwarn"
QT_MOC_LITERAL(26, 337, 21), // "getpicturelistsuccess"
QT_MOC_LITERAL(27, 359, 8), // "Picture*"
QT_MOC_LITERAL(28, 368, 29), // "getpictureDateTimeListSuccess"
QT_MOC_LITERAL(29, 398, 18), // "getpicturelistwarn"
QT_MOC_LITERAL(30, 417, 17), // "getOldListSuccess"
QT_MOC_LITERAL(31, 435, 3), // "Eld"
QT_MOC_LITERAL(32, 439, 3), // "old"
QT_MOC_LITERAL(33, 443, 14), // "getOldListWarn"
QT_MOC_LITERAL(34, 458, 6), // "errMsg"
QT_MOC_LITERAL(35, 465, 18), // "getOldListFinished"
QT_MOC_LITERAL(36, 484, 16), // "elderInfoSuccess"
QT_MOC_LITERAL(37, 501, 15), // "elderInfoFailed"
QT_MOC_LITERAL(38, 517, 21), // "elderInfoQuerySuccess"
QT_MOC_LITERAL(39, 539, 4), // "name"
QT_MOC_LITERAL(40, 544, 3), // "age"
QT_MOC_LITERAL(41, 548, 6), // "gender"
QT_MOC_LITERAL(42, 555, 10), // "recordTime"
QT_MOC_LITERAL(43, 566, 7), // "contact"
QT_MOC_LITERAL(44, 574, 6), // "remark"
QT_MOC_LITERAL(45, 581, 20), // "elderInfoQueryFailed"
QT_MOC_LITERAL(46, 602, 13), // "bloodQueryRow"
QT_MOC_LITERAL(47, 616, 3), // "row"
QT_MOC_LITERAL(48, 620, 8), // "systolic"
QT_MOC_LITERAL(49, 629, 9), // "diastolic"
QT_MOC_LITERAL(50, 639, 11), // "measureTime"
QT_MOC_LITERAL(51, 651, 16), // "bloodQueryFailed"
QT_MOC_LITERAL(52, 668, 16), // "medicineQueryRow"
QT_MOC_LITERAL(53, 685, 6), // "dosage"
QT_MOC_LITERAL(54, 692, 5), // "usage"
QT_MOC_LITERAL(55, 698, 19), // "medicineQueryFailed"
QT_MOC_LITERAL(56, 718, 16), // "activityQueryRow"
QT_MOC_LITERAL(57, 735, 4), // "type"
QT_MOC_LITERAL(58, 740, 9), // "startTime"
QT_MOC_LITERAL(59, 750, 7), // "endTime"
QT_MOC_LITERAL(60, 758, 19), // "activityQueryFailed"
QT_MOC_LITERAL(61, 778, 20), // "bloodPressureSuccess"
QT_MOC_LITERAL(62, 799, 19), // "bloodPressureFailed"
QT_MOC_LITERAL(63, 819, 26), // "bloodPressureSuccessDetail"
QT_MOC_LITERAL(64, 846, 8), // "recordId"
QT_MOC_LITERAL(65, 855, 25), // "bloodPressureFailedDetail"
QT_MOC_LITERAL(66, 881, 15), // "medicineSuccess"
QT_MOC_LITERAL(67, 897, 14), // "medicineFailed"
QT_MOC_LITERAL(68, 912, 21), // "medicineSuccessDetail"
QT_MOC_LITERAL(69, 934, 20), // "medicineFailedDetail"
QT_MOC_LITERAL(70, 955, 15), // "activitySuccess"
QT_MOC_LITERAL(71, 971, 14), // "activityFailed"
QT_MOC_LITERAL(72, 986, 21), // "activitySuccessDetail"
QT_MOC_LITERAL(73, 1008, 20), // "activityFailedDetail"
QT_MOC_LITERAL(74, 1029, 23), // "callRecordReportSuccess"
QT_MOC_LITERAL(75, 1053, 6), // "callId"
QT_MOC_LITERAL(76, 1060, 22), // "callRecordReportFailed"
QT_MOC_LITERAL(77, 1083, 18), // "callRecordQueryRow"
QT_MOC_LITERAL(78, 1102, 10), // "elderPhone"
QT_MOC_LITERAL(79, 1113, 4), // "time"
QT_MOC_LITERAL(80, 1118, 21) // "callRecordQueryFailed"

    },
    "AcceptThread\0loginsuccess\0\0nouser\0"
    "passwordwarn\0codewarn\0loginsuccess1\0"
    "loginsuccess2\0loginRoleMismatch\0msg\0"
    "phonehasbeenused\0sendwarn\0registerswarn\0"
    "password\0code\0sendvideosuccess\0"
    "sendvideowarn\0sendfilesuccess\0"
    "sendfilewarn\0sendpicturesuccess\0"
    "sendpicturewarn\0getvideolistsuccess\0"
    "Video*\0getDateTimeListSuccess\0"
    "QList<QString>\0getvideolistwarn\0"
    "getpicturelistsuccess\0Picture*\0"
    "getpictureDateTimeListSuccess\0"
    "getpicturelistwarn\0getOldListSuccess\0"
    "Eld\0old\0getOldListWarn\0errMsg\0"
    "getOldListFinished\0elderInfoSuccess\0"
    "elderInfoFailed\0elderInfoQuerySuccess\0"
    "name\0age\0gender\0recordTime\0contact\0"
    "remark\0elderInfoQueryFailed\0bloodQueryRow\0"
    "row\0systolic\0diastolic\0measureTime\0"
    "bloodQueryFailed\0medicineQueryRow\0"
    "dosage\0usage\0medicineQueryFailed\0"
    "activityQueryRow\0type\0startTime\0endTime\0"
    "activityQueryFailed\0bloodPressureSuccess\0"
    "bloodPressureFailed\0bloodPressureSuccessDetail\0"
    "recordId\0bloodPressureFailedDetail\0"
    "medicineSuccess\0medicineFailed\0"
    "medicineSuccessDetail\0medicineFailedDetail\0"
    "activitySuccess\0activityFailed\0"
    "activitySuccessDetail\0activityFailedDetail\0"
    "callRecordReportSuccess\0callId\0"
    "callRecordReportFailed\0callRecordQueryRow\0"
    "elderPhone\0time\0callRecordQueryFailed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AcceptThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      53,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  279,    2, 0x06 /* Public */,
       3,    0,  282,    2, 0x06 /* Public */,
       4,    0,  283,    2, 0x06 /* Public */,
       5,    0,  284,    2, 0x06 /* Public */,
       6,    1,  285,    2, 0x06 /* Public */,
       7,    1,  288,    2, 0x06 /* Public */,
       8,    1,  291,    2, 0x06 /* Public */,
      10,    0,  294,    2, 0x06 /* Public */,
      11,    0,  295,    2, 0x06 /* Public */,
      12,    0,  296,    2, 0x06 /* Public */,
      13,    1,  297,    2, 0x06 /* Public */,
      14,    1,  300,    2, 0x06 /* Public */,
      15,    1,  303,    2, 0x06 /* Public */,
      16,    0,  306,    2, 0x06 /* Public */,
      17,    0,  307,    2, 0x06 /* Public */,
      18,    0,  308,    2, 0x06 /* Public */,
      19,    1,  309,    2, 0x06 /* Public */,
      20,    0,  312,    2, 0x06 /* Public */,
      21,    1,  313,    2, 0x06 /* Public */,
      23,    1,  316,    2, 0x06 /* Public */,
      25,    0,  319,    2, 0x06 /* Public */,
      26,    1,  320,    2, 0x06 /* Public */,
      28,    1,  323,    2, 0x06 /* Public */,
      29,    0,  326,    2, 0x06 /* Public */,
      30,    1,  327,    2, 0x06 /* Public */,
      33,    1,  330,    2, 0x06 /* Public */,
      35,    0,  333,    2, 0x06 /* Public */,
      36,    0,  334,    2, 0x06 /* Public */,
      37,    0,  335,    2, 0x06 /* Public */,
      38,    6,  336,    2, 0x06 /* Public */,
      45,    1,  349,    2, 0x06 /* Public */,
      46,    5,  352,    2, 0x06 /* Public */,
      51,    1,  363,    2, 0x06 /* Public */,
      52,    6,  366,    2, 0x06 /* Public */,
      55,    1,  379,    2, 0x06 /* Public */,
      56,    4,  382,    2, 0x06 /* Public */,
      60,    1,  391,    2, 0x06 /* Public */,
      61,    0,  394,    2, 0x06 /* Public */,
      62,    0,  395,    2, 0x06 /* Public */,
      63,    1,  396,    2, 0x06 /* Public */,
      65,    1,  399,    2, 0x06 /* Public */,
      66,    0,  402,    2, 0x06 /* Public */,
      67,    0,  403,    2, 0x06 /* Public */,
      68,    1,  404,    2, 0x06 /* Public */,
      69,    1,  407,    2, 0x06 /* Public */,
      70,    0,  410,    2, 0x06 /* Public */,
      71,    0,  411,    2, 0x06 /* Public */,
      72,    1,  412,    2, 0x06 /* Public */,
      73,    1,  415,    2, 0x06 /* Public */,
      74,    1,  418,    2, 0x06 /* Public */,
      76,    1,  421,    2, 0x06 /* Public */,
      77,    5,  424,    2, 0x06 /* Public */,
      80,    1,  435,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, 0x80000000 | 24,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 27,    2,
    QMetaType::Void, 0x80000000 | 24,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   39,   40,   41,   42,   43,   44,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString,   47,   48,   49,   50,   44,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   47,   39,   53,   42,   54,   44,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,   47,   57,   58,   59,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   64,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   64,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   64,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::Int,   75,
    QMetaType::Void, QMetaType::QString,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString,   75,   78,   57,   79,   44,
    QMetaType::Void, QMetaType::QString,   34,

       0        // eod
};

void AcceptThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AcceptThread *_t = static_cast<AcceptThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginsuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->nouser(); break;
        case 2: _t->passwordwarn(); break;
        case 3: _t->codewarn(); break;
        case 4: _t->loginsuccess1((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->loginsuccess2((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->loginRoleMismatch((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->phonehasbeenused(); break;
        case 8: _t->sendwarn(); break;
        case 9: _t->registerswarn(); break;
        case 10: _t->password((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->code((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->sendvideosuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->sendvideowarn(); break;
        case 14: _t->sendfilesuccess(); break;
        case 15: _t->sendfilewarn(); break;
        case 16: _t->sendpicturesuccess((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->sendpicturewarn(); break;
        case 18: _t->getvideolistsuccess((*reinterpret_cast< Video*(*)>(_a[1]))); break;
        case 19: _t->getDateTimeListSuccess((*reinterpret_cast< const QList<QString>(*)>(_a[1]))); break;
        case 20: _t->getvideolistwarn(); break;
        case 21: _t->getpicturelistsuccess((*reinterpret_cast< Picture*(*)>(_a[1]))); break;
        case 22: _t->getpictureDateTimeListSuccess((*reinterpret_cast< const QList<QString>(*)>(_a[1]))); break;
        case 23: _t->getpicturelistwarn(); break;
        case 24: _t->getOldListSuccess((*reinterpret_cast< const Eld(*)>(_a[1]))); break;
        case 25: _t->getOldListWarn((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 26: _t->getOldListFinished(); break;
        case 27: _t->elderInfoSuccess(); break;
        case 28: _t->elderInfoFailed(); break;
        case 29: _t->elderInfoQuerySuccess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6]))); break;
        case 30: _t->elderInfoQueryFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 31: _t->bloodQueryRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 32: _t->bloodQueryFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 33: _t->medicineQueryRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6]))); break;
        case 34: _t->medicineQueryFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 35: _t->activityQueryRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 36: _t->activityQueryFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 37: _t->bloodPressureSuccess(); break;
        case 38: _t->bloodPressureFailed(); break;
        case 39: _t->bloodPressureSuccessDetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->bloodPressureFailedDetail((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 41: _t->medicineSuccess(); break;
        case 42: _t->medicineFailed(); break;
        case 43: _t->medicineSuccessDetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->medicineFailedDetail((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 45: _t->activitySuccess(); break;
        case 46: _t->activityFailed(); break;
        case 47: _t->activitySuccessDetail((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->activityFailedDetail((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 49: _t->callRecordReportSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->callRecordReportFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 51: _t->callRecordQueryRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 52: _t->callRecordQueryFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QString> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::loginsuccess)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::nouser)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::passwordwarn)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::codewarn)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::loginsuccess1)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::loginsuccess2)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::loginRoleMismatch)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::phonehasbeenused)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendwarn)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::registerswarn)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::password)) {
                *result = 10;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::code)) {
                *result = 11;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendvideosuccess)) {
                *result = 12;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendvideowarn)) {
                *result = 13;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendfilesuccess)) {
                *result = 14;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendfilewarn)) {
                *result = 15;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendpicturesuccess)) {
                *result = 16;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::sendpicturewarn)) {
                *result = 17;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(Video * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getvideolistsuccess)) {
                *result = 18;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QList<QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getDateTimeListSuccess)) {
                *result = 19;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getvideolistwarn)) {
                *result = 20;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(Picture * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getpicturelistsuccess)) {
                *result = 21;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QList<QString> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getpictureDateTimeListSuccess)) {
                *result = 22;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getpicturelistwarn)) {
                *result = 23;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const Eld & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getOldListSuccess)) {
                *result = 24;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getOldListWarn)) {
                *result = 25;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::getOldListFinished)) {
                *result = 26;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::elderInfoSuccess)) {
                *result = 27;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::elderInfoFailed)) {
                *result = 28;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & , int , const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::elderInfoQuerySuccess)) {
                *result = 29;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::elderInfoQueryFailed)) {
                *result = 30;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int , int , int , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::bloodQueryRow)) {
                *result = 31;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::bloodQueryFailed)) {
                *result = 32;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int , const QString & , const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::medicineQueryRow)) {
                *result = 33;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::medicineQueryFailed)) {
                *result = 34;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::activityQueryRow)) {
                *result = 35;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::activityQueryFailed)) {
                *result = 36;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::bloodPressureSuccess)) {
                *result = 37;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::bloodPressureFailed)) {
                *result = 38;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::bloodPressureSuccessDetail)) {
                *result = 39;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::bloodPressureFailedDetail)) {
                *result = 40;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::medicineSuccess)) {
                *result = 41;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::medicineFailed)) {
                *result = 42;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::medicineSuccessDetail)) {
                *result = 43;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::medicineFailedDetail)) {
                *result = 44;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::activitySuccess)) {
                *result = 45;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::activityFailed)) {
                *result = 46;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::activitySuccessDetail)) {
                *result = 47;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::activityFailedDetail)) {
                *result = 48;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::callRecordReportSuccess)) {
                *result = 49;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::callRecordReportFailed)) {
                *result = 50;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(int , const QString & , int , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::callRecordQueryRow)) {
                *result = 51;
                return;
            }
        }
        {
            typedef void (AcceptThread::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AcceptThread::callRecordQueryFailed)) {
                *result = 52;
                return;
            }
        }
    }
}

const QMetaObject AcceptThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_AcceptThread.data,
      qt_meta_data_AcceptThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AcceptThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AcceptThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AcceptThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int AcceptThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    }
    return _id;
}

// SIGNAL 0
void AcceptThread::loginsuccess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AcceptThread::nouser()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AcceptThread::passwordwarn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void AcceptThread::codewarn()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void AcceptThread::loginsuccess1(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AcceptThread::loginsuccess2(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AcceptThread::loginRoleMismatch(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AcceptThread::phonehasbeenused()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void AcceptThread::sendwarn()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void AcceptThread::registerswarn()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void AcceptThread::password(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AcceptThread::code(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void AcceptThread::sendvideosuccess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void AcceptThread::sendvideowarn()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void AcceptThread::sendfilesuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void AcceptThread::sendfilewarn()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void AcceptThread::sendpicturesuccess(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void AcceptThread::sendpicturewarn()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void AcceptThread::getvideolistsuccess(Video * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void AcceptThread::getDateTimeListSuccess(const QList<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void AcceptThread::getvideolistwarn()
{
    QMetaObject::activate(this, &staticMetaObject, 20, nullptr);
}

// SIGNAL 21
void AcceptThread::getpicturelistsuccess(Picture * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void AcceptThread::getpictureDateTimeListSuccess(const QList<QString> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void AcceptThread::getpicturelistwarn()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void AcceptThread::getOldListSuccess(const Eld & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void AcceptThread::getOldListWarn(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void AcceptThread::getOldListFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 26, nullptr);
}

// SIGNAL 27
void AcceptThread::elderInfoSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 27, nullptr);
}

// SIGNAL 28
void AcceptThread::elderInfoFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 28, nullptr);
}

// SIGNAL 29
void AcceptThread::elderInfoQuerySuccess(const QString & _t1, int _t2, const QString & _t3, const QString & _t4, const QString & _t5, const QString & _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void AcceptThread::elderInfoQueryFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void AcceptThread::bloodQueryRow(int _t1, int _t2, int _t3, const QString & _t4, const QString & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void AcceptThread::bloodQueryFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void AcceptThread::medicineQueryRow(int _t1, const QString & _t2, const QString & _t3, const QString & _t4, const QString & _t5, const QString & _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 33, _a);
}

// SIGNAL 34
void AcceptThread::medicineQueryFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 34, _a);
}

// SIGNAL 35
void AcceptThread::activityQueryRow(int _t1, const QString & _t2, const QString & _t3, const QString & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 35, _a);
}

// SIGNAL 36
void AcceptThread::activityQueryFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 36, _a);
}

// SIGNAL 37
void AcceptThread::bloodPressureSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 37, nullptr);
}

// SIGNAL 38
void AcceptThread::bloodPressureFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 38, nullptr);
}

// SIGNAL 39
void AcceptThread::bloodPressureSuccessDetail(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 39, _a);
}

// SIGNAL 40
void AcceptThread::bloodPressureFailedDetail(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 40, _a);
}

// SIGNAL 41
void AcceptThread::medicineSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 41, nullptr);
}

// SIGNAL 42
void AcceptThread::medicineFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 42, nullptr);
}

// SIGNAL 43
void AcceptThread::medicineSuccessDetail(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 43, _a);
}

// SIGNAL 44
void AcceptThread::medicineFailedDetail(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 44, _a);
}

// SIGNAL 45
void AcceptThread::activitySuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 45, nullptr);
}

// SIGNAL 46
void AcceptThread::activityFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 46, nullptr);
}

// SIGNAL 47
void AcceptThread::activitySuccessDetail(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 47, _a);
}

// SIGNAL 48
void AcceptThread::activityFailedDetail(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 48, _a);
}

// SIGNAL 49
void AcceptThread::callRecordReportSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 49, _a);
}

// SIGNAL 50
void AcceptThread::callRecordReportFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 50, _a);
}

// SIGNAL 51
void AcceptThread::callRecordQueryRow(int _t1, const QString & _t2, int _t3, const QString & _t4, const QString & _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 51, _a);
}

// SIGNAL 52
void AcceptThread::callRecordQueryFailed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 52, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
