# MCP2515 CAN communication by user space SPI linux api

## Features

- use linux user space spi api
- test on ros melodic
- support arm,arm64,x86_64
- test on jetson nvidia nano
- default can and spi speed: 500kbps

## Usage

- copy this to your ros workspace
- catkin_make
- rosrun rosrun canbus_c canbus_c


## File

- canbus_c.cpp => ros node
- mcp2515.c => library implement source code
- mcp2515.h => library header file

## Subscribed
``` canbus_port (std_msgs/UInt8MultiArray) ```
- data[0] = id, data[1]~data[n] = your_data

## explain

- In canbus_c.cpp Line 13:

```
    std::string path = "/dev/spidev0.0"; // spi device in linux device location 
    mcp2515_dev* mcp2515_device = new_mcp2515_dev(const_cast<char*>(path.c_str()),Normal,500000); // mcp2515 on Normal mode, spi speed 500kbps
```
