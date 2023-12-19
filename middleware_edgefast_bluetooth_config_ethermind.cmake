#Description: middleware.edgefast_bluetooth.config.ethermind; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_config_ethermind component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/private/lib/mcux/default/config
)


include(middleware_edgefast_bluetooth_common_ethermind)
