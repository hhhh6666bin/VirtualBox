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
              节点名称需要保证唯一，会导致一个问题：同一个节点不能重复启动
              结果：ROS 中当有重名的节点启动时，之前的节点会被关闭
              需求：特定场景下，需要多个节点多次启动且能正常运行，怎么办？
              解决：设置启动项 ros::init_options::AnonymousName
                    当创建ROS 节点时，会在用户自定义的节点名称后缀随机数，从而避免重名问题
    */
    ros::init(argc,argv,"erGouZi",ros::init_options::AnonymousName);
    //3.创建节点句柄
    ros::NodeHandle nh;
    //4.创建发布者对象
    /*
        作用：创建发布者对象

        模版：被发布的消息类型

        参数：：
            1.话题名称
            2.队列长度
            3.latch（可选） 如果设置为 true ，会保存发布方的最后一条消息，
            并且新的订阅者对象连接到发布方时，发布方会将这条消息发送给订阅者
        使用：
            latch 设置为 true 的作用：
            以静态地图发布为例，方案一：可以设置使用固态频率发送地图数据，但是效率低 方案二：可以将
            地图发布对象的 latch 设置为 true ，并且发布方只发布一次数据，每当订阅者连接时，
            将地图数据发送给订阅者（只发送一次），这样提高了数据的发送效率    
    */
    ros::Publisher pub = nh.advertise<std_msgs::String>("fang",10,true);
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
        //如果计数器>=50，那么关闭节点
        if(count>=50){
            ros::shutdown();
        } 
        setlocale(LC_ALL,"");
        count++;
        //msg.data = "hello";
        //实现字符串拼接数字
        std::stringstream ss;
        ss <<"hello --->" << count;
        msg.data = ss.str();
        // if(count<=10){
        //     pub.publish(msg);
        //     //添加日志
        //     ROS_INFO("发布的数据是:%s",ss.str().c_str());
        // }
        pub.publish(msg);
        //添加日志
        ROS_INFO("发布的数据是:%s",ss.str().c_str());
        rate.sleep();
        ros::spinOnce();//官方建议，处理回调函数
        ROS_INFO("一轮回调执行完毕。。。");

    }
    return 0;
}
