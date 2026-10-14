# syntax=docker/dockerfile:1
ARG GCC_VERSION=15.2.0

# ---- yuki-tool をソースからビルド (x86-64 / ARM64 共通) ----
FROM gcc:${GCC_VERSION} AS yuki
ARG YUKI_TOOL_VERSION=v0.5.0
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo PATH=/opt/cargo/bin:$PATH
RUN curl -fsSL https://sh.rustup.rs | sh -s -- -y --profile minimal \
  && cargo install --git https://github.com/yuki2006/yukicoder_tools \
  --tag ${YUKI_TOOL_VERSION} --root /out

# ---- 本体 ----
FROM gcc:${GCC_VERSION}
RUN apt-get update && apt-get install -y --no-install-recommends \
  python3 git gdb less clang-format \
  && rm -rf /var/lib/apt/lists/*

# AtCoder Library
ARG ACL_VERSION=v1.6
RUN git clone --depth 1 --branch ${ACL_VERSION} \
  https://github.com/atcoder/ac-library /opt/ac-library

# testlib (0.9.45)。タグは 0.9.41 で止まっているので、コミットで固定する
ARG TESTLIB_COMMIT=1e4e8a24c79c6bad3becbdb5a332ffc352b7d5dd
RUN git init -q /opt/testlib \
  && git -C /opt/testlib fetch -q --depth 1 https://github.com/MikeMirzayanov/testlib ${TESTLIB_COMMIT} \
  && git -C /opt/testlib -c advice.detachedHead=false checkout -q FETCH_HEAD \
  && cp /opt/testlib/testlib.h /usr/local/include/

# yuki-tool
COPY --from=yuki /out/bin/yuki-tool /usr/local/bin/yuki-tool

ENV CPLUS_INCLUDE_PATH=/opt/ac-library LANG=C.UTF-8

RUN printf '#!/bin/sh\nexec python3 /workspaces/cp-env/tools/cpe "$@"\n' > /usr/local/bin/cpe \
 && chmod +x /usr/local/bin/cpe
