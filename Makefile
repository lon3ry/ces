.PHONY: default all clean

default:
	cd src && $(MAKE)

all: default docs

clean:
	cd src && $(MAKE) clean
	rm -rf docs

docs: Doxyfile
	doxygen
