# Face Detection Program using OpenCV

Team: Luis Felipe Urquijo, David Alvarez, David Londono, Jose Miguel Munoz.
link video: https://youtu.be/458GXrXW0Ik

## Description

This C++ program detects faces in a given JPEG image using OpenCV’s Haar Cascade classifier. It marks the detected faces on the original image, saves the marked image, and extracts each detected face into individual image files. The program is parallelized with OpenMP to improve performance by processing face detection and saving operations concurrently.

## Requirements

Before running the program, ensure you have the following dependencies installed:

- **C++ Compiler** (g++, clang++, etc.)
- **OpenCV** (version 4.x)
- **OpenMP**

## Installation of Required Libraries (Ubuntu in my case)

1. **Clone the Repository:**
   ```bash
    git clone https://github.com/LuisFelipeU38/faceDetector.git
2. **Install OpenCV:**
   ```bash
    sudo apt-get update
    sudo apt-get install libopencv-dev
3. **Install OpenMP:**
   ```bash
    sudo apt-get install gcc
## Usage

1. **Compile the program using the provided Makefile:**
    ```bash
    make
    make 'IMAGE=image_path.jpg'

