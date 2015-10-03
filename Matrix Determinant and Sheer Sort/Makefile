all: determinant shear

determinant: determinant.cpp determinant_main.cpp
	icpc -openmp -o determinant determinant.cpp determinant_main.cpp
	icpc -w -o determinant_serial determinant.cpp determinant_main.cpp

shear: shear.cpp shear_main.cpp
	icpc -openmp -o shear shear.cpp shear_main.cpp
	icpc -w -o shear_serial shear.cpp shear_main.cpp

clean:
	rm -f shear shear_serial determinant determinant_serial
