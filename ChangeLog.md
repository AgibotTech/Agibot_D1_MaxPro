# D1 MaxPro sdk change log

## 2026年1月24日
1. 文件：
- 升级包：update_pkg_v4.1.1.6.tar.gz
- sdk: high_level_remote_client_207.zip
- 遥控器app: H12_G12_V2.0.3_ZY_2601141.apk
2. 修复内容
- 修复系统崩溃的内核驱动bug
- 内核错误向上反馈至应用层
- 运控增加接收内核错误自动趴下和红灯提示
- autoboot更新修改BAT超时为2s和修改GPS上报频次为2s
- 修复SDK控制权已释放给遥控器，遥控器按B后，狗还能继续执行SDK指令的问题
3. 问题与建议
无


## 2026年1月16日
1. 文件：
- 升级包：update_pkg_v4.1.1.0.30.tar.gz
- sdk: high_level_remote_client_206.zip
- 遥控器app: H12_G12_V2.0.3_ZY_2601141.apk
2. 修复内容
- sdk中新增异常状态接口GetAllAlerts()
- sdk中新增里程计接口GetOdometry()
- sdk中新增充电检测接口GetRobotChargingState()
- sdk中新增获取关节角度\角速度接口GetJointState()
- sdk中新增IMU加速度接口GetImuLinearAcceleration()
3. 问题与建议
- 控制权还在遥控器，但是按了B键之后，机器狗会响应SDK的指令，控制权逻辑存在问题。此版本发布
需和用户进行说明。


## 2025年12月25日
1. 文件：
- 升级包：update_pkg_v4.1.1.0.22.tar.gz
- sdk: high_level_remote_client_205.zip
- 遥控器app: H12_G12_V2.0.1_ZY_2512122_release.apk
2. 修复内容
- 优化自主对桩成功率
- 增加SDK匍匐接口调用 SwitchToCrawlMode(val)


## 2025年12月15日
1. 文件
- 升级包：update_pkg_v4.1.1.0.14.tar.gz
- sdk: high_level_remote_client_204.zip
- 遥控器app: H12_G12_V2.0.1_ZY_2512122_release.apk
2. 修复内容
- 1.0x---->2.0x sdk版本增删修改接口说明

- 2.1 删除
int32_t Move(float lm, float vm, float lrm, bool continous_move)
int32_t ContinuousGait(bool flag)
int32_t Move(float lm, float vm, float lrm)
这三个接口变成了
int32_t Move(double lm, double vm, double lrm)
移动接口,修改了入参类型,从float改为double
删除了移动一秒的接口,改为持续移动,直到调用停止接口,更符合实际使用场景

- 2.2 删除
struct RobotBatteryStatus GetRobotBatteryStatus()   // 获取机器狗电量和充电状态
变为
int32_t GetRobotChargeResult()                      // 获取机器人充电结果
int32_t GetRobotBatteryPercentage()                 // 获取机器狗电池电量(新增)

- 2.3 删除
int32_t SetSdkSwitch(bool flag)                     // 设置sdk开关
这个接口废弃,不在需要设置sdk开关,是在遥控器上设置

- 2.4 删除
int32_t SetNavigationChargingControl(bool flag)     // 设置导航/充电控制开关
int32_t GetNavigationChargingStatus()               // 获取导航/充电控制开关状态
这两个接口废弃，自主充电时不需要设置导航/充电控制开关

- 2.5 修改
int32_t Rotate_right_and_left(float radian)
变为
int32_t Rotate_right_and_left(double radian)
修改了入参类型,从float改为double

- 2.6 修改
int32_t Rotate_up_and_down(float udm, float ang)
变为
int32_t Rotate_up_and_down(float ang)
修改了入参列表,去掉了udm参数

- 2.7 修复上楼梯问题
- 2.8 遥控器app操作界面变化

## 2025年12月02日
1. 文件
- 升级包：UpdatePakV4_1_0_2_9.tar
- sdk: high_level_remote_client_202.zip、high_level_remote_server_202.zip
- 遥控器app: H12_G12_V2.0.1_ZY_2511281_release.apk
2. 修复内容
- 2.1 修复高频调用和阻塞的问题，支持50hz的频率进行接口调用
