# HomoDark

**A C++ Markdown Editor.**

这里是以 CMake 为构建系统的版本。使用 qmake 的版本移步 [FKqt/HomoDark](https://github.com/FKqt/HomoDark)。

## 简介

HomoDark 是 2022 年春季学期北京大学《程序设计实习》课程 Qt 大作业。HomoDark 是一个 C++ 开发的 Markdown 多标签编辑器。

### 编译环境：

- Qt 6.2 LTS，安装 Qt WebEngine、Qt Positioning、Qt WebChannel 三个附加库。
- MSVC v142/v143（Windows），GCC（Linux）
- C++ 17

### 字体要求：

- 微软雅黑
- Segoe MDL2 Assets
- Source Code Variable
- 思源黑体 SC VF

### 编译指南

将`CMakeLists.txt`中的`CMAKE_PREFIX_PATH`修改为你的电脑上的对应路径。

接下来，CMake 大家都会吧（逃

## 解析器

解析器为`/src/ll_md_parser.h`和`/src/__ll_md_parser_impl/*.h`组成，是基于 C++ 标准库实现的 header-only 的 markdown 解析器，可单独用于任何 C++ 工程。
