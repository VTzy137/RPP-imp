# ----------- STAGE 1: BUILD ------------
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    doxygen \
    libopencv-dev \
    nlohmann-json3-dev

WORKDIR /app

# Copy source code into builder container
COPY . .

RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

# ----------- STAGE 2: RUNTIME ------------
FROM ubuntu:22.04

# Install runtime dependencies only
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    libopencv-core4.5d \
    libopencv-imgproc4.5d \
    libopencv-highgui4.5d \
 && rm -rf /var/lib/apt/lists/*

# Create non-root user
RUN useradd -ms /bin/bash devuser

# Set working directory
WORKDIR /home/devuser/app

# Copy binary as root and make it executable
COPY --from=builder /app/build/RPP-imp ./RPP-imp
RUN chmod +x ./RPP-imp

# Change to non-root user after permissions are set
USER devuser

# Run the app
ENTRYPOINT ["./RPP-imp"]






