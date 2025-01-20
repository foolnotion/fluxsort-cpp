{
  description = "fluxsort development environment";

  inputs = {
    flake-parts.url = "github:hercules-ci/flake-parts";
    nixpkgs.url = "github:nixos/nixpkgs/master";
  };

  outputs = inputs @{ self, flake-parts, nixpkgs }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [ "x86_64-linux" "x86_64-darwin" "aarch64-darwin" ];

      perSystem = { pkgs, system, ... }:
        let
          pkgs = import nixpkgs { inherit system; };
          stdenv_ = pkgs.llvmPackages_19.stdenv;

          fluxsort = stdenv_.mkDerivation {
            name = "fluxsort";
            src = self;

            cmakeFlags = [
              "-DBUILD_SHARED_LIBS=${if pkgs.stdenv.hostPlatform.isStatic then "OFF" else "ON"}"
              "-DBUILD_TESTING=OFF"
              "-DCMAKE_BUILD_TYPE=Release"
            ];

            nativeBuildInputs = with pkgs; [ cmake git ];
          };
        in rec {
          packages = {
            default = fluxsort.overrideAttrs (old: {
              cmakeFlags = old.cmakeFlags ++ [
                "--preset ${if pkgs.stdenv.isLinux then "release-linux" else if pkgs.stdenv.isDarwin then "release-darwin" else ""}"
              ];
            });

            compat = fluxsort.overrideAttrs (old: {
              cmakeFlags = old.cmakeFlags;
            });
          };


          devShells.default = stdenv_.mkDerivation {
            name = "fluxsort";

            nativeBuildInputs = fluxsort.nativeBuildInputs ++ (with pkgs; [
              clang-tools_16
              hyperfine
              valgrind
            ]);
          };
        };
    };
}