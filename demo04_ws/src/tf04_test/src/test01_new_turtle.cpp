#include "ros/ros.h"
#include "turtlesim/Spawn.h"
/*
    需求：是向服务端发送请求，生成一只新乌龟
        话题：/spawn
        消息：turtlesim/Spwan
    包含头文件
    初始化ROS节点
    创建节点句柄
    创建客户端对象
    组织数据并发送
    处理响应
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"service_call");
    ros::NodeHandle nh;
    //4.创建客户端对象
    ros::ServiceClient client =nh.serviceClient<turtlesim::Spawn>("/spawn");
    //5.组织数据并发送
    //5-1.组织请求
    turtlesim::Spawn spawn1;
    turtlesim::Spawn spawn2;

    spawn1.request.x = 1.0;
    spawn1.request.y = 4.0;
    spawn1.request.name = "turtle2";
    spawn1.request.theta = 1.57;

    spawn2.request.x = 4.0;
    spawn2.request.y = 1.0;
    spawn2.request.name = "turtle3";
    spawn2.request.theta = 3.14;
    //5-2.处理响应
    //调用判断服务器状态的函数
    //函数1
    //client.waitForExistence();
    //函数2
    ros::service::waitForService("/spawn");
    bool flag1 = client.call(spawn1);//flag 是用来接受响应状态，响应结果也会被社至今spawn对象
    bool flag2 = client.call(spawn2);
    //6.处理响应
    if(flag1){
        ROS_INFO("乌龟生成成功，新乌龟叫：%s",spawn1.request.name.c_str());
    }else{
        ROS_INFO("请求失败！");
    }
    if(flag2){
        ROS_INFO("乌龟生成成功，新乌龟叫：%s",spawn2.request.name.c_str());
    }else{
        ROS_INFO("请求失败！");
    }
    return 0;
}
