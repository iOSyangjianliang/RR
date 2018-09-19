//
//  UINib.h
//  UIKit
//
//  Copyright (c) 2008-2017 Apple Inc. All rights reserved.
//

//nib使用 https://www.jianshu.com/p/ea40344b4411

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>

NS_ASSUME_NONNULL_BEGIN
    
NS_CLASS_AVAILABLE_IOS(4_0) @interface UINib : NSObject 

//如果bundle参数为nil，则使用主包main bundle 。
//响应内存压力释放资源（例如内存警告），必要时从软件包中重新加载。
+ (UINib *)nibWithNibName:(NSString *)name bundle:(nullable NSBundle *)bundleOrNil;

//如果bundle参数为nil，则使用主包main bundle 。
+ (UINib *)nibWithData:(NSData *)data bundle:(nullable NSBundle *)bundleOrNil;

//返回包含NIB顶级对象的数组。
//所有者和选项参数可能都是nil。
//如果owner参数为nil，则不允许连接到文件所有者。
//optionsOrNil与- [NSBundle loadNibNamed：owner：options：]指定的options相同
- (NSArray *)instantiateWithOwner:(nullable id)ownerOrNil options:(nullable NSDictionary *)optionsOrNil;
@end

NS_ASSUME_NONNULL_END
