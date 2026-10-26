set(PREFIX "lib2")

file(GLOB_RECURSE ${PREFIX}_SRC_LIST CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_LIST_DIR}/src/*.c"
  "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp"
)

add_library(${PREFIX}_src_lib SHARED
  ${${PREFIX}_SRC_LIST}
)

target_include_directories(${PREFIX}_src_lib
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/inc>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(${PREFIX}_src_lib
  PUBLIC
    project_options
  PRIVATE
    project_warnings
)

# ========================
# Third-party dependencies
# ========================
find_package(Eigen3 REQUIRED)

target_link_libraries(${PREFIX}_src_lib
  PUBLIC
    Eigen3::Eigen
)

# =======
# Install
# =======
install(TARGETS ${PREFIX}_src_lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/inc/"
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
