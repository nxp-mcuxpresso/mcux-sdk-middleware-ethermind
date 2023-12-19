#Description: middleware.edgefast_bluetooth.ble.ethermind.lib.cm33nodsp; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_ble_ethermind_lib_cm33nodsp component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(middleware_edgefast_bluetooth_ble_ethermind_cm33nodsp)
