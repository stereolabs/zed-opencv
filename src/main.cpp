///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015, STEREOLABS.
//
// All rights reserved.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////




/**************************************************************************************************
 ** This sample demonstrates how to grab images and depth/disparity map with the ZED SDK          **
 ** Both images and depth/disparity map are displayed with OpenCV                                 **
 ** Most of the functions of the ZED SDK are linked with a key press event (using opencv)         **
 ***************************************************************************************************/



//standard includes
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <chrono>

//opencv includes
#include <opencv2/opencv.hpp>

//ZED Includes
#include <zed/Camera.hpp>


//Define the structure and callback for mouse event

typedef struct mouseOCVStruct {
    float* data;
    uint32_t step;
    cv::Size _image;
    cv::Size _resize;
    std::string name;
} mouseOCV;

mouseOCV mouseStruct;

static void onMouseCallback(int32_t event, int32_t x, int32_t y, int32_t flag, void * param) {
    if (event == CV_EVENT_LBUTTONDOWN) {
        mouseOCVStruct* data = (mouseOCVStruct*) param;

        int y_int = (y * data->_image.height / data->_resize.height);
        int x_int = (x * data->_image.width / data->_resize.width);

        float* ptr_image_num = (float*) ((int8_t*) data->data + y_int * data->step);
        float dist = ptr_image_num[x_int] / 1000.f;

        if (dist > 0.)
            printf("\n%s : %2.2f m\n", data->name.c_str(), dist);
        else
            printf("\n : NAN\n");
    }
}

// save function using opencv

void saveSbSimage(sl::zed::Camera* zed, std::string filename) {
	sl::zed::resolution imSize = zed->getImageSize();

    cv::Mat SbS(imSize.height, imSize.width * 2, CV_8UC4);
    cv::Mat leftIm(SbS, cv::Rect(0, 0, imSize.width, imSize.height));
    cv::Mat rightIm(SbS, cv::Rect(imSize.width, 0, imSize.width, imSize.height));

	slMat2cvMat(zed->retrieveImage(sl::zed::SIDE::LEFT)).copyTo(leftIm);
	slMat2cvMat(zed->retrieveImage(sl::zed::SIDE::RIGHT)).copyTo(rightIm);

    cv::imshow("Saving Image", SbS);
    cv::cvtColor(SbS, SbS, CV_RGBA2RGB);

    cv::imwrite(filename, SbS);
}


//main  function

int main(int argc, char **argv) {

    if (argc > 2) {
        std::cout << "Only the path of a SVO can be passed in arg" << std::endl;
        //Sleep(2000);
        return -1;
    }

	sl::zed::SENSING_MODE dm_type = sl::zed::RAW;
	sl::zed::Camera* zed;

    if (argc == 1) // Use in Live Mode
		zed = new sl::zed::Camera(sl::zed::HD1080);
    else // Use in SVO playback mode
		zed = new sl::zed::Camera(argv[1]);

    int width = zed->getImageSize().width;
    int height = zed->getImageSize().height;

	sl::zed::ERRCODE err = zed->init(sl::zed::MODE::PERFORMANCE, 0, true);

    // ERRCODE display
	std::cout << sl::zed::errcode2str(err) << std::endl;


    // Quit if an error occurred
	if (err != sl::zed::SUCCESS) {
        delete zed;
        return 1;
    }

    char key = ' ';
    int ViewID = 2;
    int count = 0;
    int ConfidenceIdx = 100;

    bool DisplayDisp = true;
    bool displayConfidenceMap = false;

    cv::Mat disp(height, width, CV_8UC4);
    cv::Mat anaplyph(height, width, CV_8UC4);
    cv::Mat confidencemap(height, width, CV_8UC4);

    cv::Size DisplaySize(720, 404);
    cv::Mat dispDisplay(DisplaySize, CV_8UC4);
    cv::Mat anaplyphDisplay(DisplaySize, CV_8UC4);
    cv::Mat confidencemapDisplay(DisplaySize, CV_8UC4);

    /* Init mouse callback */
	sl::zed::Mat depth;
    zed->grab(dm_type);
	depth = zed->retrieveMeasure(sl::zed::MEASURE::DEPTH); // Get the pointer
    // Set the structure
    mouseStruct._image = cv::Size(width, height);
    mouseStruct._resize = DisplaySize;
    mouseStruct.data = (float*) depth.data;
    mouseStruct.step = depth.step;
    mouseStruct.name = "DEPTH";
    /***/

    //create Opencv Windows
    cv::namedWindow(mouseStruct.name, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(mouseStruct.name, onMouseCallback, (void*) &mouseStruct);
    cv::namedWindow("VIEW", cv::WINDOW_AUTOSIZE);

    std::cout<< "Press 'q' to exit"<<std::endl;


    //loop until 'q' is pressed
    while (key != 'q') {
        // DisparityMap filtering
        //zed->setDispReliability(reliabilityIdx); !!function name has been change in Release 0.8 --see ChangeLog
        zed->setConfidenceThreshold(ConfidenceIdx);

        // Get frames and launch the computation
        bool res = zed->grab(dm_type);

		depth = zed->retrieveMeasure(sl::zed::MEASURE::DEPTH); // Get the pointer

        // The following is the best way to save a disparity map/ Image / confidence map in Opencv Mat.
        // Be Careful, if you don't save the buffer/data on your own, it will be replace by a next retrieve (retrieveImage, NormalizeMeasure, getView....)
        // !! Disparity, Depth, confidence are in 8U,C4 if normalized format !! //
        // !! Disparity, Depth, confidence are in 32F,C1 if only retrieve !! //

        /***************  DISPLAY:  ***************/
        // Normalize the DISPARITY / DEPTH map in order to use the full color range of grey level image
        if (DisplayDisp)
			slMat2cvMat(zed->normalizeMeasure(sl::zed::MEASURE::DISPARITY)).copyTo(disp);
        else
			slMat2cvMat(zed->normalizeMeasure(sl::zed::MEASURE::DEPTH)).copyTo(disp);


        // To get the depth at a given position, click on the DISPARITY / DEPTH map image
        cv::resize(disp, dispDisplay, DisplaySize);
        imshow(mouseStruct.name, dispDisplay);

        if (displayConfidenceMap) {
			slMat2cvMat(zed->normalizeMeasure(sl::zed::MEASURE::CONFIDENCE)).copyTo(confidencemap);
            cv::resize(confidencemap, confidencemapDisplay, DisplaySize);
            imshow("confidence", confidencemapDisplay);
        }

        //Even if Left and Right images are still available through getView() function, it's better since v0.8.1 to use retrieveImage for cpu readback because GPU->CPU is done async during depth estimation.
        // Therefore :
        // -- if disparity estimation is enabled in grab function, retrieveImage will take no time because GPU->CPU copy has already been done during disp estimation
        // -- if disparity estimation is not enabled, GPU->CPU copy is done in retrieveImage fct, and this function will take the time of copy.
        if (ViewID == sl::zed::STEREO_LEFT || ViewID == sl::zed::STEREO_RIGHT)
			slMat2cvMat(zed->retrieveImage(static_cast<sl::zed::SIDE> (ViewID))).copyTo(anaplyph);
        else
			slMat2cvMat(zed->getView(static_cast<sl::zed::VIEW_MODE> (ViewID))).copyTo(anaplyph);

        cv::resize(anaplyph, anaplyphDisplay, DisplaySize);
        imshow("VIEW", anaplyphDisplay);

        key = cv::waitKey(5);

        // Keyboard shortcuts
        switch (key) {
                // ______________  THRESHOLD __________________
            case 'b':
                ConfidenceIdx -= 10;
                break;
            case 'n':
                ConfidenceIdx += 10;
                break;

                //re-compute stereo alignment
            case 'a':
                zed->reset();
                break;

                //Change camera settings (here --> gain)
            case 'g': //increase gain of 1
            {
                int current_gain = zed->getCameraSettingsValue(sl::zed::ZED_GAIN) + 1;
                zed->setCameraSettingsValue(sl::zed::ZED_GAIN, current_gain);
				std::cout << "set Gain to " << current_gain << std::endl;
            }
                break;

            case 'h': //decrease gain of 1
            {
                int current_gain = zed->getCameraSettingsValue(sl::zed::ZED_GAIN) - 1;
                zed->setCameraSettingsValue(sl::zed::ZED_GAIN, current_gain);
				std::cout << "set Gain to " << current_gain << std::endl;
            }
                break;


                // ______________  VIEW __________________
            case '0': // left
                ViewID = 0;
                break;
            case '1': // right
                ViewID = 1;
                break;
            case '2': // anaglyph
                ViewID = 2;
                break;
            case '3': // gray scale diff
                ViewID = 3;
                break;
            case '4': // Side by side
                ViewID = 4;
                break;
            case '5': // overlay
                ViewID = 5;
                break;

                // ______________  Display Confidence Map __________________
            case 's':
                displayConfidenceMap = !displayConfidenceMap;
                break;

                //______________ SAVE ______________
            case 'w': // image
				saveSbSimage(zed, std::string("ZEDImage") + std::to_string(count) + std::string(".png"));
                count++;
                break;

            case 'v': // disparity
            {
				std::string filename = std::string(("ZEDDisparity") + std::to_string(count) + std::string(".png"));
                cv::Mat dispSnapshot;
                disp.copyTo(dispSnapshot);
                cv::imshow("Saving Disparity", dispSnapshot);
                cv::imwrite(filename, dispSnapshot);
                count++;
                break;
            }

            case 'r':
				dm_type = sl::zed::SENSING_MODE::RAW;
				std::cout << "SENSING_MODE: Raw" << std::endl;
                break;
            case 'f':
				dm_type = sl::zed::SENSING_MODE::FULL;
				std::cout << "SENSING_MODE: FULL" << std::endl;
                break;

            case 'd':
                DisplayDisp = !DisplayDisp;
                break;
        }

        ConfidenceIdx = ConfidenceIdx < 1 ? 1 : ConfidenceIdx;
        ConfidenceIdx = ConfidenceIdx > 100 ? 100 : ConfidenceIdx;
    }

    delete zed;
    return 0;
}
