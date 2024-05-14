# Stage 1: Build the application using Alpine
FROM alpine:latest as builder

# Install build dependencies
RUN apk add --no-cache gcc musl-dev libc-dev

WORKDIR /app

# Copy the source code into the container
COPY cpu_mem_simulator.c .

# Compile the application statically
RUN gcc -static -o cpu_mem_simulator cpu_mem_simulator.c

# Stage 2: Create the final minimal image
FROM scratch

# Copy the compiled binary from the builder stage
COPY --from=builder /app/cpu_mem_simulator .

# Set the binary as the entrypoint
ENTRYPOINT ["./cpu_mem_simulator"]
