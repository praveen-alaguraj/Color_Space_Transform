# Color Space Transformation Project

## Overview
This project implements **color space transformations** from RGB Color Space to the below listed Color Space in C++. It reads an image from an input folder, process it to perform transformations, and save the resulting images in an output folder. The transformations include:

- Grayscale
- HSV (Hue, Saturation, Value)
- HSL (Hue, Saturation, Lightness)
- YCbCr (Luminance and Chrominance)
- LAB (Perceptually Uniform Color Space)

The implementation is modular, adhering to image processing standards such as ITU-R BT.601 and sRGB.

---

## Features
- Reads images from the **`input/`** folder.
- Saves output transformations in the **`output/`** folder.
- Uses know well-established formulas and conversion standards.
- Modular and easy-to-extend code structure.

---

## Prerequisites

### Dependencies
- **stb_image and stb_image_write**:
  - Included in the `libs/` directory of the project.
  - No additional installation is required for these libraries.

### Installation Steps
1. **Install CMake**:
   - Download CMake from [cmake.org](https://cmake.org/) and ensure its `bin` directory is added to your `Path` environment variable.
   - Follow the steps outlined [here](https://docs.microsoft.com/en-us/previous-versions/office/developer/sharepoint-2010/ee537574(v=office.14)) for setting up the Path.

2. **Install VS Code Extensions**:
   - Install the following extensions from the VS Code marketplace:
     - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
     - [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
     - [CPP-Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

3. **Install MinGW-w64 (compiler for Windows)**:
   - Download MinGW-w64 from [MinGW Github](https://github.com/niXman/mingw-builds-binaries/releases) and ensure to download the latest version. 
   - Used version - `x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0`
   - Add the `bin` directories of the MinGW-w64 installation to your `Path` environment variable. If you download both x86 and x64 versions, add both to the Path.

4. **Verify Setup**:
   - Ensure CMake and GCC are accessible from the command line by running:
     ```bash
     cmake --version
     gcc --version
     ```

---

## How to Use

### 1. Clone the Repository
```bash
git clone https://github.com/praveen-alaguraj/Color_Space_Transforms
cd project
```

### 2. Build the Project
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

### 3. Prepare Input Image
- Place your input image in the **`input/`** folder.

### 4. Run the Executable
- Navigate to the `build/` directory and execute the program:
```bash
./Color_Space_Transforms
```
- Enter the name of your input file (e.g., `image.png`) when prompted.

### 5. Check the Output
- Processed images will be saved in the **`output/`** folder with descriptive names, such as:
  - `image_grayscale.png`
  - `image_hsv.png`
  - `image_hsl.png`
  - `image_ycbcr.png`
  - `image_lab.png`

---

## Color Space Transformations

### 1. Grayscale
Converts an RGB image to grayscale using the formula:
```
Gray = 0.299 * R + 0.587 * G + 0.114 * B
```

### 2. HSV
Transforms RGB to the Hue, Saturation, and Value model:
- Hue is calculated as the angular position on the color wheel.
- Saturation represents the purity of color.
- Value is the brightness.

### 3. HSL
Similar to HSV but uses lightness instead of value for better midtone representation.

### 4. YCbCr
Separates the luminance (Y) and chrominance (Cb, Cr) components using the ITU-R BT.601 standard.

### 5. LAB
Converts RGB to LAB via the XYZ color space for a perceptually uniform representation.

---

## Example

### Input:
`input/image.png`

### Output:
Files in `output/`:
- `image_grayscale.png`
- `image_hsv.png`
- `image_hsl.png`
- `image_ycbcr.png`
- `image_lab.png`

---

## Acknowledgments
- **stb_image**: Image loading library by Sean Barrett.
- **stb_image_write**: Image writing library by Sean Barrett.
- **stb downloaded link**: [STB Github](https://github.com/nothings/stb/tree/master)

---

## Future Enhancements
- Support for additional color spaces (e.g., YUV, CIE L*u*v*).
- Interactive GUI for real-time transformations.
- Performance optimizations for larger images.

---

## Contact
For questions or feedback, feel free to reach out:
- **Email**: praveen.alaguraj@uni-weimar.de, hari.prasad.pullari@uni-weimar.de
- **GitHub**: https://github.com/praveen-alaguraj

