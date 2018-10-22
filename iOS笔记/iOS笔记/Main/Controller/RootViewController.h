//
//  RootViewController.h
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RootViewController : UIViewController
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *heightLayoutC_stateView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *topLayoutC_naviBar;
@property (weak, nonatomic) IBOutlet UIButton *middleTitleBtn;
@property (weak, nonatomic) IBOutlet UIButton *leftSelectBtn;

@end
