# Stereolabs ZED - OpenCV

This sample is the perfect place to get started coding with the ZED and OpenCV. It shows how to:

  - Capture image, depth and point cloud from the ZED.
  - Convert image and depth map to compatible 32-bits float OpenCV matrix.
  - Display video and depth with OpenCV.
  - Adjust several depth parameters: depth sensing mode, quality, units, resolution.
  - Save side by side image, depth image and point cloud in various formats

## Getting started

- First, download the latest version of the ZED SDK on [stereolabs.com](https://www.stereolabs.com).
- For more information, read the ZED [API documentation](https://www.stereolabs.com/developers/documentation/API/).

### Prerequisites

- Windows 7 64bits or later, Ubuntu 16.04 or 18.04
- [ZED SDK](https://www.stereolabs.com/developers/) and its dependencies ([CUDA](https://developer.nvidia.com/cuda-downloads), [OpenCV](https://github.com/opencv/opencv/releases))

OpenCV can be installed from source on Linux, please refer to this [guide](https://www.stereolabs.com/docs/getting-started/application-development/#building-on-linux-and-jetson) to proceed with the installation.

### C++

Read the [guide](./cpp) to learn how to build and launch this sample in C++.

### Python

Read the [guide](./python) to learn how to build and launch this sample in Python.
