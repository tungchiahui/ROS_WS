include_guard(GLOBAL)

# 优先查找当前构建环境中已安装的目标版本
find_package(behaviortree_cpp_v3 3.8.7 EXACT QUIET CONFIG)

if(behaviortree_cpp_v3_FOUND)
    # ROS 包和独立安装的源码包可能导出不同名称的 CMake target
    if(TARGET behaviortree_cpp_v3::behaviortree_cpp_v3)
        set(BTCPP_TARGET behaviortree_cpp_v3::behaviortree_cpp_v3)
    elseif(TARGET BT::behaviortree_cpp_v3)
        set(BTCPP_TARGET BT::behaviortree_cpp_v3)
    else()
        message(FATAL_ERROR "BehaviorTree.CPP 3.8.7 was found without a supported target")
    endif()
    message(STATUS "Using installed BehaviorTree.CPP 3.8.7: ${behaviortree_cpp_v3_DIR}")
else()
    include(FetchContent)

    # 未安装目标版本时，固定获取 3.8.7 源码
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
    set(BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(BUILD_MANUAL_SELECTOR OFF CACHE BOOL "" FORCE)
    set(ENABLE_COROUTINES OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        behaviortree_cpp_v3
        URL https://codeload.github.com/BehaviorTree/BehaviorTree.CPP/tar.gz/refs/tags/3.8.7
    )
    FetchContent_MakeAvailable(behaviortree_cpp_v3)

    # 3.8.7 会创建 sample_nodes，本篇将它排除在默认构建之外
    set_property(DIRECTORY "${behaviortree_cpp_v3_SOURCE_DIR}/sample_nodes"
        PROPERTY EXCLUDE_FROM_ALL TRUE)

    set(BTCPP_TARGET behaviortree_cpp_v3)
    message(STATUS "Building BehaviorTree.CPP 3.8.7 from source")
endif()