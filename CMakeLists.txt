cmake_minimum_required(VERSION 3.1)

project(mmpld)

# mmpld header-only library
add_subdirectory(mmpld)

# install license file
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" DESTINATION "${CMAKE_INSTALL_PREFIX}")
