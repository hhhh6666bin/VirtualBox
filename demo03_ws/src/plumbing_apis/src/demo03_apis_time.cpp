#include "ros/ros.h"
/*
    需求1：演示时间相关操作（获取当前时刻 + 设置指定时刻）
    实现：
        1.准备(头文件，节点初始化，NodeHandle创建。。。)
        2.获取当前时刻
        3.设置指定时刻
    
    需求2：程序中停顿中 5 秒
    实现：
    1。创建持续时间对象
    2.休眠

    需求3：已知程序开始运行的时间，和运行的时间，求程序结束的时间 
    实现：
        1.获取开始执行的时间
        2.模拟运行时间（N秒）
        3.计算结束时间 = 开始+持续时间
    
    注意：
        1.时刻与持续时间可以执行加减
        2.持续时间之间也可执行加减
        3.时刻之间可以相减，不可以相加

    需求4：每隔1秒钟，在控制台输出一段文本
    实现：
        策略1：ros::Rate();
        策略2：定时器
    注意：
        创建：nh.createTimer()
        参数1：时间间隔
        参数2：回调函数（时间事件 TimerEvent）
        参数3:是否只执行一次
        参数4:是否自启动（当设置为 false ，需要手动调用timer.start(）)

        定时器启动后：ros::spin()
*/
//回调函数
void cb(const ros::TimerEvent &event){
    ROS_INFO("=======");
    ROS_INFO("函数被调用的时刻：%.2f",event.current_real.toSec());
}
int main(int argc, char *argv[])
{
    // 1.准备(头文件，节点初始化，NodeHandle创建。。。)
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_time");
    ros::NodeHandle nh;//注意:必须，否则会导致时间API调用失败（要在 NodeHandle 中初始化时间操作）
    // 2.获取当前时刻
    //now函数会将当前时刻封装并返回
    //当前时刻:now 被调用执行的那一刻
    //参考系：1970年01月01日 00：00：00
    ros::Time right_time = ros::Time::now();
    ROS_INFO("当前时刻：%.2f",right_time.toSec());
    ROS_INFO("当前时刻：%d",right_time.sec);

    // 3.设置指定时刻
    ros::Time t1(20,312345678);
    ros::Time t2(100.35);

    ROS_INFO("t1 = %.2f",t1.toSec());
    ROS_INFO("t2 = %.2f",t2.toSec());
    //---------------------------------------------------------------//
    ROS_INFO("-----------------持续时间------------------");
    ros::Time start = ros::Time::now();
    ROS_INFO("开始休眠:%.2f",start.toSec());
    //核心代码
    ros::Duration du(4.5);
    du.sleep();//休眠
    ros::Time end = ros::Time::now();
    ROS_INFO("休眠结束:%.2f",end.toSec());
    //---------------------------------------------------------------//
    ROS_INFO("-----------------时间计算------------------");
    //时刻与持续时间的运算
    // 1.获取开始执行的时间
    ros::Time begin = ros::Time::now();
    // 2.模拟运行时间（N秒）
    ros::Duration du1(5);
    // 3.计算结束时间 = 开始+持续时间
    ros::Time stop = begin +du1;
    ROS_INFO("开始时刻:%.2f",begin.toSec());
    ROS_INFO("结束时刻:%.2f",stop.toSec());

    //时刻与时刻运算
    //ros::Time sum = begin + stop;不可以相加
    ros::Duration du2 = begin - stop;
    ROS_INFO("时刻相减:%.2f",du2.toSec());

    //持续时间与持续时间的运算
    ros::Duration du3 = du1 + du2;//0
    ros::Duration du4 = du1 - du2;//10
    ROS_INFO("du1 + du2 = %.2f",du3.toSec());
    ROS_INFO("du1 + du2 = %.2f",du4.toSec());
    //---------------------------------------------------------------//
    ROS_INFO("-----------------定时器------------------");
    /*
    ros::Timer createTimer(ros::Duration period,    //时间间隔 ---1s
                const ros::TimerCallback &callback, //回调函数 ---封装业务
                bool oneshot = false,               //是否一次性
                bool autostart = true)              //是否自启动
    */
    ros::Timer timer = nh.createTimer(ros::Duration(1),cb,false,false);
    timer.start();//手动启动
    ros::spin();//需要回旋

    return 0;
}
