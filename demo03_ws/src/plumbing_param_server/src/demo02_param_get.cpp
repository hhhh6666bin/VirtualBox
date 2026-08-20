#include "ros/ros.h"

/*
    演示参数查询
    实现：
        ros::NOdeHnadle-------------------------------------
            param(键,默认值) 
                存在，返回对应结果，否则返回默认值

            getParam(键,存储结果的变量)
                存在,返回 true,且将值赋值给参数2
                若果键不存在，那么返回值为 false，且不为参数2赋值

            getParamCached键,存储结果的变量)--提高变量获取效率
                存在,返回 true,且将值赋值给参数2
                若果键不存在，那么返回值为 false，且不为参数2赋值

            getParamNames(std::vector<std::string>)
                获取所有的键,并存储在参数 vector 中 

            hasParam(键)
                是否包含某个键，存在返回 true，否则返回 false

            searchParam(参数1，参数2)
                搜索键，参数1是被搜索的键，参数2存储搜索结果的变量
        ros::param------------------------------------------
*/
int main(int argc, char *argv[])
{
    //设置编码
    setlocale(LC_ALL,"");
    //初始化ROS节点
    ros::init(argc,argv,"get_param_c");
    //创建ROS节点句柄
    ros::NodeHandle nh;
    //ros::NodeHandle
    //1.param
    double radius = nh.param("radius",0.5);
    ROS_INFO("radius = %.2f",radius);
    //2.getparam()
        // double radius2 = 0.0;
        // bool result =nh.getParam("radius",radius2);
        // if(result)
        // {
        //     ROS_INFO("获取的半径是：%.2f",radius2);
        // }else{
        //     ROS_INFO("被查询的变量不存在。");
        // }
    //3.getParamCached 与 getParam 类似，只是性能上有所提升，一般测试下，看不出效果
    double radius2 = 0.0;
    bool result =nh.getParamCached("radius",radius2);
    if(result)
    {
        ROS_INFO("获取的半径是：%.2f",radius2);
    }else{
        ROS_INFO("被查询的变量不存在。");
    }
    //4.getParamNames
    std::vector<std::string> names;
    nh.getParamNames(names);
    for(auto &&name : names)
    {
        ROS_INFO("遍历的元素：%s",name.c_str());
    }
    //5.hasParam
    bool flag1 = nh.hasParam("radius");
    bool flag2 = nh.hasParam("radiusxx");
    ROS_INFO("radius 存在吗？%d",flag1);
    ROS_INFO("radiusxx 存在吗？%d",flag2);
    //6.searchParam
    std::string key;
    nh.searchParam("radius",key);
    ROS_INFO("搜索结果：%s\n",key.c_str());
    
    ROS_INFO("------------这是两种方式的分割线-------------\n");

    //ros:param----------------------------------------------------
    //1.param
    double radius_param = ros::param::param("radius",100.5);//100.5是查询不到的默认值 
    ROS_INFO("radius_param = %.2f",radius_param);
    //2.get
    // double radius_param2 = 0.0;
    // bool result =ros::param::get("radius",radius_param2);
    // if(result)
    // {
    //     ROS_INFO("获取的半径是：%.2f",radius_param2);
    // }else{
    //     ROS_INFO("被查询的变量不存在。");
    // }
    //3.getCached
    double radius_param2 = 0.0;
    bool result_param =ros::param::getCached("radius",radius_param2);
    if(result_param)
    {
        ROS_INFO("获取的半径是：%.2f",radius_param2);
    }else{
        ROS_INFO("被查询的变量不存在。");
    }
    //4.getParamNames
    std::vector<std::string> names_param;
    ros::param::getParamNames(names_param);
    for(auto &&name : names_param)
    {
        ROS_INFO("遍历的元素：%s",name.c_str());
    }
    //5.has
    bool flag_param1 = ros::param::has("radius"); 
    bool flag_param2 = ros::param::has("radiusxx"); 
    ROS_INFO("radius 存在吗？%d",flag_param1);
    ROS_INFO("radiusxx 存在吗？%d",flag_param2);
    //6.search
    std::string key_param;
    ros::param::search("radius",key_param);
    ROS_INFO("搜索结果：%s",key_param.c_str());

    return 0;
}
