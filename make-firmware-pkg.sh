#!/bin/bash

set -o errexit   # abort on nonzero exitstatus
set -o pipefail  # don't hide errors within pipes

source fw-package.env

# get name and version from build
proj_name=$(awk 'match($0,/PROJECT_NAME=\\"[a-z0-9\-]+\\"/) { print substr($0,RSTART+15,RLENGTH-17)}' build/build.ninja)
PKG_VERSION=$(awk 'match($0,/PROJECT_VER=\\"[\.a-z0-9\-]+\\"/) { print substr($0,RSTART+14,RLENGTH-16)}' build/build.ninja)

# get variant/short_hw_name/binary name from idf CMakeLists
PKG_VARIANT=$(echo ${proj_name} | cut -d - -f 3- )
PKG_FIRMWARE_BINARY=${proj_name}.bin

echo PKG_FIRMWARE_BINARY=${PKG_FIRMWARE_BINARY}
echo PKG_FULL_HW_NAME=${PKG_FULL_HW_NAME}
echo PKG_VARIANT=${PKG_VARIANT}
echo PKG_VERSION=${PKG_VERSION}
echo PKG_COMPATIBLE_MAJOR_REVS=${PKG_COMPATIBLE_MAJOR_REVS}

wget -q https://raw.githubusercontent.com/ci4rail/firmware-ota/${PKG_FIRMWARE_OTA_COMMIT_ID}/tools/make-fwpkg/io4edge-make-fwpkg.sh -O build/io4edge-make-fwpkg.sh
chmod +x build/io4edge-make-fwpkg.sh

cd build
./io4edge-make-fwpkg.sh ${PKG_FIRMWARE_BINARY} ${PKG_FULL_HW_NAME} ${PKG_VARIANT} ${PKG_VERSION} ${PKG_COMPATIBLE_MAJOR_REVS}
