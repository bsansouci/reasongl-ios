# Cheatsheet
# -----------------------------------------------------------------
#
# --- BUILD -------------------------------------------------------
# To build and run everything
# > make
#
# --- Faster Builds -----------------------------------------------
#
# Apparently you can run the following commands to make xcode build faster (depends on your config):
# > defaults write xcodebuild PBXNumberOfParallelBuildSubtasks `sysctl -n hw.ncpu`
# > defaults write xcodebuild IDEBuildOperationMaxNumberOfConcurrentCompileTasks `sysctl -n hw.ncpu`
# > defaults write com.apple.xcode PBXNumberOfParallelBuildSubtasks `sysctl -n hw.ncpu`
# > defaults write com.apple.xcode IDEBuildOperationMaxNumberOfConcurrentCompileTasks `sysctl -n hw.ncpu`
#
#
#
#
#
# --- create RAM disk --------------------------------------------
# To create and mount a RAM disk (in memory file system I think).
# > mkdir Build
# > hdid -nomount ram://4194304
# (look at number returned and use that intead of diskN below)
# > newfs_hfs -v Build /dev/rdisk2
# > diskutil mount -mountPoint `pwd`/Build /dev/disk2
#
#
#
# --- lldb --------------------------------------------------------
# Run lldb with the following command:
#
#   lldb -s defaultcommands
#
#
#
# Add breakpoint
# > breakpoint set --file bindings.m --line 240
#
# Remove breakpoint
# > breakpoint clear --file bindings.m --line 240
#
#
# Kinda useless now with `defaultcommands` but still good to remember:
# attach to running process (add -waitfor if you haven't booted the simulator yet)
# > process attach --name OCamlTest
#

DIR=$(shell pwd)

# Should be either 'iphonesimulator' or 'iphoneos'
SIMULATOR_OR_IOS_SDK=iphonesimulator

BUILD_DIR=$(DIR)/Build/Products/Debug-$(SIMULATOR_OR_IOS_SDK)

# Should be a valid version that you have.
VERSION=10.3

# I think this makes it build all architectures. Need to confirm that.
# ONLY_ACTIVE_ARCH='NO'

# Used by xcodebuild to figure out your deps.
WORKSPACE=OCamlTest/OCamlTest.xcworkspace

# Should be either 'Release' or 'Debug'
CONFIG=Debug
# Might not be needed but can be 'i386' or 'x86_64' for simulator and 'armv6' or 'armv7' or 'arm64' for devices.
ARCH=x86_64

# The scheme you want to build.
SCHEME=OCamlTest
APP_NAME=OCamlTest

# The ID of the device (can be a simulator ID or a physical device ID)
# DEVICE_ID=C798CC27-0B13-4B0F-87DF-FB2D1E515557

# The ID of your app to know what app to boot up.
BUNDLE_ID=com.sansouci.Reasongl


IOSMINREV = 7.0

HIDEOUT = /Applications/Xcode.app/Contents/Developer
TOOLDIR = $(HIDEOUT)/Toolchains/XcodeDefault.xctoolchain/usr/bin
PLT = $(HIDEOUT)/Platforms/iPhoneSimulator.platform
SDK = /Developer/SDKs/iPhoneSimulator.sdk
CURDIR = $(shell pwd)
OCAMLDIR = $(CURDIR)/bin/ocaml-iPhoneSimulator-64/release
OCAMLBIN = $(CURDIR)/bin/ocaml-host-64/release
CC = $(TOOLDIR)/clang -arch x86_64
CFLAGS = -isysroot $(PLT)$(SDK) -isystem $(OCAMLDIR)/lib/ocaml -DCAML_NAME_SPACE -I$(CURDIR)/OCamlTest/OCamlTest -I$(OCAMLDIR)/lib/ocaml -fno-objc-arc -miphoneos-version-min=$(IOSMINREV)
OCAMLOPT = $(OCAMLBIN)/bin/ocamlopt -pp 'refmt --print binary' -I $(CURDIR) -ccopt -isysroot -ccopt $(PLT)$(SDK)
# MFLAGS = -fobjc-legacy-dispatch -fobjc-abi-version=2
MLFLAGS = -c -I Build

C_FILES = CBindings
RE_FILES = RGLConstants GLConstants Bindings Reasongl PurpleRain

C_FILES_PATH=$(addprefix Build/, $(addsuffix .o, $(C_FILES)))
RE_FILES_PATH=$(addprefix Build/, $(addsuffix .cmx, $(RE_FILES)))

app:: TestApp

build:: TestApp deploy-simulator


deploy-simulator:
	## Boot the simulator if there's not one already booted
	(xcrun simctl list | grep '(Booted)' -q) || open -a "Simulator" --args -CurrentDeviceUDID $(DEVICE_ID)

	./waitforsimulator.sh

	## Install the app
	xcrun simctl install booted $(BUILD_DIR)/$(APP_NAME).app

	## Launch the app without deps on ios-deploy
	xcrun simctl launch --console booted $(BUNDLE_ID)

TestApp: Build $(C_FILES_PATH) $(RE_FILES_PATH)
		$(OCAMLOPT) $(C_FILES_PATH) $(RE_FILES_PATH) -output-obj -o Build/re_output.o
		cp $(OCAMLDIR)/lib/ocaml/libasmrun.a Build/libGobi.a
		ar -r Build/libGobi.a $(C_FILES_PATH) Build/re_output.o
		## Build the workspace
		time xcodebuild \
			-scheme $(SCHEME)\
			-workspace $(WORKSPACE)\
			-configuration $(CONFIG)\
			-arch $(ARCH)\
			-sdk $(SIMULATOR_OR_IOS_SDK)$(VERSION)\
			build\
			CONFIGURATION_BUILD_DIR=$(BUILD_DIR)

Build:
	mkdir -p Build/src

clean::
		rm -f TestApp *.o *.cm[iox]
		rm -rf Build

Build/%.o: src/%.m
		cp $< Build/$<
		$(CC) $(CFLAGS) $(MFLAGS) -c -o $@ Build/$<

Build/%.cmi: src/%.rei
		cp $< Build/$<
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl Build/$<

Build/%.cmo: src/%.re
		cp $< Build/$<
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl Build/$<

Build/%.cmx: src/%.re
		cp $< Build/$<
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl Build/$<

depend::
		$(OCAMLBIN)/bin/ocamldep -pp 'refmt --print binary' -ml-synonym .re  -I ./ *.re > MLDepend
		$(CC) $(CFLAGS) $(MFLAGS) -MM *.m > MDepend

-include MLDepend
-include MDepend
