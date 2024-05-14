# CPU and Memory Load Simulator

## Overview

The CPU and Memory Load Simulator is a simple C application designed to simulate specific CPU and memory usage on a system. It accepts parameters to specify the amount of CPU in millicores and memory in MiB that it should consume. The application is useful for testing and demonstrating resource management and monitoring in environments like Kubernetes.

## Features

- **CPU Load Simulation**: Simulate CPU usage by specifying millicores.
- **Memory Allocation**: Allocate a specified amount of memory in MiB.
- **Signal Handling**: Clean exit on receiving SIGTERM or Ctrl-C.
- **Docker Compatibility**: Comes packaged as a minimal Docker image using multi-stage builds.
- **MultiArch Support**: Docker image available for multiple architectures, making it suitable for a variety of hardware platforms.

## Getting Started

### Prerequisites

- Docker installed on your machine
- Access to Docker Hub to pull the image
- Kubernetes cluster (optional for deployment on Kubernetes)

### Deployment in Kubernetes

Below is an example of a Kubernetes Pod configuration using the spurin/cpu-mem-simulator image:

```yaml
Copy code
apiVersion: v1
kind: Pod
metadata:
  name: cpu-mem-simulator-pod
spec:
  containers:
  - name: cpu-mem-simulator
    image: spurin/cpu-mem-simulator:latest
    args: ["-millicores", "200", "-MiB", "100"]
```

Save the above YAML to a file named cpu-mem-simulator-pod.yaml and deploy it to your Kubernetes cluster using:

```bash
kubectl apply -f cpu-mem-simulator-pod.yaml
```

This will create a Pod that simulates 200 millicores of CPU usage and allocates 100 MiB of memory, closely respecting the Kubernetes resource requests and limits.

## Contributing

Contributions to improve the CPU and Memory Load Simulator are welcome. Please feel free to submit pull requests or open issues to discuss proposed changes.
