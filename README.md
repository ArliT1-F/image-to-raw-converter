# 🖼️ Image to Raw Converter

A lightweight, client-side web application that converts images into raw pixel data formats (BGR, RGB, BGRA, RGBA). No server required, no data uploaded anywhere - everything runs in your browser.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![HTML5](https://img.shields.io/badge/html5-%23E34F26.svg?style=flat&logo=html5&logoColor=white)
![JavaScript](https://img.shields.io/badge/javascript-%23323330.svg?style=flat&logo=javascript&logoColor=%23F7DF1E)

## 🌟 Features

- ✅ **100% Client-Side** - No server uploads, all processing happens in your browser
- ✅ **Universal Image Support** - PNG, JPEG, WebP, BMP, GIF, and more
- ✅ **Multiple Pixel Formats** - BGR, RGB, BGRA, RGBA
- ✅ **Optional Metadata Headers** - Include width, height, and format information
- ✅ **Batch Conversion** - Convert multiple images at once
- ✅ **Image Resizing** - Scale images by percentage before conversion
- ✅ **Custom Dimensions** - Crop or pad to specific sizes with multiple modes
- ✅ **Progress Indicator** - Real-time progress tracking for all operations
- ✅ **Drag & Drop Interface** - Simple and intuitive UI
- ✅ **Live Preview** - See your image and conversion details instantly
- ✅ **Zero Dependencies** - Pure HTML, CSS, and JavaScript
- ✅ **Self-Hostable** - Run it anywhere, even offline

## 🎯 Use Cases

- **Computer Vision** - Prepare training data for OpenCV, TensorFlow, PyTorch
- **Embedded Systems** - Convert images for microcontroller displays
- **Game Development** - Extract raw texture data
- **Image Processing** - Direct pixel manipulation in custom applications
- **Research & Education** - Understand image data structures

## 🔧 How It Works

### The Conversion Process

1. **Image Loading**: When you upload an image, the browser's native image decoder handles format conversion (JPEG, PNG, WebP, etc.)

2. **Image Processing** (Optional):
   - **Scaling**: If enabled, image is resized by percentage (e.g., 50% = half size)
   - **Custom Dimensions**: Image is resized to specific dimensions with chosen mode:
     - *Stretch*: Resizes to exact dimensions
     - *Fit*: Maintains aspect ratio, fits within bounds
     - *Fill*: Maintains aspect ratio, crops to fill bounds

3. **Canvas Rendering**: The image is drawn onto an HTML5 Canvas element at target dimensions

4. **Pixel Extraction**: Using `getImageData()`, the canvas provides RGBA pixel data in a flat array:
    `[R, G, B, A, R, G, B, A, R, G, B, A, ...]`

5. **Channel Reordering**: Pixels are reordered based on your selected format:
   - **BGR**: `[B, G, R, B, G, R, ...]`
   - **RGB**: `[R, G, B, R, G, B, ...]`
   - **BGRA**: `[B, G, R, A, B, G, R, A, ...]`
   - **RGBA**: `[R, G, B, A, R, G, B, A, ...]`

6. **Metadata (Optional)**: A 12-byte header is prepended:
   - ***Bytes 0-3***: Width (uint32, little-endian)
   - ***Bytes 4-7***: Height (uint32, little-endian)
   - ***Bytes 8-11***: Format Code (uint32, little-endian)
   - ***1 = BGRA, 2 = RGBA, 3 = BGR, 4 = RGB***

7. **File Export**: The raw binary data is downloaded as a `.raw` file

### Batch Processing
When multiple images are uploaded:
- All images are processed in parallel
- Each image gets the same settings (format, scaling, dimensions)
- Progress is tracked per image
- Downloads occur sequentially with 200ms delays to prevent browser blocking

### Data Structure Example
For a 2x2 pixel image in BGR format without metadata:
```
Pixel (0,0): Blue=255, Green=128, Red=64
Pixel (1,0): Blue=200, Green=100, Red=50
Pixel (0,1): Blue=180, Green=90, Red=45
Pixel (1,1): Blue=160, Green=80, Red=40
```

***Raw file bytes***:
[255, 128, 64, 200, 100, 50, 180, 90, 45, 160, 80, 40]


## 📦 Setup

### Option 1: Local File (Recommended)

1. Download `index.html` from this repository
2. Open it directly in any modern web browser
3. That's it! No installation needed.

### Option 2: Self-Hosted Web Server

1. Clone the repository:
   ```bash
   git clone https://github.com/ArliT1-F/image-to-raw-converter.git
   cd image-to-raw-converter
   ```
2. Serve using any static file server:
   
   **Python 3**:
   ```bash
   python -m http.server 8000
   ```
   
   **Node.js (with http-server)**:
   ```bash
   npx http-server -p 8000
   ```
   
   **PHP**:
   ```bash
   php -S localhost:8000
   ```

3. Open `http://localhost:8000` in your browser

### Option 3: GitHub Pages
1. Fork this repository
2. Go to Settings → Pages
3. Select main branch as source
4. Access at ```https://yourusername.github.io/image-to-raw-converter/```


## 🚀 Usage Guide

### Basic Conversion (Single Image)
1. **Upload an Image**
   - Click the upload area or drag & drop a single image file
   - Supported formats: PNG, JPEG, WebP, BMP, GIF, SVG, etc.

2. **Select Format**
   - ***BGR***: Standard for OpenCV (3 bytes/pixel)
   - ***RGB***: Standard for most libraries (3 bytes/pixel)
   - ***BGRA***: BGR with alpha channel (4 bytes/pixel)
   - ***RGBA***: RGB with alpha channel (4 bytes/pixel)

3. **Choose Options**
   - Check "Include metadata header" if you need width/height/format info
   - Unchecked = pure pixel data only

4. **Download**
   - Click "Download Raw Data"
   - File saved as `filename_format.raw` or `filename_format_meta.raw`

### Batch Conversion (Multiple Images)
1. **Upload Multiple Images**
   - Select multiple files at once OR drag & drop multiple images
   - All images will be listed in the batch processing panel

2. **Configure Settings**
   - Select channel order (BGR, RGB, BGRA, RGBA)
   - Enable/disable metadata headers
   - Apply same settings to all images

3. **Process & Download**
   - Images are processed automatically when uploaded
   - Click "Download All" to download all converted images
   - Each image downloads with a 200ms delay
   - Remove individual images from batch with the ✕ button

### Image Resizing (Scale by Percentage)
1. **Enable Scaling**
   - Check "Image scaling (resize by percentage)"
   - Enter percentage value (e.g., 50 = half size, 200 = double size)

2. **How It Works**
   - Scales both width and height by the same percentage
   - Maintains aspect ratio
   - Applied before custom dimensions
   - Works with both single and batch conversions

### Custom Dimensions
1. **Enable Custom Dimensions**
   - Check "Custom dimensions (resize image)"
   - Enter target width and height in pixels

2. **Choose Resize Mode**
   - **Stretch**: Stretches image to exact dimensions (may distort)
   - **Fit**: Maintains aspect ratio, fits within bounds (may have empty space)
   - **Fill**: Maintains aspect ratio, crops to fill bounds (may crop edges)

3. **Combined with Scaling**
   - Scaling is applied first, then custom dimensions
   - Example: 50% scale + 800x600 fit = scales to 50%, then fits in 800x600

### Progress Indicator
The progress bar shows real-time status:
- **Loading image...** (0-30%)
- **Processing image...** (60-90%)
- **Converting pixel data...** (30-60%)
- **Downloading...** (80-100%)

For batch operations, progress shows per-image completion.

## Reading the Raw Data
**Python with NumPy**:
```python
import numpy as np

# Without metadata
width, height = 1920, 1080  # You need to know dimensions
bgr_data = np.fromfile('image_bgr.raw', dtype=np.uint8)
bgr_image = bgr_data.reshape((height, width, 3))


# With metadata
with open('image_bgr_meta.raw', 'rb') as f:
    width = int.from_bytes(f.read(4), 'little')
    height = int.from_bytes(f.read(4), 'little')
    format_code = int.from_bytes(f.read(4), 'little')
    pixel_data = np.fromfile(f, dtype=np.uint8)
    bgr_image = pixel_data.reshape((height, width, 3))
```

**C/C++**:
```C
#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t format;
} ImageHeader;

// Read with metadata
FILE* f = fopen("image_bgr_meta.raw", "rb");
ImageHeader header;
fread(&header, sizeof(ImageHeader), 1, f);

uint8_t* pixels = malloc(header.width * header.height * 3);
fread(pixels, 1, header.width * header.height * 3, f);
fclose(f);
```

**OpenCV (Python)**:
```python
import cv2
import numpy as np

# Read raw BGR data
with open('image_bgr_meta.raw', 'rb') as f:
    width = int.from_bytes(f.read(4), 'little')
    height = int.from_bytes(f.read(4), 'little')
    f.read(4)  # skip format code
    bgr_data = np.fromfile(f, dtype=np.uint8)
    
img = bgr_data.reshape((height, width, 3))
cv2.imshow('Image', img)
cv2.waitKey(0)
```

**Example Terminal Output**:<br>
This output came specifically from running `read_raw.py` file, although `.cpp`, `.c` and `opencv` should give the exact same output.
```text
🖼️  Raw Image File Reader

==================================================
Example 1: Reading file WITH metadata
==================================================
📐 Dimensions: 554x554
🎨 Format: BGR
📊 Channels: 3
✅ Successfully loaded image!
📏 Shape: (554, 554, 3)
🎯 Data type: uint8
📈 Min value: 0, Max value: 255
🎨 Pixel at (0,0): [137 196 244]

==================================================
Example 2: Reading file WITHOUT metadata
==================================================
❌ Error: File size mismatch! Expected 6220800 bytes for 1920x1080x3, got 920748
```
The error happens because as mentioned above if metadata is not present, you won't be able to read the raw data file without knowing the exact dimensions.


## 📋 File Format Specifications
### Without Metadata
```text
Pure pixel data in selected format
Size = width × height × channels
```
### With Metadata
```text
[12-byte header][pixel data]

Header Structure:
- Offset 0-3:   Width (uint32_le)
- Offset 4-7:   Height (uint32_le)
- Offset 8-11:  Format Code (uint32_le)
  
Format Codes:
- 1 = BGRA (4 channels)
- 2 = RGBA (4 channels)
- 3 = BGR (3 channels)
- 4 = RGB (3 channels)
```

## 🗺️ Roadmap & To-Do List
### High Priority ✅ COMPLETED
- [x] **Batch Conversion** - Convert multiple images at once ✅
- [x] **Image Resizing** - Scale images before conversion ✅
- [x] **Custom Dimensions** - Crop or pad to specific sizes ✅
- [x] **Progress Indicator** - Show progress for large images ✅

### Medium Priority
- [ ] **Additional Export Formats**
    - [ ] C/C++ header files(`.h`)
    - [ ] Python NumPy arrays (`.npy`)
    - [ ] Binary with different endianness options
- [ ] **Color Space Conversions**
    - [ ] Grayscale
    - [ ] HSV/HSL
    - [ ] YUV/YCbCr
- [ ] **Bit Depth Options**
    - [ ] 16-bit per channel
    - [ ] Floating point (32-bit)
- [ ] **Save/Load Presets** - Remember frequently used settings

### Low Priority
- [ ] **Reverse Conversion** - Import raw data and view as image
- [ ] **Pixel Inspector** - Click image to see individual pixel values
- [ ] **Histogram Display** - Show color distribution
- [ ] **Comparison View** - Before/after with original
- [ ] **Command-Line Tool** - Node.js version for automation
- [ ] **API Mode** - Optional REST API for programmatic access
- [ ] **Dark Mode** - Theme toggle
- [ ] **Compression Options** - Optional RLE or other simple compression
<br>
<br>

### Community Suggestions
Have an idea? [Open an issue](https://github.com/ArliT1-F/image-to-raw-converter/issues) or submit a pull request!

### Contributing
Contributions are welcome! Please feel free to submit a Pull Request.
1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Added some AmazingFeature`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### 📄 License
This project is licensed under the MIT License - see below for details:
```text
MIT License

Copyright (c) 2024

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
### 🙏 Acknowledgments
- Built with vanilla JavaScript - no frameworks needed
- Inspired by the needs of computer vision developers
- Icons: Unicode emoji (universally supported)

## 💬 Support
- **Issues**: [GitHub Issues](https://github.com/ArliT1-F/image-to-raw-converter/issues)
- **Discussions**: [GitHub Discussions](https://github.com/ArliT1-F/image-to-raw-converter/discussions)

## Project Structure
```text
image-to-raw-converter/
├── index.html           # Main web application
├── README.md            # Documentation
├── LICENCE              # MIT License text
└── examples/            # Example readers
    ├── read_raw.py      # Python reader
    ├── read_raw.c       # C reader
    ├── read_raw.cpp     # C++ reader with OpenCV
    └── opencv_example.py # OpenCV Python example
```