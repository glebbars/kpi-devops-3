FROM alpine:latest

# Install necessary dependencies
RUN apk add --no-cache \
    g++ \
    make \
    automake \
    autoconf \
    libstdc++ \
    musl-dev

# Set the working directory inside the container
WORKDIR /app

# Copy the project files into the container
COPY . .

# Generate the build system
RUN aclocal && autoconf && automake --add-missing && ./configure

# Build the project
RUN make clean && make

# Expose the port used by the HTTP server
EXPOSE 8081

# Run the HTTP server
CMD ["./trigonometry"]
