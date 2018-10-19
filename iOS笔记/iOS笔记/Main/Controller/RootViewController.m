//
//  RootViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import "RootViewController.h"
#import "LeftSlideViewController.h"

@interface RootViewController ()<LeftSlideViewControllerDelegate>
@property (weak, nonatomic) IBOutlet UITextView *mainTextView;
@property (weak, nonatomic) IBOutlet UILabel *detailTitleLabel;

@property (strong, nonatomic) LeftSlideViewController *leftVC;

@end

@implementation RootViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    self.heightLayoutC_stateView.constant = [[UIApplication sharedApplication] statusBarFrame].size.height;
    
   
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Frameworks/QuartzCore/Headers/CALayer.h" ofType:nil];
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:path];
    NSData *data = [fileHandle readDataToEndOfFile];
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    self.mainTextView.text = str;
    
    self.detailTitleLabel.text = [path componentsSeparatedByString:@"/"].lastObject;

}
-(void)loadFrameworkData:(NSString *)filePath
{
    self.mainTextView.text = @"";
    [self.mainTextView setContentOffset:CGPointZero];

    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:filePath];
    NSData *data = [fileHandle readDataToEndOfFile];
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    self.mainTextView.text = str;
    
//    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
//        [self.mainTextView setContentOffset:CGPointZero];
//
//    });
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
- (IBAction)naviLeftBtnClick:(UIButton *)sender {
   
    [self.view addSubview:self.leftVC.view];
    [self addChildViewController:self.leftVC];
}
-(LeftSlideViewController *)leftVC
{
    if (!_leftVC) {
        LeftSlideViewController *vc = [[LeftSlideViewController alloc] init];
        vc.delegate = self;
        _leftVC = vc;
    }return _leftVC;
    
}
-(void)leftSlideViewControllerDidSelected:(LeftSlideViewController *)vc filePath:(NSString *)filePath
{
    self.detailTitleLabel.text = [filePath componentsSeparatedByString:@"/"].lastObject;
    [self loadFrameworkData:filePath];
  
    
}
@end
