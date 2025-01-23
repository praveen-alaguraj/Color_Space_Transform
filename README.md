
# Color Space Transformation Project

## Overview
This project implements **color space transformations** from RGB Color Space to the following commonly used Color Spaces using C++. It reads an input image from an input folder, processes it to perform transformations, and saves the resulting images in an output folder. The transformations include:

- **Grayscale**
- **HSV (Hue, Saturation, Value)**
- **HSI (Hue, Saturation, Intensity)**
- **LAB (Perceptually Uniform Color Space)**
- **XYZ (Device-Independent Reference Color Space)**

The implementation follows standard methods, ensuring accurate transformations.

---

## Features
- Reads images from the **`input/`** folder.
- Processes the image to generate output transformations.
- Saves transformed images in the **`output/`** folder.
- Implements standard image processing formulas for high accuracy.
- Modular and extensible code structure for easy updates.

---

## Prerequisites

### Dependencies
- **stb_image and stb_image_write**:
  - Included in the `libs/` directory of the project.
  - No additional installation is required.

### Installation Steps
1. **Install CMake**:
   - Download CMake from [cmake.org](https://cmake.org/) and ensure its `bin` directory is added to your `Path` environment variable.

2. **Install VS Code Extensions** (optional):
   - Install the following extensions from the VS Code marketplace:
     - [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
     - [CMake](https://marketplace.visualstudio.com/items?itemName=twxs.cmake)
     - [C++ Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

3. **Install MinGW-w64 (compiler for Windows)**:
   - Download MinGW-w64 from [MinGW GitHub](https://github.com/niXman/mingw-builds-binaries/releases).
   - Used version: `x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0`
   - Add the `bin` directory of the MinGW-w64 installation to your `Path` environment variable.

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
- Navigate to the `bin/` directory and execute the program:
```bash
./Color_Space_Transforms
```
- Enter the name of your input file (e.g., `image.png`) when prompted.

### 5. Check the Output
- Processed images will be saved in the **`output/`** folder with descriptive names, such as:
  - `grayscale.png`
  - `xyz.png`
  - `hsi.png`
  - `hsv.png`
  - `lab.png`

---

## Color Space Transformations

### 1. Grayscale
Converts an RGB image to grayscale using the formula:
```
Gray = 0.299 * R + 0.587 * G + 0.114 * B
```

### 2. HSV
Transforms RGB to the Hue, Saturation, and Value model:
- **Hue (H):** Angular position on the color wheel.
- **Saturation (S):** Purity of the color.
- **Value (V):** Brightness.

### 3. HSI
Similar to HSV but uses intensity instead of value, making it more aligned with human perception:
- **Hue (H):** Angle on the color wheel.
- **Saturation (S):** Ratio of chromatic content.
- **Intensity (I):** Average brightness.

### 4. LAB
Converts RGB to LAB via the XYZ color space for perceptual uniformity:
- **L (Lightness):** Brightness of the color.
- **A:** Green-Red chromatic content.
- **B:** Blue-Yellow chromatic content.

### 5. XYZ
Device-independent color space derived from RGB using:
- **Gamma correction**
- **Matrix transformation**
  
---

## Example

### Input:
`input/image.png`

### Output:
Files in `output/`:
- `grayscale.png`
- `xyz.png`
- `hsi.png`
- `hsv.png`
- `lab.png`

---

## Acknowledgments
- **stb_image**: Image loading library by Sean Barrett.
- **stb_image_write**: Image writing library by Sean Barrett.
- **stb GitHub**: [STB GitHub](https://github.com/nothings/stb)

---

## Future Enhancements
- Add support for additional color spaces (e.g., YUV, YCbCr).
- Integrate an interactive GUI for real-time transformations.
- Optimize performance for larger images.

---

## Contact
For questions or feedback, feel free to reach out:
- **Email**: praveen.alaguraj@uni-weimar.de, hari.prasad.pullari@uni-weimar.de
