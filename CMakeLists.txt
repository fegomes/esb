cmake_minimum_required(VERSION 3.9)
project(esb)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${esb_SOURCE_DIR}/bin)

file(COPY ${esb_SOURCE_DIR}/config/listener.ini.example DESTINATION ${esb_SOURCE_DIR}/bin)
file(RENAME ${esb_SOURCE_DIR}/bin/listener.ini.example ${esb_SOURCE_DIR}/bin/listener.ini)

file(COPY ${esb_SOURCE_DIR}/config/log.ini.example DESTINATION ${esb_SOURCE_DIR}/bin)
file(RENAME ${esb_SOURCE_DIR}/bin/log.ini.example ${esb_SOURCE_DIR}/bin/log.ini)

file(COPY ${esb_SOURCE_DIR}/config/http.ini.example DESTINATION ${esb_SOURCE_DIR}/bin)
file(RENAME ${esb_SOURCE_DIR}/bin/http.ini.example ${esb_SOURCE_DIR}/bin/http.ini)

add_subdirectory(log)
add_subdirectory(http)
add_subdirectory(listener)