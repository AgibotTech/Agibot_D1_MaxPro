# Highlevel函数介绍
高层运动控制接口实现对机器狗的姿态、速度、行走、特定动作等控制，也可获取机器狗的相关状态。

## 站立
| 函数名 | Standup  |
|------| ----- |
| 函数原型 | int32_t Standup() |
| 功能概述 | 站立 |
| 参数 | 无 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

## 趴下
| 函数名 | Getdown  |
|------| ----- |
| 函数原型 | int32_t GetDown() |
| 功能概述 | 趴下 |
| 参数 | 无 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

## 移动
| 函数名 | Move  |
|------| ----- |
| 函数原型 | int32_t Move(double lm, double vm, double lrm) |
| 功能概述 | 前后左右移动 |
| 参数 | lm:横向移动<br>横向左移：【0,0.4）(m/s); 横向右移：(-0.4,0](m/s); <br>vm:前后移动<br>向前移动：【0,1.5)(m/s),向后移动：(-0.5,0](m/s)；<br>lrm:左右转向<br>向左转向：【0，0.5)(rad/s),向右转向：(-0.5,0](rad/s)|
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | 持续移动，调用StopMove停止 |

## 停止运动
| 函数名 | StopMove  |
|------| ----- |
| 函数原型 | int32_t StopMove() |
| 功能概述 | 停止运动 |
| 参数 | 无|
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | 将速度指令置0，机器狗停止运动 |

## 俯仰
| 函数名 | Rotate_up_and_down  |
|------| ----- |
| 函数原型 | int32_t Rotate_up_and_down(float ang) |
| 功能概述 | 俯仰 |
| 参数 | ang:角度(-14°，11°)，-x表示仰视x度，x表示俯视x度|
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

## 向左向右转向
| 函数名 | Rotate_right_and_left  |
|------| ----- |
| 函数原型 | int32_t Rotate_right_and_left(double radian) |
| 功能概述 | 向左向右转向 |
| 参数 | radian:角度(-8,8)度|
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

##  切换到匍匐状态
| 函数名 | SwitchToCrawlMode  |
|------| ----- |
| 函数原型 | int32_t SwitchToCrawlMode(bool val) |
| 功能概述 | 切换到匍匐模式 |
| 参数 | val：设置 true 为开启，false 为关闭。 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

## 设置速度
| 函数名 | SetSpeed  |
|------| ----- |
| 函数原型 | int32_t SetSpeed(float speed) |
| 功能概述 | 设置速度 |
| 参数 | speed:机器狗运行的速度 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |


## 零力矩模式
| 函数名 | ZeroToque  |
|------| ----- |
| 函数原型 | int32_t ZeroToque() |
| 功能概述 | 零力矩模式 |
| 参数 | 无 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

## 阻尼模式
| 函数名 | Damp  |
|------| ----- |
| 函数原型 | int32_t Damp() |
| 功能概述 | 阻尼模式 |
| 参数 | 无 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | |

## 关节锁定模式
| 函数名 | JointLockMode  |
|------| ----- |
| 函数原型 | int32_t JointLockMode(bool val) |
| 功能概述 | 关节锁定模式 |
| 参数 | val：设置 true 为开启，false 为关闭。 |
| 返回值 | 调用成功返回0，否则返回相关错误码。|
| 备注 | 需要先调用int32_t Rotate_up_and_down(float udm, float ang)函数让机器狗前倾或者后仰 |

## 强化学习模式切换
| 函数名 | SwitchToRLMode  |
|------| ----- |
| 函数原型 | int32_t SwitchToRLMode(bool val) |
| 功能概述 | 切换到强化学习模式 |
| 参数 | val：设置 true 为开启，false 为关闭。 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | 上下楼梯、越障需要切换到强化学习模式 |


## 获取移动速度
| 函数名 | GetSpeed  |
|------| ----- |
| 函数原型 | int32_t GetSpeed() |
| 功能概述 | 获取运行时的速度 |
| 参数 | 无 |
| 返回值 | 成功返回0，异常返回对应的异常码 |
| 备注 | XYZ轴速度计算得出 |

## 获取倾斜角度
| 函数名 | GetAngle  |
|------| ----- |
| 函数原型 | int32_t GetAngle() |
| 功能概述 | 获取倾斜角度 |
| 参数 | 无 |
| 返回值 | 调用成功返回机器狗的倾斜的角度，仰视最大角度为14，俯视最大角度为11 |
| 备注 | 负值为仰视，正值为俯视，取值范围[-14,11] |

## 获取运动状态
| 函数名 | GetActionStatus  |
|------| ----- |
| 函数原型 | int32_t GetActionStatus() |
| 功能概述 | 获取机器的运动状态 |
| 参数 | 无|
| 返回值 | 卸力状态: 0 <br>恢复站立动作中，结束后会自动转换到平衡站立：2<br>平衡站立状态：3 <br>阻尼状态：5 <br>行走中：6 <br>趴下过程中，结束后会自动转换阻尼状态：7<br>未知：-1 |
| 备注 |  |

## 获取机器狗状态
| 函数名 | GetRobotStatus  |
|------| ----- |
| 函数原型 | struct Robotstate GetRobotStatus() |
| 功能概述 | 获取机器狗状态 |
| 参数 | 无 |
| 返回值 | 调用成功返回电机温度 <br> struct Robotstate {double driver_temperature[12]; //电机温度 四个脚每个脚3个电机 0-2是脚1 3-5是脚2 6-8是脚3 9-11是脚4 |
| 备注 |  |

## 获取电池电量
| 函数名 | GetRobotBatteryPercentage  |
|------| ----- |
| 函数原型 | int32_t GetRobotBatteryPercentage() |
| 功能概述 | 获取电池电量 |
| 参数 | 无 |
| 返回值 | 调用成功返回电池电量百分比，否则返回对应异常码 |
| 备注 |  |

## 获取机器狗速度
| 函数名 | GetRobotStatus  |
|------| ----- |
| 函数原型 | struct Robotspeed GetRobotSpeed() |
| 功能概述 | 获取机器狗状xyz轴速度和角速度 |
| 参数 | 无 |
| 返回值 | 调用成功返回机器狗速度 <br> struct Robotspeed {float body_x:机身x轴速度(单位：m/s)<br> float body_y:机身y轴速度(单位：m/s)<br>float body_z:机身z轴速度(单位：m/s)<br>float body_ang:机身角速度(单位：rad/s) |
| 备注 |  |

## 获取sdk切换控制开关状态
| 函数名 | GetSdkSwitch  |
|------| ----- |
| 函数原型 | int32_t GetSdkSwitch() |
| 功能概述 | 获取sdk切换控制开关状态 |
| 参数 | 无 |
| 返回值 | 调用成功返回0表示没有控制权，返回1表示有控制权，否则返回相关错误码。|
| 备注 |  |

## 获取sdk版本号
| 函数名 | GetSdkVersion  |
|------| ----- |
| 函数原型 | float GetSdkVersion() |
| 功能概述 | 获取sdk版本号 |
| 参数 | 无 |
| 返回值 | 调用成功返回sdk版本号|
| 备注 |  |

## 开始充电
| 函数名 | StartRobotCharging  |
|------| ----- |
| 函数原型 | int32_t StartRobotCharging() |
| 功能概述 | 开始充电 |
| 参数 | 无 |
| 返回值 | 调用成功返回0，否则返回相关错误码|
| 备注 |  |

## 结束充电
| 函数名 | StopRobotCharging  |
|------| ----- |
| 函数原型 | int32_t StopRobotCharging() |
| 功能概述 | 停止充电 |
| 参数 | 无 |
| 返回值 | 调用成功返回0，否则返回相关错误码|
| 备注 |  |

## 获取机器人充电结果
| 函数名 | GetRobotChargeResult  |
|------| ----- |
| 函数原型 | int32_t GetRobotChargeResult() |
| 功能概述 | 获取机器人充电结果 |
| 参数 | 无 |
| 返回值 | 调用成功<br>返回0表示不在充电<br>返回1表示正在找桩<br>返回2表示正在充电<br>返回3表示正在出桩<br>返回-1表示找桩失败<br>返回-2表示充电状态异常<br>否则返回相关错误码。|
| 备注 |  |

## 获取点云图上定位
| 函数名 | GetRobotCloudMapLocation  |
|------| ----- |
| 函数原型 | struct RobotCloudMapLocation GetRobotCloudMapLocation() |
| 功能概述 | 获取点云图上定位 |
| 参数 | 无 |
| 返回值 | 调用成功返回机器狗点云地图坐标系下的位置信息<br>struct RobotCloudMapLocation {<br>float position_x; // 三维空间中的坐标xyz（单位：m）<br>float position_y;<br>float position_z; <br>float orientation_x; // 四元数表示的旋转（姿态）<br>float orientation_y;<br>float orientation_z;<br>float orientation_w;<br>};|
| 备注 |  |

## 获取地图列表
| 函数名 | GetRobotMapList  |
|------| ----- |
| 函数原型 | std::vector<RobotMapInfo> GetRobotMapList() |
| 功能概述 | 获取地图列表 |
| 参数 | 无 |
| 返回值 | 调用成功返回地图列表 <br>struct RobotMapInfo {<br>std::string map_name;<br>}; |
| 备注 |  |

## 获取地图文件
| 函数名 | GetRobotMapFiles  |
|------| ----- |
| 函数原型 | int32_t GetRobotMapFiles( const std::string& map_name, const std::string& save_directory) |
| 功能概述 | 获取地图文件 |
| 参数 | map_name:地图名称(通过GetRobotMapList获取)，save_directory:调用者指定的本地保存目录 |
| 返回值 | 调用成功返回0，否则返回相关错误码。 |
| 备注 |  |


# lowlevel函数介绍
### 底层控制指令
用户通过订阅话题 `rt/lowcmd` 来发送电机控制指令，具体发送的数据结构如下：
```bash
std_msgs/Header header

float32[4] q_des_abad   //期望的Abduction关节角度（目标位置）
float32[4] q_des_hip    //期望的髋关节角度
float32[4] q_des_knee   //期望的膝关节角度
float32[4] qd_des_abad  //期望的Abduction关节角速度（目标速度）
float32[4] qd_des_hip   //期望的髋关节角速度
float32[4] qd_des_knee  //期望的膝关节角速度
float32[4] kp_abad      //Abduction关节的位置控制增益（PD控制中的P）
float32[4] kp_hip       //髋关节的P增益
float32[4] kp_knee      //膝关节的P增益
float32[4] kd_abad      //Abduction关节的速度控制增益（PD控制中的D）
float32[4] kd_hip       //髋关节的D增益
float32[4] kd_knee      //膝关节的D增益
float32[4] tau_abad_ff  //Abduction关节的前馈力矩
float32[4] tau_hip_ff   //髋关节的前馈力矩
float32[4] tau_knee_ff  //膝关节的前馈力矩
int32[4] flags          //每条腿的控制模式标志

```

### 底层数据获取
用户可通过订阅`rt/lowstate`话题获取电机、IMU数据，数据结构如下所示：
1、IMU状态信息：
```bash
float32[3] imu_angular_velocity       //roll rate（滚转角速度，绕 X 轴）
                                      // pitch rate（俯仰角速度，绕 Y 轴）
                                      // yaw rate（偏航角速度，绕 Z 轴）
float32[3] imu_linear_acceleration    // x轴加速度
                                      // y轴加速度
                                      // z轴加速度
float32[4] imu_orientation            // 四元数表示的姿态
bool imu_is_valid
uint16 imu_packet_id

```

2、电机状态信息：
```bash
float32[4] q_abad       //Abduction/内收关节角度（单位：弧度）
float32[4] q_hip        //髋关节角度
float32[4] q_knee       //膝关节角度
float32[4] qd_abad      //Abduction关节角速度（单位：rad/s）
float32[4] qd_hip       //髋关节角速度
float32[4] qd_knee      //膝关节角速度
float32[4] tau_abad     //Abduction关节力矩（单位：N*m）
float32[4] tau_hip      //髋关节力矩
float32[4] tau_knee     //膝关节力矩
int32[4] flags          //关节状态标志位
int32 spi_driver_status      //spi驱动状态
int32 abnormal_warning_level_motor  //电机异常警告等级
int32 abnormal_warning_level_soc    //电池电量警告等级
```
