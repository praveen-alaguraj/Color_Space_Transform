#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image.h"
#include "../libs/stb_image_write.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <filesystem> // For creating output folder

namespace fs = std::filesystem;

// Function to convert RGB to Grayscale
unsigned char rgb_to_grayscale(unsigned char r, unsigned char g, unsigned char b) {
    return static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
}

// Function to convert RGB to HSV
void rgb_to_hsv(unsigned char r, unsigned char g, unsigned char b, float& h, float& s, float& v) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max_val = std::fmax(rf, std::fmax(gf, bf));
    float min_val = std::fmin(rf, std::fmin(gf, bf));
    float delta = max_val - min_val;

    v = max_val;

    if (delta == 0) {
        h = 0;
        s = 0;
    } else {
        s = delta / max_val;

        if (max_val == rf) {
            h = 60 * fmod(((gf - bf) / delta), 6);
        } else if (max_val == gf) {
            h = 60 * (((bf - rf) / delta) + 2);
        } else {
            h = 60 * (((rf - gf) / delta) + 4);
        }

        if (h < 0) h += 360;
    }
}

// Function to convert RGB to YCbCr
void rgb_to_ycbcr(unsigned char r, unsigned char g, unsigned char b, unsigned char& y, unsigned char& cb, unsigned char& cr) {
    y = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
    cb = static_cast<unsigned char>(128 - 0.168736 * r - 0.331264 * g + 0.5 * b);
    cr = static_cast<unsigned char>(128 + 0.5 * r - 0.418688 * g - 0.081312 * b);
}

// Function to convert RGB to LAB via XYZ
void rgb_to_lab(unsigned char r, unsigned char g, unsigned char b, float& l, float& a, float& b_val) {
    // Convert RGB to normalized XYZ
    float rf = r / 255.0f, gf = g / 255.0f, bf = b / 255.0f;

    rf = (rf > 0.04045) ? std::pow((rf + 0.055) / 1.055, 2.4) : (rf / 12.92);
    gf = (gf > 0.04045) ? std::pow((gf + 0.055) / 1.055, 2.4) : (gf / 12.92);
    bf = (bf > 0.04045) ? std::pow((bf + 0.055) / 1.055, 2.4) : (bf / 12.92);

    float x = rf * 0.4124564 + gf * 0.3575761 + bf * 0.1804375;
    float y = rf * 0.2126729 + gf * 0.7151522 + bf * 0.0721750;
    float z = rf * 0.0193339 + gf * 0.1191920 + bf * 0.9503041;

    x /= 0.95047; y /= 1.00000; z /= 1.08883;

    x = (x > 0.008856) ? std::pow(x, 1.0 / 3.0) : (7.787 * x + 16.0 / 116.0);
    y = (y > 0.008856) ? std::pow(y, 1.0 / 3.0) : (7.787 * y + 16.0 / 116.0);
    z = (z > 0.008856) ? std::pow(z, 1.0 / 3.0) : (7.787 * z + 16.0 / 116.0);

    l = (116 * y) - 16;
    a = 500 * (x - y);
    b_val = 200 * (y - z);
}

// Function to convert RGB to HSL
void rgb_to_hsl(unsigned char r, unsigned char g, unsigned char b, float& h, float& s, float& l) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max_val = std::fmax(rf, std::fmax(gf, bf));
    float min_val = std::fmin(rf, std::fmin(gf, bf));
    float delta = max_val - min_val;

    l = (max_val + min_val) / 2;

    if (delta == 0) {
        h = 0;
        s = 0;
    } else {
        s = (l > 0.5) ? delta / (2 - max_val - min_val) : delta / (max_val + min_val);

        if (max_val == rf) {
            h = 60 * fmod(((gf - bf) / delta), 6);
        } else if (max_val == gf) {
            h = 60 * (((bf - rf) / delta) + 2);
        } else {
            h = 60 * (((rf - gf) / delta) + 4);
        }

        if (h < 0) h += 360;
    }
}

int main() {
    // Define input and output directories
    const std::string inputDir = "../input/";
    const std::string outputDir = "../output/";

    // Ensure output folder exists
    if (!fs::exists(outputDir)) {
        fs::create_directory(outputDir);
    }

    // Ask user for the input file name
    std::string inputFileName;
    std::cout << "Enter the input image file name (e.g., image.png): ";
    std::cin >> inputFileName;

    // Construct full input and output paths
    std::string inputImagePath = inputDir + inputFileName;
    std::string baseName = inputFileName.substr(0, inputFileName.find_last_of('.'));
    std::string grayscaleOutputPath = outputDir + baseName + "_grayscale.png";
    std::string hsvOutputPath = outputDir + baseName + "_hsv.png";
    std::string ycbcrOutputPath = outputDir + baseName + "_ycbcr.png";
    std::string labOutputPath = outputDir + baseName + "_lab.png";
    std::string hslOutputPath = outputDir + baseName + "_hsl.png";

    // Load the input image
    int width, height, channels;
    unsigned char* imageData = stbi_load(inputImagePath.c_str(), &width, &height, &channels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << inputImagePath << std::endl;
        return -1;
    }

    if (channels < 3) {
        std::cerr << "The input image does not have enough channels for RGB processing." << std::endl;
        stbi_image_free(imageData);
        return -1;
    }

    // Allocate memory for output images
    std::vector<unsigned char> grayscaleImage(width * height);
    std::vector<unsigned char> hsvImage(width * height * 3);
    std::vector<unsigned char> ycbcrImage(width * height * 3);
    std::vector<unsigned char> labImage(width * height * 3);
    std::vector<unsigned char> hslImage(width * height * 3);

    // Process pixels
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * channels;
            unsigned char r = imageData[idx];
            unsigned char g = imageData[idx + 1];
            unsigned char b = imageData[idx + 2];

            // Convert to Grayscale
            grayscaleImage[y * width + x] = rgb_to_grayscale(r, g, b);

            // Convert to HSV
            float h, s, v;
            rgb_to_hsv(r, g, b, h, s, v);
            hsvImage[idx] = static_cast<unsigned char>(h / 360.0f * 255);
            hsvImage[idx + 1] = static_cast<unsigned char>(s * 255);
            hsvImage[idx + 2] = static_cast<unsigned char>(v * 255);

            // Convert to YCbCr
            unsigned char yVal, cb, cr;
            rgb_to_ycbcr(r, g, b, yVal, cb, cr);
            ycbcrImage[idx] = yVal;
            ycbcrImage[idx + 1] = cb;
            ycbcrImage[idx + 2] = cr;

            // Convert to LAB
            float l, a, b_val;
            rgb_to_lab(r, g, b, l, a, b_val);
            labImage[idx] = static_cast<unsigned char>(l / 100.0f * 255);
            labImage[idx + 1] = static_cast<unsigned char>((a + 128) / 255.0f * 255);
            labImage[idx + 2] = static_cast<unsigned char>((b_val + 128) / 255.0f * 255);

            // Convert to HSL
            float h_hsl, s_hsl, l_hsl;
            rgb_to_hsl(r, g, b, h_hsl, s_hsl, l_hsl);
            hslImage[idx] = static_cast<unsigned char>(h_hsl / 360.0f * 255);
            hslImage[idx + 1] = static_cast<unsigned char>(s_hsl * 255);
            hslImage[idx + 2] = static_cast<unsigned char>(l_hsl * 255);
        }
    }

    // Save the output images
    stbi_write_png(grayscaleOutputPath.c_str(), width, height, 1, grayscaleImage.data(), width);
    stbi_write_png(hsvOutputPath.c_str(), width, height, 3, hsvImage.data(), width * 3);
    stbi_write_png(ycbcrOutputPath.c_str(), width, height, 3, ycbcrImage.data(), width * 3);
    stbi_write_png(labOutputPath.c_str(), width, height, 3, labImage.data(), width * 3);
    stbi_write_png(hslOutputPath.c_str(), width, height, 3, hslImage.data(), width * 3);

    std::cout << "Images have been saved in the output folder: " << outputDir << std::endl;

    // Free the input image memory
    stbi_image_free(imageData);

    return 0;
}