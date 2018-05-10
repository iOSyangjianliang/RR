//
//  BBShapedButton.m
//  IrregularImageButton
//
//  Created by 韦家冰 on 2017/9/3.
//  Copyright © 2017年 韦家冰. All rights reserved.
//

#import "BBShapedButton.h"

@implementation BBShapedButton

//绘制按钮时添加path遮罩
- (void)drawRect:(CGRect)rect
{
    [super drawRect:rect];
    CAShapeLayer *shapLayer = [CAShapeLayer layer];
    shapLayer.path = self.path.CGPath;
    self.layer.mask = shapLayer;
}

//覆盖方法，点击时判断点是否在path内，YES则响应，NO则不响应
- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    // 判断父类能不能响应点击
    BOOL res = [super pointInside:point withEvent:event];
    if (res){
        // 再判断点击是不是在path内
        res = [self.path containsPoint:point];
    }
    return res;
}

@end
