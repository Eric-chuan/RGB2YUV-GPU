#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>

extern "C" void convert_rgb_to_yu12(uint8_t *input, uint8_t *output);

int main()
{
    int width = 3840, height = 2160;
    size_t size = width * height * 3;
    FILE *color_file_input, *yuv_file_output;
    uint8_t* color_frame_input = (uint8_t*)malloc(size * sizeof(uint8_t));
    uint8_t* yuv_output = (uint8_t*)malloc(size * sizeof(uint8_t) / 2);
    if ((color_file_input = fopen("../data/input.yuv", "rb")) == NULL){
        printf("cannot ---open this file\n");
        return 0;
    }
    int count = 0;
    if((count = fread(color_frame_input, 1, height * width * 3, color_file_input)) != width * height * 3){
        fseek(color_file_input, 0, SEEK_SET);
		count = fread(color_frame_input, 1, height * width * 3, color_file_input);
    }

    timeval start, end;
    gettimeofday(&start, NULL);
    convert_rgb_to_yu12(color_frame_input, yuv_output);
    gettimeofday(&end, NULL);
    printf("convert time = %f\n", (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0);

    //output to yuv file
    if ((yuv_file_output = fopen("../output.yuv", "wb")) == NULL){
        printf("cannot ---open this file\n");
        return 0;
    }
    fwrite(yuv_output, sizeof(uint8_t), size / 2, yuv_file_output);

    //output to png file by opencv
    // std::string filename="out.png";
    // cv::Mat yuvImg;
    // yuvImg.create(height * 3 / 2, width, CV_8UC1);
    // memcpy(yuvImg.data, yuv_output, size / 2 * sizeof(uint8_t));
    // cv::Mat rgb_img;
    // cv::cvtColor(yuvImg, rgb_img, CV_YUV2BGR_I420);
    // cv::imwrite(filename, rgb_img);
    fclose(color_file_input);
    fclose(yuv_file_output);
    return 1;
}