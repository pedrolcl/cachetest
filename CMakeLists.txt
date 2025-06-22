cmake_minimum_required(VERSION 3.16)

project(cachetest LANGUAGES C)

if(DEFINED ENV{TEMP})
    set(TEMPDIR "$ENV{TEMP}")
else()
    message(FATAL_ERROR "Cannot find a temporary directory. Define the TEMP environment variable.")
endif()

set(SOUNDFONT "${TEMPDIR}/soundfont.dls")
if (NOT EXISTS ${SOUNDFONT})
    message(STATUS "Downloading DLS file for testing to ${SOUNDFONT}")
    file(DOWNLOAD "http://www.ronimusic.com/sf2/Airfont_340.dls" ${SOUNDFONT})
endif()

file(SIZE ${SOUNDFONT} SOUNDFONTSIZE)
file(MD5 ${SOUNDFONT} SOUNDFONTHASH)
message(STATUS "DLS file ${SOUNDFONT} size: ${SOUNDFONTSIZE}")
message(STATUS "DLS file ${SOUNDFONT} MD5 hash: ${SOUNDFONTHASH}")
if (NOT (SOUNDFONTSIZE EQUAL 81362584 AND SOUNDFONTHASH STREQUAL "40c0cd4ad29ae411a8fc3d6681002a2b"))
    message(FATAL_ERROR "The downloaded DLS file is corrupted.")
endif()

add_executable(cachetest main.c)

enable_testing(TRUE)
add_test(SIMPLE cachetest)
