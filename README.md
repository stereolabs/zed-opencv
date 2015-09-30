# zed-opencv

**This sample is designed to work with the ZED stereo camera only and requires the ZED SDK. For more information: https://www.stereolabs.com**

It demonstrates how to grab images and disparity map with the ZED SDK and link the results with OpenCV.

**Warning :**
 - GPU->CPU readback is time-consuming
 - This sample is not designed to operate in real time
     
Both images and depth/disparity map are displayed.                                 
Most of the functions of the ZED SDK are linked with a key press event (using OpenCV).
  
##Build the program

Open a terminal in With OpenCV directory and execute the following command:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
 

##Run the program

Open a terminal in build directory and execute the following command:

    $ ./ZED\ with\ OpenCV [path to SVO file]
 
##Keyboard shortcuts
 
               Main Hotkeys              |            Display Hotkeys            
----------------------------------------|---------------------------------------
 'b'   : Decrease reliability index by 1 | '0'   : Left View                    
 'n'   : Increase reliability index by 1 | '1'   : Right View                   
 'r'   : Sensing Mode : RAW              | '2'   : Anaglyph View                
 'f'   : Sensing Mode : FULL             | '3'   : Gray Scale Difference View   
 's'   : Display Confidence Map          | '4'   : Side by Side View            
 'w'   : Save Side by Side image in PNG  | '5'   : Overlay View                 
 'v'   : Save Disparity image in PNG     | 'd'   : Toggle Disparity / Depth view
