set(sscsettings_LIB_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/sscconfiguration.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/plugin_exporter.cpp
)

kde4_add_kcfg_files(sscsettings_LIB_SRCS sscconfig.kcfgc)

kde4_add_ui_files(sscsettings_LIB_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/sscconfiguration.ui
)

kde4_add_plugin(sscsettings ${sscsettings_LIB_SRCS})

target_link_libraries(sscsettings ${QT_LIBRARIES} ${QT_LIBRARIES}
  ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} sscdaccess)

install(TARGETS sscsettings DESTINATION ${PLUGIN_INSTALL_DIR} COMPONENT ssc)
install(FILES sscconfiguration.desktop DESTINATION ${SERVICES_INSTALL_DIR} COMPONENT ssc)
