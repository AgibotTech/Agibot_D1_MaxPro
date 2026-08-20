#include <unistd.h>

#include <algorithm>
#include <atomic>
#include <csignal>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <functional>

#include "high_level_base.h"

std::atomic<bool> running(true);
std::shared_ptr<Robot> robot;

void signalHandler(int signum)
{
  std::cout << "\nInterrupt signal (" << signum << ") received. Exiting...\n";
  running = false;
  robot = nullptr;
  exit(0);
}

void printHelp()
{
  std::cout << "\n=====================================\n";
  std::cout << "Robot Control Console - Commands Manual\n";
  std::cout << "=====================================\n";
  std::cout << "  stand                   - 站立\n";
  std::cout << "  down                    - 趴下\n";
  std::cout << "  zero                    - 0力矩模式\n";
  std::cout << "  damp                    - 阻尼模式\n";
  std::cout << "  stop                    - 停止运动\n";
  std::cout << "  status                  - 获取状态\n";
  std::cout << "  high_knee [0|1]         - 设置高抬腿模式\n";
  // std::cout << "  movef [x]               - 前后移动指定距离\n";
  // std::cout << "  moves [x]               - 左右移动指定距离\n";
  // std::cout << "  seth [x]                - 设置高度\n";
  // std::cout << "  sets [x]                - 设置速度\n";
  // std::cout << "  fmove                   - 结束移动动作\n";
  std::cout << "  gets                    - 获取速度\n";
  std::cout << "  getas                   - 获取所有详细速度\n";
  std::cout << "  geta                    - 获取倾斜角度\n";
  // std::cout << "  geth                    - 获取高度\n";
  std::cout << "  move_cont [x] [y] [z]   - 持续移动\n";
  std::cout << "  udrotate [angle]        - 向上向下转向\n";
  // std::cout << "  getss                   - 获取左右移动距离\n";
  // std::cout << "  getf                    - 获取前后移动距离\n";
  // std::cout << "  pam [0|1]               - 设置参数调整\n";
  std::cout << "  getrs                   - 获取机器狗状态\n";
  std::cout << "  getvers                 - 获取sdk版本\n";
  // std::cout << "  getcml                  - 获取机器人云图位置\n";
  std::cout << "  scharge                 - 开始充电\n";
  std::cout << "  stcharge                - 停止充电\n";
  // std::cout << "  getml                   - 获取机器人地图列表\n";
  // std::cout << "  getmf [map_name | save_directory]    - 获取机器人地图文件\n";
  std::cout << "  lrrotate [radian]       - 向左向右转向\n";
  std::cout << "  switchrlm [0|1]         - 切换到强化学习模式\n";
  std::cout << "  jointlock [0|1]         - 关节锁定模式\n";
  std::cout << "  getchrs                 - 获取充电状态\n";
  std::cout << "  getcss                  - 获取sdk控制开关状态\n";
  std::cout << "  getbas                  - 获取机器狗电池电量\n";
  std::cout << "  crawl [0|1]             - 切换匍匐模式\n";
  std::cout << "  getalle                 - 获取所有告警信息(同步)\n";
  std::cout << "  getallse                - 获取所有告警信息(异步)\n";
  std::cout << "  getodom                 - 获取里程计信息\n";
  std::cout << "  getjoint                - 获取关节状态(角度和角速度)\n";
  std::cout << "  getimu                  - 获取imu加速度(xyz轴)\n";
  std::cout << "  getrcs                  - 获取机器狗充电状态\n";
  std::cout << "  help                    - 显示帮助信息\n";
  std::cout << "  exit                    - 退出程序\n";
  std::cout << "=====================================\n\n";
}

void onAlertsReceived(const std::vector<AlertItem> &items)
{
  for (const auto &alert : items)
  {
    std::cout << "sync key: " << alert.key << ", code: " << alert.code << ", key_str: " << alert.key_str << ", timestamp: " << alert.timestamp << std::endl;
  }
}

int main(int argc, char **argv)
{
  std::signal(SIGINT, signalHandler);
  std::signal(SIGTSTP, signalHandler);
  std::signal(SIGTERM, signalHandler);
  float result;
  int32_t ret;

  std::cout << "Starting Robot Control Client...\n";

  robot = createQuadruped();
  if (!robot)
  {
    std::cerr << "Failed to create robot instance!\n";
    return -1;
  }
  std::cout << "Robot instance created successfully\n";

  ret = robot->init();
  if (ret != 0)
  {
    std::cerr << "Robot initialization failed with code: " << ret << "\n";
    std::cerr << "Exiting program...\n";
    return -1;
  }
  std::cout << "Robot initialized successfully\n";

  std::cout << "\nRobot Control Client Ready\n";
  std::cout << "Type 'help' for available commands\n\n";

  while (running)
  {
    std::string command;
    std::cout << ">>> ";

    if (!std::getline(std::cin, command))
    {
      running = false;
      break;
    }

    if (command.empty())
      continue;

    std::string cmd_lower = command;
    std::transform(cmd_lower.begin(), cmd_lower.end(), cmd_lower.begin(), ::tolower);

    if (cmd_lower == "exit" || cmd_lower == "quit")
    {
      running = false;
      if (robot)
      {
        try
        {
          robot->StopMove();
        }
        catch (...)
        {
          std::cerr << "Exception in StopMove during exit\n";
        }
      }
      std::cout << "Exiting robot control...\n";
    }
    else if (cmd_lower == "help" || cmd_lower == "?")
    {
      printHelp();
    }
    else if (cmd_lower == "stand")
    {
      try
      {
        ret = robot->Standup();
        std::cout << "Standup command: " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
      }
      catch (...)
      {
        std::cerr << "Exception in Standup command\n";
      }
    }

    else if (cmd_lower == "down")
    {
      try
      {
        ret = robot->Getdown();
        std::cout << "Getdown command: " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
      }
      catch (...)
      {
        std::cerr << "Exception in Getdown command\n";
      }
    }
    else if (cmd_lower == "zero")
    {
      try
      {
        ret = robot->ZeroTorque();
        std::cout << "ZeroTorque command: " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
      }
      catch (...)
      {
        std::cerr << "Exception in ZeroTorque command\n";
      }
    }
    else if (cmd_lower == "damp")
    {
      try
      {
        ret = robot->Damp();
        std::cout << "Damp command: " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
      }
      catch (...)
      {
        std::cerr << "Exception in Damp command\n";
      }
    }
    else if (cmd_lower == "stop")
    {
      try
      {
        ret = robot->StopMove();
        std::cout << "StopMove command: " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
      }
      catch (...)
      {
        std::cerr << "Exception in StopMove command\n";
      }
    }

    else if (cmd_lower.find("movef") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      float distance;
      iss >> cmd >> distance;

      if (iss.fail())
      {
        std::cout << "Invalid arguments! Usage: movef distance\n";
      }
      else
      {
        try
        {
          ret = robot->MoveForward(distance);
          std::cout << "MoveForward: distance=" << distance << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in MoveForward command\n";
        }
      }
    }

    else if (cmd_lower.find("lrrotate") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      double radian;
      iss >> cmd >> radian;

      if (iss.fail())
      {
        std::cout << "Invalid arguments! Usage: Rotate_right_and_left radian\n";
      }
      else
      {
        try
        {
          ret = robot->Rotate_right_and_left(radian);
          std::cout << "Rotate_right_and_left: radian=" << radian << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in Rotate_right_and_left command\n";
        }
      }
    }

    else if (cmd_lower.find("moves") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      float distance;
      iss >> cmd >> distance;

      if (iss.fail())
      {
        std::cout << "Invalid arguments! Usage: moves distance\n";
      }
      else
      {
        try
        {
          ret = robot->MoveSideways(distance);
          std::cout << "MoveSideways: distance=" << distance << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in MoveSideways command\n";
        }
      }
    }

    else if (cmd_lower.find("seth") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      float height;
      iss >> cmd >> height;

      if (iss.fail())
      {
        std::cout << "Invalid arguments! Usage: seth height\n";
      }
      else
      {
        try
        {
          ret = robot->SetHeight(height);
          std::cout << "SetHeight: height=" << height << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in SetHeight command\n";
        }
      }
    }

    else if (cmd_lower.find("sets") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      float speed;
      iss >> cmd >> speed;

      if (iss.fail())
      {
        std::cout << "Invalid arguments! Usage: sets speed\n";
      }
      else
      {
        try
        {
          ret = robot->SetSpeed(speed);
          std::cout << "SetSpeed: speed=" << speed << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in SetSpeed command\n";
        }
      }
    }

    else if (cmd_lower == "fmove")
    {
      try
      {
        ret = robot->FinishMovement();
        std::cout << "FinishMovement command: " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
      }
      catch (...)
      {
        std::cerr << "Exception in FinishMovement command\n";
      }
    }

    else if (cmd_lower == "gets")
    {
      try
      {
        result = robot->GetSpeed();
        std::cout << "GetSpeed command result = " << result << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
      catch (...)
      {
        std::cerr << "Exception in GetSpeed command\n";
      }
    }

    else if (cmd_lower == "geta")
    {
      try
      {
        result = robot->GetAngle();
        std::cout << "GetAngle command ret = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetAngle command\n";
      }
    }

    else if (cmd_lower == "geth")
    {
      try
      {
        result = robot->GetHeight();
        std::cout << "GetHeight command result = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetHeight command\n";
      }
    }

    else if (cmd_lower == "getss")
    {
      try
      {
        result = robot->GetSideways();
        std::cout << "GetSideways command ret = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetSideways command\n";
      }
    }

    else if (cmd_lower == "getf")
    {
      try
      {
        result = robot->GetForward();
        std::cout << "GetForward command result = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetForward command\n";
      }
    }

    else if (cmd_lower == "getvers")
    {
      try
      {
        result = robot->GetSdkVersion();
        std::cout << "GetSdkVersion command result = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetSdkVersion command\n";
      }
    }

    else if (cmd_lower == "getcss")
    {
      try
      {
        int32_t result = robot->GetSdkSwitch();
        std::cout << "GetSdkSwitch command result = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetSdkSwitch command\n";
      }
    }

    else if (cmd_lower == "getcml")
    {
      try
      {
        RobotCloudMapLocation result = robot->GetRobotCloudMapLocation();

        std::cout << "📍 机器人云图位置:\n"
                  << "  位置 (x, y, z): [" << std::fixed << std::setprecision(3) << result.position_x << ", " << result.position_y << ", "
                  << result.position_z << "] \n"
                  << "  姿态 (四元数 x, y, z, w): [" << result.orientation_x << ", " << result.orientation_y << ", " << result.orientation_z << ", "
                  << result.orientation_w << "]\n";
      }
      catch (const std::exception &e)
      {
        std::cerr << "❌ 获取云图位置失败: " << e.what() << "\n";
      }
      catch (...)
      {
        std::cerr << "❌ 获取云图位置失败: 未知错误\n";
      }
    }

    else if (cmd_lower == "scharge")
    {
      try
      {
        int32_t result = robot->StartRobotCharging();
        if (result == 0)
        {
          std::cout << "✅ 充电启动成功！机器人将前往充电桩。\n";
        }
        else
        {
          std::cout << "❌ 充电失败，错误码: " << result << "\n";
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << "❌ 启动充电失败: " << e.what() << "\n";
      }
      catch (...)
      {
        std::cerr << "❌ 启动充电失败: 未知错误\n";
      }
    }

    else if (cmd_lower == "stcharge")
    {
      try
      {
        int32_t result = robot->StopRobotCharging();
        if (result == 0)
        {
          std::cout << "✅ 停止充电成功\n";
        }
        else
        {
          std::cout << "❌ 停止充电失败，错误码: " << result << "\n";
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << "❌ 停止充电失败: " << e.what() << "\n";
      }
      catch (...)
      {
        std::cerr << "❌ 停止充电失败: 未知错误\n";
      }
    }

    else if (cmd_lower == "getml")
    {
      try
      {
        std::vector<RobotMapInfo> result = robot->GetRobotMapList();

        if (result.empty())
        {
          std::cout << "🗺️  地图列表为空\n";
        }
        else
        {
          std::cout << "🗺️  地图列表 (" << result.size() << " 个):\n";
          for (size_t i = 0; i < result.size(); ++i)
          {
            std::cout << "  " << (i + 1) << ". " << result[i].map_name << "\n";
          }
        }
      }
      catch (const std::exception &e)
      {
        std::cerr << "❌ 获取地图列表失败: " << e.what() << "\n";
      }
      catch (...)
      {
        std::cerr << "❌ 获取地图列表失败: 未知错误\n";
      }
    }

    else if (cmd_lower.find("getmf") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      std::string map_name;
      std::string save_directory;
      iss >> cmd >> map_name >> save_directory;

      if (map_name.empty() || save_directory.empty())
      {
        std::cout << "Invalid arguments! Usage: getmf <map_name> <save_directory>\n";
      }
      else
      {
        try
        {
          int32_t result = robot->GetRobotMapFiles(map_name, save_directory);
          std::cout << "GetRobotMapFiles: map='" << map_name << "', save_dir='" << save_directory << "' -> " << (result == 0 ? "SUCCESS" : "FAILED")
                    << " (code: " << result << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in GetRobotMapFiles command\n";
        }
      }
    }

    else if (cmd_lower == "getrs")
    {
      try
      {
        struct Robotstate robot_status;
        robot_status = robot->GetRobotStatus();

        // 打印电机温度
        std::cout << "Motor Temperatures:" << std::endl;
        for (int i = 0; i < 12; ++i)
        {
          std::cout << "  Motor[" << i << "] = " << robot_status.driver_temperature[i] << " °C" << std::endl;
        }
      }
      catch (...)
      {
        std::cerr << "Exception in GetRobotStatus command\n";
      }
    }

    else if (cmd_lower == "getas")
    {
      try
      {
        struct Robotspeed robot_speed;
        robot_speed = robot->GetRobotSpeed();
        // 打印速度
        std::cout << "robot_speed x: " << robot_speed.body_x << std::endl;
        std::cout << "robot_speed y: " << robot_speed.body_y << std::endl;
        std::cout << "robot_speed z: " << robot_speed.body_z << std::endl;
        std::cout << "robot_speed ang: " << robot_speed.body_ang << std::endl;
      }
      catch (...)
      {
        std::cerr << "Exception in GetRobotSpeed command\n";
      }
    }

    else if (cmd_lower.find("pam") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      int flag_int;
      iss >> cmd >> flag_int;
      bool flag = (flag_int != 0);

      if (iss.fail())
      {
        std::cout << "Invalid argument! Usage: pam [0|1]\n";
      }
      else
      {
        try
        {
          ret = robot->ParameterAdjustmentMode(flag);
          std::cout << "ParameterAdjustmentMode: " << flag << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in ParameterAdjustmentMode command\n";
        }
      }
    }

    else if (cmd_lower == "status")
    {
      try
      {
        ret = robot->GetActionStatus();
        std::cout << "Action status: " << ret << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetActionStatus command\n";
      }
    }
    else if (cmd_lower.find("high_knee") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      int val_int;
      iss >> cmd >> val_int;
      bool val = (val_int != 0);

      if (iss.fail())
      {
        std::cout << "Invalid argument! Usage: high_knee [0|1]\n";
      }
      else
      {
        try
        {
          ret = robot->Highknee(val);
          std::cout << "Highknee command: " << val << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in Highknee command\n";
        }
      }
    }
    else if (cmd_lower.find("crawl") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      int val_int;
      iss >> cmd >> val_int;
      bool val = (val_int != 0);

      if (iss.fail())
      {
        std::cout << "Invalid argument! Usage: crawl [0|1]\n";
      }
      else
      {
        try
        {
          ret = robot->SwitchToCrawlMode(val);
          std::cout << "SwitchToCrawlMode command: " << val << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in SwitchToCrawlMode command\n";
        }
      }
    }
    else if (cmd_lower.find("switchrlm") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      int val_int;
      iss >> cmd >> val_int;
      bool val = (val_int != 0);

      if (iss.fail())
      {
        std::cout << "Invalid argument! Usage: switchrlm [0|1]\n";
      }
      else
      {
        try
        {
          ret = robot->SwitchToRLMode(val);
          std::cout << "switchrlm command: " << val << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in switchrlm command\n";
        }
      }
    }
    else if (cmd_lower.find("jointlock") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      int val_int;
      iss >> cmd >> val_int;
      bool val = (val_int != 0);

      if (iss.fail())
      {
        std::cout << "Invalid argument! Usage: jointlock [0|1]\n";
      }
      else
      {
        try
        {
          ret = robot->JointLockMode(val);
          std::cout << "JointLockMode command: " << val << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in JointLockMode command\n";
        }
      }
    }

    else if (cmd_lower == "getbas")
    {
      try
      {
        int32_t result = robot->GetRobotBatteryPercentage();
        std::cout << "GetRobotBatteryPercentage command result = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetRobotBatteryPercentage command\n";
      }
    }

    else if (cmd_lower == "getalle")
    {
      try
      {
        std::vector<AlertItem> allalerts = robot->GetAllAlerts();
        for (const auto &alert : allalerts)
        {
          std::cout << "key: " << alert.key << ", code: " << alert.code << ", key_str: " << alert.key_str << ", timestamp: " << alert.timestamp << std::endl;
        }
      }
      catch (...)
      {
        std::cerr << "Exception in GetAllAlerts command\n";
      }
    }
    else if (cmd_lower == "getallse")
    {
      try
      {
        ret = robot->FetchAllAlertsAsync(onAlertsReceived);
        std::cout << "FetchAllAlertsAsync command ret = " << ret << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in FetchAllAlertsAsync command\n";
      }
    }
    else if (cmd_lower == "getodom")
    {
      try
      {
        struct Odometry robot_odom_status;
        robot_odom_status = robot->GetOdometry();
        std::cout << "=== Robot Odometry ===" << std::endl;
        std::cout << "Position (x, y, z): ("
                  << robot_odom_status.position[0] << ", "
                  << robot_odom_status.position[1] << ", "
                  << robot_odom_status.position[2] << ")" << std::endl;
        std::cout << "Orientation (qx, qy, qz, qw): ("
                  << robot_odom_status.orientation[0] << ", "
                  << robot_odom_status.orientation[1] << ", "
                  << robot_odom_status.orientation[2] << ", "
                  << robot_odom_status.orientation[3] << ")" << std::endl;

        std::cout << "Linear velocity (vx, vy, vz): ("
                  << robot_odom_status.linear[0] << ", "
                  << robot_odom_status.linear[1] << ", "
                  << robot_odom_status.linear[2] << ")" << std::endl;

        std::cout << "Angular velocity (wx, wy, wz): ("
                  << robot_odom_status.angular[0] << ", "
                  << robot_odom_status.angular[1] << ", "
                  << robot_odom_status.angular[2] << ")" << std::endl;
      }
      catch (...)
      {
        std::cerr << "Exception in GetOdometry command\n";
      }
    }
    else if (cmd_lower == "getjoint")
    {
      try
      {
        struct Joint_status robot_joint_status;
        robot_joint_status = robot->GetJointState();
        std::cout << "\n=== Robot Joint Status ===" << std::endl;
        for (int i = 0; i < 12; ++i)
        {
          int leg = i / 3 + 1; // 腿号：1～4
          const char *joint_name = (i % 3 == 0) ? "Adab" : (i % 3 == 1) ? "Hip"
                                                                        : "Knee";
          std::cout << "Leg " << leg << " " << joint_name
                    << " - Angle: " << robot_joint_status.joint_angles[i]
                    << " rad, Velocity: " << robot_joint_status.joint_velocities[i]
                    << " rad/s" << std::endl;
        }
      }
      catch (...)
      {
        std::cerr << "Exception in GetJointState command\n";
      }
    }
    else if (cmd_lower == "getimu")
    {
      try
      {
        struct Imu_linear_acceleration robot_imu_status;
        robot_imu_status = robot->GetImuLinearAcceleration();
        std::cout << "\n=== IMU Linear Acceleration ===" << std::endl;
        std::cout << "Ax: " << robot_imu_status.imu_ax << " m/s²" << std::endl;
        std::cout << "Ay: " << robot_imu_status.imu_ay << " m/s²" << std::endl;
        std::cout << "Az: " << robot_imu_status.imu_az << " m/s²" << std::endl;
      }
      catch (...)
      {
        std::cerr << "Exception in GetImuLinearAcceleration command\n";
      }
    }
    else if (cmd_lower == "getrcs")
    {
      try
      {
        ret = robot->GetRobotChargingState();
        std::cout << "GetRobotChargingState command ret = " << ret << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetRobotChargingState command\n";
      }
    }

    else if (cmd_lower == "test")
    {
      while (1)
      {
        result = robot->GetSpeed();
        std::cout << "GetSpeed 20ms command result = " << result << "\n";
        if (result == -1.0)
        {
          std::cout << "failed GetSpeed command result = " << result << "\n";
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
      }
    }

    else if (cmd_lower.find("move_cont") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      double x, y, z;
      iss >> cmd >> x >> y >> z;

      if (iss.fail())
      {
        std::cout << "Invalid arguments! Usage: move_cont x y z\n";
      }
      else
      {
        try
        {
          ret = robot->Move(x, y, z);
          std::cout << "Move (continuous): x=" << x << ", y=" << y << ", z=" << z << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret
                    << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in Move (continuous) command\n";
        }
      }
    }
    else if (cmd_lower.find("udrotate") == 0)
    {
      std::istringstream iss(command);
      std::string cmd;
      double rads;
      float angle;
      iss >> cmd >> angle;

      if (iss.fail())
      {
        std::cout << "Invalid argument! Usage: rotate rads angle\n";
      }
      else
      {
        try
        {
          ret = robot->Rotate_up_and_down(angle);
          std::cout << "Rotate:" << ", angle=" << angle << " -> " << (ret == 0 ? "SUCCESS" : "FAILED") << " (code: " << ret << ")\n";
        }
        catch (...)
        {
          std::cerr << "Exception in Rotate command\n";
        }
      }
    }

    else if (cmd_lower == "getchrs")
    {
      try
      {
        int32_t result = robot->GetRobotChargeResult();
        std::cout << "GetRobotChargeResult command result = " << result << "\n";
      }
      catch (...)
      {
        std::cerr << "Exception in GetRobotChargeResult command\n";
      }
    }
    else
    {
      std::cout << "Unknown command: " << command << "\n";
      std::cout << "Type 'help' for available commands\n";
    }
  }

  // 清理资源
  std::cout << "Shutting down robot control client\n";
  if (robot)
  {
    try
    {
      robot->StopMove();
      robot->Getdown();
    }
    catch (...)
    {
      std::cerr << "Exception during cleanup\n";
    }
  }

  return 0;
}