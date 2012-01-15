#!/bin/bash

# use this script in the Scheme Config
# set it in Build Phase to a Script in Pre-Build section

# Auto Increment Version Script
cd "${SRCROOT}"

stdout="${SRCROOT}/build-set-info.log"
stderr="${SRCROOT}/build-set-info.log"

buildPlist="${INFOPLIST_FILE}"


CFBuildNumber=$(/usr/libexec/PlistBuddy -c "Print CFBuildNumber" "$buildPlist")
CFOldBuildNumber=$CFBuildNumber
CFBuildNumber=$(($CFBuildNumber + 1))
/usr/libexec/PlistBuddy -c "Set :CFBuildNumber $CFBuildNumber" "$buildPlist"

CFBuildBaseVersion=$(/usr/libexec/PlistBuddy -c "Print CFBuildBaseVersion" "$buildPlist")

BuildNumber=$(printf "%02d" $CFBuildNumber)
CFBundleVersion="$CFBuildBaseVersion.$BuildNumber"

/usr/libexec/PlistBuddy -c "Set :CFBundleVersion $CFBundleVersion" "$buildPlist"
/usr/libexec/PlistBuddy -c "Set :CFBundleShortVersionString $CFBuildBaseVersion" "$buildPlist"

CFBuildDate="$(date +%Y-%m-%d\ %H:%M:%S)"

/usr/libexec/PlistBuddy -c "Set :CFBuildDate $CFBuildDate" "$buildPlist"

touch "$buildPlist"
CFNewBuildNumber=$(/usr/libexec/PlistBuddy -c "Print CFBuildNumber" "$buildPlist")
echo "Set Build Date and Number in '$buildPlist' from $CFOldBuildNumber to $CFNewBuildNumber"