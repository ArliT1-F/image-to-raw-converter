#!/usr/bin/env python3
"""
Read raw files and display using OpenCV
Requires: pip install opencv-python numpy
"""
import cv2
import numpy as np
import sys


def read_raw_opencv(filename, has_metadata=True, width=None, height=None, format='BGR'):
    """
    Read raw file and convert to OpenCV format
    
    Args:
        filename: Path to raw file
        has_metadata: Whether file includes metadata header
        width: Image width (required if has_metadata=False)
        height: Image height (required if has_metadata=False)
        format: Color format (BGR, RGB, BGRA, RGBA)
    
    Returns:
        numpy.ndarray: Image in OpenCV BGR format
    """
    
    if has_metadata:
        with open(filename, 'rb') as f:
            # Read metadata
            width = int.from_bytes(f.read(4), byteorder='little')
            height = int.from_bytes(f.read(4), byteorder='little')
            format_code = int.from_bytes(f.read(4), byteorder='little')
            
            # Decode format
            formats = {1: 'BGRA', 2: 'RGBA', 3: 'BGR', 4: 'RGB'}
            format = formats.get(format_code, 'BGR')
            
            # Read pixel data
            channels = 4 if 'A' in format else 3
            pixel_data = np.fromfile(f, dtype=np.uint8)
            image = pixel_data.reshape((height, width, channels))
    else:
        if width is None or height is None:
            raise ValueError("Width and height must be provided when has_metadata=False")
        
        channels = 4 if 'A' in format else 3
        pixel_data = np.fromfile(filename, dtype=np.uint8)
        image = pixel_data.reshape((height, width, channels))
    
    # Convert to OpenCV BGR format
    if format == 'RGB':
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    elif format == 'RGBA':
        image = cv2.cvtColor(image, cv2.COLOR_RGBA2BGRA)
        # If you want to remove alpha: image = image[:, :, :3]
    elif format == 'BGRA':
        # If you want to remove alpha: image = image[:, :, :3]
        pass
    # BGR is already in correct format
    
    print(f"✅ Loaded {width}x{height} image in {format} format")
    print(f"📊 Shape: {image.shape}, Dtype: {image.dtype}")
    
    return image


def main():
    # Example 1: Read and display with metadata
    print("Reading file with metadata...")
    img = read_raw_opencv('test_bgr_meta.raw', has_metadata=True)
    
    # Display image
    cv2.imshow('Raw Image', img)
    print("Press any key to close window...")
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    
    # Save as PNG
    cv2.imwrite('output_opencv.png', img)
    print("💾 Saved as output_opencv.png")
    
    # Example 2: Read without metadata (you must know dimensions)
    # img = read_raw_opencv('test_bgr.raw', has_metadata=False, 
    #                       width=1920, height=1080, format='BGR')


if __name__ == '__main__':
    main()