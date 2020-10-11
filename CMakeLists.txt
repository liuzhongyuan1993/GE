cmake_minimum_required(VERSION 3.12)

set (PROJECT_NAME GE)
project(${PROJECT_NAME})

find_program (ISPC_EXECUTABLE ispc)
if (NOT ISPC_EXECUTABLE)
    message(FATAL_ERROR "Failed to find ispc" )
endif()
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/Src SOURCE_LIST)

file(GLOB_RECURSE HEADER_LIST "Src/*.h")
file(GLOB_RECURSE SOURCE_LIST "Src/*.cpp")
file(GLOB_RECURSE ISPC_LIST "Src/*.ispc")

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        # 获取相对路径
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)
 
function(source_group_all)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    #add_executable(${ARGV})
endfunction(source_group_all)

set(ISPC_BUILD_OUTPUT)
foreach(_source IN ITEMS ${ISPC_LIST})
    get_filename_component(_source_path "${_source}" PATH)
    get_filename_component(_source_name "${_source}" NAME_WE)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")

    set(ISPC_HEADER_NAME "${_source_path}/${_source_name}Ispc.h")
    set(ISPC_OBJ_NAME "${CMAKE_CURRENT_BINARY_DIR}/IspcObj/${_source_name}Ispc${CMAKE_CXX_OUTPUT_EXTENSION}")

    list(APPEND ISPC_BUILD_OUTPUT ${ISPC_HEADER_NAME} ${ISPC_OBJ_NAME})
    add_custom_command(OUTPUT ${ISPC_HEADER_NAME} ${ISPC_OBJ_NAME}
    COMMAND ${ISPC_EXECUTABLE} ${_source} -O2 --target=sse2 --arch=x86
    -h ${ISPC_HEADER_NAME} -o ${ISPC_OBJ_NAME}
    VERBATIM
    DEPENDS ${ISPC_EXECUTABLE}
    DEPENDS ${_source})

endforeach()

source_group_all(Game ${SOURCE_LIST} ${HEADER_LIST} ${ISPC_LIST})
add_executable(Game ${SOURCE_LIST} ${HEADER_LIST} ${ISPC_LIST} ${ISPC_BUILD_OUTPUT})

message("****begin source lists****")
foreach(SOURCE IN ITEMS  ${HEADER_LIST} ${SOURCE_LIST} ${ISPC_LIST} ${ISPC_BUILD_OUTPUT})
    message(${SOURCE})
endforeach()
message("****end source lists****")
