FROM ubuntu:22.04


RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
      build-essential \
      libreadline-dev \
      libncurses-dev \
 	valgrind \
 	gcc \
   	 gdb \
	sudo \
	gdb \
  	clang \
      git && \
    rm -rf /var/lib/apt/lists/*



RUN apt-get update && \
 apt-get install -y --reinstall libreadline-dev 
   

# Create a non-root user and add to sudoers (for debugging)
RUN useradd -m grace && \
    echo "grace ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Switch to the non-root user
USER grace

# Set working directory
WORKDIR /workspace

# Default command
CMD ["tail", "-f", "/dev/null"]