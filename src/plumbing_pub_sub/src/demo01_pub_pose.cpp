#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>

ros::Publisher posePublisher;  // 小车 A 的发布器

void publishPose()
{
  // 创建并填充位姿消息
  geometry_msgs::PoseStamped poseMsg;
  poseMsg.pose.position.x = 1.0;  // 示例：假设指定的路径点为 (1.0, 0.0, 0.0)
  poseMsg.pose.position.y = 0.0;
  poseMsg.pose.position.z = 0.0;

  // 发布位姿消息给小车 B
  posePublisher.publish(poseMsg);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "car_A");
  ros::NodeHandle nh;

  // 创建发布器，发布位姿消息给小车 B
  posePublisher = nh.advertise<geometry_msgs::PoseStamped>("/car_B/pose", 1);

  ros::Rate rate(1.0);  // 每秒发布一次位姿消息，可以根据需要调整发布频率

  while (ros::ok())
  {
    publishPose();
    rate.sleep();
  }

  return 0;
}