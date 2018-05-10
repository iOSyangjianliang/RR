//
//  UIRRButton.m
//  RR_UIButton
//
//  Created by 杨建亮 on 2018/3/8.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#define SCALE 0.6
#import "UIRRButton.h"

@implementation UIRRButton

#pragma mark  设置button内部图片的位置
- (CGRect)imageRectForContentRect:(CGRect)contentRect
{
    CGFloat imageW = contentRect.size.width;
    CGFloat imageH = contentRect.size.height * SCALE;
    return CGRectMake(0, 0, imageW, imageH);
}

#pragma  mark 设置button内部文字的位置
- (CGRect)titleRectForContentRect:(CGRect)contentRect
{
    CGFloat titleX = 0;
    CGFloat titleY = contentRect.size.height * SCALE;
    CGFloat titleW = contentRect.size.width;
    CGFloat titleH = contentRect.size.height * (1 - SCALE);
    return CGRectMake(titleX, titleY, titleW, titleH);
}
@end
