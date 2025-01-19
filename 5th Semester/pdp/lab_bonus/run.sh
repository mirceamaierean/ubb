xcrun -sdk macosx metal -c poly_mult.metal -o poly_mult.air
xcrun -sdk macosx metallib poly_mult.air -o poly_mult.metallib

chmod 777 ./karatsuba.metallib
# clang++ -o karatsuba karatsuba.mm -framework Metal -framework Foundation -framework CoreGraphics -std=c++17
clang++ -o metal_poly_mult main.mm -framework Metal -framework Foundation -framework CoreGraphics -std=c++17

# ./metal_poly_mult polynomials.txt
./karatsuba polynomials.txt

# diff karatsuba_metal_output.txt metal_poly_mult.txt