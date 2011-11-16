# - Try to find dsound.dll
# Once done this will define
#
#  DIRECTSOUND_FOUND - system has direct sound
#  DIRECTSOUND_INCLUDE_DIR - include directory
#  DIRECTSOUND_LIBRARY - Link these to use direct sound

# Copyright (c) 2008-2011, Peter Grasch, <grasch@simon-listens.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.


FIND_PATH(DIRECTSOUND_INCLUDE_DIR dsound.h PATHS
		${CMAKE_CURRENT_SOURCE_DIR} 
    "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
    )

FIND_PATH(DIRECTSOUND_SAL_INCLUDE_DIR sal.h PATHS
		${CMAKE_CURRENT_SOURCE_DIR} 
    "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
    "C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/include"
    )



FIND_LIBRARY(_DSOUD_LIB NAMES dsound )

FIND_LIBRARY(_DXGUID_LIB NAMES dxguid PATHS
     ${CMAKE_CURRENT_SOURCE_DIR}
     "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86" #TODO:better esearch path ant cosinder achitecture
     C:/Windows/system32)

SET (DIRECTSOUND_LIBRARY ${_DSOUD_LIB} ${_DXGUID_LIB} )

set(DIRECTSOUND_INCLUDE_DIRS ${DIRECTSOUND_INCLUDE_DIR})# ${DIRECTSOUND_SAL_INCLUDE_DIR})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DIRECTSOUND DEFAULT_MSG DIRECTSOUND_LIBRARY)

if (DIRECTSOUND_FOUND)
	if (NOT DIRECTSOUND_FIND_QUIETLY)
		message(STATUS "Found dsound: ${DIRECTSOUND_LIBRARY}")
	endif (NOT DIRECTSOUND_FIND_QUIETLY)
	
else (DIRECTSOUND_FOUND)
	if (DIRECTSOUND_FIND_QUIETLY)
		message(FATAL_ERROR "Could not find dsound.dll! Please COPY C:/Windows/system32/dsound.dll to ${CMAKE_CURRENT_SOURCE_DIR}, rename it to dsound_simon.dll and try again!")
	endif (DIRECTSOUND_FIND_QUIETLY)
endif (DIRECTSOUND_FOUND)


MARK_AS_ADVANCED(DIRECTSOUND_LIBRARY)

