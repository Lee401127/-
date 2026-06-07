#include "acceptthread.h"

int loginstatus;

AcceptThread::AcceptThread(int socketfd, QObject *parent)
{
    this->socketfd=socketfd;
}

int AcceptThread::getfd()
{
    return this->socketfd;
}

void AcceptThread::run()
{

    char recvbuf[8192] = {0};
    HEAD head = {};


        LOGIN_RESP login_resp = { 0 };
        CODE_RESP code_resp={0};
        REGISTER_RESP register_resq={0};
        DOCUMENT_RESP document_resq={0};
        PICTURE_RESP picture_resq={0};
        VIDEO_RESP video_resq={0};
        GET_VIDEO_RESP get_video_resq={0};
        GET_PICTURE_RESP get_picture_resq={0};
        GET_OLDLIST_RESP get_oldlist_resp={0};
        ElderInfoResp elderinforesp={0};
        ElderInfoQueryResp elderInfoQueryResp = {0};
        BloodPressureQueryResp bloodQueryResp = {0};
        MedicineQueryResp medicineQueryResp = {0};
        ActivityQueryResp activityQueryResp = {0};
        BloodPressureResp bloodprssureresp={0};
        MedicineResp medivineresp={0};
        ActivityResp activityresp={0};
        CALL_RECORD_REPORT_RESP call_report_resp = {0};
        CALL_RECORD_QUERY_RESP call_query_resp = {0};
        while (true)
        {

            char recvbuf[8192];
           int res= read(socketfd, recvbuf, sizeof(recvbuf));
         //   qDebug()<<"res"<<res<<endl;

qDebug()<<"36"<<endl;
            memcpy(&head, recvbuf, sizeof(HEAD));
qDebug() << "Received service_type:" << head.service_type;
            if (head.service_type == LOGIN)
                { memcpy(&login_resp, recvbuf + sizeof(HEAD), sizeof (LOGIN_RESP));
                if (login_resp.status_code == 0)
                {
                    qDebug()<<"登录1"<<login_resp.phone<<endl;
                    emit loginsuccess(login_resp.phone);
                }else if(login_resp.status_code==1){
                    qDebug()<<"登录"<<login_resp.error_message<<endl;
                    emit nouser();

                }else if(login_resp.status_code==2)
                {
                    emit passwordwarn();
                }else if(login_resp.status_code==3)
                {
                    emit codewarn();
                }else if(login_resp.status_code==4)
                {         qDebug()<<"登录2"<<login_resp.phone<<endl;
                    emit loginsuccess1(login_resp.phone);
                }else if(login_resp.status_code==5)
                {
                    emit loginsuccess2(login_resp.phone);
                    qDebug()<<"登录3"<<login_resp.phone<<endl;
                }else if(login_resp.status_code==6)
                {
                    emit loginRoleMismatch(QString::fromUtf8(login_resp.error_message));
                }
            }
            else if(head.service_type == CODE)
            {memcpy(&code_resp, recvbuf + sizeof(HEAD),sizeof (CODE_RESP));

                if(code_resp.status_code==0)
                {
                    QString codeStr = QString::fromUtf8(code_resp.code, 7); // 需确保数据为UTF-8格式

                    emit code(codeStr);
                    qDebug()<<"code get success"<<code_resp.code<<code_resp.phone<<endl;
                }else if (code_resp.status_code==1) {
                    emit phonehasbeenused();
                }else if (code_resp.status_code==2) {
                    emit sendwarn();
                }

            }
            else if (head.service_type==REGISTER)
            {memcpy(&register_resq, recvbuf + sizeof(HEAD), sizeof (REGISTER_RESP));
                if(register_resq.status_code==0)
                {

                    emit password(register_resq.password);
                    qDebug()<<"password"<<register_resq.password<<"phone"<<register_resq.phone<<endl;
                }else if (register_resq.status_code==1) {
                    emit registerswarn();}
            }else if (head.service_type==SEND_VIDEO) {
                    memcpy(&video_resq, recvbuf + sizeof(HEAD), sizeof (VIDEO_RESP));
                    if(video_resq.status_code==0)
                    {
                        QString fileStr = QString::fromUtf8(video_resq.document_name, 20);
                        emit sendvideosuccess(fileStr);

                    }else if (video_resq.status_code==1) {
                        emit sendvideowarn();
                    }
}
        else if (head.service_type==SEND_PICTURE) {
                       memcpy(&picture_resq, recvbuf + sizeof(HEAD), sizeof (PICTURE_RESP));
                       if(picture_resq.status_code==0)
                       {
                           QString fileStr = QString::fromUtf8(picture_resq.document_name, 20);
                           emit sendpicturesuccess(fileStr);

                       }else if (picture_resq.status_code==1) {
                           emit sendpicturewarn();
                       }
             }else if (head.service_type==DOCUMENT) {
                       memcpy(&document_resq, recvbuf + sizeof(HEAD), sizeof (DOCUMENT_RESP));
                       if(document_resq.status_code==0)
                       {
                          emit sendfilesuccess();
                       }else if (document_resq.status_code==1) {
                          emit sendfilewarn();
                       }
                   } else if (head.service_type==GET_VIDEO_LIST) {
                    qDebug()<<"120"<<endl;
                    memcpy(&get_video_resq, recvbuf + sizeof(HEAD), sizeof (GET_VIDEO_RESP));
                    qDebug()<<"113aa"<<endl;
                    if(get_video_resq.status_code==0)
                    { QList<QString> dateList; // 假设使用 Qt 的 QList 存储结果

                        for (int i = 0; i < MAX_DATE; i++) {
                            if (strlen(get_video_resq.datetime[i]) > 0) { // 检查是否非空
                                dateList.append(QString::fromLocal8Bit(get_video_resq.datetime[i]));
                                 qDebug() << "getvideo_resp.datetime[i]:" << get_video_resq.datetime[i]<<endl;
                            }
                        }

                        if (!dateList.isEmpty()) {
                            emit getDateTimeListSuccess(dateList); // 发送信号返回时间列表
                        }
                        qDebug()<<"1"<<get_video_resq.video_arr[0].video_name<<endl;
                  // 判断 video_arr 是否有效（是否至少有一个有效元素）
                        bool hasValidData = false;

                        // 检查是否存在至少一个有效数据
                        for (int i = 0; i < MAX_VIDEO; i++) {
                            if (strlen(get_video_resq.video_arr[i].video_name) > 0) { // 修正判断条件
                                hasValidData = true;
                                break;
                            }
                        }

                        // 如果存在有效数据，遍历并发送有效项
                        if (hasValidData) {
                            for (int i = 0; i < MAX_VIDEO; i++) {
                                // 仅在 video_name 不为空时发送信号
                                if (strlen(get_video_resq.video_arr[i].video_name) > 0) {
                                    emit getvideolistsuccess(&get_video_resq.video_arr[i]);
                                }
                            }
                        }


                    }else if (get_video_resq.status_code==1) {
                        emit getvideolistwarn();
                              qDebug()<<"2"<<get_video_resq.video_arr[0].video_name<<endl;
                                   qDebug()<<"3"<<get_video_resq.error_message<<endl;
                    }

            }else if (head.service_type==GET_PICTURE_LIST) {
                qDebug()<<"120"<<endl;
                memcpy(&get_picture_resq, recvbuf + sizeof(HEAD), sizeof (GET_PICTURE_RESP));
                qDebug()<<"113aa"<<endl;
                if(get_picture_resq.status_code==0)
                { QList<QString> dateList; // 假设使用 Qt 的 QList 存储结果

                    for (int i = 0; i < MAX_DATE; i++) {
                        if (strlen(get_picture_resq.datetime[i]) > 0) { // 检查是否非空
                            dateList.append(QString::fromLocal8Bit(get_picture_resq.datetime[i]));
                             qDebug() << "getpicture_resp.datetime[i]:" << get_picture_resq.datetime[i]<<endl;
                        }
                    }

                    if (!dateList.isEmpty()) {
                        emit getpictureDateTimeListSuccess(dateList); // 发送信号返回时间列表
                    }
                    qDebug()<<"1"<<get_picture_resq.picture_arr[0].picture_name<<endl;
              // 判断 video_arr 是否有效（是否至少有一个有效元素）
                    bool hasValidData = false;

                    // 检查是否存在至少一个有效数据
                    for (int i = 0; i < MAX_VIDEO; i++) {
                        if (strlen(get_picture_resq.picture_arr[i].picture_name) > 0) { // 修正判断条件
                            hasValidData = true;
                            break;
                        }
                    }

                    // 如果存在有效数据，遍历并发送有效项
                    if (hasValidData) {
                        for (int i = 0; i < MAX_PICTURE; i++) {
                            // 仅在 video_name 不为空时发送信号
                            if (strlen(get_picture_resq.picture_arr[i].picture_name) > 0) {
                                // 这里不能直接把局部数组元素的地址发出去：
                                // AcceptThread 所在线程通过 queued signal 触发主线程槽函数时，
                                // recv 循环会继续覆盖 get_picture_resq，导致指针悬空（随机崩溃/列表不全）。
                                Picture *p = new Picture(get_picture_resq.picture_arr[i]);
                                emit getpicturelistsuccess(p);
                            }
                        }
                    }


                }else if (get_picture_resq.status_code==1) {
                    emit getpicturelistwarn();
                          qDebug()<<"2"<<get_picture_resq.picture_arr[0].picture_name<<endl;
                               qDebug()<<"3"<<get_picture_resq.error_message<<endl;
                }
}            else if (head.service_type == GET_OLD_LIST) {
                qDebug()<<"213"<<endl;
            memcpy(&get_oldlist_resp, recvbuf + sizeof(HEAD), sizeof(GET_OLDLIST_RESP));

             if (get_oldlist_resp.status_code == 0) {
                 for (int i = 0; i < MAX_OLD; i++) {
                     if (get_oldlist_resp.old_arr[i].oldnum > 0 &&
                         strlen(get_oldlist_resp.old_arr[i].phone) > 0) {
                         emit getOldListSuccess(get_oldlist_resp.old_arr[i]); // 发送拷贝
                         qDebug()<<"221"<<endl;
                     }
                 }
                 emit getOldListFinished(); // 可选，表示所有老人发送完毕
             } else {
                 emit getOldListWarn(QString::fromLocal8Bit(get_oldlist_resp.error_message));
             }

}else if (head.service_type == ELDERINFO) {
                memcpy(&elderinforesp, recvbuf + sizeof(HEAD), sizeof(ElderInfoResp));
                if (elderinforesp.status_code == 0) {
                    emit elderInfoSuccess();
                } else if (elderinforesp.status_code == 1) {
                    emit elderInfoFailed();
                }
            }
            else if (head.service_type == ELDERINFO_QUERY) {
                memcpy(&elderInfoQueryResp, recvbuf + sizeof(HEAD), sizeof(ElderInfoQueryResp));
                if (elderInfoQueryResp.status_code == 0) {
                    emit elderInfoQuerySuccess(
                        QString::fromLocal8Bit(elderInfoQueryResp.elderInfo.name),
                        elderInfoQueryResp.elderInfo.age,
                        QString::fromLocal8Bit(elderInfoQueryResp.elderInfo.gender),
                        QString::fromLocal8Bit(elderInfoQueryResp.elderInfo.recordTime),
                        QString::fromLocal8Bit(elderInfoQueryResp.elderInfo.contact),
                        QString::fromLocal8Bit(elderInfoQueryResp.elderInfo.remark)
                    );
                }
                else {
                    emit elderInfoQueryFailed(QString::fromLocal8Bit(elderInfoQueryResp.error_message));
                }
            }
            else if (head.service_type == BLOODPRESSURERECORD_QUERY) {
                memcpy(&bloodQueryResp, recvbuf + sizeof(HEAD), sizeof(BloodPressureQueryResp));
                if (bloodQueryResp.status_code == 0) {
                    for (int i = 0; i < MAX_OLD; ++i) {
                        if (strlen(bloodQueryResp.records[i].measureTime) == 0) continue;
                        emit bloodQueryRow(
                            i,
                            bloodQueryResp.records[i].systolic,
                            bloodQueryResp.records[i].diastolic,
                            QString::fromLocal8Bit(bloodQueryResp.records[i].measureTime),
                            QString::fromLocal8Bit(bloodQueryResp.records[i].remark));
                    }
                }
                else {
                    emit bloodQueryFailed(QString::fromLocal8Bit(bloodQueryResp.error_message));
                }
            }
            else if (head.service_type == MEDICINERECORD_QUERY) {
                memcpy(&medicineQueryResp, recvbuf + sizeof(HEAD), sizeof(MedicineQueryResp));
                if (medicineQueryResp.status_code == 0) {
                    for (int i = 0; i < MAX_OLD; ++i) {
                        if (strlen(medicineQueryResp.records[i].medicineName) == 0) continue;
                        emit medicineQueryRow(
                            i,
                            QString::fromLocal8Bit(medicineQueryResp.records[i].medicineName),
                            QString::fromLocal8Bit(medicineQueryResp.records[i].dosage),
                            QString::fromLocal8Bit(medicineQueryResp.records[i].recordTime),
                            QString::fromLocal8Bit(medicineQueryResp.records[i].usage),
                            QString::fromLocal8Bit(medicineQueryResp.records[i].remark));
                    }
                }
                else {
                    emit medicineQueryFailed(QString::fromLocal8Bit(medicineQueryResp.error_message));
                }
            }
            else if (head.service_type == ACTIVITYRECORD_QUERY) {
                memcpy(&activityQueryResp, recvbuf + sizeof(HEAD), sizeof(ActivityQueryResp));
                if (activityQueryResp.status_code == 0) {
                    for (int i = 0; i < MAX_OLD; ++i) {
                        if (strlen(activityQueryResp.records[i].activityType) == 0) continue;
                        emit activityQueryRow(
                            i,
                            QString::fromLocal8Bit(activityQueryResp.records[i].activityType),
                            QString::fromLocal8Bit(activityQueryResp.records[i].startTime),
                            QString::fromLocal8Bit(activityQueryResp.records[i].nendTime));
                    }
                }
                else {
                    emit activityQueryFailed(QString::fromLocal8Bit(activityQueryResp.error_message));
                }
            }
            else if (head.service_type == BLOODPRESSURERECORD) {
                memcpy(&bloodprssureresp, recvbuf + sizeof(HEAD), sizeof(BloodPressureResp));
                if (bloodprssureresp.status_code == 0) {
                    emit bloodPressureSuccess();
                    emit bloodPressureSuccessDetail(bloodprssureresp.record_id);
                } else if (bloodprssureresp.status_code == 1) {
                    emit bloodPressureFailed();
                    emit bloodPressureFailedDetail(QString::fromLocal8Bit(bloodprssureresp.error_message));
                }
            }
            else if (head.service_type == MEDICINERECORD) {
                memcpy(&medivineresp, recvbuf + sizeof(HEAD), sizeof(MedicineResp));
                if (medivineresp.status_code == 0) {
                    emit medicineSuccess();
                    emit medicineSuccessDetail(medivineresp.record_id);
                } else if (medivineresp.status_code == 1) {
                    emit medicineFailed();
                    emit medicineFailedDetail(QString::fromLocal8Bit(medivineresp.error_message));
                }
            }
            else if (head.service_type == ACTIVITYRECORD) {
                memcpy(&activityresp, recvbuf + sizeof(HEAD), sizeof(ActivityResp));
                if (activityresp.status_code == 0) {
                    emit activitySuccess();
                    emit activitySuccessDetail(activityresp.record_id);
                } else if (activityresp.status_code == 1) {
                    emit activityFailed();
                    emit activityFailedDetail(QString::fromLocal8Bit(activityresp.error_message));
                }
            }
            else if (head.service_type == CALL_RECORD_REPORT) {
                memcpy(&call_report_resp, recvbuf + sizeof(HEAD), sizeof(CALL_RECORD_REPORT_RESP));
                if (call_report_resp.status_code == 0) {
                    emit callRecordReportSuccess(call_report_resp.call_id);
                } else {
                    emit callRecordReportFailed(QString::fromLocal8Bit(call_report_resp.error_message));
                }
            }
            else if (head.service_type == CALL_RECORD_QUERY) {
                memcpy(&call_query_resp, recvbuf + sizeof(HEAD), sizeof(CALL_RECORD_QUERY_RESP));
                if (call_query_resp.status_code != 0) {
                    emit callRecordQueryFailed(QString::fromLocal8Bit(call_query_resp.error_message));
                } else {
                    for (int i = 0; i < call_query_resp.record_count && i < MAX_CALL_RECORD; ++i) {
                        const CallRecordRow &r = call_query_resp.records[i];
                        if (r.call_id <= 0) continue;
                        emit callRecordQueryRow(
                            r.call_id,
                            QString::fromUtf8(r.elder_phone),
                            r.call_type,
                            QString::fromUtf8(r.call_time),
                            QString::fromUtf8(r.remark));
                    }
                }
            }
}
}
