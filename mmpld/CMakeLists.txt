project(mmpld)

file(GLOB_RECURSE header_files RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*.h")

add_library(mmpld_target INTERFACE)

target_include_directories(mmpld_target INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(mmpld_target INTERFACE ${header_files})
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/" DESTINATION "include" FILES_MATCHING PATTERN "*.h")

# IDE friendly target
if(MSVC)
    add_custom_target(mmpld SOURCES ${header_files})

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "Header Files" FILES ${header_files})
endif()
