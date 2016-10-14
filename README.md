# zed-opencv

**This sample is designed to work with the ZED stereo camera only and requires the ZED SDK. For more information: https://www.stereolabs.com**

It demonstrates how to grab images and disparity map with the ZED SDK and link the results with OpenCV.

**Warning :**
 - GPU->CPU readback is time-consuming
 - This sample is not designed to operate in real time

Both images and depth/disparity map are displayed.                                 
Most of the functions of the ZED SDK are linked with a key press event (using OpenCV).

## Build the program

Open a terminal in With OpenCV directory and execute the following command:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make


## Run the program

Open a terminal in build directory and execute the following command:

    $ ./ZED\ with\ OpenCV [path to SVO file]

## Keyboard shortcuts


  Display hotkeys    |           Description      |  Hotkeys    |           Description                                           
-------------|------------------------------------|-------------|------------------------------------
 '0'         | Left image                         | 'a'         | Re-compute stereo alignment                                                 
 '1'         | Right image                        | 'w'         | Save side by side images into a png file                                                  
 '2'         | Left gray rectified image          | 'v'         | Save the disparity map in a png file                                                    
 '3'         | Right gray rectified image         | 'r'         | Sensing mode `STANDARD `                                                    
 '4'         | Left raw image                     | 'f'         | Sensing mode `FILL `                                                    
 '5'         | Right raw image                    | 'd'         | Toggle disparity / depth map display                                                    
 '6'         | Left gray raw image                | 'g'         | Increase camera exposure                                                    
 '7'         | Right gray raw image               | 'h'         | Decrease camera exposure                
 '8'         | Anaglyph view                      | 'b'         | Increase disparity map confidence threshold                                                   
 '9'         | Difference view                    | 'n'         | Decrease disparity map confidence threshold                    
 's'         | Left and Right image side by side  | 'q'         | Quit the sample            
 'o'         | Overlay view                       | -         | -                     
 'c'         | Display depth map confidence       | -         | -        
