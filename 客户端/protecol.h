#pragma once
#define MAX_DATE 30     // 左侧视频列表最大长度
#define MAX_VIDEO 20    // 单次获取最大视频列表长度
#define MAX_PICTURE 20    // 单次获取最大图片列表长度
#define MAX_OLD 20    // 单次获取最大图片列表长度
#define MAX_CALL_RECORD 20
typedef struct sendmsgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[2];    /* message data */
}MSGBUF;
union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds* buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short* array;  /* Array for GETALL, SETALL */
    struct seminfo* __buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};


typedef enum {
    LOGIN,	//登录
    REGISTER,	//注册
    CODE,	//获取验证码
    DOCUMENT,	// 传输文件
    SEND_PICTURE,   // 发送抓拍图片
    SEND_VIDEO,     // 发送录制视频信息
    GET_VIDEO_LIST, // 获取视频列表
    GET_PICTURE_LIST,//获取图片列表
    GET_OLD_LIST,	//获取老人列表
    ELDERINFO,
    ELDERINFO_QUERY, //按手机号查询老人基本信息
    BLOODPRESSURERECORD_QUERY, //按手机号查询血压记录
    MEDICINERECORD_QUERY, //按手机号查询药品记录
    ACTIVITYRECORD_QUERY, //按手机号查询活动记录
    BLOODPRESSURERECORD,
    MEDICINERECORD,
    ACTIVITYRECORD,
    CALL_RECORD_REPORT,
    CALL_RECORD_QUERY
}SERVICE_TYPE;

//头包
typedef struct {

    SERVICE_TYPE service_type;	//操作类型
    int data_len;	//数据长度
    char crc32[9];	//CRC校验码
    int client_fd;	//客户端文件描述符

}HEAD;




//业务接口
//----------1.1(验证码)----------
//响应
typedef struct {

    char phone[12];	//手机号码
    char code[7];	//验证码
    int status_code;	//状态码	0：成功发送验证码
                        //			1：手机号已经存在
                        //			2：短信验证码发送失败
    char error_message[64];	//错误信息


}CODE_RESP;
//请求
typedef struct {
    char phone[12];	//手机号码
    int type;	//验证码类型  0:短信验证码
                //            1:图形验证码

}CODE_REQ;


//----------1.2(注册)----------
//响应
typedef struct {
    char phone[12];	//手机号码
    char password[12];	//随机密码
    int status_code;	//状态码    0：注册成功，返回初始密码
                        //			1：注册失败，返回错误信息
    char error_message[64];	//错误信息


}REGISTER_RESP;


//请求
typedef struct {

    char phone[12];	//手机号码
    char code[7];	//验证码
    int  kind;//类型 0：老人 1：护工 2：家属

}REGISTER_REQ;



//----------2(登录)----------
//响应
typedef struct {

    char phone[12];	//手机号码
    int status_code;	//状态码	0：登录成功老人
                        //			1：用户名不存在
                        //			2：密码错误
                        //			3：验证码错误
                        //			4：登陆成功护工
                        //			5：登陆成功家属
    char error_message[64];	//错误信息


}LOGIN_RESP;


//请求
typedef struct {

    char phone[12];	//手机号码
    char password[33];	//随机密码
    char code[7];	//验证码
    int  kind;//类型 0：老人 1：护工 2：家属
}LOGIN_REQ;





//--------4(文件信息)---------
//响应
typedef struct {
    int  status_code;       // 状态码			//0 成功   1 失败
    char error_message[64]; // 错误信息
    char document_name[40]; // 文件名
    int  index;             // 碎片编号
}DOCUMENT_RESP;
//请求
typedef struct {
    char phone[12];         // 用户账号
    char document_name[40]; // 文件名
    int  document_size;     // 文件大小
    char document_type[5];  // 文件类型
    char creat_time[20];    // 创建时间 格式"YYYY-MM-DD HH:MM:SS"
    int  piece_index;       // 碎片编号
    char piece_data[1024];  // 碎片内容
    int  piece_size;        // 单个碎片大小
    int  piece_num;         // 总碎片数
}DOCUMENT_REQ;
//--------5(图片信息)---------
// 定义图片表结构体
typedef struct {
    char picture_name[50];      // 图片名称，对应varchar(50)
    char picture_time[20];      // 图片时间
    int picture_type;           // 图片类型，对应int 0车牌号 1进场 2出场 3抓拍
} Picture;
typedef struct {
    int oldnum;
    char phone[12];
}Eld;
//请求
typedef struct {
    char phone[12];         // 用户id
    Picture picture;
} PICTURE_REQ;
//响应
typedef struct {
    int  status_code;       // 状态码
    char error_message[64]; // 错误信息
    char document_name[40]; // 文件名
} PICTURE_RESP;
//--------6(更新视频信息)---------
// 定义视频播放结构体
typedef struct {
    char video_name[50];      // 视频名称，对应varchar(50)
    char cover_path[50];      // 封面路径，对应varchar(50)
    char video_time[20];      // 保存时间，datetime类型这里用字符串表示
    int video_current;        // 上次播放进度，对应int
    int video_alltime;        // 视频总时长，对应int
    char video_starttime[20]; // 上一次播放时间，datetime类型用字符串表示
} Video;
// 发送（更新）视频信息
typedef struct {
    char phone[12];         // 用户id
    Video video;
    int type;	//0代表插入  1代表更新
} VIDEO_REQ;

typedef struct {
    int  status_code;       // 状态码
    char error_message[64]; // 错误信息
    char document_name[40]; // 文件名
} VIDEO_RESP;
//--------7(获取视频信息)---------
// 获取视频列表
typedef struct {    // from 与 to 不能超过 MAX_VIDEO
    int from;
    int to;
    int type;       // 0 按月 1 按天  -1 查询视频
    char time[20];  // 当前选择的日期

} GET_VIDEO_REQ;

typedef struct {
    int  status_code;           // 状态码
    char error_message[64];     // 错误信息
    char datetime[MAX_DATE][20];// 左侧日期列表
    Video video_arr[MAX_VIDEO]; // 视频信息
} GET_VIDEO_RESP;

//--------7(获取图片信息)---------
// 获取视频列表
typedef struct {    // from 与 to 不能超过 MAX_PICTURE
    int from;
    int to;
    int type;       // 0 按月 1 按天  -1 查询图片
    char time[20];  // 当前选择的日期

} GET_PICTURE_REQ;

typedef struct {
    int  status_code;           // 状态码
    char error_message[64];     // 错误信息
    char datetime[MAX_DATE][20];// 左侧日期列表
    Picture picture_arr[MAX_PICTURE]; // 图片信息
} GET_PICTURE_RESP;

//--------8(获取老人信息)---------
// 获取视频列表
typedef struct {
    int from;
    int to;
    char family_phone[12];
} GET_OLDLIST_REQ;

typedef struct {
    int  status_code;           // 状态码
    char error_message[64];     // 错误信息

    Eld old_arr[MAX_OLD]; // 老人信息
} GET_OLDLIST_RESP;
// 1. 老人基本信息
typedef  struct {
    int age;                     // 年龄
    char gender[20];          // 性别
    char recordTime[20];      // 记录时间
    char name[20];            // 姓名
    char contact[20];         // 联系人
    char remark[64];          // 备注
}ElderInfo1;

// 2. 血压记录
typedef struct  {
    int systolic;          // 收缩压 (mmHg)
    int diastolic;         // 舒张压 (mmHg)
    char measureTime[20];     // 测量时间
    char remark[20];          // 备注
}BloodPressureRecord1;

// 3. 药品记录
typedef struct {
    char medicineName[20];    // 药品名称
    char dosage[20];          // 剂量 (如 "10mg" 或 "1片")
    char recordTime[20];      // 记录时间
    char usage[20];           // 用法 (如 "口服，每日三次")
    char remark[64];          // 备注
}MedicineRecord1;

// 4. 活动记录
typedef struct{
    char activityType[20];    // 活动类型 (如 "散步", "锻炼")
    char startTime[20];       // 活动开始时间
    char nendTime[20];         // 活动结束时间
} ActivityRecord1;

// 1. 老人基本信息请求/响应
typedef struct {
    char phone[12];          // 手机号
    int type;                // 0:插入 1:更新
    ElderInfo1 elderInfo;    // 直接使用原有结构体
} ElderInfoReq;

typedef struct {
    int status_code;
    char error_message[64];
    char elder_phone[12];  // 成功时返回老人手机号（与 elder_id 主键一致）；失败可全 0
} ElderInfoResp;

// 老人信息查询请求/响应
typedef struct {
    char phone[12];          // 要查询的老人手机号
} ElderInfoQueryReq;

typedef struct {
    int status_code;         // 0 成功 1 未找到 2 失败
    char error_message[64];
    ElderInfo1 elderInfo;    // 查询到的老人信息
} ElderInfoQueryResp;

typedef struct {
    char phone[12];
} BloodPressureQueryReq;

typedef struct {
    int status_code;
    char error_message[64];
    BloodPressureRecord1 records[MAX_OLD];
} BloodPressureQueryResp;

typedef struct {
    char phone[12];
} MedicineQueryReq;

typedef struct {
    int status_code;
    char error_message[64];
    MedicineRecord1 records[MAX_OLD];
} MedicineQueryResp;

typedef struct {
    char phone[12];
} ActivityQueryReq;

typedef struct {
    int status_code;
    char error_message[64];
    ActivityRecord1 records[MAX_OLD];
} ActivityQueryResp;

// 2. 血压记录请求/响应
typedef struct {
    char phone[12];
    int type;
    BloodPressureRecord1 bpRecord;   // 血压记录
} BloodPressureReq;

typedef struct {
    int status_code;
    char error_message[64];
    int record_id;           // 血压记录ID
} BloodPressureResp;

// 3. 药品记录请求/响应
typedef struct {
    char phone[12];
    int type;
    MedicineRecord1 medRecord;       // 药品记录
} MedicineReq;

typedef struct {
    int status_code;
    char error_message[64];
    int record_id;
} MedicineResp;

// 4. 活动记录请求/响应
typedef struct {
    char phone[12];
    int type;
    ActivityRecord1 actRecord;       // 活动记录（注意原结构体中 nendTime 拼写，可保留）
} ActivityReq;

typedef struct {
    int status_code;
    char error_message[64];
    int record_id;
} ActivityResp;

typedef struct {
    int call_id;
    char elder_phone[12];
    int call_type;
    char call_time[32];
    char remark[128];
} CallRecordRow;

typedef struct {
    char elder_phone[12];
    int call_type;
    char remark[128];
} CALL_RECORD_REPORT_REQ;

typedef struct {
    int status_code;
    char error_message[64];
    int call_id;
} CALL_RECORD_REPORT_RESP;

typedef struct {
    char family_phone[12];
    char elder_phone[12];
    int from;
    int to;
} CALL_RECORD_QUERY_REQ;

typedef struct {
    int status_code;
    char error_message[64];
    int record_count;
    CallRecordRow records[MAX_CALL_RECORD];
} CALL_RECORD_QUERY_RESP;
