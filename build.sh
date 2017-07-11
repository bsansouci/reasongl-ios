mkdir -p _build

cp ./bin/ocaml-iPhoneSimulator-64/release/lib/ocaml/libasmrun.a _build/libGobi.a

./bin/ocaml-iPhoneSimulator-64/release/bin/ocamlopt hello.ml -output-obj -o _build/libGobi.o

ar -r _build/libGobi.a _build/libGobi.o
