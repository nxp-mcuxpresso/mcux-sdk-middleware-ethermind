#Description: middleware.edgefast_bluetooth.extension.common.ethermind; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_extension_common_ethermind component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/aes_cmac_pl.c
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/BT_common_pl.c
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/device_queue_pl.c
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/sm_pl.c
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/sm_ssp_pl.c
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/smp_pl.c
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension/gatt_db_pl.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/bluetooth/export/extension
)


include(middleware_edgefast_bluetooth_common_ethermind)
