#include "getCodeUtil.h"
#include "getCodeUtil.h"
int basefd = -1;
const char* hostname = "106.ihuyi.cn";
const char* send_sms_uri = "/webservice/sms.php?method=Submit&format=json";
getCodeUtil::getCodeUtil(char* mobile)
{
    //this->mobile = new char[12];
    this->mobile = mobile;
    this->isSend();
}

getCodeUtil::~getCodeUtil()
{

    delete this->mycode;
}


/**
 * 安全网络连接函数
 * 支持IPv4/IPv6，使用现代getaddrinfo接口
 */
int getCodeUtil::safe_connect(const char* host, const char* service)
{
    struct addrinfo hints = { 0 };
    struct addrinfo* result, * rp;
    int sockfd = -1;

    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

    int ret = getaddrinfo(host, service, &hints, &result);
    if (ret != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return -1;
    }

    /* 遍历所有返回的地址直到成功连接 */
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        sockfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (sockfd == -1)
            continue;

        if (connect(sockfd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;  /* 连接成功 */

        SAFE_CLOSE(sockfd);
    }

    freeaddrinfo(result);

    if (rp == NULL) {  /* 所有地址尝试失败 */
        fprintf(stderr, "Could not connect to %s:%s\n", host, service);
        return -1;
    }

    return sockfd;
}

/**
 * 安全HTTP POST请求函数
 * 完整处理发送和接收，包含错误检查
 */
ssize_t getCodeUtil::http_post(const char* page, const char* poststr)
{
    char sendline[MAXLINE + 1] = { 0 };
    char recvline[MAXLINE + 1] = { 0 };
    ssize_t n, total, sent;

    /* 构造请求头 */
    int header_len = snprintf(sendline, MAXLINE,
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/x-www-form-urlencoded\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n\r\n"
        "%s", page, hostname, strlen(poststr), poststr);

    if (header_len >= MAXLINE) {
        fprintf(stderr, "Request too large\n");
        return -1;
    }

    /* 完整发送数据 */
    total = strlen(sendline);
    sent = 0;
    while (sent < total) {
        n = write(basefd, sendline + sent, total - sent);
        if (n <= 0) {
            perror("write failed");
            return -1;
        }
        sent += n;
    }

    /* 读取响应 */
    while ((n = read(basefd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        printf("Response:\n%s\n", recvline);

        /* 简单解析HTTP状态码 */
        if (strstr(recvline, "HTTP/1.1 200 OK") == NULL) {
            fprintf(stderr, "HTTP request failed\n");
            return -1;
        }
    }

    return n;
}

/**
 * 安全短信发送函数
 * 使用环境变量存储敏感信息
 */
int getCodeUtil::send_sms()
{
    char params[MAXPARAM + 1] = { 0 };


    const char* account = "C10225481";//APIID
    const char* password = "140749f5508e0dd721ae5c7a697f0f0c";//APIKEY
    //const char*  mobile = "17337638338";//手机号码

    if (!account || !password || !this->mobile) {
        fprintf(stderr, "Missing environment variables:\n");
        fprintf(stderr, "Required: SMS_ACCOUNT, SMS_PASSWORD, SMS_MOBILE\n");
        return -1;
    }

    //生成验证码
    char* code = new char[7];
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 6; ++i)
    {
        code[i] = static_cast<char>((rand() % 10) + '0');
        code[6] = '\0';
    }

    //const char* content = "您的验证码是：19810327。请不要把验证码泄露给其他人。";//模板确定一致



    char* content = new char[1024];
    sprintf(content, "%s%s%s", "您的验证码是：", code, "。请不要把验证码泄露给其他人。");
    //code开辟空间
    this->mycode = new char[7];
    this->mycode = code;


    /* 安全构造参数 */
    int param_len = snprintf(params, MAXPARAM,
        "account=%s&password=%s&mobile=%s&content=%s",
        account, password, this->mobile, content);

    if (param_len < 0 || param_len >= MAXPARAM) {
        fprintf(stderr, "Parameter string too long\n");
        return -1;
    }

    return http_post(send_sms_uri, params);
}

char* getCodeUtil::getCode()
{
    return this->mycode;
}

bool getCodeUtil::isSend()
{
    /* 建立安全连接 */
    if ((basefd = safe_connect(hostname, "80")) == -1) {
        fprintf(stderr, "Connection failed\n");
        return false;
    }

    /* 发送短信 */
    if (send_sms() < 0)
    {
        fprintf(stderr, "SMS sending failed\n");
        SAFE_CLOSE(basefd);
        return false;
    }

    printf("Message sent successfully\n");
    SAFE_CLOSE(basefd);
    //return EXIT_SUCCESS;
    return true;
}
