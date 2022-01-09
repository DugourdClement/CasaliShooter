#!/usr/bin/env python3
from array import array
from PIL import Image
import argparse
import io
import os


__author__ = "Kuruyia"
__version__ = "1.0.0"
__license__ = "MIT"

# The "Simple Image for Space Invaders" (.si2) file format specifications
# Authors: Alexandre "Kuruyia" SOLLIER, Marc AMBAUD (2019 - 2020)
#
# | Address | Length | Description                         |
# |---------|--------|-------------------------------------|
# | 0x00    | 2      | Magic number ("SI")                 |
# | 0x02    | 4      | Header magic number ("HEAD")        |
# | 0x06    | 2      | File version                        |
# | 0x08    | 4      | Pixel count                         |
# | 0x0C    | 4      | Image width                         |
# | 0x10    | 4      | Data magic number ("DATA")          |
# | 0x14    | ???    | Uncompressed image data as RGBA8888 |
# "File version", "Pixel count" and "Image width" entries are little-endian, unsigned numbers.


def is_file_si2(filePath):
    # Check the magic number
    with open(filePath, 'rb') as file:
        return file.read(2) == b'SI'


def convert_from_si2(source, output):
    # Print summary
    print('Source image: .si2')
    _, outExtension = os.path.splitext(output)
    print('Output image: {}'.format(outExtension))

    # Read si2 image data
    with open(source, 'rb') as file:
        file.seek(0x08)
        pixelCount = int.from_bytes(file.read(4), byteorder='little', signed=False)
        lineSize = int.from_bytes(file.read(4), byteorder='little', signed=False)
        imageSize = (lineSize, int(pixelCount/lineSize))
        file.seek(0x14)
        imageData = file.read()

    # Print summary 2: Electric Boogaloo
    print('Image size is {}x{}'.format(imageSize[0], imageSize[1]))
    print()
    print('Starting conversion...')

    # Save the converted image
    img = Image.frombytes('RGBA', imageSize, imageData)
    img.save(output)


def convert_to_si2(source, output):
    # Print summary
    _, outExtension = os.path.splitext(source)
    print('Source image: {}'.format(outExtension))
    print('Output image: .si2')

    # Read source image
    with Image.open(source) as img:
        imageSize = img.size

        if img.mode != 'RGBA':
            # Convert image mode if unsupported
            print('Source image mode "{}" is unsupported, attempting conversion...'.format(img.mode))

            imgConvt = img.convert('RGBA')
            imageData = imgConvt.load()
        else:
            imageData = img.load()

    # Print summary 2: Electric Boogaloo
    print('Image size is {}x{}'.format(imageSize[0], imageSize[1]))
    print()
    print('Starting conversion...')

    # Convert the image
    with open(output, 'wb') as file:
        file.write(b'SIHEAD\01\00')
        file.write((imageSize[0]*imageSize[1]).to_bytes(4, byteorder='little'))
        file.write((imageSize[0]).to_bytes(4, byteorder='little'))
        file.write(b'DATA')

        for y in range(0, imageSize[1]):
            for x in range(0, imageSize[0]):
                file.write(bytes(imageData[x, y]))


def main():
    # Setup argument parser
    parser = argparse.ArgumentParser(description='This tool converts images compatible with PIL to the minGL 2 Simple Image format (.si2), and vice versa.')
    parser.add_argument('-v', '--version', action='version', version='%(prog)s 1.0')
    parser.add_argument('<source image file>', help='The path to the image to convert. A .si2 will be converted to a .png file. Any other image type will be converted to a .si2 file.')
    parser.add_argument('<output file>', help='The path to output the converted image to.')

    args = vars(parser.parse_args())
    source = args['<source image file>']
    output = args['<output file>']

    # Check that source file exists
    if not os.path.isfile(source):
        exit('"{}"\nThe specified path does not exist.'.format(source))

    # Check if source file is in the .si2 format
    isSourceSi2 = is_file_si2(source)

    if isSourceSi2:
        convert_from_si2(source, output)
    else:
        convert_to_si2(source, output)

    print('Done!')

    # with Image.open(source) as img:
    #     for y in range(0, img.height):
    #         for x in range(0, img.width):
    #             print(img.getpixel((x, y)))


if __name__ == "__main__":
    main()