#! /bin/bash

clear

rootdir=$rootdir

#rmdir "$rootdir/build"
if [ ! -d "$rootdir/build" ]; then
    mkdir "$rootdir/build"

fi
cd "$rootdir/build"
cmake ..
make

#echo " "
#echo "Installing into X-Plane"
#echo " "
#xpfolder="/media/X-Plane/X-Plane_12_Testing"
#
#if [ ! -f "$xpfolder/Resources/dlls/64/libopenvr_api.steamvr" ]; then
# echo "Backing up original libopenvr_api.so"
# mv "$xpfolder/Resources/dlls/64/libopenvr_api.so" "$xpfolder/Resources/dlls/64/libopenvr_api.steamvr"
#fi
#
#echo "Replacing X-Plane's libopenvr_api.so with compiled version"
#cp "$(pwd)/bin/linux64/vrclient.so" "$xpfolder/Resources/dlls/64/libopenvr_api.so"
#
#echo " "
#echo "Done."

mv "$(pwd)/bin/linux64/vrclient.so" "$rootdir/build/libopenvr_api.so"

echo " "
echo " "
echo "Build script is done."
