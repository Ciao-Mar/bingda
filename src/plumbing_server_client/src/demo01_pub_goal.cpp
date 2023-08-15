#include "ros/ros.h"
#include <geometry_msgs/PoseStamped.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "goal_publisher");
  ros::NodeHandle nh;

  // 创建发布器，发布到 /car_A/move_base_simple/goal
  ros::Publisher goalAPub = nh.advertise<geometry_msgs::PoseStamped>("/car_A/move_base_simple/goal", 1);

  // 创建发布器，发布到 /car_B/move_base_simple/goal
  ros::Publisher goalBPub = nh.advertise<geometry_msgs::PoseStamped>("/car_B/move_base_simple/goal", 1);

  // 创建目标点消息
  geometry_msgs::PoseStamped goalMsg;
  goalMsg.header.frame_id = "map";
  goalMsg.pose.position.x = 1.0;
  goalMsg.pose.position.y = 2.0;
  goalMsg.pose.orientation.w = 1.0;

  ros::Rate rate(1);  // 控制发布频率为1Hz

  while (ros::ok())
  {
    // 发布目标点消息到 /car_A/move_base_simple/goal
    goalAPub.publish(goalMsg);

    // 发布目标点消息到 /car_B/move_base_simple/goal
    goalBPub.publish(goalMsg);

    ros::spinOnce();
    rate.sleep();
  }

  return 0;
}