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

- Windows 10, Ubuntu LTS
- [ZED SDK](https://www.stereolabs.com/developers/) and its dependencies ([CUDA](https://developer.nvidia.com/cuda-downloads), [OpenCV](https://github.com/opencv/opencv/releases))

OpenCV can be installed from source on Linux, please refer to this [guide](https://www.stereolabs.com/docs/getting-started/application-development/#building-on-linux-and-jetson) to proceed with the installation.

### C++

Read the [guide](./cpp) to learn how to build and launch this sample in C++.

### Python

Read the [guide](./python) to learn how to build and launch this sample in Python.


## Installing OpenCV

### Installing OpenCV on Windows

OpenCV provides already compiled binaries, it can be downloaded at https://opencv.org/releases/

### Installing OpenCV on Linux

Some sample can require OpenCV, here is a tutorial on how to install it.

OpenCV can be downloaded at this location : https://opencv.org/releases/

For a more detailed OpenCV tutorial installation, [refer to the opencv documention](https://docs.opencv.org/4.1.0/d7/d9f/tutorial_linux_install.html).

#### Installation steps

- Install the required dependencies

```bash
sudo apt-get install build-essential cmake libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
```

- Download source archive from http://opencv.org/releases.html and extract it

```bash
wget https://github.com/opencv/opencv/archive/4.1.0.zip -O /tmp/opencv_src.zip
cd ~/
unzip /tmp/opencv_src.zip ; rm /tmp/opencv_src.zip
```

- Navigate to the extracted sources, create a temporary build directory and enter it. For example,

```bash
cd ~/opencv-*
mkdir build
cd build
```

- Run cmake

```bash
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local -DBUILD_TESTS=OFF -DBUILD_PERF_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_JAVA=OFF -DWITH_OPENGL=ON ..
```

- Execute make. The compilation can take a while

```bash
make -j$(nproc)
```

- Install the libraries

```bash
sudo make install
```
