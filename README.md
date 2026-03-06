# sdk简介
- 本文档描述了 D1 MaxPro 的软件开发工具包 (SDK)，对机器狗的能力进行了封装（包括高层运动控制、底层电机/关节控制、图传、点云、里程计等），方便具备一定开发能力的用户进行二次开发。
- 各章节分别介绍不同服务接口的调用方法、数据输入/输出的标准格式定义与一些功能开发示例。
- 接口定义会随量产开发状态产生变更，请以最新版本的接口定义文档为准。
- SDK程序与狗本体内程序通讯存在特定协议，故不同版本的SDK程序与狗本体内程序通讯存在差异，请根据设备版本选择对应版本SDK程序。若条件允许，建议更新狗内程序到最新版本，以获得更好的兼容性。
- SDK接口控制时，全部状态均由二次开发者设计指定，本体运控不做额外的干预与状态跳转。
- 运行SDK时, 请保证系统有足够的资源, 否则可能出现运动控制模块失效的情况
- 编程语言：当前支持C++进行开发，暂不支持其他编程语言

# 快速开始
## 获取sdk
way1:可联系售后支持人员获取
way2:通过如下github地址获取
```bash
https://github.com/AgibotTech/Agibot_D1_MaxPro.git
```


## 环境依赖
推荐在Ubuntu20.04 x86上进行开发，暂不支持Mac、Windows系统进行开发
- 高层开发sdk，不需要安装ros1系统
- 底层开发sdk，必须安装ros1系统
  
## 网络配置
### 网络连接
| 网络接口 | 机器狗IP地址 
|---------|-----------|
| 无线网络 | 192.168.12.1 |
| 有线网络 | 192.168.144.3 |
| Type-C口 | 192.168.55.1 |
- 用户的开发电脑可通过无线、有线和typeC口方式连接机器狗，推荐使用有线连接
- 注意用户开发电脑IP不要设置为与机器狗相同的IP，避免冲突

!!! info wifi说明
    wifi名称：lxaic2-xx (xx为sn后两位)
    wifi密码：lxai2024

### ssh登录
设备提供ssh登录，通过无线或有线与设备创建连接后，可通过ssh登录设备
```bash
#无线连接方式
ssh jetson@192.168.12.1     #密码:lxai2023
#有线连接方式
ssh jetson@192.168.144.3    #密码:lxai2023
#type-C口连接方式
ssh jetson@192.168.55.1     #密码:lxai2023
```


## sdk编译
sdk结构如下：
```
.
├── src/              # demo示例脚本
├── docs/             # 详细的文档文件
├── include/          # SDK 的 C++ 头文件
├── urdf/             # urdf文件
├── build.sh          # 编译脚本文件
└── build/            # 预编译库文件 (.so)

```
执行build.sh指令然后就可以运行提供的demo程序`high_level_remote_tcp_client_test.cpp`
```bash
./build.sh
cd build
./high_level_remote_tcp_client_test
```


# API函数介绍
- **[API 函数介绍](../Agibot_D1_MaxPro (copy)/docs/api.md)**: 所有 SDK 函数的详细说明。


# 其他服务介绍
## 图传服务
前后普通相机的视频分别以Gstreamer方式推流到以下URL:
`rtsp://192.168.144.3:8554/camf`和`rtsp://192.168.144.3:8554/camb`。
默认会在遥控器侧拉流显示实时画面。



# sdk更新记录
| 修订日期 | 修订内容 | sdk版本 |
| ------- | ------- | ------ |
| 2025-12-25 | - 优化自主对桩成功率<br>增加SDK匍匐接口调用 SwitchToCrawlMode(val) | V2.0.5 |
|2026--1-16 | 新增部分接口：<br>- sdk中新增异常状态接口GetAllAlerts()<br>- sdk中新增里程计接口GetOdometry()<br>- sdk中新增充电检测接口GetRobotChargingState()<br>- sdk中新增获取关节角度\角速度接口GetJointState()<br>- sdk中新增IMU加速度接口GetImuLinearAcceleration() | V2.0.6 |
| 2026-01-24 | - 修复系统崩溃的内核驱动bug<br>- 内核错误向上反馈至应用层<br>- 运控增加接收内核错误自动趴下和红灯提示<br>- autoboot更新修改BAT超时为2s和修改GPS上报频次为2s<br>- 修复SDK控制权已释放给遥控器，遥控器按B后，狗还能继续执行SDK指令的问题 | V2.0.7 |





