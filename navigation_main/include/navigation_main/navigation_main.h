#ifndef _NAVIGATION_MAIN_H_
#define _NAVIGATION_MAIN_H_

// ROS basic
#include "ros/ros.h"

// ROS msgs
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Bool.h>

// ROS srvs
#include "std_srvs/Empty.h"

// ROS param
#include <dynamic_reconfigure/server.h>

#include "navigation_main/navigation_main_paramConfig.h"

// Other lib
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <string>

class Navigation_Main {
   public:
    Navigation_Main();

    void Init(ros::NodeHandle *nh_global, ros::NodeHandle *nh_local, std::string node_name);
    double GetUpdateFrequency();

    void Loop();

   private:
    bool UpdateParams(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);

    void SetDynamicReconfigure();

    void SetTimeout(geometry_msgs::Pose poseGoal);
    bool isTimeout();

    // Callback functions
    void Odom_Callback(const nav_msgs::Odometry::ConstPtr &msg);
    void RobotMissionState_Callback(const std_msgs::Bool::ConstPtr &msg);
    void MainMission_Callback(const geometry_msgs::PoseStamped::ConstPtr &msg);
    void DynamicParam_Callback(navigation_main::navigation_main_paramConfig &config, uint32_t level);

    // Other functions
    double Distance_Between_A_and_B(geometry_msgs::Pose poseA, geometry_msgs::Pose poseB);

    // NodeHandle
    ros::NodeHandle *nh_local_;
    ros::NodeHandle *nh_global_;

    // Subscriber
    ros::Subscriber robot_odom_sub_;
    ros::Subscriber robot_mission_state_sub_;
    ros::Subscriber main_mission_state_sub_;

    // Publisher
    ros::Publisher main_mission_state_pub_;
    ros::Publisher robot_goal_pub_;

    // Server
    ros::ServiceServer param_srv_;

    // Parameters
    bool param_active_;
    bool param_publish_;
    bool param_update_params_;
    bool param_use_dynamic_reconfigure_;

    double param_update_frequency_;
    double param_timeout_;
    double param_timeout_a_;
    double param_timeout_b_;
    double param_timeout_min_;
    double param_timeout_max_;

    std::string param_node_name_;
    std::string param_robot_odom_topic_;
    std::string param_robot_mission_state_topic_;
    std::string param_robot_goal_topic_;
    std::string param_main_mission_topic_;
    std::string param_main_mission_state_topic_;

    // Variables
    bool is_mission_start_;
    bool is_reach_goal_;

    // Timeout
    ros::Time start_time_;

    // Robot Odometry
    geometry_msgs::Pose robot_goal_;
    geometry_msgs::Pose robot_odom_;
};

extern Navigation_Main navigation_main_;

#endif