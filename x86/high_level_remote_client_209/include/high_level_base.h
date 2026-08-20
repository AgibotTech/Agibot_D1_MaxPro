#ifndef HIGH_LEVEL_BASE_H
#define HIGH_LEVEL_BASE_H

#include <stdint.h>
#include <memory>
#include <vector>

// 获取里程计信息
struct Odometry
{
  double position[3];    // 坐标位置
  double orientation[4]; // 姿态四元数
  double linear[3];      // 线速度
  double angular[3];     // 角速度
};

// 获取关节状态(角度和角速度)
struct Joint_status
{
  float joint_angles[12];     // 关节角度
  float joint_velocities[12]; // 关节角速度
                              // 0-2腿1 ahk
                              // 3-5腿2 ahk
                              // 6-8腿3 ahk
                              // 9-11腿4 ahk
};

// 获取imu加速度(xyz轴)
struct Imu_linear_acceleration
{
  double imu_ax;
  double imu_ay;
  double imu_az;
};

struct Robotstate
{
  double driver_temperature[12]; // 电机温度 四个脚每个脚3个电机 0-2是脚1 3-5是脚2 6-8是脚3 9-11是脚4
};

struct Robotspeed
{
  float body_x;   // 机身x轴速度（单位：m/s）
  float body_y;   // 机身y轴速度（单位：m/s）
  float body_z;   // 机身z轴速度（单位：m/s）
  float body_ang; // 机身角速度（单位：rad/s）
};

struct RobotCloudMapLocation
{
  float position_x; // 三维空间中的坐标xyz（单位：m）
  float position_y;
  float position_z;
  float orientation_x; // 四元数表示的旋转（姿态）
  float orientation_y;
  float orientation_z;
  float orientation_w;
};

struct RobotMapInfo
{
  std::string map_name;
};

struct AlertItem
{
  int key;
  int code;
  std::string key_str;
  std::string timestamp;
};
using AlertCallback = std::function<void(const std::vector<AlertItem> &)>;
// 基础机器狗接口（抽象类）
class Robot
{
public:
  virtual ~Robot() = default;

  // 通用接口 ========================
  virtual int32_t init() = 0;                                                                           // 初始化
  virtual int32_t StopMove() = 0;                                                                       // 停止
  virtual int32_t Standup() = 0;                                                                        // 站立
  virtual int32_t Getdown() = 0;                                                                        // 趴下
  virtual int32_t ZeroTorque() = 0;                                                                     // 0力矩模式
  virtual int32_t Damp() = 0;                                                                           // 阻尼
  virtual int32_t Highknee(bool val) = 0;                                                               // 切高抬腿
  virtual int32_t Move(double lm, double vm, double lrm) = 0;                                           // 横向前后左右移动 1秒
  virtual int32_t Rotate_up_and_down(float ang) = 0;                                                    // 向上向下转向(固定)
  virtual int32_t GetActionStatus() = 0;                                                                // 获取状态
  virtual int32_t MoveForward(float distance) = 0;                                                      // 前后移动指定距离
  virtual int32_t MoveSideways(float distance) = 0;                                                     // 左右移动指定距离
  virtual int32_t FinishMovement() = 0;                                                                 // 结束移动动作
  virtual int32_t SetHeight(float height) = 0;                                                          // 设置高度
  virtual int32_t SetSpeed(float speed) = 0;                                                            // 设置速度
  virtual float GetSpeed() = 0;                                                                         // 获取速度
  virtual float GetAngle() = 0;                                                                         // 获取倾斜角度
  virtual float GetHeight() = 0;                                                                        // 获取高度
  virtual float GetSideways() = 0;                                                                      // 获取左右移动距离
  virtual float GetForward() = 0;                                                                       // 获取前后移动距离
  virtual int32_t ParameterAdjustmentMode(bool flag) = 0;                                               // 参数调整模式
  virtual struct Robotstate GetRobotStatus() = 0;                                                       // 获取机器狗状态
  virtual struct Robotspeed GetRobotSpeed() = 0;                                                        // 获取机器狗x、y、z轴速度和角速度
  virtual float GetSdkVersion() = 0;                                                                    // 获取sdk版本
  virtual struct RobotCloudMapLocation GetRobotCloudMapLocation() = 0;                                  // 获取机器狗云图位置
  virtual int32_t StartRobotCharging() = 0;                                                             // 开始充电
  virtual int32_t StopRobotCharging() = 0;                                                              // 停止充电
  virtual std::vector<RobotMapInfo> GetRobotMapList() = 0;                                              // 获取机器狗地图列表
  virtual int32_t GetRobotMapFiles(const std::string &map_name, const std::string &save_directory) = 0; // 获取机器狗地图文件
  virtual int32_t Rotate_right_and_left(double radian) = 0;                                             // 向左向右转向(固定)
  virtual int32_t SwitchToRLMode(bool val) = 0;                                                         // 切换到强化学习模式
  virtual int32_t JointLockMode(bool val) = 0;                                                          // 关节锁定模式
  virtual int32_t GetRobotChargeResult() = 0;                                                           // 获取机器狗充电结果
  virtual int32_t GetSdkSwitch() = 0;                                                                   // 获取sdk切换控制开关状态
  virtual int32_t GetRobotBatteryPercentage() = 0;                                                      // 获取机器狗电池电量
  virtual int32_t SwitchToCrawlMode(bool val) = 0;                                                      // 切换到匍匐模式
  virtual std::vector<AlertItem> GetAllAlerts() = 0;                                                    // 获取所有告警信息
  virtual int32_t FetchAllAlertsAsync(AlertCallback callback) = 0;                                      // 获取所有告警信息(异步)
  virtual struct Odometry GetOdometry() = 0;                                                            // 获取里程计信息
  virtual struct Joint_status GetJointState() = 0;                                                      // 获取关节状态(角度和角速度)
  virtual struct Imu_linear_acceleration GetImuLinearAcceleration() = 0;                                // 获取imu加速度(xyz轴)
  virtual int32_t GetRobotChargingState() = 0;                                                          // 获取机器狗充电状态
};

std::shared_ptr<Robot> createQuadruped();

#endif // HIGH_LEVEL_BASE_H