#Description: middleware.edgefast_bluetooth.common.ethermind.hci; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_common_ethermind_hci component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(middleware_edgefast_bluetooth_common_ethermind_hci_platform)
include(middleware_edgefast_bluetooth_pal)
