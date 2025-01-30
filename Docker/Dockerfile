# Use the official Ubuntu image
FROM ubuntu:latest

# Update package list and install essential tools
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    gdb \
    git \
    vim \
    nano \
    curl \
    python3 python3-venv \
    man \
    clang valgrind 
    

RUN apt-get install -y \
    libx11-dev 

 #create a new user
RUN useradd -m grace

#switch to the new user
USER grace 

# Clone the francinette repository
RUN bash -c "$(curl -fsSL https://raw.github.com/xicodomingues/francinette/master/bin/install.sh)"

# Add francinette to PATH
ENV PATH="/home/grace/francinette:${PATH}"

# Set working directory
WORKDIR /workspace

# Default command to keep the container running
CMD ["tail", "-f", "/dev/null"]