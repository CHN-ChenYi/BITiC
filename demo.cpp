#include <cmath>
#include <iostream>

#include "BITiC.hpp"
using namespace std;

void TestYUV() {
  BMP image("YUV_input.bmp");

  BMP image2(image);
  image2.GrayScale();
  image2.write("grayscale.bmp");

  static int delta;
  static auto linear_transform = [](const int &y) { return y + delta; };
  cout << "Please input the delta of luminance" << endl;
  cin >> delta;
  // delta = 50;
  BMP image3(image);
  image3.ModifyLuminance(linear_transform);
  image3.write("luminance_linear.bmp");

  static double ratio;
  static auto exponential_transform = [](const int &y) {
    return int(exp(log(y / 255.0) * ratio) * 255);  // ratio > 1 for darker
  };
  cout << "Please input the exponent of luminance" << endl;
  cin >> ratio;
  // ratio = 2;
  BMP image4(image);
  image4.ModifyLuminance(exponential_transform);
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

int main() {
  // TestYUV();
  // TestBin();
  return 0;
}
