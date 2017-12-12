set -ex

if [ ! -d ~/.opam/4.04.0+ios+arm64 ]; then
  echo "Installing ios arm64";
  opam switch -A 4.04.0 4.04.0+ios+arm64
  eval `opam config env`
  opam pin add -y ocamlbuild https://github.com/ocaml/ocamlbuild.git
  opam pin add -y topkg https://github.com/whitequark/topkg.git#ios
  opam remove -y conf-ios
  ARCH=arm64 SUBARCH=arm64 PLATFORM=iPhoneOS SDK=10.3 VER=8.0 \
    opam install -y conf-ios
  opam install -y ocaml-ios
fi;

if [ ! -d ~/.opam/4.04.0+ios+amd64 ]; then
  echo "Installing ios amd64";
  opam switch -A 4.04.0 4.04.0+ios+amd64
  eval `opam config env`
  opam pin add -y ocamlbuild https://github.com/ocaml/ocamlbuild.git
  opam pin add -y topkg https://github.com/whitequark/topkg.git#ios
  ARCH=amd64 SUBARCH=x86_64 PLATFORM=iPhoneSimulator SDK=10.3 VER=8.0 \
    opam install -y conf-ios
  opam install -y ocaml-ios
fi;
