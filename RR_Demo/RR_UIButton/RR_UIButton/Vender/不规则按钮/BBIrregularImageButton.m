

#import "BBIrregularImageButton.h"
#import "UIImage+ColorAtPixel.h"

@implementation BBIrregularImageButton

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    // 如果superResult = no（点击在bounds之外）,直接返回NO，不处理
    BOOL response = [super pointInside:point withEvent:event];
    if (!response) {
        return response;
    }
    // 判断设置有image
    if (self.currentImage || self.currentBackgroundImage) {
        // 重点
        response = [self isAlphaVisibleAtPoint:point];
    }
    return response;
}


/**
 截图
 */
-(UIImage *)shotViewImage{
    
    UIImage *imageRet = [[UIImage alloc]init];
    UIGraphicsBeginImageContextWithOptions(self.frame.size, false, 0.0);
    [self.layer renderInContext:UIGraphicsGetCurrentContext()];
    imageRet = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return imageRet;
}


/**
 判断点击点像素的透明度
 */
- (BOOL)isAlphaVisibleAtPoint:(CGPoint)point
{
    UIImage *shotViewImage = [self shotViewImage];// 截图button
    UIColor *pixelColor = [shotViewImage colorAtPixel:point];// 获取图片某一像素点的颜色值，第三方
    CGFloat alpha = 0.0;
    [pixelColor getRed:NULL green:NULL blue:NULL alpha:&alpha];
    return alpha >= 0.1;
}


@end
