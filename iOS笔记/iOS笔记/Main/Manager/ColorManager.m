//
//  ColorManager.m
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/22.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "ColorManager.h"

@implementation ColorManager
+ (UIColor *)colorWithType:(DisplayColorType)color
{
    if (color == DisplayColor_explain)
    {
        return [UIColor colorWithRed:0/255.f green:132.f/255.f blue:0/255.f alpha:1];
    }
    else if (color == DisplayColor_keyword)
    {
        return [UIColor colorWithRed:186.f/255.f green:45.f/255.f blue:162.f/255.f alpha:1];
    }
    else if (color == DisplayColor_macro)
    {
        return [UIColor colorWithRed:120.f/255.f green:73.f/255.f blue:42.f/255.f alpha:1];
    }
    else if (color == DisplayColor_framework)
    {
        return [UIColor colorWithRed:209.f/255.f green:27.f/255.f blue:47.f/255.f alpha:1];
    }
    
    return [UIColor blackColor];
}
@end
