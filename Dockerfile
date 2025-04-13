# ----------- STAGE 1: BUILD ------------
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git

# Tạo user non-root
RUN useradd -ms /bin/bash devuser
USER devuser
WORKDIR /home/devuser/app

# Copy toàn bộ mã nguồn
COPY --chown=devuser:devuser . .

# Build project
RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

# ----------- STAGE 2: RUNTIME ------------
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y libstdc++6

# Tạo user non-root
RUN useradd -ms /bin/bash devuser
USER devuser
WORKDIR /home/devuser/app

# Copy file thực thi từ builder
COPY --from=builder /home/devuser/app/build/RPP-imp ./RPP-imp

# Cấp quyền thực thi
RUN chmod +x ./RPP-imp

# Chạy ứng dụng
ENTRYPOINT ["./RPP-imp"]




