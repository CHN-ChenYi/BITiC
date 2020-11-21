#include <cmath>

#include "BITiC.hpp"
using namespace std;
using namespace BITiC;

void TestYUV() {
  BMP image("YUV_input.bmp");

  BMP image2(image);
  image2.GrayScale();
  image2.write("grayscale.bmp");

  int delta = 50;
  BMP image3(image);
  image3.ModifyLuminance([delta](const double &y) { return y + delta; });
  image3.write("luminance_linear.bmp");

  double ratio = 2;
  BMP image4(image);
  image4.ModifyLuminance([ratio](const double &y) {
    return int(exp(log(y / 255.0) * ratio) * 255);  // ratio > 1 for darker
  });
  image4.write("luminance_exponential.bmp");
}

void TestBin() {
  BMP image;
  image.read("bin_input.bmp");

  BMP image2(image);
  image2.Binarization();
  image2.write("bin.bmp");

  image.Binarization(image.width() / 2.5, image.width() / 4);
  image.write("local_bin.bmp");

  std::vector<std::pair<int, int>> structing_element;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++)
      structing_element.push_back(std::make_pair(i, j));
  }

  BMP image3(image), image4(image), image5(image);
  image3.Dilation(structing_element);
  image3.write("dilation.bmp");

  image.Erosion(structing_element);
  image.write("erosion.bmp");

  image4.Opening(structing_element);
  image4.write("opening.bmp");

  image5.Closing(structing_element);
  image5.write("closing.bmp");
}

void TestHis() {
  BMP image("his_input_2.bmp"), image2(image);
  image.HistogramEqualization(Channel::kBlueChannel | Channel::kGreenChannel |
                              Channel::kRedChannel);
  image.write("equalization.bmp");

  image2.HistogramEqualization(Channel::kGrayChannel, 256);
  // image2.write("equalization_gray_.bmp");
  image2.GrayScale();
  image2.write("equalization_gray.bmp");

  BMP image3("his_input_1.bmp");
  image3.LogarithmicEnhancement();
  image3.write("logarithmic_enhance.bmp");
}

void TestGeo() {
  BMP image("geo_input.bmp"), image1(image), image2(image), image3(image);
  image.Translation(100, 100);
  image.write("translation.bmp");

  image1.Mirror(true, true);
  image1.write("mirror.bmp");

  image2.Shear(false, -0.7);
  image2.write("shear.bmp");

  image3.Scale(0.75, 1.2);
  image3.write("scale.bmp");
}

int main() {
  // TestYUV();
  // TestBin();
  // TestHis();
  TestGeo();
  return 0;
}
