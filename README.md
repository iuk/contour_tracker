```
int myContourTracker(cv::Mat &img_in, std::vector<cv::Point2i> &contour_out, int neighbour)
```

* img_in: image input, 8-bit 1-channel, 0 is background, >0 is frontground
* contour_out: contour output
* neighbour: neighbourhood, use neighbour=8 or neighbour =4
