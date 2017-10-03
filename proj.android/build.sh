#! /bin/sh

ndk-build
cat local.properties > sdk.dir=/Users/skalexey/bin/android-sdk
ant debug install

