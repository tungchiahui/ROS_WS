include("${PROJECT_SOURCE_DIR}/cmake/BehaviorTree.cmake")

add_executable(${PROJECT_NAME}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    project_options
    project_warnings
    ${BTCPP_TARGET}
)

# 将源码目录中的 XML 完整路径作为字符串交给程序
target_compile_definitions(${PROJECT_NAME}
    PRIVATE BT_XML_PATH="${PROJECT_SOURCE_DIR}/trees/mission.xml"
)

add_subdirectory(lib1)
add_subdirectory(lib2)

target_link_libraries(lib1_src_lib
  PRIVATE
    lib2_src_lib
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    lib1_src_lib
    lib2_src_lib
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  INSTALL_RPATH "$ORIGIN/../${CMAKE_INSTALL_LIBDIR}"
)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
