//
//  ColorManager.h
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/22.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, DisplayColorType ) {
    DisplayColor_explain,         //注释说明的颜色
    
    DisplayColor_keyword,         //eg: @interface的颜色
    
    DisplayColor_macro            //eg: #import的颜色
};

@interface ColorManager : NSObject
+ (UIColor *)colorWithType:(DisplayColorType) color;

@end

NS_ASSUME_NONNULL_END
