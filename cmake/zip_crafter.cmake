# Package up all the files for a release. This is to be run as part of a CI job.
if(ZIP_RELEASE)
	if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		set(RELEASE_OS "linux")
	elseif(APPLE)
		set(RELEASE_OS "mac")
	elseif(WIN32)
		set(RELEASE_OS "windows")
	else()
		set(RELEASE_OS ${CMAKE_SYSTEM_NAME})
	endif()
	set(RELEASE_NAME "ccc_${GIT_TAG}_${RELEASE_OS}")
	add_custom_target(releasezip ALL
		COMMAND
			${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/${RELEASE_NAME}" &&
			${CMAKE_COMMAND} -E copy ${RELEASE_CONTENTS} "${CMAKE_BINARY_DIR}/${RELEASE_NAME}" &&
			${CMAKE_COMMAND} -E tar "cfv" "${RELEASE_NAME}.zip" --format=zip ${CMAKE_BINARY_DIR}/"${RELEASE_NAME}"
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
	)
endif()
