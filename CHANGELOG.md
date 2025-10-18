# Changelog

## Version 2.0.0 - Feature-Complete Release

### 🎉 Major Features Added

#### 1. Batch Conversion
- **Upload multiple images at once** using file picker or drag & drop
- **Batch processing panel** shows all images with status indicators
- **Individual image management** - remove images from batch with ✕ button
- **Download All button** - downloads all converted images sequentially
- **Status tracking** per image: Pending → Processing → Ready → Downloaded
- All images use the same conversion settings

#### 2. Image Resizing (Scale by Percentage)
- **Percentage-based scaling** - resize images by any percentage (1-1000%)
- **Maintains aspect ratio** automatically
- **Applied before custom dimensions** for flexible workflows
- Works with both single and batch conversions
- Example: 50% = half size, 200% = double size

#### 3. Custom Dimensions
- **Specify exact width and height** in pixels
- **Three resize modes**:
  - **Stretch**: Fit to exact dimensions (may distort)
  - **Fit**: Maintain aspect ratio, fit within bounds (letterbox/pillarbox)
  - **Fill**: Maintain aspect ratio, crop to fill (no empty space)
- **Combine with scaling** for advanced workflows
- Real-time preview updates

#### 4. Progress Indicator
- **Real-time progress bar** with gradient animation
- **Status messages** for each operation:
  - Loading image... (0-30%)
  - Processing image... (60-90%)
  - Converting pixel data... (30-60%)
  - Downloading... (80-100%)
- **Batch progress tracking** - shows per-image completion
- Auto-hides after completion

### 🐛 Bug Fixes
- Fixed filename parsing for files with multiple dots (e.g., "my.image.v2.png")
- Fixed buffer overflow risk in C reader (`read_raw.c`)
- Added null-termination to string buffers in C code
- Fixed portability issues in Python readers (replaced `np.fromfile` with `np.frombuffer`)
- Added input validation for non-image files
- Added large file warning (>100MB)

### 📝 Documentation Updates
- Updated features list with all new capabilities
- Added comprehensive usage guide for all features
- Updated "How It Works" section with new processing steps
- Added batch processing documentation
- Fixed typos: "Standart" → "Standard", "Commnity" → "Community", "Github" → "GitHub"
- Fixed code samples in README (import statements, filenames)
- Reorganized project structure with `examples/` directory
- Updated project structure documentation

### 🎨 UI/UX Improvements
- Updated page title from "BGR Converter" to "Image to Raw Converter"
- Changed "BGR Data Size" label to "Raw Data Size"
- Added batch list panel with scrollable view
- Added visual status indicators (⏳ Pending, ✓ Ready, ⬇️ Downloading)
- Improved form layout and spacing
- Added hover effects for better interactivity

### 🔧 Technical Improvements
- Added validation for image dimensions and format codes
- Added overflow protection in C reader
- Improved error handling across all example readers
- Better memory management in C/C++ readers
- Cross-platform compatibility improvements

### ✅ Completed Roadmap Items
- [x] Batch Conversion
- [x] Image Resizing
- [x] Custom Dimensions
- [x] Progress Indicator

### 📊 Statistics
- **413 lines of code added**
- **34 lines modified**
- **4 major features implemented**
- **10+ bug fixes**
- **Zero breaking changes** - fully backward compatible

---

## Previous Versions

### Version 1.0.0 - Initial Release
- Single image conversion
- BGR, RGB, BGRA, RGBA formats
- Optional metadata headers
- Drag & drop interface
- Example readers in Python, C, C++, OpenCV
