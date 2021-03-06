PROJECT(VTKTIFF)
INCLUDE_REGULAR_EXPRESSION("^(tif|fax|port|uv|vtk|tconf|t4|mk|z).*$")

INCLUDE_DIRECTORIES(${VTKTIFF_SOURCE_DIR})

# library object files common to compression and decompression
SET(common_SRCS
tif_aux.c tif_close.c
tif_codec.c tif_compress.c tif_dir.c tif_dirinfo.c tif_dirread.c
tif_dirwrite.c tif_dumpmode.c tif_error.c tif_fax3.c tif_flush.c
tif_getimage.c tif_jpeg.c tif_luv.c tif_lzw.c tif_next.c
tif_ojpeg.c tif_open.c tif_packbits.c tif_pixarlog.c tif_predict.c
tif_print.c tif_read.c tif_strip.c tif_swab.c tif_thunder.c tif_tile.c
tif_version.c tif_warning.c
tif_write.c tif_zip.c)

ADD_DEFINITIONS( -DJPEG_SUPPORT -DZIP_SUPPORT -D_HPUX_SOURCE)

IF(WIN32)
  IF(BUILD_SHARED_LIBS)
    SET(TIFFDLL 1)
  ELSE(BUILD_SHARED_LIBS)
    SET(TIFFSTATIC 1)
  ENDIF(BUILD_SHARED_LIBS)
ENDIF(WIN32)

IF(NOT UNIX)
  ADD_DEFINITIONS( -DTIF_PLATFORM_CONSOLE )
  SET(common_SRCS ${common_SRCS} tif_win32.c fax3sm_winnt.c)
  IF (NOT BORLAND)
    IF(NOT MINGW)
      SET(common_SRCS ${common_SRCS} vtktiff.def)
    ENDIF(NOT MINGW) 
  ENDIF(NOT BORLAND)
ELSE (NOT UNIX)
  SET(common_SRCS ${common_SRCS} tif_unix.c tif_fax3sm.c)
  IF(NOT CMAKE_CROSSCOMPILING)
    ADD_EXECUTABLE(mkg3states mkg3states.c)
    EXPORT(TARGETS mkg3states FILE ${EXPORT_EXECUTABLES_FILE} NAMESPACE "${EXPORT_EXECUTABLES_NAMESPACE}" APPEND)
  ENDIF(NOT CMAKE_CROSSCOMPILING)

  GET_TARGET_PROPERTY(mkg3statesExe mkg3states LOCATION)

  ADD_CUSTOM_COMMAND(
    OUTPUT ${VTKTIFF_BINARY_DIR}/tif_fax3sm.c
    COMMAND ${mkg3statesExe}
    ARGS -c const ${VTKTIFF_BINARY_DIR}/tif_fax3sm.c
    DEPENDS mkg3states
    )
ENDIF (NOT UNIX)

CONFIGURE_FILE(${VTKTIFF_SOURCE_DIR}/.NoDartCoverage
               ${VTKTIFF_BINARY_DIR}/.NoDartCoverage)
CONFIGURE_FILE(${VTKTIFF_SOURCE_DIR}/tiffDllConfig.h.in
               ${VTKTIFF_BINARY_DIR}/tiffDllConfig.h)

ADD_LIBRARY(vtktiff ${common_SRCS})
TARGET_LINK_LIBRARIES( vtktiff ${VTK_ZLIB_LIBRARIES} ${VTK_JPEG_LIBRARIES} )

# Apply user-defined properties to the library target.
IF(VTK_LIBRARY_PROPERTIES)
  SET_TARGET_PROPERTIES(vtktiff PROPERTIES ${VTK_LIBRARY_PROPERTIES})
ENDIF(VTK_LIBRARY_PROPERTIES)

IF(NOT VTK_INSTALL_NO_LIBRARIES)
  INSTALL(TARGETS vtktiff
    RUNTIME DESTINATION ${VTK_INSTALL_BIN_DIR_CM24} COMPONENT RuntimeLibraries
    LIBRARY DESTINATION ${VTK_INSTALL_LIB_DIR_CM24} COMPONENT RuntimeLibraries
    ARCHIVE DESTINATION ${VTK_INSTALL_LIB_DIR_CM24} COMPONENT Development)
ENDIF(NOT VTK_INSTALL_NO_LIBRARIES)
IF(NOT VTK_INSTALL_NO_DEVELOPMENT)
  INSTALL(FILES
    ${VTKTIFF_BINARY_DIR}/tiffDllConfig.h
    ${VTKTIFF_SOURCE_DIR}/tiffvers.h
    ${VTKTIFF_SOURCE_DIR}/vtk_tiff_mangle.h
    ${VTKTIFF_SOURCE_DIR}/tiff.h
    ${VTKTIFF_SOURCE_DIR}/tiffio.h
    ${VTKTIFF_SOURCE_DIR}/tconf.h
    DESTINATION ${VTK_INSTALL_INCLUDE_DIR_CM24}/vtktiff
    COMPONENT Development)
ENDIF(NOT VTK_INSTALL_NO_DEVELOPMENT)
