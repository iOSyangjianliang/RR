//
//  AttStringManager.h
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/23.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AttStringManager : NSObject
- (instancetype)initWithString:(NSString *)str;
@property(nonatomic, strong, readonly)NSMutableAttributedString *attString;
@end

NS_ASSUME_NONNULL_END
