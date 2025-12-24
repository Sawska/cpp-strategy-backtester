all: build

configure:
	cmake -S . -B build

build: configure
	cmake --build build

test: build
	cd build && ctest --output-on-failure

clean:
	rm -rf build

run: build
	./build/bin/backtester_run