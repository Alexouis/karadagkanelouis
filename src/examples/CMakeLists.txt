#/*
# * File             CMakeLists.txt
# * Directory        examples
# * Created Date     Saturday, November 13th 2021, 9:52:39 pm
# * Author           Nouhou KANE
# * Email            nouhou.kane@ensea.fr
# * 
# * Copyright (c) 2021  ENSEA(FR)
# * __________________________________________________________________________
# */


file(GLOB_RECURSE examples ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/src/client ${CMAKE_SOURCE_DIR}/src/render)

foreach(example ${examples})
    message(${example})
    get_filename_component(EXECNAME ${example} NAME_WE)
    message(${EXECNAME})
    # Compile "client" executable
    add_executable(${EXECNAME} ${example})
    target_include_directories(${EXECNAME} PUBLIC 
        ${CMAKE_SOURCE_DIR}/src/client
        ${CMAKE_SOURCE_DIR}/src/render
        ${jsoncpp_include_dir}
    )
    target_link_libraries(${EXECNAME} 
        ${lib_client_target}
        $<TARGET_NAME:client_static>
        tmx-loader 
        jsonCppLibrary
    )
    #message(${JSONCPPLIB})

    endforeach()

