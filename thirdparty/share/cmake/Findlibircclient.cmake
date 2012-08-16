#
# /usr/lib/libircclient.a
# /usr/include/libircclient/libirc_errors.h
# /usr/include/libircclient/libirc_rfcnumeric.h
# /usr/include/libircclient/libirc_options.h
# /usr/include/libircclient/libircclient.h
# /usr/include/libircclient/libirc_events.h
#

FIND_PATH(libircclient_INCLUDE_DIR NAMES libircclient/libircclient.h)
MARK_AS_ADVANCED(libircclient_INCLUDE_DIR)

FIND_LIBRARY(libircclient_LIBRARY NAMES ircclient)
MARK_AS_ADVANCED(libircclient_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(libircclient DEFAULT_MSG libircclient_LIBRARY libircclient_INCLUDE_DIR)

IF ("${libircclient_INCLUDE_DIR}" MATCHES "NOTFOUND")
	SET (libircclient_LIBRARY)
	SET (libircclient_INCLUDE_DIR)
ELSEIF ("${libircclient_LIBRARY}" MATCHES "NOTFOUND")
	SET (libircclient_LIBRARY)
	SET (libircclient_INCLUDE_DIR)
ELSE ("${libircclient_INCLUDE_DIR}" MATCHES "NOTFOUND")
	SET (libircclient_FOUND 1)
	SET (libircclient_LIBRARIES ${libircclient_LIBRARY})
	SET (libircclient_INCLUDE_DIRS ${libircclient_INCLUDE_DIR})
ENDIF ("${libircclient_INCLUDE_DIR}" MATCHES "NOTFOUND")
