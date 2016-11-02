# Stereolabs ZED - OpenCV

This sample shows how to interface the ZED SDK and OpenCV to acquire and display ZED stereo images and depth map.

## Getting started

- First, download the latest version of the ZED SDK on [stereolabs.com](https://www.stereolabs.com).
- Make sure you have OpenCV installed.
- For more information, check out this [blog post](https://www.stereolabs.com/blog/index.php/2015/06/28/zed-with-opencv/) and read the ZED [API documentation](https://www.stereolabs.com/developers/documentation/API/).

### Prerequisites

- Windows 7 64bits or later, Ubuntu 16.04
- [ZED SDK](https://www.stereolabs.com/developers/) and its dependencies ([CUDA](https://developer.nvidia.com/cuda-downloads), [OpenCV 3.1](http://opencv.org/downloads.html))


## Build the program

Download the sample and follow these instructions:

#### Build for Windows

- Create a "build" folder in the source folder
- Open cmake-gui and select the source and build folders
- Generate the Visual Studio `Win64` solution
- Open the resulting solution and change configuration to `Release`
- Build solution

#### Build for Linux

Open a terminal in the sample directory and execute the following command:

    mkdir build
    cd build
    cmake ..
    make

## Run the program

- Navigate to the build directory and launch the executable file
- Or open a terminal in the build directory and run the sample :

        ./ZED\ with\ OpenCV [path to SVO file]

You can optionally provide an SVO file path (recorded stereo video of the ZED)

## Features

This sample is the perfect place to get started coding with the ZED.
It shows how to use the basic functions of the ZED SDK:

  - Capture stereo video from the ZED or an SVO file.
  - Capture depth map as a compatible 32bits float OpenCV matrix.
  - Display stereo video in several viewing modes: raw, rectified, grayscale, anaglyph, overlay, difference and side-by-side.
  - Display disparity and depth map.
  - Adjust several depth parameters: depth sensing mode, max range, depth confidence.

To learn how to add camera tracking capabilities, see the dedicated [tracking sample](https://github.com/stereolabs/zed-tracking-viewer).

### Keyboard shortcuts

This table lists keyboard shortcuts that you can use in the sample application.

Parameter             | Description                   |   Hotkey
---------------------|------------------------------------|-------------------------------------------------
 Left image view      | Display left rectified RGB image.                      |         '0'                             
Right image view      | Display right rectified RGB image.                        |          '1'                              
Side by Side view        | Display the left and right images side by side.  |'2'
Overlay view         | Display overlay view.        |      '3'
Difference view         | Display difference view. |           '4'         
Anaglyph view         | Display anaglyph view. |            '5'                 
Depth view         | Toggle between disparity / depth map display.           |           'd'                                                      
Confidence view         | Display depth map confidence. The confidence value is mapped between 0 (high confidence threshold, sparse data) and 100 (low confidence threshold, dense data).       | 'c'
Confidence threshold        | Increase/Decrease depth map confidence threshold.    |       'b'/'n'     
Sensing mode         | Toggle between `STANDARD` sensing mode (faster, should be used by most applications) / `FILL` (fully dense and filtered depth map).     |             's'                                                    
Exit         | Quit the application.             | 'q'


## Limitations

 - For simplicity's sake, this sample uses GPU->CPU data transfer to retrieve and display the images with OpenCV.
 - For optimal performance, we recommend using a direct device to device copy of the ZED SDK GPU buffer to OpenGL buffer, rather than using the CPU as an intermediate.
