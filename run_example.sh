#!/usr/bin/env -S nix shell . nixpkgs#gnumake nixpkgs#llvmPackages_19.clang --command bash

# Run the example
fsembed example_filesystem example
make -C fsembed_filesystems/example
clang++ -std=c++23 -O3   example.cpp fsembed_filesystems/example/fsembed.o -o example

./example