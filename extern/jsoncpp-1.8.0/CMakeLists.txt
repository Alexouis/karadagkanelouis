#/*
# * File             CMakeLists.txt
# * Directory        jsoncpp-1.8.0
# * Created Date     Tuesday, November 16th 2021, 4:37:29 pm
# * Author           Nouhou KANE
# * Email            nouhou.kane@ensea.fr
# * 
# * Copyright (c) 2021  ENSEA(FR)
# * __________________________________________________________________________
# */

file(GLOB_RECURSE jsoncppHeaders ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


set(JSONCPPLIB jsonCppLibrary)

# Build the "shared" library and add required includes
add_library(${JSONCPPLIB} SHARED ${jsoncpp_sources} ${jsoncppHeaders})
target_include_directories(${JSONCPPLIB} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# vim: set sw=2 sts=2 et: