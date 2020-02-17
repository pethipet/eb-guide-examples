#functions for platform detection

macro(eb_test_and_set VAR_NAME VALUE PARENT_SCOPE)
    if(NOT ${VAR_NAME})
        set(${VAR_NAME} ${VALUE} ${PARENT_SCOPE})
    endif()
endmacro()

function(eb_determine_arch_vs)
    if(CMAKE_GENERATOR MATCHES "ARMV4I")
        eb_test_and_set(EB_PLATFORM_ARCH ARM PARENT_SCOPE)
        set(EBProduct_Arch  "ARMV4I"         PARENT_SCOPE)
    elseif(CMAKE_GENERATOR MATCHES "SH4")
        eb_test_and_set(EB_PLATFORM_ARCH SH4 PARENT_SCOPE)
        set(EBProduct_Arch "SH4"             PARENT_SCOPE)
    elseif(CMAKE_GENERATOR MATCHES "Win64")
        eb_test_and_set(EB_PLATFORM_ARCH X64 PARENT_SCOPE)
        set(EBProduct_Arch "x64"             PARENT_SCOPE)
    else()
        eb_test_and_set(EB_PLATFORM_ARCH X86 PARENT_SCOPE)
        set(EBProduct_Arch  "x86"            PARENT_SCOPE)
    endif()
endfunction(eb_determine_arch_vs)

function(eb_determine_sdk_vs)
    if(CMAKE_GENERATOR MATCHES "Visual Studio [0-9]+ 20[0-9][0-9]$")
        eb_test_and_set(EB_PLATFORM_OS "Win32" PARENT_SCOPE)
    elseif(CMAKE_GENERATOR MATCHES "Visual Studio [0-9]+$")
        eb_test_and_set(EB_PLATFORM_OS "Win32" PARENT_SCOPE)
    elseif(CMAKE_GENERATOR MATCHES "Visual Studio [0-9][0-9] Win64$")
        eb_test_and_set(EB_PLATFORM_OS "Win64" PARENT_SCOPE)
    elseif(CMAKE_GENERATOR MATCHES "Visual Studio [0-9]+ 20[0-9][0-9] Win64$")
        eb_test_and_set(EB_PLATFORM_OS "Win64" PARENT_SCOPE)
    else()
        MESSAGE(FATAL_ERROR "CMAKE_GENERATOR : '${CMAKE_GENERATOR}' not supported")
    endif()
endfunction(eb_determine_sdk_vs)

function(eb_determine_arch_gcc)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM")
        eb_test_and_set(EB_PLATFORM_ARCH ARM PARENT_SCOPE)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "SH4")
        eb_test_and_set(EB_PLATFORM_ARCH SH4 PARENT_SCOPE)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "[xX]86")
        eb_test_and_set(EB_PLATFORM_ARCH X86 PARENT_SCOPE)
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "i686")
        eb_test_and_set(EB_PLATFORM_ARCH X86 PARENT_SCOPE)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "[xX]64")
        eb_test_and_set(EB_PLATFORM_ARCH X64 PARENT_SCOPE)
    else()
        message(FATAL_ERROR "unsupported architecture. CMAKE_SYSTEM_PROCESSOR is '${CMAKE_SYSTEM_PROCESSOR}'")
    endif()
endfunction(eb_determine_arch_gcc)

macro(eb_determine_platform_variable VAR_NAME)
    if(${VAR_NAME})
        STRING(TOUPPER ${${VAR_NAME}} VAR_CONTENT)
        set(${VAR_NAME}_${VAR_CONTENT} TRUE)
        message(STATUS "${VAR_NAME}: ${${VAR_NAME}}")
    else()
        set(${VAR_NAME} unknown)
        message(FATAL_ERROR "${VAR_NAME}: ${${VAR_NAME}}")
    endif()
endmacro()

macro(eb_determine_platform)
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        eb_determine_arch_vs()
        eb_determine_sdk_vs()
        eb_test_and_set(EB_PLATFORM_OS_FAMILY "Windows" "")
    elseif(CMAKE_GENERATOR MATCHES "Unix" OR CMAKE_GENERATOR MATCHES "Ninja")
        eb_determine_arch_gcc()
        if(CMAKE_SYSTEM_NAME MATCHES "QNX")
            eb_test_and_set(EB_PLATFORM_OS QNX "")
            eb_test_and_set(EB_PLATFORM_OS_FAMILY POSIX "")
        elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
            eb_test_and_set(EB_PLATFORM_OS "Linux" "")
            eb_test_and_set(EB_PLATFORM_OS_FAMILY POSIX "")
        elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
            eb_test_and_set(EB_PLATFORM_OS_FAMILY "Windows" "")
        elseif(CMAKE_SYSTEM_NAME STREQUAL TKERNEL)
            eb_test_and_set(EB_PLATFORM_OS TKERNEL "")
            eb_test_and_set(EB_PLATFORM_OS_FAMILY TKERNEL "")
        endif()
    endif()

    # -------------------------------
    # Create platform variables and print status messages
    eb_determine_platform_variable(EB_PLATFORM_ARCH)
    eb_determine_platform_variable(EB_PLATFORM_OS_FAMILY)
    eb_determine_platform_variable(EB_PLATFORM_OS)

    CMAKE_DEPENDENT_OPTION(EB_PLATFORM_ARCH_ARM_NEON "enable ARM NEON support" OFF EB_PLATFORM_ARCH_ARM OFF)
    CMAKE_DEPENDENT_OPTION(EB_PLATFORM_ARCH_ARM_A64 "enable ARM A64 support" OFF EB_PLATFORM_ARCH_ARM OFF)
endmacro()

#perform platform detection
eb_determine_platform()
