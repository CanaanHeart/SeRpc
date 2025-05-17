# 指定基础镜像和版本
FROM ubuntu:24.04

# 防止安装过程在交互暂停
ENV DEBIAN_FRONTEND=noninteractive

# 设置挂在点
VOLUME [ "volume0" ]

# 更新apt并安装构建环境 + 常用工具
RUN apt update && apt install -y --no-install-recommends \
    build-essential \
    git \
    wget \
    curl \
    unzip \
    ca-certificates \
    libssl-dev \
    pkg-config \
    gdb \
    libzookeeper-mt-dev

# 设置工作目录
WORKDIR /workspace

# 安装cmake
COPY /pkgs/cmake-4.0.1.tar.gz /home/cmake/
RUN tar -zxvf /home/cmake/cmake-4.0.1.tar.gz -C /home/cmake \
    && cd /home/cmake/cmake-4.0.1 \
    && ./bootstrap -- -DCMAKE_USE_OPENSSL=ON \
    && make -j$(nproc) \
    && make install \
    && cd /workspace

# 安装protobuf
COPY /pkgs/protobuf-cpp-3.21.12.tar.gz /home/protobuf/
RUN tar -zxvf /home/protobuf/protobuf-cpp-3.21.12.tar.gz -C /home/protobuf \
    && cd /home/protobuf/protobuf-3.21.12 \
    && ./configure \
    && make -j$(nproc) \
    && make install \
    && ldconfig \
    && cd /workspace

COPY /pkgs/SeRpc.tar.xz /workspace/
RUN tar -xJvf /workspace/SeRpc.tar.xz -C /workspace/ \
    && cd SeRpc/example && protoc --cpp_out=. user.proto  && cd .. \
    && cd src && protoc --cpp_out=. rpcheader.proto && mv rpcheader.pb.h ../inc/ \
    && cd /workspace/SeRpc/build \
    && cmake .. \
    && make \
    && cd ../bin

CMD ["/bin/bash"]