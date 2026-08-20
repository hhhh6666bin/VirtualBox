#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include  "tf2/LinearMath/Quaternion.h"
/*
    发布方：要求订阅乌龟的位姿信息，转换成相对窗体的坐标关系，并发布
    准备：
        话题：/turtle1/pose
        消息：turtle1/Pose
    流程：
    1.包含头文件
    2.设置编码，节点初始化，NodeHandle
    3.创建订阅对象，订阅 /turtle1/pose
    4.回调函数处理订阅到的信息：将位姿信息转换成坐相对关系并发布（关注）
    5.spin()


*/
void doPose(const turtlesim::Pose::ConstPtr& pose){
    //获取位姿信息，转换成坐标系相对关系（核心），并发布
    //1.创建发布对象
    static tf2_ros::TransformBroadcaster pub;
    //2.组织被发布的数据
    geometry_msgs::TransformStamped ts;
    ts.header.stamp = ros::Time::now();
    ts.header.frame_id = "world";
    ts.child_frame_id = "turtle1";
    //坐标系偏移量设置
    ts.transform.translation.x = pose->x;
    ts.transform.translation.y = pose->y;
    ts.transform.translation.z = 0;
    //坐标系四元数
    /*
        位姿信息没有四元数，但是有个偏航角度，又已知乌龟是2d，没有翻滚与俯仰角度，
        所以可以得出乌龟的欧拉角：0 0 theta
    */
    tf2::Quaternion qtn;//创建四元数对象
    //向对象设置欧拉角，这个对象可以将欧拉角转换成四元数
    qtn.setRPY(0,0,pose->theta);
    ts.transform.rotation.w = qtn.getW();
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();

    //3.发布
    pub.sendTransform(ts);
}
int main(int argc, char *argv[])
{
    // 2.设置编码，节点初始化，NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;
    // 3.创建订阅对象，订阅 /turtle1/pose
    ros::Subscriber sub  = nh.subscribe("/turtle1/pose",100,doPose);
    // 4.回调函数处理订阅到的信息：将位姿信息转换成坐相对关系并发布（关注）
    // 6.spin()
    ros::spin();
    return 0;
}
