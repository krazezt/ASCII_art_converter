#include "read_img.cpp"
#include <fstream>

char ascii_art[16] = {'@', '&', '$', 'W', 'B', 'G', '#', '8', 'a', 'o', 'c', '+', '~', '-', '.', ' '};

int main(int argc, char const *argv[])
{
    while (1) {
        std::string file_dir = "../images/", filename;
        std::cout << "Input image file name, nothing = exit : ";
        std::cin >> filename;
        if (filename[0] == '\0') break;
        file_dir.append(filename);
        file_dir.append(".png");
        int *img_info = new int[3];
        img_info[2] = 100;
        unsigned char *data = read_img(file_dir, &img_info);

        int sizeX = img_info[1], sizeY = img_info[2];
        int *hex_data = read_data(data, img_info);

        std::cout << "Data reading finished!\n";

        std::ofstream outfile;
        std::string output_filename = filename;
        output_filename.append(".txt");
        outfile.open(output_filename);

        for (int i = 0; i < sizeY; i+=2) {
            for (int j = 0; j < sizeX; j++) {
                //std::cout << i << '-' << j << '-' << hex_data[i*sizeX+j] << ' ';
                outfile << ascii_art[hex_data[i*sizeX+j]];
            }
            outfile << "\n";
        }
        std::cout << "Done!\n";
        outfile.close();
    }
    return 0;
}
