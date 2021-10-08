# HW1

### Introduction
[bmp file](https://zh.wikipedia.org/wiki/BMP)
<!-- jpg
riff
tiff
png
psd
pcx
tga
gif -->

### BitMap File Header
void printHeader(BMP_t *bmp);

### Image Processing
- void RGBToGrayLevel(BMP_t *bmp);
- void NegativeFilmTransfer_GrayLevel(BMP_t *bmp);
- void InvertImage_GrayLevel(BMP_t *bmp);
- void MirrorImage_GrayLevel(BMP_t *bmp);
- void Rotate90CCW_GrayLevel(BMP_t *bmp);
- void Rotate90CW_GrayLevel(BMP_t *bmp);
- void printGrayHistogram(uint8_t *data, uint32_t dataLength);

### Image Sampling
- Subsampling
- Upsampling


