#include "navigation_main/navigation_main.h"

int main(int argc, char** argv) {
    ros::init(argc, argv, "navigation_main");

    ros::NodeHandle nh_global("/");
    ros::NodeHandle nh_local("~");

    do {
        try {
            ROS_INFO_STREAM("[navigation_main] : Initializing ...");
            nav_main.Init(&nh_global, &nh_local);
            ros::spin();
        } catch (const char* s) {
            ROS_FATAL_STREAM("[navigation_main] : " << s);
            ROS_FATAL_STREAM("[navigation_main] : Resuming ...");
        } catch (...) {
            ROS_FATAL_STREAM("[navigation_main] : Unexpected error occurred.");
            ROS_FATAL_STREAM("[navigation_main] : Resuming ...");
        }
    } while (ros::ok());

    return EXIT_SUCCESS;
}