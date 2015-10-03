all: stencil implicit

stencil: stencil.cpp stencil_main.cpp
	icpc -openmp -o stencil stencil.cpp stencil_main.cpp

implicit: implicit.cpp implicit_main.cpp
	icpc -openmp -o implicit implicit.cpp implicit_main.cpp

clean:
	rm -f implicit stencil 
