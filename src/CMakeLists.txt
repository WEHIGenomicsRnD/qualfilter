cmake_minimum_required (VERSION 3.5)
project (qualfilter CXX)
 
# add seqan3 and sharg parser to search path
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../seqan3/build_system")
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../sharg-parser/build_system")

# require seqan3 with a version between >=3.0.0 and <4.0.0
find_package (seqan3 3.0 REQUIRED)
find_package (sharg 1.0 REQUIRED)
 
# build app with seqan3
add_executable (qualfilter qualfilter.cpp)
target_link_libraries (qualfilter seqan3::seqan3 sharg::sharg)

install(TARGETS qualfilter DESTINATION "${CMAKE_INSTALL_BINDIR}")
