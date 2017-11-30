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

CURDIR = $(shell pwd)

# This section is for simulator. Uncomment the next section to build to device
SIMULATOR_OR_IOS_SDK=iphonesimulator
ARCH=x86_64
PLT = $(HIDEOUT)/Platforms/iPhoneSimulator.platform
SDK = /Developer/SDKs/iPhoneSimulator.sdk
OCAMLDIR = $(CURDIR)/bin/ocaml-iPhoneSimulator-64/release
OCAMLBIN = $(CURDIR)/bin/ocaml-host-64/release



# NOTE: Currently, if you want to build for device, you'll need to have opam installed
# and set up gobi (https://github.com/saschatimme/gobi - follow the Readme through
# gobi_setup).
# TODO(jared): Get our iphoneos stuff building an ios-sysroot, so we don't depend on gobi

# Uncomment this section to build to device
SIMULATOR_OR_IOS_SDK=iphoneos
ARCH=arm64
PLT = $(HIDEOUT)/Platforms/iPhoneOS.platform
SDK = /Developer/SDKs/iPhoneOS.sdk
OCAMLDIR = ~/.opam/4.04.0+ios+arm64/ios-sysroot
OCAMLBIN = ~/.opam/4.04.0+ios+arm64/ios-sysroot





BUILD_DIR=$(CURDIR)/Build/Products/Debug-$(SIMULATOR_OR_IOS_SDK)

# Should be a valid version that you have.
VERSION=11.1

# I think this makes it build all architectures. Need to confirm that.
# ONLY_ACTIVE_ARCH='NO'

# Used by xcodebuild to figure out your deps.
WORKSPACE=OCamlTest/OCamlTest.xcworkspace

# Should be either 'Release' or 'Debug'
CONFIG=Debug

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



CC = $(TOOLDIR)/clang -arch $(ARCH)
CFLAGS = -isysroot $(PLT)$(SDK) -isystem $(OCAMLDIR)/lib/ocaml -DCAML_NAME_SPACE -I$(CURDIR)/OCamlTest/OCamlTest -I$(OCAMLDIR)/lib/ocaml/caml -I$(OCAMLDIR)/lib/ocaml -I$(OCAMLDIR)/../stdlib/ -fno-objc-arc -miphoneos-version-min=$(IOSMINREV)
OCAMLOPT = $(OCAMLBIN)/bin/ocamlopt -pp 'refmt --print binary' -I $(CURDIR) -no-alias-deps -ccopt -isysroot -ccopt $(PLT)$(SDK)
MLFLAGS = -c -I Build/src -I Build/reasongl-interface/src -I Build/reprocessing/src -I $(OCAMLDIR)/lib/ocaml bigarray.cmxa

C_FILES = CTgls CBindings bigarray_stubs mmap_unix
REASONGL_INTERFACE_FILES = RGLConstants RGLEvents RGLInterface ReasonglInterface
REASONGL_FILES = GLConstants Bindings Tgls Reasongl
REPROCESSING_FILES = Reprocessing_Events Reprocessing_Common Reprocessing_Constants Reprocessing_Matrix Reprocessing_Shaders Reprocessing_Internal Reprocessing_Font Reprocessing_Types Reprocessing_Utils Reprocessing_Hotreload Reprocessing_Env Reprocessing_Draw Reprocessing_ClientWrapper Reprocessing
REPROCESSING_LITE_FILES = Reprocessing_lite Reprocessing_lite_Utils Reprocessing_lite_Draw
APP_FILES= ${REPROCESSING_LITE_FILES} FlappyBird

C_FILES_PATH=$(addprefix Build/src/, $(addsuffix .o, $(C_FILES)))
RE_FILES_PATH=\
	$(addprefix Build/reasongl-interface/src/, $(addsuffix .cmx, $(REASONGL_INTERFACE_FILES))) \
	$(addprefix Build/src/, $(addsuffix .cmx, $(REASONGL_FILES))) \
	$(addprefix Build/reprocessing/src/, $(addsuffix .cmx, $(REPROCESSING_FILES))) \
	$(addprefix Build/src/, $(addsuffix .cmx, $(APP_FILES)))


app:: TestApp

build:: TestApp deploy-simulator

reason-watch:
	# Brew install watchexec if you don't have it https://github.com/mattgreen/watchexec
	watchexec -w src $(MAKE) TestReason


deploy-simulator:
	## Boot the simulator if there's not one already booted
	(xcrun simctl list | grep '(Booted)' -q) || open -a "Simulator" --args -CurrentDeviceUDID $(DEVICE_ID)

	./waitforsimulator.sh

	## Install the app
	xcrun simctl install booted $(BUILD_DIR)/$(APP_NAME).app

	## Launch the app without deps on ios-deploy
	xcrun simctl launch --console booted $(BUNDLE_ID)

TestReason: Build $(C_FILES_PATH) $(RE_FILES_PATH)
		$(OCAMLOPT) bigarray.cmxa $(C_FILES_PATH) $(RE_FILES_PATH) -output-obj -o Build/re_output.o
		cp $(OCAMLDIR)/lib/ocaml/libasmrun.a Build/libGobi.a
		ar -r Build/libGobi.a $(C_FILES_PATH) Build/re_output.o

TestApp: TestReason
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
	mkdir -p Build/src Build/reasongl-interface/src Build/reprocessing/src

clean::
		rm -f TestApp *.o *.cm[iox]
		rm -rf Build/src/* Build/Products Build/libGobi.a Build/reasongl-interface/src/* Build/reprocessing/src/*

Build/src/bigarray_stubs.o: src/bigarray_stubs.c
		cp $< Build/$<
		$(CC) $(CFLAGS) $(MFLAGS) -c -o $@ Build/$<

Build/src/mmap_unix.o: src/mmap_unix.c
		cp $< Build/$<
		$(CC) $(CFLAGS) $(MFLAGS) -c -o $@ Build/$<


Build/%.o: %.m
		cp $< Build/$<
		$(CC) $(CFLAGS) $(MFLAGS) -c -o $@ Build/$<

Build/%.cmi: %.rei
		cp $< Build/$<
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl Build/$<

Build/%.cmo: %.re
		cp $< Build/$<
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl Build/$<

Build/%.cmx: %.re
		cp $< Build/$<
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl Build/$<

depend::
		$(OCAMLBIN)/bin/ocamldep -pp 'refmt --print binary' -ml-synonym .re  -I ./ *.re > MLDepend
		$(CC) $(CFLAGS) $(MFLAGS) -MM *.m > MDepend

-include MLDepend
-include MDepend
