/*
 * Read raw BGR/RGB files and display using OpenCV
 * Compile: g++ -o opencv_read opencv_read.cpp `pkg-config --cflags --libs opencv4`
 * Or: g++ -o opencv_read opencv_read.cpp -I/usr/include/opencv4 -lopencv_core -lopencv_imgcodecs -lopencv_highgui
 */

#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>

struct ImageMetadata {
    uint32_t width;
    uint32_t height;
    uint32_t format; // 1=BGRA, 2=RGBA, 3=BGR, 4=RGB
};

cv::Mat readRawWithMetadata(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    // Read metadata header (12 bytes)
    ImageMetadata meta;
    file.read(reinterpret_cast<char*>(&meta.width), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&meta.height), sizeof(uint32_t));
    file.read(reinterpret_cast<char*>(&meta.format), sizeof(uint32_t));
    
    std::cout << "📐 Dimensions: " << meta.width << "x" << meta.height << std::endl;
    std::cout << "🎨 Format code: " << meta.format << std::endl;
    
    // Determine channels
    int channels = (meta.format == 1 || meta.format == 2) ? 4 : 3;
    int cvType = (channels == 4) ? CV_8UC4 : CV_8UC3;
    
    // Calculate expected size
    size_t dataSize = meta.width * meta.height * channels;
    
    // Read pixel data
    std::vector<uint8_t> buffer(dataSize);
    file.read(reinterpret_cast<char*>(buffer.data()), dataSize);
    
    if (!file) {
        throw std::runtime_error("Failed to read pixel data");
    }
    
    file.close();
    
    // Create OpenCV Mat
    cv::Mat image(meta.height, meta.width, cvType, buffer.data());
    
    // Convert to BGR if necessary
    cv::Mat result;
    if (meta.format == 4) { // RGB
        cv::cvtColor(image, result, cv::COLOR_RGB2BGR);
    } else if (meta.format == 2) { // RGBA
        cv::cvtColor(image, result, cv::COLOR_RGBA2BGRA);
    } else {
        result = image.clone(); // BGR or BGRA
    }
    
    std::cout << "✅ Successfully loaded image!" << std::endl;
    std::cout << "📊 Channels: " << result.channels() << std::endl;
    
    return result;
}

cv::Mat readRawWithoutMetadata(const std::string& filename, 
                                int width, int height, 
                                const std::string& format = "BGR") {
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    int channels = (format == "BGRA" || format == "RGBA") ? 4 : 3;
    int cvType = (channels == 4) ? CV_8UC4 : CV_8UC3;
    size_t dataSize = width * height * channels;
    
    std::vector<uint8_t> buffer(dataSize);
    file.read(reinterpret_cast<char*>(buffer.data()), dataSize);
    
    if (!file) {
        throw std::runtime_error("Failed to read pixel data");
    }
    
    file.close();
    
    cv::Mat image(height, width, cvType, buffer.data());
    cv::Mat result;
    
    if (format == "RGB") {
        cv::cvtColor(image, result, cv::COLOR_RGB2BGR);
    } else if (format == "RGBA") {
        cv::cvtColor(image, result, cv::COLOR_RGBA2BGRA);
    } else {
        result = image.clone();
    }
    
    return result;
}

int main(int argc, char** argv) {
    try {
        std::cout << "🖼️  OpenCV Raw Image Reader\n" << std::endl;
        
        // Example 1: Read with metadata
        std::cout << "Reading file with metadata..." << std::endl;
        cv::Mat img = readRawWithMetadata("test_bgr_meta.raw");
        
        // Display image
        cv::imshow("Raw Image", img);
        std::cout << "Press any key to close..." << std::endl;
        cv::waitKey(0);
        
        // Save as PNG
        cv::imwrite("output_opencv.png", img);
        std::cout << "💾 Saved as output_opencv.png" << std::endl;
        
        // Example 2: Read without metadata (you must know dimensions)
        // cv::Mat img2 = readRawWithoutMetadata("test_bgr.raw", 1920, 1080, "BGR");
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}