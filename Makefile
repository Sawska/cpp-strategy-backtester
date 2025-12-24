all: build

configure:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

build: configure
	cmake --build build

test: build
	cd build && ctest --output-on-failure

clean:
	rm -rf build

run: build
	./build/bin/backtester_run

docker-build:
	docker build -t hft-backtester .

docker-run:
	# Використовуємо $(PWD) для підстановки поточної папки
	docker run --rm -v $(PWD)/data:/app/data hft-backtester

docker-all: docker-build docker-run