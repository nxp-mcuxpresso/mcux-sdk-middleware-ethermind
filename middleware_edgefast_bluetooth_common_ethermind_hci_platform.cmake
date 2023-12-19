#Description: middleware.edgefast_bluetooth.common.ethermind.hci_platform; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_common_ethermind_hci_platform component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/port/pal/mcux/bluetooth/hci_platform.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(middleware_edgefast_bluetooth_rw610_controller)
