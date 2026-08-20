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
    turtlesim::Spawn spawn;
    spawn.request.x = 4.0;
    spawn.request.y = 1.0;
    spawn.request.name = "turrtle2";
    spawn.request.theta = 3.14;
    //5-2.处理响应
    //调用判断服务器状态的函数
    //函数1
    //client.waitForExistence();
    //函数2
    ros::service::waitForService("/spawn");
    bool flag = client.call(spawn);//flag 是用来接受响应状态，响应结果也会被社至今spawn对象
    //6.处理响应
    if(flag){
        ROS_INFO("乌龟生成成功，新乌龟叫：%s",spawn.request.name.c_str());
    }else{
        ROS_INFO("请求失败！");
    }

    return 0;
}
