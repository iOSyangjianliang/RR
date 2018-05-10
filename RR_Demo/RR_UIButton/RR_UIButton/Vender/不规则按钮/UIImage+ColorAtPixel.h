//
//  UIImage+ColorAtPixel.h
//  IrregularImageButton
//
//  Created by 韦家冰 on 2017/9/3.
//  Copyright © 2017年 韦家冰. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage (ColorAtPixel)


/**
 获取图片上某坐标点对应的像素的rgba值

 @param point 坐标点
 */
- (UIColor *)colorAtPixel:(CGPoint)point;

@end
