FROM --platform=linux/amd64 debian:bullseye

# Essentials.
RUN apt-get update && apt-get install -y \
  git \
  clang \
  curl \
  gnupg2\
  cmake \
  && rm -rf /var/lib/apt/lists/*

# Crystal
RUN curl -fsSL https://crystal-lang.org/install.sh | bash \
  && apt-get install -y clang \
  && rm -rf /var/lib/apt/lists/*

# Emeralds
WORKDIR /opt
RUN git clone https://github.com/Oblivious-Oblivious/Emeralds && \
  cd Emeralds && \
  chmod 755 install && ./install

WORKDIR /app
RUN git clone https://github.com/Oblivious-Oblivious/margaret && \
  cd margaret && \
  em install all

CMD ["/bin/bash"]

# docker buildx build --platform linux/amd64 -t margaret .
# docker run -it --platform linux/amd64 margaret
