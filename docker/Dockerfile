FROM ubuntu:20.04 AS llvm_builder
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Tokyo \
    GIT_SSL_NO_VERIFY=1
# Build llvm
RUN apt-get -y update \
 && apt-get -y  --no-install-recommends install \
    build-essential \
    cmake \
    curl \
    gcc \
    git \
    gnulib \
    libffi-dev \
    libgmp-dev \
    libmpc-dev \
    libtool \
    ninja-build \
    python3 \
    tzdata \
    zlib1g-dev \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*
RUN git clone https://github.com/llvm/llvm-project.git -b llvmorg-13.0.0 --depth 1
RUN mkdir /llvm-project/build
WORKDIR /llvm-project
RUN cmake -S llvm -B build -G Ninja \
    -DLLVM_TARGETS_TO_BUILD="AArch64;RISCV;WebAssembly;X86" \
    -DCMAKE_C_COMPILER="gcc" \
    -DCMAKE_BUILD_TYPE="Release" \
    -DLLVM_PARALLEL_LINK_JOBS="1" \
    # -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;compiler-rt;libc;libclc;libcxx;libcxxabi;libunwind;lld;lldb;openmp;parallel-libs;polly;pstl" && \
    -DLLVM_ENABLE_PROJECTS="clang"
RUN cmake --build build && \
    cmake --build build --target install

# Build GoogleTest
WORKDIR /
RUN git clone https://github.com/google/googletest.git -b release-1.11.0 --depth 1
RUN mkdir /googletest/build 
WORKDIR /googletest/build
RUN cmake .. \
    -DCMAKE_C_COMPILER="gcc" \
    -DCMAKE_CXX_COMPILER="g++" 
RUN make -j 8 && make install

# Build enviroment
FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive \
    TZ=Asia/Tokyo
RUN apt-get -y update \
 && apt-get -y  --no-install-recommends install \
    cmake \
    gcc \
    git \
    g++ \
    make \
    zlib1g-dev \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*
COPY --from=llvm_builder /usr/local/bin/ /usr/local/bin/
COPY --from=llvm_builder /usr/local/include/ /usr/local/include/
COPY --from=llvm_builder /usr/local/lib/ /usr/local/lib/
