{
  description = "C macro utilities - enum and variant X-macros";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs = { self, nixpkgs }:
    let
      forAllSystems = f:
        nixpkgs.lib.genAttrs
          [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ]
          (system: f nixpkgs.legacyPackages.${system});
    in
    {
      packages = forAllSystems (pkgs: rec {
        c-macros = pkgs.stdenv.mkDerivation {
          pname = "c-macros";
          version = "0.1.0";
          src = ./.;
          dontBuild = true;
          installPhase = ''
            mkdir -p $out/include/c-macros
            cp enum.h variant.h $out/include/c-macros/
          '';
        };

        default = c-macros;

        enum-example = pkgs.stdenv.mkDerivation {
          name = "enum-example";
          src = ./.;
          buildInputs = [ c-macros ];
          buildPhase = ''
            $CC -Wall -Wextra -std=c11 examples/enum_example.c -o enum-example
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp enum-example $out/bin/
          '';
        };

        variant-example = pkgs.stdenv.mkDerivation {
          name = "variant-example";
          src = ./.;
          buildInputs = [ c-macros ];
          buildPhase = ''
            $CC -Wall -Wextra -std=c11 examples/variant_example.c -o variant-example
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp variant-example $out/bin/
          '';
        };
      });

      devShells = forAllSystems (pkgs: {
        default = pkgs.mkShell {
          packages = [ pkgs.gcc ];
        };
      });
    };
}
