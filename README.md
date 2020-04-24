### 用法

```
int myContourTracker(cv::Mat &img_in, std::vector<cv::Point2i> &contour_out, int neighbour)
```

* img_in: 输入图片，8bit & 单通道，像素=0表示是背景，>0表示是前景
* contour_out: 输出的轮廓线
* neighbour: 设置邻域, 可以选择8邻域(neighbour=8) 或者4邻域(neighbour=4)

### Usage

```
int myContourTracker(cv::Mat &img_in, std::vector<cv::Point2i> &contour_out, int neighbour)
```

* img_in: image input, 8-bit & 1-channel, =0 is background, >0 is frontground
* contour_out: contour output
* neighbour: neighbourhood, use neighbour=8 or neighbour =4

### Screenshot
![](Jietu20200424-114311.jpg)
