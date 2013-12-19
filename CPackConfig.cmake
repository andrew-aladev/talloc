set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Lightweight implementation of simplified talloc api")
set (CPACK_PACKAGE_VERSION ${TRALLOC_VERSION})
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set (CPACK_RESOURCE_FILE_README  "${PROJECT_SOURCE_DIR}/README.rst")

set (CPACK_GENERATOR "DEB" "RPM")

set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrew Aladjev <aladjev.andrew@gmail.com>")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "")

set (CPACK_RPM_PACKAGE_REQUIRES "")

set (CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set (CPACK_STRIP_FILES true)