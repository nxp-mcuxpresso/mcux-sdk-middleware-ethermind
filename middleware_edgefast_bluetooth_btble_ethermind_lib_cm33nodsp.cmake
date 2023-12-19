#Description: middleware.edgefast_bluetooth.btble.ethermind.lib.cm33nodsp; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_btble_ethermind_lib_cm33nodsp component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


include(middleware_edgefast_bluetooth_btble_ethermind_cm33nodsp)
