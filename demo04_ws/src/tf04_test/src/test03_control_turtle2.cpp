#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Twist.h"

/*
    需求1：换算出 turtle1 相对于 turtle2 的关系
    需求1：换算出 turtle2 相对于 turtle3 的关系
    需求2：计算出角速度和线速度并发布
    实现2跟随1，3跟随2
        
*/
int main(int argc, char *argv[])
{
    // 2.设置编码，节点初始化，NodeHandle
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"tfs_sub");
    ros::NodeHandle nh;
    // 3.创建订阅对象 
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener sub(buffer);
    //A.创建发布对象
    ros::Publisher pub1 = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",100);
    ros::Publisher pub2 = nh.advertise<geometry_msgs::Twist>("/turtle3/cmd_vel",100);

    // 4.编写解析逻辑；    
    ros::Rate rate(10);
    while(ros::ok()){
        //核心
        try
        {
            // 1.计算 son1 和 son2 的相对关系
            /*
                A 相对于 B 坐标关系

                参数1：目标坐标系
                参数2：源坐标系
                参数3：ros::Time(0) 取间隔最短的两个坐标关系帧计算相对关系
                返回值：geometry_msgs::TransformStamped  源相对于目标坐标系的相对关系
            */
            geometry_msgs::TransformStamped son1ToSon2 = buffer.lookupTransform("turtle2","turtle1",ros::Time(0)); 
            // ROS_INFO("turtle1 相对于 turtle2 的信息：父级：%s, 子级：%s, 偏移量(%.2f,%.2f,%.2f)",
            //         son1ToSon2.header.frame_id.c_str(),//turtle2
            //         son1ToSon2.child_frame_id.c_str(),//turtle1
            //         son1ToSon2.transform.translation.x,
            //         son1ToSon2.transform.translation.y,
            //         son1ToSon2.transform.translation.z);     
            //B.根据相对计算并组织速度消息
            geometry_msgs::Twist twist1;           
            /*
                组织速度，只需要设置线速度 x 与 角速度的 z；
                x = 系数 * 开方（y^2 + x^2）
                z = 系数 * 反正切（对边，邻边）

            */
           twist1.linear.x = 0.5 * sqrt(pow(son1ToSon2.transform.translation.x,2)+pow(son1ToSon2.transform.translation.y,2));
           twist1.angular.z = 4 *atan2(son1ToSon2.transform.translation.y,son1ToSon2.transform.translation.x);         
           //C.发布
           pub1.publish(twist1);

        }
        catch(const std::exception& e)
        {
            ROS_INFO("turtle2异常提示:%s",e.what());
        }
         try
        { 
            geometry_msgs::TransformStamped son2ToSon3 = buffer.lookupTransform("turtle3","turtle2",ros::Time(0)); 
            //B.根据相对计算并组织速度消息
            geometry_msgs::Twist twist2;
            twist2.linear.x = 0.5 * sqrt(pow(son2ToSon3.transform.translation.x,2)+pow(son2ToSon3.transform.translation.y,2));
            twist2.angular.z = 4 *atan2(son2ToSon3.transform.translation.y,son2ToSon3.transform.translation.x);
           
            //C.发布
            pub2.publish(twist2);
        }
        catch(const std::exception& e)
        {
            ROS_INFO("turtle3异常提示:%s",e.what());
        }
        
    }
    ros::spinOnce();
    return 0;
}
