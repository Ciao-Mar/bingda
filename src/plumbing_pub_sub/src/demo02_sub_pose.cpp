#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
  // 在回调函数中处理接收到的位姿消息
  // 这里可以编写您希望执行的逻辑
  // 例如，打印位姿信息
  ROS_INFO("Received pose: x=%.2f, y=%.2f, z=%.2f", msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);

  // 判断小车 A 是否到达指定路径点
  if (msg->pose.position.x == 1.0 && msg->pose.position.y == 0.0 && msg->pose.position.z == 0.0)
  {
    // 当小车 A 到达指定路径点时，小车 B 开始运动
    ROS_INFO("Car A has reached the specified path point. Car B starts moving.");
    // 在这里编写小车 B 开始运动的代码
  }
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "car_B");
  ros::NodeHandle nh;

  // 创建订阅器，订阅小车 A 的位姿主题
  ros::Subscriber poseSub = nh.subscribe("/car_A/pose", 1, poseCallback);

  ros::spin();  // 进入循环，持续接收消息并调用回调函数

  return 0;
}