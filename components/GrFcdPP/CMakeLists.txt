# Gnuradio FunCube Pro+ component

message(STATUS "${Boost_LIBRARIES}")

set(ENABLE_FCDPP 1)
set(FCD_LIB_PATH ${GR_OSMOSDR_SOURCE_DIR}/lib/fcd)


# Libs
list(APPEND OSMO_MODULE_LIBRARIES SoapyOsmoSDR)
list(APPEND OSMO_MODULE_LIBRARIES ${Boost_LIBRARIES})
list(APPEND OSMO_MODULE_LIBRARIES ${FCD_LIB_PATH})

# Includes
include_directories(${GNURADIO_FCDPP_INCLUDE_DIRS})
include_directories(${FCD_LIB_PATH})

# Sources
file(GLOB glob_srcs "${FCD_LIB_PATH}/*.cc")
list(APPEND OSMO_MODULE_SOURCES ${glob_srcs})

SOAPY_SDR_MODULE_UTIL(
    TARGET GrFcdProPlusSupport
    SOURCES ${OSMO_MODULE_SOURCES}
    LIBRARIES ${OSMO_MODULE_LIBRARIES}
)