//
//  UIImage+ColorAtPixel.m
//  IrregularImageButton
//
//  Created by 韦家冰 on 2017/9/3.
//  Copyright © 2017年 韦家冰. All rights reserved.
//

#import "UIImage+ColorAtPixel.h"

@implementation UIImage (ColorAtPixel)

//获取图片上某坐标点对应的像素的rgba值

- (UIColor *)colorAtPixel:(CGPoint)point{
    
    //如果图片上不存在该点返回nil
    if (!CGRectContainsPoint(CGRectMake(0.0f, 0.0f, self.size.width, self.size.height), point)) {
        return nil;
    }
    
    NSInteger pointX = truncl(point.x); //直接舍去小数，如1.58 -> 1.0
    NSInteger pointY= truncl(point.y);
    
    CGImageRef cgImage = self.CGImage;
    NSUInteger width = self.size.width;
    NSUInteger height = self.size.height;
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB(); //bitmap上下文使用的颜色空间
    
    int bytesPerPixel = 4; //bitmap在内存中所占的比特数
    int bytesPerRow = bytesPerPixel * 1; //bitmap的每一行在内存所占的比特数
    NSUInteger bitsPerComponent = 8; //内存中像素的每个组件的位数.例如，对于32位像素格式和RGB 颜色空间，你应该将这个值设为8.
    unsigned char pixelData[4] = {0, 0, 0, 0}; //初始化像素信息
    
    //创建位图文件环境。位图文件可自行百度 bitmap
    CGContextRef context = CGBitmapContextCreate(pixelData,
                                                 1,
                                                 1,
                                                 bitsPerComponent,
                                                 bytesPerRow,
                                                 colorSpace,
                                                 kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big); //指定bitmap是否包含alpha通道，像素中alpha通道的相对位置，像素组件是整形还是浮点型等信息的字符串。
    CGColorSpaceRelease(colorSpace);
    CGContextSetBlendMode(context, kCGBlendModeCopy); //当一个颜色覆盖上另外一个颜色，两个颜色的混合方式
    CGContextTranslateCTM(context, -pointX, pointY - (CGFloat)height); //改变画布位置
    CGContextDrawImage(context, CGRectMake(0.0f, 0.0f, (CGFloat)width, (CGFloat)height ), cgImage); //绘制图片
    CGContextRelease(context);
    
    
    CGFloat red = (CGFloat)pixelData[0] / 255.0f;
    CGFloat green = (CGFloat)pixelData[1] / 255.0f;
    CGFloat blue = (CGFloat)pixelData[2] / 255.0f;
    CGFloat alpha = (CGFloat)pixelData[3] / 255.0f;
    
    UIColor *pointColor = [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
    return pointColor;
}

@end
