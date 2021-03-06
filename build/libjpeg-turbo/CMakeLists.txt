SET(SRC ${3RDPARTY_DIR}/libjpeg-turbo)

SET(JPEG_LIB_VERSION 80)
SET(DLL_VERSION 8)
SET(FULLVERSION ${DLL_VERSION}.0.2)
CONFIGURE_FILE(${SRC}/win/jconfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h)
CONFIGURE_FILE(${SRC}/win/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

SET(SOURCE_FILES
	${SRC}/jcapimin.c
	${SRC}/jcapistd.c
	${SRC}/jccoefct.c
	${SRC}/jccolor.c
	${SRC}/jcdctmgr.c
	${SRC}/jchuff.c
	${SRC}/jcinit.c
	${SRC}/jcmainct.c
	${SRC}/jcmarker.c
	${SRC}/jcmaster.c
	${SRC}/jcomapi.c
	${SRC}/jcparam.c
	${SRC}/jcphuff.c
	${SRC}/jcprepct.c
	${SRC}/jcsample.c
	${SRC}/jctrans.c
	${SRC}/jdapimin.c
	${SRC}/jdapistd.c
	${SRC}/jdatadst.c
	${SRC}/jdatasrc.c
	${SRC}/jdcoefct.c
	${SRC}/jdcolor.c
	${SRC}/jddctmgr.c
	${SRC}/jdhuff.c
	${SRC}/jdinput.c
	${SRC}/jdmainct.c
	${SRC}/jdmarker.c
	${SRC}/jdmaster.c
	${SRC}/jdmerge.c
	${SRC}/jdphuff.c
	${SRC}/jdpostct.c
	${SRC}/jdsample.c
	${SRC}/jdtrans.c
	${SRC}/jerror.c
	${SRC}/jfdctflt.c
	${SRC}/jfdctfst.c
	${SRC}/jfdctint.c
	${SRC}/jidctflt.c
	${SRC}/jidctfst.c
	${SRC}/jidctint.c
	${SRC}/jidctred.c
	${SRC}/jquant1.c
	${SRC}/jquant2.c
	${SRC}/jutils.c
	${SRC}/jmemmgr.c
	${SRC}/jmemnobs.c
	${SRC}/transupp.c
)

SET(NAFLAGS -I${SRC}/simd/)

IF(MSVC)
	SET(NAFLAGS ${NAFLAGS} -DMSVC)
	SET(SIMDEXT .obj)
ELSE()
	SET(SIMDEXT .o)
ENDIF()

IF(X64)
	SET(SOURCE_FILES ${SOURCE_FILES} ${SRC}/simd/jsimd_x86_64.c)
	SET(SIMD_BASENAMES jfsseflt-64 jccolss2-64 jdcolss2-64 jcgrass2-64
		jcsamss2-64 jdsamss2-64 jdmerss2-64 jcqnts2i-64 jfss2fst-64 jfss2int-64
		jiss2red-64 jiss2int-64 jiss2fst-64 jcqnts2f-64 jiss2flt-64)
	IF(WIN32)
		SET(NAFLAGS ${NAFLAGS} -fwin64 -DWIN64 -D__x86_64__)
	ELSE()
		SET(NAFLAGS ${NAFLAGS} -felf64 -DELF -D__x86_64__)
	ENDIF()
ELSE()
	SET(SOURCE_FILES ${SOURCE_FILES} ${SRC}/simd/jsimd_i386.c)
	SET(SIMD_BASENAMES jsimdcpu jccolmmx jcgrammx jdcolmmx jcsammmx jdsammmx
		jdmermmx jcqntmmx jfmmxfst jfmmxint jimmxred jimmxint jimmxfst jcqnt3dn
		jf3dnflt ji3dnflt jcqntsse jfsseflt jisseflt jccolss2 jcgrass2 jdcolss2
		jcsamss2 jdsamss2 jdmerss2 jcqnts2i jfss2fst jfss2int jiss2red jiss2int
		jiss2fst jcqnts2f jiss2flt)
	IF(WIN32)
		SET(NAFLAGS ${NAFLAGS} -fwin32 -DWIN32)
	ELSE()
		SET(NAFLAGS ${NAFLAGS} -felf -DELF)
	ENDIF()
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SOURCE_GROUP("Source Files" FILES ${SOURCE_FILES})

FILE(GLOB INC_FILES *.inc)

FOREACH(FILE ${SIMD_BASENAMES})
	SET(DEPFILE "")
	SET(SIMD_SRC ${SRC}/simd/${FILE}.asm)
	IF(${FILE} MATCHES col)
		SET(DEPFILE ${SIMD_SRC})
		STRING(REGEX REPLACE "col" "clr" DEPFILE ${DEPFILE})
	ENDIF()
	IF(${FILE} MATCHES mer)
		SET(DEPFILE ${SIMD_SRC})
		STRING(REGEX REPLACE "mer" "mrg" DEPFILE ${DEPFILE})
	ENDIF()
	IF(${FILE} MATCHES gra)
		SET(DEPFILE ${SIMD_SRC})
		STRING(REGEX REPLACE "gra" "gry" DEPFILE ${DEPFILE})
	ENDIF()
	SET(SIMD_OBJ ${CMAKE_CURRENT_BINARY_DIR}/${FILE}.obj)
	ADD_CUSTOM_COMMAND(OUTPUT ${SIMD_OBJ}
    		DEPENDS ${SIMD_SRC} ${DEPFILE} ${INC_FILES}
    		COMMAND yasm ${NAFLAGS} ${SIMD_SRC} -o${SIMD_OBJ})
	SET(SIMD_OBJS ${SIMD_OBJS} ${SIMD_OBJ})
ENDFOREACH()

ADD_DEFINITIONS(-DWITH_SIMD)

ADD_LIBRARY(libjpeg-turbo STATIC ${SOURCE_FILES} ${SIMD_OBJS})
