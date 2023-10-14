#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "sensor_msgs/msg/imu.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/convert.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"

class IMU_DR : public rclcpp::Node {
public:
    IMU_DR() : Node("IMU_DR_deadreckon") {
        
        tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(this);

        


        // tf_broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(*this);
        // timer_ = this->create_wall_timer(
        // 100ms, std::bind(&IMU_DR::imuCallback, this));



    }

private:
    // void rec_data(const sensor_msgs::msg::Imu::SharedPtr msg) {
    
    // }

    void imuCallback( const std::shared_ptr<sensor_msgs::msg::Imu> msg) {
       
        // Extract orientation from the IMU message
        // tf2::Quaternion tf_orientation;
        // tf2::fromMsg(msg->orientation, tf_orientation);

        // Create a transformation message
        geometry_msgs::msg::TransformStamped transform_stamped;
        
        double pos_x = msg->linear_acceleration.x ;
        double pos_y = msg->linear_acceleration.y ;

        auto n_pos_x =+  pos_x*0.01;
        auto n_pos_y =+  pos_y*0.01;
    

        
        transform_stamped.header.stamp = this->get_clock()->now();
        transform_stamped.header.frame_id = "odom";  // Parent frame
        transform_stamped.child_frame_id = "imu_link";   // Child frame
        transform_stamped.transform.translation.x = n_pos_x;  
        transform_stamped.transform.translation.y = n_pos_y;
        transform_stamped.transform.translation.z = 0.0; //msg->linear_acceleration.z;

        tf2::Quaternion q;
        q.setRPY(msg->angular_velocity.x, msg->angular_velocity.y, msg->angular_velocity.z);
        transform_stamped.transform.rotation.x = q.x();
        transform_stamped.transform.rotation.y = q.y();
        transform_stamped.transform.rotation.z = q.z();
        transform_stamped.transform.rotation.w = q.w();
        RCLCPP_INFO(this->get_logger(), "I heard: '%f'", n_pos_x);

        
        // transform_stamped.transform.rotation = tf2::toMsg(tf_orientation);

        // Broadcast the transformation
        tf_broadcaster_->sendTransform(transform_stamped);

    }
    // rclcpp::TimerBase::SharedPtr timer_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<IMU_DR>());
    rclcpp::shutdown();
    return 0;
}