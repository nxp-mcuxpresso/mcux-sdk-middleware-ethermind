
if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.controller.wifi_nxp)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/controller/controller.h
                port/pal/mcux/bluetooth/controller/controller_wifi_nxp.c
                port/pal/mcux/bluetooth/controller/controller_hci_uart.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth/controller
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
        mcux_add_include(
        INCLUDES middleware/wifi_nxp/fwdnld_intf_abs/
                 middleware/wireless/ethermind/port/pal/mcux/bluetooth/controller
                 middleware/wifi_nxp/wifi_bt_firmware/nw61x
                 middleware/wifi_nxp/wifi_bt_firmware/IW416
                 middleware/wifi_nxp/wifidriver
                 middleware/wifi_nxp/firmware_dnld
                 BASE_PATH ${SdkRootDirPath}
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.controller.rw610)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/controller/controller.h
                port/pal/mcux/bluetooth/controller/controller_rw610.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth/controller
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.controller.features.files)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/controller/controller_features.h
                port/pal/mcux/bluetooth/controller/controller_features.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth/controller
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.common)
    mcux_add_source(
        SOURCES bluetooth/export/eOSAL/eBT_assert.h
                bluetooth/export/eOSAL/eBT_config.h
                bluetooth/export/eOSAL/eBT_debug_api.h
                bluetooth/export/eOSAL/eBT_fops.h
                bluetooth/export/eOSAL/eBT_os.h
                bluetooth/export/eOSAL/eBT_serial.h
                bluetooth/export/eOSAL/eBT_timer.h
                bluetooth/export/include/*.h
                bluetooth/export/vendor/vendor_specific_commands.h
                bluetooth/export/vendor/vendor_specific_init.c
                bluetooth/export/vendor/vendor_specific_init.h
                bluetooth/private/protocols/att/att.h
                bluetooth/private/protocols/avctp/avctp.h
                bluetooth/private/protocols/avdtp/avdtp.h
                bluetooth/private/protocols/bnep/bnep.h
                bluetooth/private/protocols/dbase/database.h
                bluetooth/private/protocols/hci_1.2/hci_h.h
                bluetooth/private/protocols/mcap/mcap.h
                bluetooth/private/protocols/obex/obex.h
                bluetooth/private/protocols/rfcomm/rfcomm.h
                bluetooth/private/protocols/sdp/sdp.h
                bluetooth/private/protocols/sm/sm.h
                bluetooth/private/protocols/sm/sm_extern.h
                bluetooth/private/protocols/sm/sm_internal.h
                bluetooth/private/protocols/smp/smp.h
                bluetooth/private/protocols/smp/smp_extern.h
                bluetooth/private/protocols/smp/smp_fsm.h
                bluetooth/private/protocols/smp/smp_fsm_engine.h
                bluetooth/private/protocols/smp/smp_internal.h
                bluetooth/private/utils/aes_cmac/*.h
                bluetooth/private/utils/at_parser/at_parser_hsp_hfp.h
                bluetooth/private/utils/btsnoop/*.h
                bluetooth/private/utils/object_parser/*.h
                bluetooth/private/utils/racp/*.h
                bluetooth/private/utils/security/*.h
                bluetooth/private/utils/status/*.h
                bluetooth/private/utils/storage/storage.h
                bluetooth/private/utils/xml_parser/xml_common_defines.h
                bluetooth/private/utils/xml_parser/xml_encoder.h
                bluetooth/private/utils/xml_parser/xml_parser.h
                port/osal/src/freertos/*.*
                port/pal/mcux/bluetooth/BT_assert.h
                port/pal/mcux/bluetooth/BT_config.h
                port/pal/mcux/bluetooth/BT_debug.h
                port/pal/mcux/bluetooth/BT_debug_api.h
                port/pal/mcux/bluetooth/BT_fops.h
                port/pal/mcux/bluetooth/BT_os.h
                port/pal/mcux/bluetooth/BT_status_pl.c
                port/pal/mcux/bluetooth/BT_storage_pl.c
                port/pal/mcux/bluetooth/BT_storage_pl.h
                port/pal/mcux/bluetooth/BT_timer.h
                port/pal/mcux/bluetooth/btsnoop_pl.c
                port/pal/mcux/bluetooth/btsnoop_pl.h
                port/pal/mcux/bluetooth/ctn_pl.c
                port/pal/mcux/bluetooth/ctn_pl.h
                port/pal/mcux/bluetooth/cry_pl.c
                port/pal/mcux/bluetooth/cry_pl.h
                port/pal/mcux/bluetooth/ftp_pl.c
                port/pal/mcux/bluetooth/ftp_pl.h
                port/pal/mcux/bluetooth/ht_read_task_pl.c
                port/pal/mcux/bluetooth/map_pl.c
                port/pal/mcux/bluetooth/map_pl.h
                port/pal/mcux/bluetooth/obex_pl.c
                port/pal/mcux/bluetooth/obex_pl.h
                port/pal/mcux/bluetooth/pbap_pl.c
                port/pal/mcux/bluetooth/pbap_pl.h
                port/pal/mcux/bluetooth/write_task_extern_pl.h
                port/pal/mcux/bluetooth/write_task_pl.c
                port/pal/mcux/bluetooth/write_task_pl.h
                port/pal/mcux/bluetooth/littlefs_pl.c
                port/pal/mcux/bluetooth/littlefs_pl.h
                port/pal/mcux/bluetooth/fw_loader_uart.c
                port/pal/mcux/bluetooth/fw_loader_uart.h
				port/pal/mcux/bluetooth/audio_pl.c
				port/pal/mcux/bluetooth/leaudio_pl.c
                port/pal/mcux/ethal/*.*
                port/pal/mcux/sbc/sbc_os.h
                port/pal/mcux/lc3/LC3_os.h
                port/pal/mcux/EM_platform.c
                port/pal/mcux/EM_platform.h
                bluetooth/private/utils/sbc/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/toolspec/mcuxpresso/*.*
        TOOLCHAINS mcux
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/eOSAL
                 bluetooth/export/include
                 bluetooth/export/vendor
                 bluetooth/private/protocols/att
                 bluetooth/private/protocols/avctp
                 bluetooth/private/protocols/avdtp
                 bluetooth/private/protocols/bnep
                 bluetooth/private/protocols/common
                 bluetooth/private/protocols/dbase
                 bluetooth/private/protocols/hci_1.2
                 bluetooth/private/protocols/mcap
                 bluetooth/private/protocols/obex
                 bluetooth/private/protocols/rfcomm
                 bluetooth/private/protocols/sdp
                 bluetooth/private/protocols/sm
                 bluetooth/private/protocols/smp
                 bluetooth/private/protocols/write_task
                 bluetooth/private/utils/aes_cmac
                 bluetooth/private/utils/at_parser
                 bluetooth/private/utils/btsnoop
                 bluetooth/private/utils/object_parser
                 bluetooth/private/utils/racp
                 bluetooth/private/utils/security
                 bluetooth/private/utils/status
                 bluetooth/private/utils/storage
                 bluetooth/private/utils/xml_parser
                 port/pal/mcux/bluetooth
                 port/pal/mcux/ethal
                 port/pal/mcux/sbc
                 port/pal/mcux/lc3
                 port/osal/src/freertos
                 port/pal/mcux
                 bluetooth/private/utils/sbc
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mcux
        INCLUDES port/pal/mcux/toolspec/mcuxpresso
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.hci_uart)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/hci_uart.c
                port/pal/mcux/bluetooth/hci_uart.h
                port/pal/mcux/bluetooth/hci_uart_internal.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.hci_rpmsg)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/hci_rpmsg.c
                port/pal/mcux/bluetooth/hci_uart.h
                port/pal/mcux/bluetooth/hci_uart_internal.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.hci_platform)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/hci_platform.c
                port/pal/mcux/bluetooth/hci_platform.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.hps_pl)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/hps_pl.c
                port/pal/mcux/bluetooth/hps_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.https_pl)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/https_pl.c
                port/pal/mcux/bluetooth/https_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.ipsp_pl)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/ipsp_pl.c
                port/pal/mcux/bluetooth/ipsp_pl.h
                port/pal/mcux/bluetooth/ipspr_ping.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.pan_pl)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/pan_pl.c
                port/pal/mcux/bluetooth/pan_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.a2dp)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/a2dp_pl.c
                port/pal/mcux/bluetooth/a2dp_pl.h
                port/pal/mcux/bluetooth/a2dp_pl_media_16KHz.h
                port/pal/mcux/bluetooth/a2dp_pl_media_48KHz.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.vcom)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/vcom_pl.c
                port/pal/mcux/bluetooth/vcom_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.niface)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/niface.c
                port/pal/mcux/bluetooth/niface.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.sco_audio_pl)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/sco_audio_pl.c
                port/pal/mcux/bluetooth/sco_audio_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.port.pal.mcux.bluetooth.hfp_ag_pl)
    mcux_add_source(
        SOURCES port/pal/mcux/bluetooth/hfp_ag_pl.c
                port/pal/mcux/bluetooth/hfp_ag_pl.h
                port/pal/mcux/bluetooth/nwsim.c
                port/pal/mcux/bluetooth/nwsim.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES port/pal/mcux/bluetooth
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.appl.br.al)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/br/al/appl_avrcp.c
                bluetooth/export/appl/reference/br/al/appl_avrcp.h
                bluetooth/export/appl/reference/br/al/appl_avrcp_ct.c
                bluetooth/export/appl/reference/br/al/appl_avrcp_ct.h
                bluetooth/export/appl/reference/br/al/appl_avrcp_tg.c
                bluetooth/export/appl/reference/br/al/appl_avrcp_tg.h
                bluetooth/export/appl/reference/br/al/appl_avrcp_tg_virtual_media_player.c
                bluetooth/export/appl/reference/br/al/appl_avrcp_tg_virtual_media_player.h
                bluetooth/export/appl/reference/br/al/avrcp_al_api.c
                bluetooth/export/appl/reference/br/al/avrcp_al_internal.c
                bluetooth/export/appl/reference/br/al/avrcp_al_internal.h
                bluetooth/export/appl/reference/br/al/BT_avrcp_al_api.h
                bluetooth/export/appl/reference/br/al/avrcp_al_extern.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/br/al
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.ga.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/ga/source/core/bap/bap_interface.c
                bluetooth/private/profiles/ga/source/core/bap/bap_broadcast.c
                bluetooth/private/profiles/ga/source/core/bap/bap_internal.c
                bluetooth/private/profiles/ga/source/core/bap/bass/bass_api.c
                bluetooth/private/profiles/ga/source/core/bap/bass/bass_db.c
                bluetooth/private/profiles/ga/source/core/bap/bass/bass_internal.c
                bluetooth/private/profiles/ga/source/core/brr/brr_interface.c
                bluetooth/private/profiles/ga/source/core/csip/csip_interface.c
                bluetooth/private/profiles/ga/source/core/csip/csip_internal.c
                bluetooth/private/profiles/ga/source/core/micp/micp_interface.c
                bluetooth/private/profiles/ga/source/core/micp/micp_internal.c
                bluetooth/private/profiles/ga/source/core/vcp/vcp_interface.c
                bluetooth/private/profiles/ga/source/core/vcp/vcp_internal.c
                bluetooth/private/profiles/ga/source/core/otp/otc_api.c
                bluetooth/private/profiles/ga/source/core/otp/otc_internal.c
                bluetooth/private/profiles/ga/source/core/otp/otc_transport.c
                bluetooth/private/profiles/ga/source/core/otp/ots_api.c
                bluetooth/private/profiles/ga/source/core/otp/ots_internal.c
                bluetooth/private/profiles/ga/source/core/otp/ots_transport.c
                bluetooth/private/profiles/ga/source/core/cap_internal.c
                bluetooth/private/profiles/ga/source/core/cap_api.c
                bluetooth/private/profiles/ga/source/core/cap_utils_api.c
                bluetooth/private/profiles/ga/source/profiles/ccp/ccp_ce_api.c
                bluetooth/private/profiles/ga/source/profiles/ccp/ccp_ce_internal.c
                bluetooth/private/profiles/ga/source/profiles/ccp/ccp_se_api.c
                bluetooth/private/profiles/ga/source/profiles/ccp/ccp_se_internal.c
                bluetooth/private/profiles/ga/source/profiles/hap/hap_api.c
                bluetooth/private/profiles/ga/source/profiles/hap/hap_internal.c
                bluetooth/private/profiles/ga/source/profiles/tmap/tmap_api.c
                bluetooth/private/profiles/ga/source/profiles/tmap/tmap_internal.c
                bluetooth/private/profiles/ga/source/profiles/mcp/mcp_ce_api.c
                bluetooth/private/profiles/ga/source/profiles/mcp/mcp_ce_internal.c
                bluetooth/private/profiles/ga/source/profiles/mcp/mcp_se_api.c
                bluetooth/private/profiles/ga/source/profiles/mcp/mcp_se_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/ga/source
                 bluetooth/private/profiles/ga/source/core/bap
                 bluetooth/private/profiles/ga/source/core/bap/bass
                 bluetooth/private/profiles/ga/source/core/brr
                 bluetooth/private/profiles/ga/source/core/csip
                 bluetooth/private/profiles/ga/source/core/micp
                 bluetooth/private/profiles/ga/source/core/vcp
                 bluetooth/private/profiles/ga/source/core/otp
                 bluetooth/private/profiles/ga/source/profiles/ccp
                 bluetooth/private/profiles/ga/source/profiles/mcp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.appl.br.profile_appl)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/br/profile_appl/appl_a2dp.c
                bluetooth/export/appl/reference/br/profile_appl/appl_a2dp.h
                bluetooth/export/appl/reference/br/profile_appl/appl_bip.h
                bluetooth/export/appl/reference/br/profile_appl/appl_bip_initiator.c
                bluetooth/export/appl/reference/br/profile_appl/appl_bip_responder.c
                bluetooth/export/appl/reference/br/profile_appl/appl_bpp.h
                bluetooth/export/appl/reference/br/profile_appl/appl_bpp_printer.c
                bluetooth/export/appl/reference/br/profile_appl/appl_bpp_sender.c
                bluetooth/export/appl/reference/br/profile_appl/appl_ctn.h
                bluetooth/export/appl/reference/br/profile_appl/appl_ctn_cce.c
                bluetooth/export/appl/reference/br/profile_appl/appl_ctn_cse.c
                bluetooth/export/appl/reference/br/profile_appl/appl_did.h
                bluetooth/export/appl/reference/br/profile_appl/appl_did_client.c
                bluetooth/export/appl/reference/br/profile_appl/appl_did_server.c
                bluetooth/export/appl/reference/br/profile_appl/appl_ftp.h
                bluetooth/export/appl/reference/br/profile_appl/appl_ftp_client.c
                bluetooth/export/appl/reference/br/profile_appl/appl_ftp_server.c
                bluetooth/export/appl/reference/br/profile_appl/appl_hdp.c
                bluetooth/export/appl/reference/br/profile_appl/appl_hdp.h
                bluetooth/export/appl/reference/br/profile_appl/appl_hfp_ag.c
                bluetooth/export/appl/reference/br/profile_appl/appl_hfp_ag.h
                bluetooth/export/appl/reference/br/profile_appl/appl_hfp_ag_atrsp.h
                bluetooth/export/appl/reference/br/profile_appl/appl_hfp_unit.c
                bluetooth/export/appl/reference/br/profile_appl/appl_hfp_unit.h
                bluetooth/export/appl/reference/br/profile_appl/appl_hid_device.c
                bluetooth/export/appl/reference/br/profile_appl/appl_hid_device.h
                bluetooth/export/appl/reference/br/profile_appl/appl_hid_host.c
                bluetooth/export/appl/reference/br/profile_appl/appl_hid_host.h
                bluetooth/export/appl/reference/br/profile_appl/appl_map.h
                bluetooth/export/appl/reference/br/profile_appl/appl_map_mce.c
                bluetooth/export/appl/reference/br/profile_appl/appl_map_mse.c
                bluetooth/export/appl/reference/br/profile_appl/appl_opp.h
                bluetooth/export/appl/reference/br/profile_appl/appl_opp_client.c
                bluetooth/export/appl/reference/br/profile_appl/appl_opp_server.c
                bluetooth/export/appl/reference/br/profile_appl/appl_pbap_pce.c
                bluetooth/export/appl/reference/br/profile_appl/appl_pbap_pce.h
                bluetooth/export/appl/reference/br/profile_appl/appl_pbap_pse.c
                bluetooth/export/appl/reference/br/profile_appl/appl_pbap_pse.h
                bluetooth/export/appl/reference/br/profile_appl/appl_sap_client.c
                bluetooth/export/appl/reference/br/profile_appl/appl_sap_client.h
                bluetooth/export/appl/reference/br/profile_appl/appl_sap_server.c
                bluetooth/export/appl/reference/br/profile_appl/appl_sap_server.h
                bluetooth/export/appl/reference/br/profile_appl/appl_spp.c
                bluetooth/export/appl/reference/br/profile_appl/appl_spp.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/br/profile_appl
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.appl.multiprofile)
    mcux_add_source(
        SOURCES bluetooth/export/appl/multiprofile/appl_a2dp.c
                bluetooth/export/appl/multiprofile/appl_a2dp.h
                bluetooth/export/appl/multiprofile/appl_hfp_ag.c
                bluetooth/export/appl/multiprofile/appl_hfp_ag.h
                bluetooth/export/appl/multiprofile/appl_hfp_ag_atrsp.h
                bluetooth/export/appl/multiprofile/appl_hfp_unit.c
                bluetooth/export/appl/multiprofile/appl_hfp_unit.h
                bluetooth/export/appl/multiprofile/appl_common.c
                bluetooth/export/appl/multiprofile/appl_common.h
                bluetooth/export/appl/multiprofile/appl_hci.c
                bluetooth/export/appl/multiprofile/appl_hci.h
                bluetooth/export/appl/multiprofile/appl_hci_api.c
                bluetooth/export/appl/multiprofile/appl_spp.c
                bluetooth/export/appl/multiprofile/appl_spp.h
                bluetooth/export/appl/multiprofile/appl_utils.c
                bluetooth/export/appl/multiprofile/appl_utils.h
                bluetooth/export/appl/multiprofile/profile_fsm_engine.c
                bluetooth/export/appl/multiprofile/profile_fsm_engine.h
                bluetooth/export/appl/multiprofile/profile_fsm_handlers.c
                bluetooth/export/appl/multiprofile/profile_fsm_handlers.h
                bluetooth/export/appl/multiprofile/profile_fsm_table.c
                bluetooth/export/appl/multiprofile/al/appl_avrcp.c
                bluetooth/export/appl/multiprofile/al/appl_avrcp.h
                bluetooth/export/appl/multiprofile/al/appl_avrcp_ct.c
                bluetooth/export/appl/multiprofile/al/appl_avrcp_ct.h
                bluetooth/export/appl/multiprofile/al/appl_avrcp_tg.c
                bluetooth/export/appl/multiprofile/al/appl_avrcp_tg.h
                bluetooth/export/appl/multiprofile/al/appl_avrcp_tg_virtual_media_player.c
                bluetooth/export/appl/multiprofile/al/appl_avrcp_tg_virtual_media_player.h
                bluetooth/export/appl/multiprofile/al/avrcp_al_api.c
                bluetooth/export/appl/multiprofile/al/BT_avrcp_al_api.h
                bluetooth/export/appl/multiprofile/al/avrcp_al_internal.c
                bluetooth/export/appl/multiprofile/al/avrcp_al_internal.h
                bluetooth/export/appl/multiprofile/le/appl_hci_le.c
                bluetooth/export/appl/multiprofile/le/appl_hci_le.h
                bluetooth/export/appl/multiprofile/le/appl_l2cap_le.c
                bluetooth/export/appl/multiprofile/le/appl_l2cap_le.h
                bluetooth/export/appl/multiprofile/le/appl_gatt_server.c
                bluetooth/export/appl/multiprofile/le/appl_gatt_server.h
                bluetooth/export/appl/multiprofile/le/appl_gap_config_params.c
                bluetooth/export/appl/multiprofile/le/appl_le.c
                bluetooth/export/appl/multiprofile/le/appl_le.h
                bluetooth/export/appl/multiprofile/le/appl_service.c
                bluetooth/export/appl/multiprofile/le/appl_service.h
                bluetooth/export/appl/multiprofile/le/gatt.c
                bluetooth/export/appl/multiprofile/le/gatt.h
                bluetooth/export/appl/multiprofile/le/appl_smp.c
                bluetooth/export/appl/multiprofile/le/appl_smp.h
                bluetooth/export/appl/multiprofile/le/gatt.c
                bluetooth/export/appl/multiprofile/le/gatt.h
                bluetooth/export/appl/multiprofile/le/gatt_db.h
                bluetooth/export/appl/multiprofile/le/common/gatt_db_common_handler.c
                bluetooth/export/appl/multiprofile/le/common/gatt_db_dyn_common.c
                bluetooth/export/appl/multiprofile/appl_a2dp_standalone.c
                bluetooth/export/appl/multiprofile/appl_a2dp_standalone.h
                bluetooth/export/appl/multiprofile/appl_hfp_ag_standalone.c
                bluetooth/export/appl/multiprofile/appl_hfp_ag_standalone.h
                bluetooth/export/appl/multiprofile/appl_hfp_unit_standalone.c
                bluetooth/export/appl/multiprofile/appl_hfp_unit_standalone.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/multiprofile
                 bluetooth/export/appl/multiprofile/al
                 bluetooth/export/appl/multiprofile/le
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.appl.br.profile_appl.pan)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/br/profile_appl/appl_pan.c
                bluetooth/export/appl/reference/br/profile_appl/appl_pan.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/br/profile_appl
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.appl.br.protocol_appl)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/br/protocol_appl/appl_avctp.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_avctp.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_avdtp.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_avdtp.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_bnep.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_bnep.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_dbase.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_dbase_dyn.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_hci.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_hci.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_hci_api.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_l2cap.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_l2cap.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_mcap.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_mcap.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_obex_client.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_obex_client.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_obex_common.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_obex_server.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_obex_server.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_rfcomm.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_rfcomm.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_sdp.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_sdp.h
                bluetooth/export/appl/reference/br/protocol_appl/appl_sm.c
                bluetooth/export/appl/reference/br/protocol_appl/appl_sm.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/br/protocol_appl
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.appl.le.common)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/appl_le.c
                bluetooth/export/appl/reference/le/appl_le.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.le.protocol_appl)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/protocol_appl/appl_att_client.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_att_client.h
                bluetooth/export/appl/reference/le/protocol_appl/appl_gap_le.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_gap_le.h
                bluetooth/export/appl/reference/le/protocol_appl/appl_hci_le.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_hci_le.h
                bluetooth/export/appl/reference/le/protocol_appl/appl_hci_le_api.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_l2cap_le.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_l2cap_le.h
                bluetooth/export/appl/reference/le/protocol_appl/appl_l2cap_ecbfc.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_l2cap_ecbfc.h
                bluetooth/export/appl/reference/le/protocol_appl/appl_smp.c
                bluetooth/export/appl/reference/le/protocol_appl/appl_smp.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/protocol_appl
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.le.profile_appl.common)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/appl_gatt_client.c
                bluetooth/export/appl/reference/le/profile_appl/appl_gatt_client.h
                bluetooth/export/appl/reference/le/profile_appl/appl_gatt_server.c
                bluetooth/export/appl/reference/le/profile_appl/appl_gatt_server.h
                bluetooth/export/appl/reference/le/profile_appl/gatt.c
                bluetooth/export/appl/reference/le/profile_appl/gatt.h
                bluetooth/export/appl/reference/le/profile_appl/appl_beacon.c
                bluetooth/export/appl/reference/le/profile_appl/appl_beacon.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.client)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/client/appl_bac.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_bpc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_cpmc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_cscc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_dic.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_fml.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_glc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_hidh.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_hrc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_htc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_pasp.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_pxm.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_rscc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_hpc.c
                bluetooth/export/appl/reference/le/profile_appl/client/appl_tic.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/client
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.client.ipspr)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/client/appl_ipspr.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/client
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/appl_service.c
                bluetooth/export/appl/reference/le/profile_appl/server/appl_service.h
                bluetooth/export/appl/reference/le/profile_appl/server/appl_service_mops.c
                bluetooth/export/appl/reference/le/profile_appl/server/appl_service_mops.h
                bluetooth/export/appl/reference/le/profile_appl/server/gatt_db.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.bps)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/bps/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/bps
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.cpms)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/cpms/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/cpms
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.cscs)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/cscs/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/cscs
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.basic)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/basic/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/basic
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.gls)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/gls/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/gls
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.hid)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/hid/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/hid
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.hps)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/hps/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/hps
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.hrs)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/hrs/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/hrs
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.hts)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/hts/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/hts
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.ipspn)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/ipspn/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/ipspn
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.pass)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/pass/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/pass
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.pxr)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/pxr/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/pxr
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.rscs)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/rscs/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/rscs
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.tis)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/tis/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/tis
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.server.pts)
    mcux_add_source(
        SOURCES bluetooth/export/appl/reference/le/profile_appl/server/pts/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/appl/reference/le/profile_appl/server/pts
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.btdm.lib)
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_a2dp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_avrcp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_bip.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_bpp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_core.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_ctn.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_ftp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_gatt.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_ga.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_hfp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_hid.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_map.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_opp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_pan.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_pbap.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_protocol.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_sap.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_spp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_util.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_sbc_common.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_sbc_decoder.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_sbc_encoder.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_common.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_decoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_encoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_common.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_common.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_a2dp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_avrcp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_bip.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_bpp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_core.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_ctn.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_ftp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_gatt.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_ga.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_hfp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_hid.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_map.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_opp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_pan.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_pbap.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_protocol.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_sap.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_spp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_util.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_sbc_common.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_sbc_decoder.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_sbc_encoder.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_common.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_decoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_encoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_common.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_common.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_a2dp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_avrcp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_bip.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_bpp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_core.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_ctn.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_ftp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_gatt.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_ga.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_hfp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_hid.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_map.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_opp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_pan.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_pbap.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_protocol.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_sap.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_spp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_util.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_sbc_common.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_sbc_decoder.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_sbc_encoder.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_common.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_decoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_encoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_ndsp_common.a
        TOOLCHAINS mcux
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS mcux
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS mcux
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_odsp_common.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_a2dp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_avrcp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_bip.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_bpp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_core.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_ctn.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_ftp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_gatt.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_ga.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_hfp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_hid.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_map.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_opp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_pan.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_pbap.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_protocol.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_sap.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_spp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_util.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_sbc_common.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_sbc_decoder.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_sbc_encoder.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_common.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_decoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_encoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_ndsp_common.lib
        TOOLCHAINS mdk
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_ndsp_decoder.lib
        TOOLCHAINS mdk
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_ndsp_encoder.lib
        TOOLCHAINS mdk
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_odsp_common.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_odsp_decoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_lc3_odsp_encoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.btdm_lite.lib)
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_a2dp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_avrcp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_bip.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_bpp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/lite/libethermind_bt_core.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_ga.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_core.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_common.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_decoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_encoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_common.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_common.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_ga.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_core.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_gatt.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_protocol.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_util.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_ga.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_core.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_common.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_decoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_encoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_common.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_common.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_ga.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.ble_core_dm.lib)
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_core.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_gatt.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_protocol.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/gcc/libethermind_bt_util.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_core.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_gatt.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_protocol.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/iar/libethermind_bt_util.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_core.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_gatt.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_protocol.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mcuxpresso/libethermind_bt_util.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_core.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_gatt.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_protocol.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/btdm/${wireless_ble_lib_sel}/mdk/libethermind_bt_util.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.br_only.lib)
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_a2dp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_avrcp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_bip.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_bpp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_core.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_ctn.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_ftp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_hfp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_hid.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_map.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_opp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_pan.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_pbap.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_protocol.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_sap.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_spp.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_util.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_sbc_common.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_sbc_decoder.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/gcc/libethermind_br_sbc_encoder.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_a2dp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_avrcp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_bip.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_bpp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_core.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_ctn.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_ftp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_hfp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_hid.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_map.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_opp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_pan.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_pbap.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_protocol.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_sap.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_spp.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_util.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_sbc_common.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_sbc_decoder.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/iar/libethermind_br_sbc_encoder.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_a2dp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_avrcp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_bip.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_bpp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_core.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_ctn.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_ftp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_hfp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_hid.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_map.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_opp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_pan.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_pbap.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_protocol.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_sap.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_spp.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_br_util.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_sbc_common.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_sbc_decoder.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mcuxpresso/libethermind_sbc_encoder.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_a2dp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_avrcp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_bip.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_bpp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_core.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_ctn.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_ftp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_hfp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_hid.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_map.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_opp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_pan.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_pbap.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_protocol.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_sap.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_spp.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_util.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_sbc_common.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_sbc_decoder.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/br/${wireless_ble_lib_sel}/mdk/libethermind_br_sbc_encoder.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.ble_only.lib)
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_core.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_gatt.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_protocol.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_util.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_ga.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_common.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_decoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_encoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_common.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS armgcc
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_common.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS armgcc
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_core.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_gatt.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_protocol.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_util.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_ga.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_common.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_decoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_encoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_common.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS iar
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_common.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS iar
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_core.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_gatt.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_protocol.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_util.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_ga.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_common.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_encoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_decoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_ndsp_common.a
        TOOLCHAINS mcux
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_ndsp_decoder.a
        TOOLCHAINS mcux
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_ndsp_encoder.a
        TOOLCHAINS mcux
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_odsp_common.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_odsp_decoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_lc3_odsp_encoder.a
        TOOLCHAINS mcux
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_core.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_gatt.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_protocol.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_util.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_ga.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_common.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_decoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_encoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_ndsp_common.lib
        TOOLCHAINS mdk
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_ndsp_decoder.lib
        TOOLCHAINS mdk
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_ndsp_encoder.lib
        TOOLCHAINS mdk
        CORES cm33
        DSP NO_DSP
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_odsp_common.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_odsp_decoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_lc3_odsp_encoder.lib
        TOOLCHAINS mdk
        CORES cm7f cm4f cm33
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.ble_only_without_lc3.lib)
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_core.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_gatt.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_protocol.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/gcc/libethermind_ble_util.a
        TOOLCHAINS armgcc
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_core.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_gatt.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_protocol.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/iar/libethermind_ble_util.a
        TOOLCHAINS iar
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_core.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_gatt.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_protocol.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mcuxpresso/libethermind_ble_util.a
        TOOLCHAINS mcux
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_core.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_gatt.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_protocol.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_library(
        LIBS bluetooth/private/lib/mcux/default/ble/${wireless_ble_lib_sel}/mdk/libethermind_ble_util.lib
        TOOLCHAINS mdk
        CORES ${wireless_ble_core_arch}
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.config)
    mcux_add_source(
        SOURCES bluetooth/private/lib/mcux/default/config/BT_features.h
                bluetooth/private/lib/mcux/default/config/BT_limits.h
                bluetooth/private/lib/mcux/default/config/db_gen.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/lib/mcux/default/config
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.extension.common)
    mcux_add_source(
        SOURCES bluetooth/export/extension/aes_cmac_pl.c
                bluetooth/export/extension/aes_cmac_pl.h
                bluetooth/export/extension/BT_common_pl.c
                bluetooth/export/extension/BT_common_pl.h
                bluetooth/export/extension/device_queue_pl.c
                bluetooth/export/extension/device_queue_pl.h
                bluetooth/export/extension/sm_pl.c
                bluetooth/export/extension/sm_pl.h
                bluetooth/export/extension/sm_ssp_pl.c
                bluetooth/export/extension/sm_ssp_pl.h
                bluetooth/export/extension/smp_pl.c
                bluetooth/export/extension/smp_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/extension
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.extension.gatt_db)
    mcux_add_source(
        SOURCES bluetooth/export/extension/gatt_db_pl.c
                bluetooth/export/extension/gatt_db_pl.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/export/extension
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.core.include.libFile)
    mcux_add_source(
        SOURCES port/pal/mcux/*.h
                port/pal/mcux/ethal/*.h
                port/pal/mcux/bluetooth/*.h
                port/pal/mcux/bluetooth/controller/*.h
                port/pal/mcux/sbc/*.h
                port/pal/mcux/lc3/*.h
                port/osal/src/freertos/*.h
                bluetooth/private/protocols/common/*.h
                bluetooth/private/protocols/device_queue/*.h
                bluetooth/private/protocols/write_task/*.h
                bluetooth/private/protocols/hci_transport/*.h
                bluetooth/private/protocols/hci_1.2/*.h
                bluetooth/private/protocols/el2cap/*.h
                bluetooth/private/protocols/sdp/*.h
                bluetooth/private/protocols/dbase/*.h
                bluetooth/private/protocols/rfcomm/*.h
                bluetooth/private/protocols/irobex/*.h
                bluetooth/private/protocols/obex/*.h
                bluetooth/private/protocols/sm/*.h
                bluetooth/private/protocols/avdtp/*.h
                bluetooth/private/protocols/avctp/*.h
                bluetooth/private/protocols/bnep/*.h
                bluetooth/private/protocols/smp/*.h
                bluetooth/private/protocols/att/*.h
                bluetooth/private/protocols/fsm_engine/*.h
                bluetooth/private/protocols/gatt_db/*.h
                bluetooth/private/profiles/hfp_unit/*.h
                bluetooth/private/profiles/hfp_ag/*.h
                bluetooth/private/profiles/pbap/*.h
                bluetooth/private/profiles/map/*.h
                bluetooth/private/profiles/ctn/*.h
                bluetooth/private/profiles/bip/*.h
                bluetooth/private/profiles/bpp/*.h
                bluetooth/private/profiles/sap/*.h
                bluetooth/private/profiles/hid/*.h
                bluetooth/private/profiles/hid_host/*.h
                bluetooth/private/profiles/a2dp/*.h
                bluetooth/private/profiles/avrcp/*.h
                bluetooth/private/profiles/spp/*.h
                bluetooth/private/profiles/opp/*.h
                bluetooth/private/profiles/ftp/*.h
                bluetooth/private/profiles/pan/*.h
                bluetooth/private/utils/at_parser/*.h
                bluetooth/private/utils/racp/*.h
                bluetooth/private/utils/btsnoop/*.h
                bluetooth/private/utils/jpl/*.h
                bluetooth/private/utils/object_parser/*.h
                bluetooth/private/utils/xml_parser/*.h
                bluetooth/private/utils/storage/*.h
                bluetooth/private/utils/security/*.h
                bluetooth/private/utils/aes_cmac/*.h
                bluetooth/private/lib/mcux/default/config/*.h
                bluetooth/private/utils/sbc/*.h
                bluetooth/private/utils/lc3/export/include/*.h
                bluetooth/private/utils/lc3/private/fixed/config/*.h
                bluetooth/export/include/*.h
                bluetooth/export/extension/*.h
                bluetooth/export/eOSAL/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/sbc/iar/*.h
        TOOLCHAINS iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/sbc/keil/*.h
        TOOLCHAINS mdk
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/sbc/mcuxpresso/*.h
        TOOLCHAINS mcux armgcc
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/lc3/iar/*.h
        TOOLCHAINS iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/lc3/keil/*.h
        TOOLCHAINS mdk
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/lc3/mcuxpresso/*.h
        TOOLCHAINS mcux armgcc
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES examples/ethermind
                 port/pal/mcux
                 port/pal/mcux/toolspec/iar
                 port/pal/mcux/ethal
                 port/pal/mcux/bluetooth
                 port/pal/mcux/sbc
                 port/pal/mcux/lc3
                 port/osal/src/freertos
                 bluetooth/private/protocols/common
                 bluetooth/private/protocols/device_queue
                 bluetooth/private/protocols/write_task
                 bluetooth/private/protocols/hci_transport
                 bluetooth/private/protocols/hci_1.2
                 bluetooth/private/protocols/el2cap
                 bluetooth/private/protocols/sdp
                 bluetooth/private/protocols/dbase
                 bluetooth/private/protocols/rfcomm
                 bluetooth/private/protocols/irobex
                 bluetooth/private/protocols/obex
                 bluetooth/private/protocols/sm
                 bluetooth/private/protocols/avdtp
                 bluetooth/private/protocols/avctp
                 bluetooth/private/protocols/bnep
                 bluetooth/private/protocols/smp
                 bluetooth/private/protocols/att
                 bluetooth/private/protocols/fsm_engine
                 bluetooth/private/protocols/gatt_db
                 bluetooth/private/profiles/hfp_unit
                 bluetooth/private/profiles/hfp_ag
                 bluetooth/private/profiles/pbap
                 bluetooth/private/profiles/map
                 bluetooth/private/profiles/ctn
                 bluetooth/private/profiles/bip
                 bluetooth/private/profiles/bpp
                 bluetooth/private/profiles/sap
                 bluetooth/private/profiles/hid
                 bluetooth/private/profiles/hid_host
                 bluetooth/private/profiles/a2dp
                 bluetooth/private/profiles/avrcp
                 bluetooth/private/profiles/spp
                 bluetooth/private/profiles/opp
                 bluetooth/private/profiles/ftp
                 bluetooth/private/profiles/pan
                 bluetooth/private/utils/at_parser
                 bluetooth/private/utils/racp
                 bluetooth/private/utils/btsnoop
                 bluetooth/private/utils/jpl
                 bluetooth/private/utils/object_parser
                 bluetooth/private/utils/xml_parser
                 bluetooth/private/utils/storage
                 bluetooth/private/utils/security
                 bluetooth/private/utils/aes_cmac
                 bluetooth/private/lib/mcux/default/config
                 bluetooth/private/utils/sbc
                 bluetooth/private/utils/lc3/export/include
                 bluetooth/private/utils/lc3/private/fixed/config
                 bluetooth/export/include
                 bluetooth/export/extension
                 bluetooth/export/eOSAL
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS iar
        INCLUDES port/pal/mcux/sbc/iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mdk
        INCLUDES port/pal/mcux/sbc/keil
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mcux armgcc
        INCLUDES port/pal/mcux/sbc/mcuxpresso
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS iar
        INCLUDES port/pal/mcux/lc3/iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mdk
        INCLUDES port/pal/mcux/lc3/keil
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mcux armgcc
        INCLUDES port/pal/mcux/lc3/mcuxpresso
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.lc3.include.libFile)
    mcux_add_source(
        SOURCES port/pal/mcux/*.h
                port/pal/mcux/ethal/*.h
                port/pal/mcux/lc3/*.h
                bluetooth/private/utils/lc3/export/include/*.h
                bluetooth/private/utils/lc3/private/fixed/common/*.h
                bluetooth/private/utils/lc3/private/fixed/config/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/lc3/iar/*.h
        TOOLCHAINS iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/lc3/keil/*.h
        TOOLCHAINS mdk
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/lc3/mcuxpresso/*.h
        TOOLCHAINS mcux armgcc
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES examples/ethermind
                 port/pal/mcux
                 port/pal/mcux/toolspec/iar
                 port/pal/mcux/ethal
                 port/pal/mcux/lc3
                 port/osal/src/freertos
                 bluetooth/private/utils/lc3/export/include
                 bluetooth/private/utils/lc3/private/fixed/common
                 bluetooth/private/utils/lc3/private/fixed/config
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS iar
        INCLUDES port/pal/mcux/lc3/iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mdk
        INCLUDES port/pal/mcux/lc3/keil
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mcux armgcc
        INCLUDES port/pal/mcux/lc3/mcuxpresso
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.lc3_ndsp.include.libFile)
    mcux_add_source(
        SOURCES port/pal/mcux/*.h
                port/pal/mcux/ethal/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES examples/ethermind
                 port/pal/mcux
                 port/pal/mcux/toolspec/iar
                 port/pal/mcux/ethal
                 port/osal/src/freertos
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.lc3_odsp.include.libFile)
    mcux_add_source(
        SOURCES port/pal/mcux/*.h
                port/pal/mcux/ethal/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES examples/ethermind
                 port/pal/mcux
                 port/pal/mcux/toolspec/iar
                 port/pal/mcux/ethal
                 port/osal/src/freertos
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.sbc.include.libFile)
    mcux_add_source(
        SOURCES port/pal/mcux/*.h
                port/pal/mcux/ethal/*.h
                port/pal/mcux/sbc/*.h
                port/osal/src/freertos/*.h
                bluetooth/private/utils/sbc/*.h
                bluetooth/private/utils/sbc/private/fixed/common/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/sbc/iar/*.h
        TOOLCHAINS iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/sbc/keil/*.h
        TOOLCHAINS mdk
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_source(
        SOURCES port/pal/mcux/sbc/mcuxpresso/*.h
        TOOLCHAINS mcux armgcc
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES examples/ethermind
                 port/pal/mcux
                 port/pal/mcux/toolspec/iar
                 port/pal/mcux/ethal
                 port/pal/mcux/sbc
                 port/osal/src/freertos
                 bluetooth/private/utils/sbc
                 bluetooth/private/utils/sbc/private/fixed/common
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS iar
        INCLUDES port/pal/mcux/sbc/iar
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mdk
        INCLUDES port/pal/mcux/sbc/keil
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        TOOLCHAINS mcux armgcc
        INCLUDES port/pal/mcux/sbc/mcuxpresso
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.att.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/att/att.h
                bluetooth/private/protocols/att/att_api.c
                bluetooth/private/protocols/att/att_extern.h
                bluetooth/private/protocols/att/att_fsm.h
                bluetooth/private/protocols/att/att_fsm_defines.h
                bluetooth/private/protocols/att/att_fsm_handlers.c
                bluetooth/private/protocols/att/att_fsm_handlers.h
                bluetooth/private/protocols/att/att_fsm_table.c
                bluetooth/private/protocols/att/att_init.c
                bluetooth/private/protocols/att/att_internal.c
                bluetooth/private/protocols/att/att_internal.h
                bluetooth/private/protocols/att/att_l2cap.c
                bluetooth/private/protocols/att/att_l2cap_ecbfc.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/att
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.avctp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/avctp/avctp.h
                bluetooth/private/protocols/avctp/avctp_api.c
                bluetooth/private/protocols/avctp/avctp_bh.c
                bluetooth/private/protocols/avctp/avctp_extern.h
                bluetooth/private/protocols/avctp/avctp_incoming.c
                bluetooth/private/protocols/avctp/avctp_init.c
                bluetooth/private/protocols/avctp/avctp_internal.h
                bluetooth/private/protocols/avctp/avctp_l2cap.c
                bluetooth/private/protocols/avctp/avctp_outgoing.c
                bluetooth/private/protocols/avctp/avctp_utils.c
                bluetooth/private/protocols/avctp/avctp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/avctp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.avdtp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/avdtp/avdtp.h
                bluetooth/private/protocols/avdtp/avdtp_api.c
                bluetooth/private/protocols/avdtp/avdtp_api_utils.c
                bluetooth/private/protocols/avdtp/avdtp_bh.c
                bluetooth/private/protocols/avdtp/avdtp_extern.h
                bluetooth/private/protocols/avdtp/avdtp_incoming.c
                bluetooth/private/protocols/avdtp/avdtp_init.c
                bluetooth/private/protocols/avdtp/avdtp_internal.h
                bluetooth/private/protocols/avdtp/avdtp_l2cap.c
                bluetooth/private/protocols/avdtp/avdtp_outgoing.c
                bluetooth/private/protocols/avdtp/avdtp_utils.c
                bluetooth/private/protocols/avdtp/avdtp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/avdtp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.bnep.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/bnep/bnep.h
                bluetooth/private/protocols/bnep/bnep_api.c
                bluetooth/private/protocols/bnep/bnep_bh.c
                bluetooth/private/protocols/bnep/bnep_core.c
                bluetooth/private/protocols/bnep/bnep_extern.h
                bluetooth/private/protocols/bnep/bnep_init.c
                bluetooth/private/protocols/bnep/bnep_internal.h
                bluetooth/private/protocols/bnep/bnep_l2cap.c
                bluetooth/private/protocols/bnep/bnep_utils.c
                bluetooth/private/protocols/bnep/bnep_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/bnep
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.commom.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/common/BT_common.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.dbase.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/dbase/database.h
                bluetooth/private/protocols/dbase/db_extern.h
                bluetooth/private/protocols/dbase/db_internal.h
                bluetooth/private/protocols/dbase/db_sdp_interface.c
                bluetooth/private/protocols/dbase/db_sdp_dyn_interface.c
                bluetooth/private/protocols/dbase/db_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/dbase
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.device_queue.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/device_queue/device_queue.c
                bluetooth/private/protocols/device_queue/device_queue_internal.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/device_queue
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.el2cap.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/el2cap/l2cap_channels.c
                bluetooth/private/protocols/el2cap/l2cap_command.c
                bluetooth/private/protocols/el2cap/l2cap_config.c
                bluetooth/private/protocols/el2cap/l2cap_connect.c
                bluetooth/private/protocols/el2cap/l2cap_credit_mode.c
                bluetooth/private/protocols/el2cap/l2cap_data_recv.c
                bluetooth/private/protocols/el2cap/l2cap_data_send.c
                bluetooth/private/protocols/el2cap/l2cap_disconnect.c
                bluetooth/private/protocols/el2cap/l2cap_ecbfc.c
                bluetooth/private/protocols/el2cap/l2cap_extern.h
                bluetooth/private/protocols/el2cap/l2cap_fec.c
                bluetooth/private/protocols/el2cap/l2cap_fixed_channel.c
                bluetooth/private/protocols/el2cap/l2cap_group.c
                bluetooth/private/protocols/el2cap/l2cap_init.c
                bluetooth/private/protocols/el2cap/l2cap_internal.h
                bluetooth/private/protocols/el2cap/l2cap_le.c
                bluetooth/private/protocols/el2cap/l2cap_lmp.c
                bluetooth/private/protocols/el2cap/l2cap_ping.c
                bluetooth/private/protocols/el2cap/l2cap_sm.c
                bluetooth/private/protocols/el2cap/l2cap_utils.c
                bluetooth/private/protocols/el2cap/l2cap_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/el2cap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.fsm_engine.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/fsm_engine/fsm_engine.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.gatt_db.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/gatt_db/gatt_db_api.c
                bluetooth/private/protocols/gatt_db/gatt_db_dyn_api.c
                bluetooth/private/protocols/gatt_db/gatt_db_extern.h
                bluetooth/private/protocols/gatt_db/gatt_db_init.c
                bluetooth/private/protocols/gatt_db/gatt_db_internal.c
                bluetooth/private/protocols/gatt_db/gatt_db_internal.h
                bluetooth/private/protocols/gatt_db/gatt_db_storage.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/gatt_db
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.hci_1.2.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/hci_1.2/hci_api.c
                bluetooth/private/protocols/hci_1.2/hci_command_queue.c
                bluetooth/private/protocols/hci_1.2/hci_commands.c
                bluetooth/private/protocols/hci_1.2/hci_connect.c
                bluetooth/private/protocols/hci_1.2/hci_defines.h
                bluetooth/private/protocols/hci_1.2/hci_dev_attr.c
                bluetooth/private/protocols/hci_1.2/hci_dev_attr.h
                bluetooth/private/protocols/hci_1.2/hci_disconnect.c
                bluetooth/private/protocols/hci_1.2/hci_events.c
                bluetooth/private/protocols/hci_1.2/hci_extern.h
                bluetooth/private/protocols/hci_1.2/hci_h.h
                bluetooth/private/protocols/hci_1.2/hci_host_controller_api.c
                bluetooth/private/protocols/hci_1.2/hci_informational_api.c
                bluetooth/private/protocols/hci_1.2/hci_init.c
                bluetooth/private/protocols/hci_1.2/hci_internal.h
                bluetooth/private/protocols/hci_1.2/hci_iso_data_queue.c
                bluetooth/private/protocols/hci_1.2/hci_le_api.c
                bluetooth/private/protocols/hci_1.2/hci_link_control_api.c
                bluetooth/private/protocols/hci_1.2/hci_link_policy_api.c
                bluetooth/private/protocols/hci_1.2/hci_sm.c
                bluetooth/private/protocols/hci_1.2/hci_status_api.c
                bluetooth/private/protocols/hci_1.2/hci_testing_api.c
                bluetooth/private/protocols/hci_1.2/hci_utils.c
                bluetooth/private/protocols/hci_1.2/hci_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/hci_1.2
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.hci_transport.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/hci_transport/hci_transport_internal.h
                bluetooth/private/protocols/hci_transport/hci_transport_version.h
                bluetooth/private/protocols/hci_transport/ht_core.c
                bluetooth/private/protocols/hci_transport/ht_read_task.c
                bluetooth/private/protocols/hci_transport/ht_single_task.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/hci_transport
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.irobex.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/irobex/obex_al.c
                bluetooth/private/protocols/irobex/obex_al.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/irobex
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.mcap.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/mcap/mcap.h
                bluetooth/private/protocols/mcap/mcap_api.c
                bluetooth/private/protocols/mcap/mcap_bh.c
                bluetooth/private/protocols/mcap/mcap_extern.h
                bluetooth/private/protocols/mcap/mcap_incoming.c
                bluetooth/private/protocols/mcap/mcap_init.c
                bluetooth/private/protocols/mcap/mcap_internal.h
                bluetooth/private/protocols/mcap/mcap_l2cap.c
                bluetooth/private/protocols/mcap/mcap_psstore.c
                bluetooth/private/protocols/mcap/mcap_utils.c
                bluetooth/private/protocols/mcap/mcap_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/mcap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.obex.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/obex/obex.h
                bluetooth/private/protocols/obex/obex_api.c
                bluetooth/private/protocols/obex/obex_auth_api.c
                bluetooth/private/protocols/obex/obex_auth_internal.c
                bluetooth/private/protocols/obex/obex_bh.c
                bluetooth/private/protocols/obex/obex_extern.h
                bluetooth/private/protocols/obex/obex_fsm.h
                bluetooth/private/protocols/obex/obex_fsm_engine.c
                bluetooth/private/protocols/obex/obex_fsm_engine.h
                bluetooth/private/protocols/obex/obex_fsm_handlers.c
                bluetooth/private/protocols/obex/obex_fsm_handlers.h
                bluetooth/private/protocols/obex/obex_fsm_table.c
                bluetooth/private/protocols/obex/obex_init.c
                bluetooth/private/protocols/obex/obex_internal.c
                bluetooth/private/protocols/obex/obex_internal.h
                bluetooth/private/protocols/obex/obex_l2cap.c
                bluetooth/private/protocols/obex/obex_rfcomm.c
                bluetooth/private/protocols/obex/obex_util.h
                bluetooth/private/protocols/obex/obex_util_api.c
                bluetooth/private/protocols/obex/obex_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/obex
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.rfcomm.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/rfcomm/rfcomm.h
                bluetooth/private/protocols/rfcomm/rfcomm_api.c
                bluetooth/private/protocols/rfcomm/rfcomm_bh.c
                bluetooth/private/protocols/rfcomm/rfcomm_extern.h
                bluetooth/private/protocols/rfcomm/rfcomm_incoming.c
                bluetooth/private/protocols/rfcomm/rfcomm_init.c
                bluetooth/private/protocols/rfcomm/rfcomm_internal.h
                bluetooth/private/protocols/rfcomm/rfcomm_l2cap.c
                bluetooth/private/protocols/rfcomm/rfcomm_outgoing.c
                bluetooth/private/protocols/rfcomm/rfcomm_sm.c
                bluetooth/private/protocols/rfcomm/rfcomm_support.h
                bluetooth/private/protocols/rfcomm/rfcomm_utils.c
                bluetooth/private/protocols/rfcomm/rfcomm_version.h
                bluetooth/private/protocols/rfcomm/rfcomm_write.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/rfcomm
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.sdp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/sdp/sdp.h
                bluetooth/private/protocols/sdp/sdp_api.c
                bluetooth/private/protocols/sdp/sdp_bh.c
                bluetooth/private/protocols/sdp/sdp_client.c
                bluetooth/private/protocols/sdp/sdp_extern.h
                bluetooth/private/protocols/sdp/sdp_init.c
                bluetooth/private/protocols/sdp/sdp_internal.h
                bluetooth/private/protocols/sdp/sdp_l2cap.c
                bluetooth/private/protocols/sdp/sdp_pdu_handler.c
                bluetooth/private/protocols/sdp/sdp_server.c
                bluetooth/private/protocols/sdp/sdp_util.c
                bluetooth/private/protocols/sdp/sdp_util_api.c
                bluetooth/private/protocols/sdp/sdp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/sdp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.sm.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/sm/sm.h
                bluetooth/private/protocols/sm/sm_api.c
                bluetooth/private/protocols/sm/sm_core.c
                bluetooth/private/protocols/sm/sm_extern.h
                bluetooth/private/protocols/sm/sm_init.c
                bluetooth/private/protocols/sm/sm_interface.c
                bluetooth/private/protocols/sm/sm_internal.h
                bluetooth/private/protocols/sm/sm_psstore.c
                bluetooth/private/protocols/sm/sm_ui.c
                bluetooth/private/protocols/sm/sm_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/sm
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.smp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/smp/smp.h
                bluetooth/private/protocols/smp/smp_api.c
                bluetooth/private/protocols/smp/smp_core.c
                bluetooth/private/protocols/smp/smp_extern.h
                bluetooth/private/protocols/smp/smp_fsm.h
                bluetooth/private/protocols/smp/smp_fsm_engine.c
                bluetooth/private/protocols/smp/smp_fsm_engine.h
                bluetooth/private/protocols/smp/smp_fsm_handlers.c
                bluetooth/private/protocols/smp/smp_fsm_handlers.h
                bluetooth/private/protocols/smp/smp_fsm_retval.c
                bluetooth/private/protocols/smp/smp_fsm_table.c
                bluetooth/private/protocols/smp/smp_init.c
                bluetooth/private/protocols/smp/smp_interface.c
                bluetooth/private/protocols/smp/smp_internal.h
                bluetooth/private/protocols/smp/smp_psstore.c
                bluetooth/private/protocols/smp/smp_tools.c
                bluetooth/private/protocols/smp/smp_utils.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/smp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.protocols.write_task.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/protocols/write_task/write_task.c
                bluetooth/private/protocols/write_task/write_task_internal.h
                bluetooth/private/protocols/write_task/write_task_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/protocols/write_task
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.aes_cmac.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/aes_cmac/aes_cmac.c
                bluetooth/private/utils/aes_cmac/aes_cmac.h
                bluetooth/private/utils/aes_cmac/aes_cmac_test.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/aes_cmac
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.at_parser.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/at_parser/at_parser.c
                bluetooth/private/utils/at_parser/at_parser_ag.c
                bluetooth/private/utils/at_parser/at_parser_hsp_hfp.c
                bluetooth/private/utils/at_parser/at_parser_hsp_hfp.h
                bluetooth/private/utils/at_parser/at_parser_internal.h
                bluetooth/private/utils/at_parser/at_parser_utils.c
                bluetooth/private/utils/at_parser/at_parser_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/at_parser
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.btsnoop.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/btsnoop/btsnoop.c
                bluetooth/private/utils/btanalyzer/btanalyzer.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.jpl.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/jpl/jpl_core.c
                bluetooth/private/utils/jpl/jpl_internal.h
                bluetooth/private/utils/jpl/jpl_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/jpl
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.object_parser.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/object_parser/object_parser_api.c
                bluetooth/private/utils/object_parser/object_parser_api.h
                bluetooth/private/utils/object_parser/tokenizer.c
                bluetooth/private/utils/object_parser/tokenizer.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/object_parser
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.racp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/racp/racp.c
                bluetooth/private/utils/racp/racp.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/racp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.security.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/security/security.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.status.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/status/status.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.storage.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/storage/storage.c
                bluetooth/private/utils/storage/storage.h
                bluetooth/private/utils/storage/storage_internal.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/storage
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.xml_parser.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/xml_parser/xml_common_defines.h
                bluetooth/private/utils/xml_parser/xml_encoder.c
                bluetooth/private/utils/xml_parser/xml_encoder.h
                bluetooth/private/utils/xml_parser/xml_encoder_internal.h
                bluetooth/private/utils/xml_parser/xml_parser.c
                bluetooth/private/utils/xml_parser/xml_parser.h
                bluetooth/private/utils/xml_parser/xml_parser_internal.h
                bluetooth/private/utils/xml_parser/xml_parser_stack.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/xml_parser
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.ga.include)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/ga/eOSAL/GA_os.h
                bluetooth/private/profiles/ga/eOSAL/GA_timer.h
                bluetooth/private/profiles/ga/eOSAL/GA_debug.h
                bluetooth/private/profiles/ga/eOSAL/GA_config.h
                bluetooth/private/profiles/ga/eOSAL/GA_fops.h
                bluetooth/private/profiles/ga/include/GA_hap_api.h
                bluetooth/private/profiles/ga/include/GA_tmap_api.h
                bluetooth/private/profiles/ga/include/GA_api.h
                bluetooth/private/profiles/ga/include/GA_assigned_numbers.h
                bluetooth/private/profiles/ga/include/GA_audio_config.h
                bluetooth/private/profiles/ga/include/GA_bearer_api.h
                bluetooth/private/profiles/ga/include/GA_ccp_ce_api.h
                bluetooth/private/profiles/ga/include/GA_ccp_se_api.h
                bluetooth/private/profiles/ga/include/GA_common.h
                bluetooth/private/profiles/ga/include/GA_error.h
                bluetooth/private/profiles/ga/include/GA_features.h
                bluetooth/private/profiles/ga/include/GA_limits.h
                bluetooth/private/profiles/ga/include/GA_mcp_ce_api.h
                bluetooth/private/profiles/ga/include/GA_mcp_se_api.h
                bluetooth/private/profiles/ga/include/GA_property_config.h
                bluetooth/private/profiles/ga/include/GA_bass_api.h
                bluetooth/private/profiles/ga/include/GA_bass_db.h
                bluetooth/private/profiles/ga/include/GA_pbp_api.h
                bluetooth/private/profiles/ga/include/GA_version.h
                bluetooth/private/profiles/ga/source/core/bap/bap.h
                bluetooth/private/profiles/ga/source/core/bap/bass/bass_extern.h
                bluetooth/private/profiles/ga/source/core/bap/bass/bass_internal.h
                bluetooth/private/profiles/ga/source/core/csip/csip.h
                bluetooth/private/profiles/ga/source/core/csip/csip_extern.h
                bluetooth/private/profiles/ga/source/core/csip/csip_internal.h
                bluetooth/private/profiles/ga/source/core/micp/micp.h
                bluetooth/private/profiles/ga/source/core/micp/micp_extern.h
                bluetooth/private/profiles/ga/source/core/micp/micp_internal.h
                bluetooth/private/profiles/ga/source/core/vcp/vcp.h
                bluetooth/private/profiles/ga/source/core/vcp/vcp_extern.h
                bluetooth/private/profiles/ga/source/core/vcp/vcp_internal.h
                bluetooth/private/profiles/ga/source/core/otp/otc.h
                bluetooth/private/profiles/ga/source/core/otp/otc_extern.h
                bluetooth/private/profiles/ga/source/core/otp/otc_internal.h
                bluetooth/private/profiles/ga/source/core/otp/otc_transport.h
                bluetooth/private/profiles/ga/source/core/otp/otp_common.h
                bluetooth/private/profiles/ga/source/core/otp/ots.h
                bluetooth/private/profiles/ga/source/core/otp/ots_extern.h
                bluetooth/private/profiles/ga/source/core/otp/ots_internal.h
                bluetooth/private/profiles/ga/source/core/otp/ots_transport.h
                bluetooth/private/profiles/ga/source/core/cap.h
                bluetooth/private/profiles/ga/source/core/cap_extern.h
                bluetooth/private/profiles/ga/source/core/cap_internal.h
                bluetooth/private/profiles/ga/source/profiles/ccp/ccp_extern.h
                bluetooth/private/profiles/ga/source/profiles/ccp/ccp_internal.h
                bluetooth/private/profiles/ga/source/profiles/mcp/mcp_extern.h
                bluetooth/private/profiles/ga/source/profiles/mcp/mcp_internal.h
                bluetooth/private/profiles/ga/source/core/brr/brr_internal.h
                bluetooth/private/profiles/ga/source/profiles/hap/hap_extern.h
                bluetooth/private/profiles/ga/source/profiles/hap/hap_internal.h
                bluetooth/private/profiles/ga/source/profiles/tmap/tmap_extern.h
                bluetooth/private/profiles/ga/source/profiles/tmap/tmap_internal.h
                bluetooth/export/include/ga/bearer/l2cap_coc.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/ga/eOSAL
                 bluetooth/private/profiles/ga/include
                 bluetooth/private/profiles/ga/source/profiles/ccp
                 bluetooth/private/profiles/ga/source/profiles/mcp
                 bluetooth/private/profiles/ga/source/core
                 bluetooth/private/profiles/ga/source/core/bap
                 bluetooth/private/profiles/ga/source/core/bap/bass
                 bluetooth/private/profiles/ga/source/core/csip
                 bluetooth/private/profiles/ga/source/core/micp
                 bluetooth/private/profiles/ga/source/core/vcp
                 bluetooth/private/profiles/ga/source/core/otp
                 bluetooth/export/include/ga/bearer
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.a2dp_sink.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/a2dp/a2dp_extern.h
                bluetooth/private/profiles/a2dp/a2dp_internal.h
                bluetooth/private/profiles/a2dp/a2dp_sink.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/a2dp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.a2dp_source.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/a2dp/a2dp_extern.h
                bluetooth/private/profiles/a2dp/a2dp_internal.h
                bluetooth/private/profiles/a2dp/a2dp_source.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/a2dp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.a2dp_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/a2dp/a2dp.h
                bluetooth/private/profiles/a2dp/a2dp_core.c
                bluetooth/private/profiles/a2dp/a2dp_events.c
                bluetooth/private/profiles/a2dp/a2dp_utils.c
                bluetooth/private/profiles/a2dp/a2dp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/a2dp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.avrcp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/avrcp/avrcp.h
                bluetooth/private/profiles/avrcp/avrcp_api.c
                bluetooth/private/profiles/avrcp/avrcp_ca_internal.h
                bluetooth/private/profiles/avrcp/avrcp_ca_utils.c
                bluetooth/private/profiles/avrcp/avrcp_cai_api.c
                bluetooth/private/profiles/avrcp/avrcp_cai_internal.c
                bluetooth/private/profiles/avrcp/avrcp_car_api.c
                bluetooth/private/profiles/avrcp/avrcp_car_internal.c
                bluetooth/private/profiles/avrcp/avrcp_events.c
                bluetooth/private/profiles/avrcp/avrcp_extern.h
                bluetooth/private/profiles/avrcp/avrcp_internal.h
                bluetooth/private/profiles/avrcp/avrcp_utils.c
                bluetooth/private/profiles/avrcp/avrcp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/avrcp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.bip_initiator.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/bip/bip_initiator_api.c
                bluetooth/private/profiles/bip/bip_initiator_internal.c
                bluetooth/private/profiles/bip/bip_internal.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/bip
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.bip_responder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/bip/bip_extern.h
                bluetooth/private/profiles/bip/bip_internal.h
                bluetooth/private/profiles/bip/bip_responder_api.c
                bluetooth/private/profiles/bip/bip_responder_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/bip
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.bip_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/bip/bip.h
                bluetooth/private/profiles/bip/bip_extern.h
                bluetooth/private/profiles/bip/bip_internal.h
                bluetooth/private/profiles/bip/bip_utils.c
                bluetooth/private/profiles/bip/bip_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/bip
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.bpp_printer.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/bpp/bpp_internal.h
                bluetooth/private/profiles/bpp/bpp_printer_api.c
                bluetooth/private/profiles/bpp/bpp_printer_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/bpp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.bpp_sender.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/bpp/bpp_internal.h
                bluetooth/private/profiles/bpp/bpp_sender_api.c
                bluetooth/private/profiles/bpp/bpp_sender_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/bpp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.bpp_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/bpp/bpp_extern.h
                bluetooth/private/profiles/bpp/bpp_internal.h
                bluetooth/private/profiles/bpp/bpp_utils.c
                bluetooth/private/profiles/bpp/bpp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/bpp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.ctn_cce.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/ctn/ctn_cce_api.c
                bluetooth/private/profiles/ctn/ctn_internal.h
                bluetooth/private/profiles/ctn/ctn_cce_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/ctn
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.ctn_cse.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/ctn/ctn_cse_api.c
                bluetooth/private/profiles/ctn/ctn_internal.h
                bluetooth/private/profiles/ctn/ctn_cse_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/ctn
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.ctn_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/ctn/ctn_internal.h
                bluetooth/private/profiles/ctn/ctn_version.h
                bluetooth/private/profiles/ctn/ctn_util.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/ctn
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.ftp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/ftp/ftp_client_api.c
                bluetooth/private/profiles/ftp/ftp_client_internal.c
                bluetooth/private/profiles/ftp/ftp_internal.h
                bluetooth/private/profiles/ftp/ftp_server_api.c
                bluetooth/private/profiles/ftp/ftp_server_internal.c
                bluetooth/private/profiles/ftp/ftp_utils.c
                bluetooth/private/profiles/ftp/ftp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/ftp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.hfp_ag.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/hfp_ag/hfp_ag_api.c
                bluetooth/private/profiles/hfp_ag/hfp_ag_extern.h
                bluetooth/private/profiles/hfp_ag/hfp_ag_internal.c
                bluetooth/private/profiles/hfp_ag/hfp_ag_internal.h
                bluetooth/private/profiles/hfp_ag/hfp_ag_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/hfp_ag
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.hfp_unit.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/hfp_unit/hfp_unit_api.c
                bluetooth/private/profiles/hfp_unit/hfp_unit_extern.h
                bluetooth/private/profiles/hfp_unit/hfp_unit_internal.c
                bluetooth/private/profiles/hfp_unit/hfp_unit_internal.h
                bluetooth/private/profiles/hfp_unit/hfp_unit_internal_1_5.c
                bluetooth/private/profiles/hfp_unit/hfp_unit_internal_1_6.c
                bluetooth/private/profiles/hfp_unit/hfp_unit_internal_1_7.c
                bluetooth/private/profiles/hfp_unit/hfp_unit_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/hfp_unit
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.hid.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/hid/hid_device.c
                bluetooth/private/profiles/hid/hid_device_internal.h
                bluetooth/private/profiles/hid/hid_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/hid
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.hid_host.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/hid_host/hid_host.c
                bluetooth/private/profiles/hid_host/hid_host_extern.h
                bluetooth/private/profiles/hid_host/hid_host_internal.h
                bluetooth/private/profiles/hid_host/hid_host_l2cap.c
                bluetooth/private/profiles/hid_host/hid_host_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/hid_host
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.map_mce.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/map/map_internal.h
                bluetooth/private/profiles/map/map_mce_api.c
                bluetooth/private/profiles/map/map_mce_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/map
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.map_mse.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/map/map_internal.h
                bluetooth/private/profiles/map/map_mse_api.c
                bluetooth/private/profiles/map/map_mse_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/map
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.map_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/map/map_internal.h
                bluetooth/private/profiles/map/map_util.c
                bluetooth/private/profiles/map/map_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/map
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.opp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/opp/opp_client_api.c
                bluetooth/private/profiles/opp/opp_client_internal.c
                bluetooth/private/profiles/opp/opp_internal.h
                bluetooth/private/profiles/opp/opp_server_api.c
                bluetooth/private/profiles/opp/opp_server_internal.c
                bluetooth/private/profiles/opp/opp_utils.c
                bluetooth/private/profiles/opp/opp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/opp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.pan.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/pan/pan.h
                bluetooth/private/profiles/pan/pan_arp.c
                bluetooth/private/profiles/pan/pan_bridge.c
                bluetooth/private/profiles/pan/pan_core.c
                bluetooth/private/profiles/pan/pan_extern.h
                bluetooth/private/profiles/pan/pan_internal.h
                bluetooth/private/profiles/pan/pan_utils.c
                bluetooth/private/profiles/pan/pan_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/pan
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.pbap_pce.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/pbap/pbap_extern.h
                bluetooth/private/profiles/pbap/pbap_internal.h
                bluetooth/private/profiles/pbap/pbap_pce_api.c
                bluetooth/private/profiles/pbap/pbap_pce_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/pbap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.pbap_pse.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/pbap/pbap_extern.h
                bluetooth/private/profiles/pbap/pbap_internal.h
                bluetooth/private/profiles/pbap/pbap_pse_api.c
                bluetooth/private/profiles/pbap/pbap_pse_internal.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/pbap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.pbap_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/pbap/pbap_common_utils.c
                bluetooth/private/profiles/pbap/pbap_extern.h
                bluetooth/private/profiles/pbap/pbap_internal.h
                bluetooth/private/profiles/pbap/pbap_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/pbap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.sap_client.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/sap/sap_client.c
                bluetooth/private/profiles/sap/sap_internal.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/sap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.sap_server.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/sap/sap_internal.h
                bluetooth/private/profiles/sap/sap_server.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/sap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.sap_common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/sap/sap_internal.h
                bluetooth/private/profiles/sap/sap_common.c
                bluetooth/private/profiles/sap/sap_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/sap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.profiles.spp.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/profiles/spp/spp.c
                bluetooth/private/profiles/spp/spp_internal.h
                bluetooth/private/profiles/spp/spp_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/profiles/spp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3.common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3/private/fixed/common/lc3_common.c
                bluetooth/private/utils/lc3/private/fixed/common/lc3_defines.h
                bluetooth/private/utils/lc3/private/fixed/common/lc3_extern.h
                bluetooth/private/utils/lc3/private/fixed/common/lc3_fft.c
                bluetooth/private/utils/lc3/private/fixed/common/lc3_init.c
                bluetooth/private/utils/lc3/private/fixed/common/lc3_internal.h
                bluetooth/private/utils/lc3/private/fixed/common/lc3_math_util.c
                bluetooth/private/utils/lc3/private/fixed/common/lc3_tables.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3/private/fixed/common
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3.decoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3/private/fixed/decoder/lc3_decode.c
                bluetooth/private/utils/lc3/private/fixed/decoder/lc3_decoder_api.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3/private/fixed/decoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3.encoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3/private/fixed/encoder/lc3_encode.c
                bluetooth/private/utils/lc3/private/fixed/encoder/lc3_encoder_api.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3/private/fixed/encoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3_ndsp.common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_common.c
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_defines.h
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_extern.h
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_fft.c
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_init.c
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_internal.h
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_math_util.c
                bluetooth/private/utils/lc3_nodsp/private/fixed/common/lc3_ndsp_tables.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3_nodsp/private/fixed/common
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3_ndsp.decoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3_ndsp/private/fixed/decoder/lc3_ndsp_decode.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3_ndsp/private/fixed/decoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3_ndsp.encoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3_ndsp/private/fixed/encoder/lc3_ndsp_encode.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3_ndsp/private/fixed/encoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3_odsp.common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_common.c
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_defines.h
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_extern.h
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_fft.c
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_init.c
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_internal.h
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_math_util.c
                bluetooth/private/utils/lc3_optdsp/private/fixed/common/lc3_odsp_tables.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3_optdsp/private/fixed/common
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3_odsp.decoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3_optdsp/private/fixed/decoder/lc3_odsp_decode.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3_optdsp/private/fixed/decoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.lc3_odsp.encoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/lc3_optdsp/private/fixed/encoder/lc3_odsp_encode.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/lc3_optdsp/private/fixed/encoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.cmsis.files)
    mcux_add_source(
        SOURCES arm_math_types.h
                arm_math_memory.h
                arm_math.h
                dsp/*.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES CMSIS/DSP/Include
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.sbc.common.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/sbc/private/fixed/common/sbc_common.c
                bluetooth/private/utils/sbc/private/fixed/common/sbc_common_extern.h
                bluetooth/private/utils/sbc/private/fixed/common/sbc_version.h
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/sbc/private/fixed/common
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.sbc.decoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder.c
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_bitallocation.c
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_bitunpacking.c
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_extern.h
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_init.c
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_internal.h
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_ppsf.c
                bluetooth/private/utils/sbc/private/fixed/decoder/sbcdecoder_utils.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/sbc/private/fixed/decoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.private.utils.sbc.encoder.libFile)
    mcux_add_source(
        SOURCES bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder.c
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_bitallocation.c
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_bitpacking.c
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_extern.h
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_init.c
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_internal.h
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_ppaf.c
                bluetooth/private/utils/sbc/private/fixed/encoder/sbcencoder_scale_factor.c
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/private/utils/sbc/private/fixed/encoder
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.a2dp)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/a2dp/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/a2dp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.avrcp)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/avrcp/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/avrcp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.bip)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/bip/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/bip
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.bpp)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/bpp/*.*
                bluetooth/tools/resources/bpp/RUN_OF-BV-01-I-C_FROM_HERE/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/bpp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.ctn)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/ctn/*.*
                bluetooth/tools/resources/ctn/root/telecom/CTN/calendar/*.*
                bluetooth/tools/resources/ctn/root/telecom/CTN/notes/*.*
                bluetooth/tools/resources/ctn/root/telecom/CTN/tasks/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/ctn
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.ftp)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/ftp/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/ftp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.map)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/map/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/map
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.opp)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/opp/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/opp
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.pan)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/pan/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/pan
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()

if(CONFIG_MCUX_PRJSEG_middleware.wireless.ethermind.bluetooth.tools.resources.pbap)
    mcux_add_source(
        SOURCES bluetooth/tools/resources/pbap/phonebook/*.*
                bluetooth/tools/resources/pbap/phonebook/root/SIM1/telecom/cch/*.*
                bluetooth/tools/resources/pbap/phonebook/root/SIM1/telecom/fav/*.*
                bluetooth/tools/resources/pbap/phonebook/root/SIM1/telecom/mch/*.*
                bluetooth/tools/resources/pbap/phonebook/root/SIM1/telecom/och/*.*
                bluetooth/tools/resources/pbap/phonebook/root/SIM1/telecom/pb/*.*
                bluetooth/tools/resources/pbap/phonebook/root/SIM1/telecom/spd/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/cch/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/fav/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/ich/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/mch/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/och/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/pb/*.*
                bluetooth/tools/resources/pbap/phonebook/root/telecom/spd/*.*
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
    mcux_add_include(
        INCLUDES bluetooth/tools/resources/pbap
        BASE_PATH ${SdkRootDirPath}/middleware/wireless/ethermind/
    )
endif()
