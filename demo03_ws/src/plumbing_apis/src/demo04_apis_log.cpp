#include "ros/ros.h"
/*
    ROS中的日志：
        演示不同级别日志的基本使用

*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_log");
    ros::NodeHandle nh;
    //日志输出
    ROS_DEBUG("LLLL");//不会打印到控制台
    ROS_INFO("SSSSS");
    ROS_WARN("wwwww");
    ROS_ERROR("UUUUU");
    ROS_FATAL("DDDD");

    return 0;
}
