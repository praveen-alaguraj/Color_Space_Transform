#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image.h"
#include "../libs/stb_image_write.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// RGB to Grayscale (Luminance-Based)
unsigned char rgb_to_grayscale(unsigned char r, unsigned char g, unsigned char b) {
    return static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
}

// RGB to XYZ
void rgb_to_xyz(unsigned char r, unsigned char g, unsigned char b, float& x, float& y, float& z) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    rf = (rf > 0.04045f) ? std::pow((rf + 0.055f) / 1.055f, 2.4f) : (rf / 12.92f);
    gf = (gf > 0.04045f) ? std::pow((gf + 0.055f) / 1.055f, 2.4f) : (gf / 12.92f);
    bf = (bf > 0.04045f) ? std::pow((bf + 0.055f) / 1.055f, 2.4f) : (bf / 12.92f);

    x = rf * 0.4124f + gf * 0.3576f + bf * 0.1805f;
    y = rf * 0.2126f + gf * 0.7152f + bf * 0.0722f;
    z = rf * 0.0193f + gf * 0.1192f + bf * 0.9505f;
}

// RGB to HSI
void rgb_to_hsi(unsigned char r, unsigned char g, unsigned char b, float& h, float& s, float& i) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    i = (rf + gf + bf) / 3.0f;

    float min_val = std::min(rf, std::min(gf, bf));

    if (i == 0) {
        s = 0;
    } else {
        s = 1 - (min_val / i);
    }

    if (s == 0) {
        h = 0;
    } else {
        float num = ((rf - gf) + (rf - bf)) / 2.0f;
        float den = std::sqrt((rf - gf) * (rf - gf) + (rf - bf) * (gf - bf));
        float theta = std::acos(num / den);

        h = (bf > gf) ? (2 * M_PI - theta) : theta;
        h = h * (180.0f / M_PI);
    }
}

// RGB to HSV
void rgb_to_hsv(unsigned char r, unsigned char g, unsigned char b, float& h, float& s, float& v) {
    float rf = r / 255.0f;
    float gf = g / 255.0f;
    float bf = b / 255.0f;

    float max_val = std::max({rf, gf, bf});
    float min_val = std::min({rf, gf, bf});
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

// RGB to LAB (via XYZ)
void rgb_to_lab(unsigned char r, unsigned char g, unsigned char b, float& l, float& a, float& b_val) {
    float x, y, z;
    rgb_to_xyz(r, g, b, x, y, z);

    x /= 0.95047; y /= 1.00000; z /= 1.08883;

    x = (x > 0.008856) ? std::pow(x, 1.0 / 3.0) : (7.787 * x + 16.0 / 116.0);
    y = (y > 0.008856) ? std::pow(y, 1.0 / 3.0) : (7.787 * y + 16.0 / 116.0);
    z = (z > 0.008856) ? std::pow(z, 1.0 / 3.0) : (7.787 * z + 16.0 / 116.0);

    l = (116 * y) - 16;
    a = 500 * (x - y);
    b_val = 200 * (y - z);
}

// Processing function
void process_image(const std::string& inputImagePath, const std::string& outputDir) {
    int width, height, channels;
    unsigned char* imageData = stbi_load(inputImagePath.c_str(), &width, &height, &channels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << inputImagePath << std::endl;
        return;
    }

    std::vector<unsigned char> grayscaleImage(width * height);
    std::vector<unsigned char> xyzImage(width * height * 3);
    std::vector<unsigned char> hsiImage(width * height * 3);
    std::vector<unsigned char> hsvImage(width * height * 3);
    std::vector<unsigned char> labImage(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = (y * width + x) * channels;
            unsigned char r = imageData[idx];
            unsigned char g = imageData[idx + 1];
            unsigned char b = imageData[idx + 2];

            // Grayscale
            grayscaleImage[y * width + x] = rgb_to_grayscale(r, g, b);

            // XYZ
            float x_val, y_xyz, z;
            rgb_to_xyz(r, g, b, x_val, y_xyz, z);
            xyzImage[idx] = static_cast<unsigned char>(x_val * 255);
            xyzImage[idx + 1] = static_cast<unsigned char>(y_xyz * 255);
            xyzImage[idx + 2] = static_cast<unsigned char>(z * 255);

            // HSI
            float h_hsi, s_hsi, i;
            rgb_to_hsi(r, g, b, h_hsi, s_hsi, i);
            hsiImage[idx] = static_cast<unsigned char>(h_hsi / 360.0f * 255);
            hsiImage[idx + 1] = static_cast<unsigned char>(s_hsi * 255);
            hsiImage[idx + 2] = static_cast<unsigned char>(i * 255);

            // HSV
            float h, s, v;
            rgb_to_hsv(r, g, b, h, s, v);
            hsvImage[idx] = static_cast<unsigned char>(h / 360.0f * 255);
            hsvImage[idx + 1] = static_cast<unsigned char>(s * 255);
            hsvImage[idx + 2] = static_cast<unsigned char>(v * 255);

            // LAB
            float l, a, b_val;
            rgb_to_lab(r, g, b, l, a, b_val);
            labImage[idx] = static_cast<unsigned char>(l / 100.0f * 255);
            labImage[idx + 1] = static_cast<unsigned char>((a + 128) / 255.0f * 255);
            labImage[idx + 2] = static_cast<unsigned char>((b_val + 128) / 255.0f * 255);
        }
    }

    // Save images
    stbi_write_png((outputDir + "grayscale.png").c_str(), width, height, 1, grayscaleImage.data(), width);
    stbi_write_png((outputDir + "xyz.png").c_str(), width, height, 3, xyzImage.data(), width * 3);
    stbi_write_png((outputDir + "hsi.png").c_str(), width, height, 3, hsiImage.data(), width * 3);
    stbi_write_png((outputDir + "hsv.png").c_str(), width, height, 3, hsvImage.data(), width * 3);
    stbi_write_png((outputDir + "lab.png").c_str(), width, height, 3, labImage.data(), width * 3);

    stbi_image_free(imageData);
    std::cout << "Images saved to " << outputDir << std::endl;
}

int main() {
    const std::string inputDir = "../input/";
    const std::string outputDir = "../output/";

    if (!fs::exists(outputDir)) fs::create_directory(outputDir);

    std::string inputFileName;
    std::cout << "Enter the input image file name (e.g., image.png): ";
    std::cin >> inputFileName;

    process_image(inputDir + inputFileName, outputDir);

    return 0;
}
