#include "ros/ros.h"
#include "turtlesim/Pose.h"

/*
    需求：订阅乌龟的位姿信息，并输出到控制台
        包含头文件
        初始化ROS节点
        创建节点句柄
        创建订阅对象
        处理订阅到的数据（回调函数）
        spin()
*/
void doPose(const turtlesim::Pose::ConstPtr &pose){
    ROS_INFO("\n乌龟的位姿信息：坐标(%.2f,%.2f),\n朝向(%.2f),\n线速度:%.2f,\n角速度:%.2f\n",
            pose->x,pose->y,pose->theta,pose->linear_velocity,pose->angular_velocity);
}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"sub_pose");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,doPose);
    ros::spin();
    return 0;
}
