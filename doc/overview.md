# babeltrader core
babeltrader核心库, 包含了base, api以及utils

## 总览
babeltrader整体项目目录大致如下
```
babeltrader
    |
    |---- include
    |
    |---- base
    |
    |---- api
    |      |---- cpp
    |      |---- py
    |      |---- java
    |      |---- golang
    |      |---- ....
    |
    |---- utils
    |
    |---- ${upstream}
    |          |
    |          |---- trade
    |          |
    |          |---- quote
    |          |
    |          |---- api
    |                 |---- cpp
    |                 |---- py
    |                 |---- java
    |                 |---- golang
    |                 |---- ....
    |
    |---- ......
```
其中base, api以及utils包含在babeltrader-core当中; ${upstream}代表一个上手, 为一个单独的项目

### include
通用的c头文件

### base
base为所有的其他组件的基础库, 提供了简单的架构

### api
api定义了接口, 所有的 ${upstream}/api 中的接口全部为api的子类

### utils
utils定义了一些方便使用的函数, 例如一些服务读取配置文件的基类
