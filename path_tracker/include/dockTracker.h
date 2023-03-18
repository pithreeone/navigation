#include <ros/ros.h>
#include <ros/time.h>
#include <ros/console.h>
#include <cmath>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Transform.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <std_srvs/Empty.h>


class DockTracker{
public:
    DockTracker(ros::NodeHandle& nh, ros::NodeHandle& nh_local);
    ~DockTracker();
    bool initializeParams(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);
    void initialize();

private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_local_;
    ros::ServiceServer params_srv_;
    
    // Subscriber
    ros::Subscriber goal_sub_;
    ros::Subscriber pose_sub_;
    void goalCB(const geometry_msgs::PoseStamped& data);
    void poseCB(const nav_msgs::Odometry& data);
    
    // Publisher
    ros::Publisher pub_;
    void velocityPUB();

    // Timer
    ros::Timer timer_;
    void timerCB(const ros::TimerEvent& e);
    double t_bef_;
    double t_now_;

    double goal_[3];
    double pose_[3];
    double vel_[3];
    double dock_dist_;
    bool if_get_goal_;
    bool count_dock_dist_;
    double a_;
    double dist_;
    double cosx_;
    double sinx_;

    bool p_active_;
    double control_frequency_;
    double linear_max_vel_;
    double profile_percent_;
    double tolerance_;

    double distance(double x1, double y1, double x2, double y2);
};