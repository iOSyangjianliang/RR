//
//  LeftSlideViewController.h
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/17.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class LeftSlideViewController;
@protocol LeftSlideViewControllerDelegate <NSObject>
@optional
-(void)leftSlideViewControllerDidSelected:(LeftSlideViewController *)vc filePath:(NSString *)filePath;
@end
@interface LeftSlideViewController : UIViewController
@property(nonatomic, weak) id<LeftSlideViewControllerDelegate>delegate;
@end

NS_ASSUME_NONNULL_END
