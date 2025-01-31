#ifndef COMMAND_H
#define COMMAND_H

#define RET_OK 0
#define RET_ERROR -1
#define RET_AGAIN -2    //重新读取
#define RET_EXIT -3
#include <QString> //客户端退出
#include<vector>
using namespace std;

struct DeMessageHead{
    QChar mark[2]={'C','A'};   // "DE" 认证deroy的协议
    QChar version;
    QChar encoded;   //0 不加密，1 加密
    int length;//若为-1，表示只请求
};

struct DeMessagePacket
{
    /* data */
    int mode;  //1 请求,2 应答,3 消息通知
    int error; //0 成功,非0,对应的错误码

    int sequence;   //序列号
    int command;    //命令号,对应具体操作
};

//命令枚举
enum command {
    CommandEnum_Paint//CA机构生成密钥对，示证者和证明者连接过去，并获得这个公钥𝑃𝐾_𝐶𝐴
};


enum login_status{
    login_success=0,
    err_wrongpwd,
    err_nouser,
};




#endif // COMMAND_H
