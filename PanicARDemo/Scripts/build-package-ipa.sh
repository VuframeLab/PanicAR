#!/bin/bash

echo "BuildIPA in ${SRCROOT}"

cd "${SRCROOT}"

stdout="${SRCROOT}/build-package-ipa.log"
stderr="${SRCROOT}/build-package-ipa.log"

APPLICATION_SRC="${TARGET_BUILD_DIR}/${PRODUCT_NAME}.app"
echo ${APPLICATION_SRC}


buildPlist="${INFOPLIST_FILE}"
CFBundleVersion=$(/usr/libexec/PlistBuddy -c "Print CFBundleVersion" "$buildPlist")
echo "build: ${CFBundleVersion}"

# TARGET_BASE="${SRCROOT}/Deploy/${PRODUCT_NAME}_build${BuildNumber}_$(date +%Y-%m-%d_%H-%M-%S)"
TARGET_BASE="${SRCROOT}/Deploy/${PRODUCT_NAME}_${CFBundleVersion}_${CONFIGURATION}"
TARGET_IPA="${TARGET_BASE}.ipa"
TARGET_TXT="${TARGET_BASE}.txt"
echo ${TARGET_IPA}

DATE=$(date +%Y-%m-%d\ %H:%M:%S)
echo -e "${PRODUCT_NAME}: build ${CFBundleVersion}, ${DATE}" > "${TARGET_TXT}"


echo "${CODE_SIGN_IDENTITY}"
/usr/bin/xcrun -sdk iphoneos PackageApplication -v "${APPLICATION_SRC}" -o "${TARGET_IPA}" --sign "${CODE_SIGN_IDENTITY}"
# --embed "${PPROFILE}"

echo "$PWD"
git tag -a -m "${PRODUCT_NAME}" "${CFBundleVersion}"