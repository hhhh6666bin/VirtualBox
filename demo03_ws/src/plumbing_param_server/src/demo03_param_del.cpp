#include "ros/ros.h"

/*
    演示参数删除
    实现：
        ros::NOdeHnadle-------------------------------------
            nh.deleteParam("radius");

        ros::param------------------------------------------
*/
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"del_param_c");
    ros::NodeHandle nh;;
    //ros::NOdeHnadle-------------------------------------
    bool flag1 = nh.deleteParam("radius");
    if(flag1)
    {
        ROS_INFO("删除成功！");
    }else{
        ROS_INFO("删除失败！");
    }
    //ros::param------------------------------------------
    bool flag2 = ros::param::del("radius_param");
    if(flag2)
    {
        ROS_INFO("删除成功！");
    }else{
        ROS_INFO("删除失败！");
    }
    return 0;
}
