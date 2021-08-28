#include <iostream>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "../stb_lib/stb_image.h"
}

unsigned char* read_img(std::string filename, int** output_img_info)
{
    int x, y, n;
    unsigned char *data = stbi_load(filename.c_str(), &x, &y, &n, 0);

    if (data != nullptr && x > 0 && y > 0)
    {
        (*output_img_info)[0] = n;
        (*output_img_info)[1] = x;
        (*output_img_info)[2] = y;
        return data;
    } else {
        std::cout << "Error !\n";
        return data;
    }
}

int* read_data(unsigned char* data, int* img_info)              // return an x*y array that saves values of each x*y pixels
{
    int sizeX = img_info[1], sizeY = img_info[2];
    int *result = new int[sizeX*sizeY];

    if (img_info[0] == 3) {
        for  (int i = 0; i < sizeY; i++)
            for (int j = 0; j < sizeX; j++) {   //Trung bình cộng 3 màu :)))
                result[i*sizeX+j] = (
                    static_cast<int>(data[(i*sizeX+j)*3]) +
                    static_cast<int>(data[(i*sizeX+j)*3+1]) +
                    static_cast<int>(data[(i*sizeX+j)*3+2])
                    )/48;                       //48 = 3*16, thang mô phỏng màu có 16 mức :))
            }
    }

    stbi_image_free(data);
    return result;
}