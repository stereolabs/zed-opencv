# Stereolabs ZED - OpenCV

This sample is the perfect place to get started coding with the ZED and OpenCV. It shows how to:

  - Capture image, depth and point cloud from the ZED.
  - Convert image and depth map to compatible 32-bits float OpenCV matrix.
  - Display video and depth with OpenCV.
  - Adjust several depth parameters: depth sensing mode, quality, units, resolution.
  - Save side by side image, depth image and point cloud in various formats

## Build the program

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

You can optionally provide an SVO file path (recorded stereo video of the ZED).

### Keyboard shortcuts

This table lists keyboard shortcuts that you can use in the sample application.

Parameter             | Description                   |   Hotkey
---------------------|------------------------------------|-------------------------------------------------
Save Side by Side      | Save side by side image.       |   's'                             
Save Depth             | Save depth image.              |   'p'                              
Save Point Cloud       | Save 3D point cloud.        |   'd'
Switch cloud format    | Toggle between point cloud formats.    |   'm'
Switch depth format    | Toggle between depth image formats. |   'n'                                                      
Exit         | Quit the application.             | 'q'
