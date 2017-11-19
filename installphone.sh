CURDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export TOOLCHAIN_BIN=/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin
export MIN_IOS_VERSION=9.3
# PLATFORMS=(iPhoneSimulator iPhoneOS)
# ARCHS32=(i386 arm)
# SUBARCHS32=(i386 armv7)
# ARCHS64=(amd64 arm64)
# SUBARCHS64=(x86_64 arm64)

# for BITS in 64 32
# do
# 	SUBARCHS=SUBARCHS${BITS}[@]
# 	SUBARCHS=( "${!SUBARCHS}" )
# 	ARCHS=ARCHS${BITS}[@]
# 	ARCHS=( "${!ARCHS}" )
# 	export HOST_BIN=$(pwd)/bin/ocaml-host-${BITS}/release/bin
# 	echo ${HOST_BIN}
# 	for i in 0 1
# 	do
# 		export PLATFORM=${PLATFORMS[i]}
# 		export ARCH=${ARCHS[i]}
# 		export SUBARCH=${SUBARCHS[i]}
# 		COMPILER_DIR=$(pwd)/bin/ocaml-${PLATFORM}-${BITS}
# 		cp -R bin/ocaml-ios ${COMPILER_DIR}
# 		cd ${COMPILER_DIR}
# 		export PREFIX=$(pwd)
# 		make world opt install || exit $?
# 		cd ../..
# 	done
# done
BITS=64
export SHARPBANGSCRIPTS=false
export PLATFORM=iPhoneOS
export ARCH=arm64
export SUBARCH=arm64
export HOST_BIN=$CURDIR/bin/ocaml-host-${BITS}/release/bin
echo ${HOST_BIN}
COMPILER_DIR=$CURDIR/bin/ocaml-${PLATFORM}-${BITS}
cp -R bin/ocaml-ios ${COMPILER_DIR}
cd ${COMPILER_DIR}
export PREFIX=$(pwd)
make world opt install || exit $?
cd ../..

