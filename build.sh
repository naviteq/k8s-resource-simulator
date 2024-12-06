#!/usr/bin/env bash

docker buildx create --name build_cross --driver-opt env.BUILDKIT_STEP_LOG_MAX_SIZE=10000000 --driver-opt env.BUILDKIT_STEP_LOG_MAX_SPEED=10000000 || true
docker buildx use build_cross

# Build and push the scratch-based image (tagged as latest)
docker buildx build \
  --platform linux/386,linux/amd64,linux/arm64/v8,linux/arm/v6,linux/arm/v7,linux/ppc64le,linux/s390x \
  -t spurin/cpu-mem-simulator:latest \
  --target final_scratch . \
  --push

  #--platform linux/386,linux/amd64,linux/arm64/v8,linux/arm/v6,linux/arm/v7,linux/ppc64le,linux/s390x \
# Build and push the ubuntu-based image with bash
docker buildx build \
  --platform linux/amd64,linux/arm64/v8,linux/arm/v7,linux/ppc64le,linux/s390x \
  -t spurin/cpu-mem-simulator:ubuntu \
  --target final_ubuntu . \
  --push
