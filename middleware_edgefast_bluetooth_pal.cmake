#Description: middleware.edgefast_bluetooth.pal; user_visible: False
include_guard(GLOBAL)
message("middleware_edgefast_bluetooth_pal component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)

#OR Logic component
if(CONFIG_USE_middleware_edgefast_bluetooth_btble_ethermind_cm33nodsp) 
    include(middleware_edgefast_bluetooth_btble_ethermind_cm33nodsp)
endif()
if(CONFIG_USE_middleware_edgefast_bluetooth_ble_ethermind_cm33nodsp) 
    include(middleware_edgefast_bluetooth_ble_ethermind_cm33nodsp)
endif()

include(middleware_edgefast_bluetooth_pal_db_gen_ethermind)
include(middleware_edgefast_bluetooth_pal_platform_ethermind)
include(middleware_edgefast_bluetooth_porting)
include(middleware_mbedtls_RW612)
include(middleware_edgefast_bluetooth_common_ethermind)
include(middleware_edgefast_bluetooth_pal_host_msd_fatfs_ethermind)
