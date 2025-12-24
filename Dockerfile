FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN cmake -S . -B build && \
    cmake --build build

RUN mkdir -p data

CMD ["sh", "-c", "python3 scripts/generate_data.py && ./build/bin/backtester_run data/market_data.csv"]