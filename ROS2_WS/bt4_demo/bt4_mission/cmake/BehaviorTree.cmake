include_guard(GLOBAL)

# 严格使用本教程验证的版本，避免链接到另一个 4.x 版本。
find_package(behaviortree_cpp 4.10.0 EXACT QUIET CONFIG)

if(behaviortree_cpp_FOUND)
    if(TARGET BT::behaviortree_cpp)
        set(BTCPP_TARGET BT::behaviortree_cpp)
    elseif(TARGET behaviortree_cpp::behaviortree_cpp)
        set(BTCPP_TARGET behaviortree_cpp::behaviortree_cpp)
    elseif(TARGET behaviortree_cpp)
        set(BTCPP_TARGET behaviortree_cpp)
    else()
        message(FATAL_ERROR "BehaviorTree.CPP 4.10.0 was found without a supported target")
    endif()
    message(STATUS "Using installed BehaviorTree.CPP 4.10.0: ${behaviortree_cpp_DIR}")
else()
    include(FetchContent)
    set(BTCPP_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BTCPP_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    # 后面的 Groot2 和日志实践继续使用同一份依赖。
    set(BTCPP_GROOT_INTERFACE ON CACHE BOOL "" FORCE)
    set(BTCPP_SQLITE_LOGGING ON CACHE BOOL "" FORCE)

    FetchContent_Declare(
        behaviortree_cpp
        URL https://codeload.github.com/BehaviorTree/BehaviorTree.CPP/tar.gz/refs/tags/4.10.0
        URL_HASH SHA256=c758fdedb3666f7ca4c9998a4c0b243251e0a5fb5d03c99e2ee63d615af7a71d
    )
    # 4.10.0 上游用顶层版本生成库版本字符串，在此临时指定库版本。
    set(_BTCPP_PARENT_VERSION "${CMAKE_PROJECT_VERSION}")
    set(CMAKE_PROJECT_VERSION "4.10.0")
    FetchContent_MakeAvailable(behaviortree_cpp)
    set(CMAKE_PROJECT_VERSION "${_BTCPP_PARENT_VERSION}")
    set(BTCPP_TARGET behaviortree_cpp)
    message(STATUS "Building BehaviorTree.CPP 4.10.0 from source")
endif()