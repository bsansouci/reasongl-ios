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
MLFLAGS = -c

MOBS = bindings.o
MLOBS = test.cmx hello.cmx

build:: TestApp

TestApp: $(MOBS) $(MLOBS)
		$(OCAMLOPT) $(MOBS) $(MLOBS) -output-obj -o hello.o
		cp $(OCAMLDIR)/lib/ocaml/libasmrun.a libGobi.a
		ar -r libGobi.a $(MOBS) hello.o


clean::
		rm -f TestApp *.o *.cm[iox]

%.o: %.c
		$(CC) $(CFLAGS) $(MFLAGS) -c -o $@ -impl $<

%.cmi: %.rei
		$(OCAMLOPT) $(MLFLAGS) -c -impl $<

%.cmo: %.re
		$(OCAMLOPT) $(MLFLAGS) -c -impl $<

%.cmx: %.re
		$(OCAMLOPT) $(MLFLAGS) -o $@ -impl $<

depend::
		$(OCAMLBIN)/bin/ocamldep -pp 'refmt --print binary' -ml-synonym .re  -I ./ *.re > MLDepend
		$(CC) $(CFLAGS) $(MFLAGS) -MM *.m > MDepend

-include MLDepend
-include MDepend
