FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt update && apt upgrade -y && \
    apt install -y \
    bash \
    coreutils \
    curl \
    wget \
    git \
    vim \
    nano \
    net-tools \
    iputils-ping \
    traceroute \
    dnsutils \
    openssh-client \
    sudo \
    software-properties-common \
    build-essential \
    gcc \
    g++ \
    make \
    python3 \
    python3-pip \
    python3-venv \
    default-jdk \
    maven \
    unzip \
    zip \
    jq \
    tree \
    htop \
    tcpdump \
    lsof \
    strace \
    rsync \
    x11-apps \
    iproute2 \
    libgl1 \
    libglu1-mesa \
    libglx-mesa0 \
    libx11-6 \
    libxext6 \
    libxrender1 \
    libxi6 \
    libxrandr2 \
    libxinerama1 \
    libxcursor1 \
    libxxf86vm1 \
    mesa-utils \
    libglfw3 \
    libglew-dev \
    libglm-dev \
    libosmesa6 \
    libosmesa6-dev \
    mesa-utils-extra \
    freeglut3-dev \
    libglu1-mesa-dev \
    libgl1-mesa-dev \
    libglfw3-dev 

COPY entrypoint /entrypoint

RUN chmod +x /entrypoint

WORKDIR /root

ENTRYPOINT ["/entrypoint"]
