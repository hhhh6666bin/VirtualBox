#include "plumbing_head_src/hello.h"
#include "ros/ros.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_head");
    //函数调用
    hello_ns::MyHello myhello;
    myhello.run();
    return 0;
}
