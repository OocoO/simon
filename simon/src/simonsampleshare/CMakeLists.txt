set(simonsampleshare_LIB_SRCS
  sampleshare.cpp
  simonsampledataprovider.cpp
)

set(simonsampleshare_LIB_HDRS sampleshare.h)

kde4_add_ui_files(simonsampleshare_LIB_SRCS sampleshare.ui)

kde4_add_library(simonsampleshare SHARED ${simonsampleshare_LIB_SRCS})

target_link_libraries(simonsampleshare ${QT_LIBRARIES} sscdaccess
  ${KDE4_KDEUI_LIBS} sscobjects simonscenarios simonuicomponents simonprogresstracking)

set_target_properties(simonsampleshare PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})

install(FILES ${simonsampleshare_LIB_HDRS} DESTINATION ${INCLUDE_INSTALL_DIR}/simon/simonsampleshare COMPONENT simondevel)

install( TARGETS simonsampleshare DESTINATION ${SIMON_LIB_INSTALL_DIR} COMPONENT simon )
