#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
/*
    发布方实现：
        1.包含头文件 
            Ros中文本类型 --->std_msgs/String.h
        2.初始ROS节点

        3.创建节点句柄
        4.创建发布者对象
        5.编写发布逻辑并发布数据
*/
int main(int argc, char *argv[])
{
    //2.初始ROS节点
    /*
        作用：ROS初始化函数
        参数 ：
            1.argc    ---- 封装实参个数 （n+1）
            2.argv    ---- 封装参数的数组
            3.name    ---- 为节点命名（唯一性）
            4.options ---- 节点启动选项
        使用：
            1.argc 与 argv 的使用
              如果按照ROS中的特定格式传入实参，那么ROS 可以加以使用，比如用来设置全局参数，给节点重命名
            2.options 的使用
    */
    ros::init(argc,argv,"erGouZi");
    //3.创建节点句柄
    ros::NodeHandle nh;
    //4.创建发布者对象
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang",10);
    //5.编写发布逻辑并发布数据
    //要求以10hz的频率发布数据，并且文本后添加编号
    //先创建被发布的消息
    std_msgs::String msg;
    //发布频率
    ros::Rate rate(10);
    //设置编号
    int count = 0;
    //编写循环，循环中发布数据
    ros::Duration(3).sleep();
    while(ros::ok())
    {
        setlocale(LC_ALL,"");
        count++;
        //msg.data = "hello";
        //实现字符串拼接数字
        std::stringstream ss;
        ss <<"hello --->" << count;
        msg.data = ss.str();
        pub.publish(msg);
        //添加日志
        ROS_INFO("发布的数据是:%s",ss.str().c_str());
        rate.sleep();
        ros::spinOnce();//官方建议，处理回调函数

    }
    return 0;
}
