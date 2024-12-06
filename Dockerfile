# Stage 1: Build the application using Alpine
FROM alpine:latest AS builder

# Install build dependencies
RUN apk add --no-cache gcc musl-dev libc-dev

WORKDIR /app

# Copy the source code into the container
COPY cpu_mem_simulator.c .

# Compile the application statically
RUN gcc -static -o cpu_mem_simulator cpu_mem_simulator.c

# Stage 2a: Create the minimal scratch based image
FROM scratch:latest AS final_scratch
COPY --from=builder /app/cpu_mem_simulator .
ENTRYPOINT ["./cpu_mem_simulator"]

# Stage 2b: Create a ubuntu based image
FROM ubuntu:latest AS final_ubuntu
COPY --from=builder /app/cpu_mem_simulator .
ENTRYPOINT ["./cpu_mem_simulator"]
