FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    pkg-config \
    libcpp-httplib-dev \
    nlohmann-json3-dev \
    ca-certificates \
    && rm /var/lib/apt/lists/*

WORKDIR /app

COPY CMakeLists.txt ./
COPY backend/ ./backend/
COPY frontend/ ./frontend/

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --config Release

EXPOSE 8080

RUN ln -s /app/build/NeuroDigit /usr/local/bin/neurodigit

CMD ["neurodigit", "server"]