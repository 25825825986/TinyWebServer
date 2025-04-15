#include "config.h"

int main(int argc, char *argv[])
{
    //需要修改的数据库信息,登录名,密码,库名
    string user = "root";
    string passwd = "050422";
    string databasename = "Tinyserverdb";

    //命令行解析
    Config config;
    config.parse_arg(argc, argv);

    WebServer server;

    //初始化
    server.init(config.PORT, user, passwd, databasename, config.LOGWrite, 
                config.OPT_LINGER, config.TRIGMode,  config.sql_num,  config.thread_num, 
                config.close_log, config.actor_model);
    

    //日志
    server.log_write();

    //数据库
    server.sql_pool();

    //线程池
    server.thread_pool();

    //触发模式
    server.trig_mode();

    //监听
    server.eventListen();

    //运行
    server.eventLoop();

    return 0;
}

/*
// 建立yourdb库
create database Tinyserverdb;

// 创建user表
USE Tinyserverdb;
CREATE TABLE user(
    username char(50) NULL,
    passwd char(50) NULL
)ENGINE=InnoDB;

// 添加数据
INSERT INTO user(username, passwd) VALUES('fengyue', '123456');

//项目结构
TinyWebServer/
├── build.sh            # 构建脚本
├── makefile            # Makefile 文件
├── main.cpp            # 程序入口，初始化数据库信息
├── webserver.cpp/.h    # 核心服务器逻辑
├── config.cpp/.h       # 全局配置解析
├── CGImysql/           # CGI 与 MySQL 辅助类
├── http/               # HTTP 解析与连接处理
├── lock/               # 同步机制封装
├── log/                # 同步/异步日志系统
├── threadpool/         # 半同步/半反应堆线程池
├── timer/              # 非活动连接定时器管理
├── test_pressure/      # 内置 Webbench 压力测试工具
└── README.md           # 项目说明文档

*/