#Description: middleware.edgefast_bluetooth.rw610.controller; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_rw610_controller component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/pal/mcux/bluetooth/controller/controller_rw610.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/port/pal/mcux/bluetooth/controller
)


include(middleware_edgefast_bluetooth_common_ethermind)
