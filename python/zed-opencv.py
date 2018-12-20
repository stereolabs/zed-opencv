import sys
import numpy as np
import pyzed.sl as sl
import cv2

help_string = "[s] Save side by side image [d] Save Depth, [n] Change Depth format, [p] Save Point Cloud, [m] Change Point Cloud format, [q] Quit"
prefix_point_cloud = "Cloud_"
prefix_depth = "Depth_"
path = "./"

count_save = 0
mode_point_cloud = 0
mode_depth = 0
point_cloud_format = sl.POINT_CLOUD_FORMAT.POINT_CLOUD_FORMAT_XYZ_ASCII
depth_format = sl.DEPTH_FORMAT.DEPTH_FORMAT_PNG

def get_depth_format_name(f) :

    if f == sl.DEPTH_FORMAT.DEPTH_FORMAT_PNG :
        return "PNG"
    elif f == sl.DEPTH_FORMAT.DEPTH_FORMAT_PFM :
        return "PFM"
    elif f == sl.DEPTH_FORMAT.DEPTH_FORMAT_PGM :
        return "PGM"
    else :
        return ""

def get_point_cloud_format_name(f) :

    if f == sl.POINT_CLOUD_FORMAT.POINT_CLOUD_FORMAT_XYZ_ASCII :
        return "XYZ"
    elif f == sl.POINT_CLOUD_FORMAT.POINT_CLOUD_FORMAT_PCD_ASCII :
        return "PCD"
    elif f == sl.POINT_CLOUD_FORMAT.POINT_CLOUD_FORMAT_PLY_ASCII :
        return "PLY"
    elif f == sl.POINT_CLOUD_FORMAT.POINT_CLOUD_FORMAT_VTK_ASCII :
        return "VTK"
    else :
        return ""

def save_point_cloud(zed, filename) :
    print("Saving Point Cloud...")
    saved = sl.save_camera_point_cloud_as(zed, point_cloud_format, filename, True)
    if saved :
        print("Done")
    else :
        print("Failed... Please check that you have permissions to write on disk")

def save_depth(zed, filename) :
    max_value = 65535.
    scale_factor = max_value / zed.get_depth_max_range_value()

    print("Saving Depth Map...")
    saved = sl.save_camera_depth_as(zed, depth_format, filename, scale_factor)
    if saved :
        print("Done")
    else :
        print("Failed... Please check that you have permissions to write on disk")

def save_sbs_image(zed, filename) :

    image_sl_left = sl.Mat()
    zed.retrieve_image(image_sl_left, sl.VIEW.VIEW_LEFT)
    image_cv_left = image_sl_left.get_data()

    image_sl_right = sl.Mat()
    zed.retrieve_image(image_sl_right, sl.VIEW.VIEW_RIGHT)
    image_cv_right = image_sl_right.get_data()

    sbs_image = np.concatenate((image_cv_left, image_cv_right), axis=1)

    cv2.imwrite(filename, sbs_image)
    

def process_key_event(zed, key) :
    global mode_depth
    global mode_point_cloud
    global count_save
    global depth_format
    global point_cloud_format

    if key == 100 or key == 68:
        save_depth(zed, path + prefix_depth + str(count_save))
        count_save += 1
    elif key == 110 or key == 78:
        mode_depth += 1
        depth_format = sl.DEPTH_FORMAT(mode_depth % 3)
        print("Depth format: ", get_depth_format_name(depth_format))
    elif key == 112 or key == 80:
        save_point_cloud(zed, path + prefix_point_cloud + str(count_save))
        count_save += 1
    elif key == 109 or key == 77:
        mode_point_cloud += 1
        point_cloud_format = sl.POINT_CLOUD_FORMAT(mode_point_cloud % 4)
        print("Point Cloud format: ", get_point_cloud_format_name(point_cloud_format))
    elif key == 104 or key == 72:
        print(help_string)
    elif key == 115:
        save_sbs_image(zed, "ZED_image" + str(count_save) + ".png")
        count_save += 1
    else:
        a = 0

def print_help() :
    print(" Press 's' to save Side by side images")
    print(" Press 'p' to save Point Cloud")
    print(" Press 'd' to save Depth image")
    print(" Press 'm' to switch Point Cloud format")
    print(" Press 'n' to switch Depth format")


def main() :

    # Create a ZED camera object
    zed = sl.Camera()

    # Set configuration parameters
    init = sl.InitParameters()
    init.camera_resolution = sl.RESOLUTION.RESOLUTION_HD1080
    init.depth_mode = sl.DEPTH_MODE.DEPTH_MODE_PERFORMANCE
    init.coordinate_units = sl.UNIT.UNIT_METER
    if len(sys.argv) >= 2 :
        init.svo_input_filename = sys.argv[1]

    # Open the camera
    err = zed.open(init)
    if err != sl.ERROR_CODE.SUCCESS :
        print(repr(err))
        zed.close()
        exit(1)

    # Display help in console
    print_help()

    # Set runtime parameters after opening the camera
    runtime = sl.RuntimeParameters()
    runtime.sensing_mode = sl.SENSING_MODE.SENSING_MODE_STANDARD

    # Prepare new image size to retrieve half-resolution images
    image_size = zed.get_resolution()
    new_width = image_size.width /2
    new_height = image_size.height /2

    # Declare your sl.Mat matrices
    image_zed = sl.Mat(new_width, new_height, sl.MAT_TYPE.MAT_TYPE_8U_C4)
    depth_image_zed = sl.Mat(new_width, new_height, sl.MAT_TYPE.MAT_TYPE_8U_C4)
    point_cloud = sl.Mat()

    key = ' '
    while key != 113 :
        err = zed.grab(runtime)
        if err == sl.ERROR_CODE.SUCCESS :
            # Retrieve the left image, depth image in the half-resolution
            zed.retrieve_image(image_zed, sl.VIEW.VIEW_LEFT, sl.MEM.MEM_CPU, int(new_width), int(new_height))
            zed.retrieve_image(depth_image_zed, sl.VIEW.VIEW_DEPTH, sl.MEM.MEM_CPU, int(new_width), int(new_height))
            # Retrieve the RGBA point cloud in half resolution
            zed.retrieve_measure(point_cloud, sl.MEASURE.MEASURE_XYZRGBA, sl.MEM.MEM_CPU, int(new_width), int(new_height))

            # To recover data from sl.Mat to use it with opencv, use the get_data() method
            # It returns a numpy array that can be used as a matrix with opencv
            image_ocv = image_zed.get_data()
            depth_image_ocv = depth_image_zed.get_data()

            cv2.imshow("Image", image_ocv)
            cv2.imshow("Depth", depth_image_ocv)

            key = cv2.waitKey(10)

            process_key_event(zed, key)

    cv2.destroyAllWindows()
    zed.close()

    print("\nFINISH")

if __name__ == "__main__":
    main()
