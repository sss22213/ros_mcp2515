#include <ros/ros.h>
#include <string.h>
#include <memory>
#include <string>
#include "std_msgs/UInt8MultiArray.h"
#include "std_msgs/UInt8.h"
extern "C" {
    #include "mcp2515.h"
}

// declare mcp2515
std::string path = "/dev/spidev0.0";
mcp2515_dev* mcp2515_device = new_mcp2515_dev(const_cast<char*>(path.c_str()),Normal,500000);

// can send data
void can_process_func(const std_msgs::UInt8MultiArray::ConstPtr& uint8_t_data)
{
    if(uint8_t_data->data.size() < 2)return;
    uint8_t *tx_buffer = (uint8_t*)malloc(sizeof(uint8_t_data->data.size()));
    uint8_t can_id = uint8_t_data->data[0];
    // send data to can
    for(int idx = 1; idx < uint8_t_data->data.size(); ++idx)
    {
        tx_buffer[idx-1] = uint8_t_data->data[idx];
    }
    mcp2515_send_data(mcp2515_device, can_id, tx_buffer, uint8_t_data->data.size()-1);
    free(tx_buffer);
}
//
int main(int argc, char **argv)
{
    ros::init(argc, argv, "canbus_c");
    ros::NodeHandle n;

    // initial mcp2515
    mcp2515_initial(mcp2515_device);
    // set mcp2515
    mcp2515_can_speed(mcp2515_device, can_500kpbs);
    // set mcp2515 operate mode
    mcp2515_set_mode(mcp2515_device);
    // set node to get send information
    ros::Subscriber data_sub = n.subscribe("canbus_port", 1, can_process_func);
    ros::Rate rate(20);
    while (ros::ok()) 
    {
		ros::spin();
	}
    return 0;
}