//
//  RootViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import "RootViewController.h"
#import "LeftSlideViewController.h"
#import "AttStringManager.h"

@interface RootViewController ()<LeftSlideViewControllerDelegate,UITextViewDelegate>
@property (weak, nonatomic) IBOutlet UITextView *mainTextView;
@property (weak, nonatomic) IBOutlet UILabel *detailTitleLabel;

@property (strong, nonatomic) LeftSlideViewController *leftVC;




@end

static NSString *const UD_lastApiPath = @"UD_lastApiPath";
@implementation RootViewController

- (void)viewDidLoad {
    [super viewDidLoad];
   
    [self setUI];
   
    [self setData];
 
}
- (void)setUI
{
    [self.navigationController setNavigationBarHidden:YES animated:NO];
    self.heightLayoutC_stateView.constant = [[UIApplication sharedApplication] statusBarFrame].size.height;
    self.mainTextView.delegate = self;
    
    self.mainTextView.editable = NO;
}
-(void)setData
{
    NSString *path = [[NSUserDefaults standardUserDefaults] objectForKey:UD_lastApiPath];
    if (!path) {
        path = [NSString stringWithFormat:@"QuartzCore/Headers/Test.h"];
    }
    [self loadFrameworkData:path];
    self.detailTitleLabel.text = [path componentsSeparatedByString:@"/"].lastObject;
}
-(void)loadFrameworkData:(NSString *)filePath
{
    self.mainTextView.text = nil;
    [self.mainTextView setContentOffset:CGPointZero];

    NSString *bundle = [[NSBundle mainBundle] pathForResource:@"Frameworks" ofType:nil];
    NSString *fullPath = [NSString stringWithFormat:@"%@/%@",bundle,filePath];
    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:fullPath];
    NSData *data = [fileHandle readDataToEndOfFile];
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
   
    AttStringManager *att = [[AttStringManager alloc] initWithString:str];
    self.mainTextView.attributedText = att.attString;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
-(void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    return;
    CGFloat offset=scrollView.contentOffset.y;
    if (offset > 0) {
        CGFloat heightState = 44.f-15;
        CGFloat top = offset<heightState?offset:heightState;
        CGFloat alpha = 1-offset/heightState;
        self.topLayoutC_naviBar.constant = -top;
        self.middleTitleBtn.alpha = alpha;
        self.leftSelectBtn.alpha = alpha;
    }else{
        self.topLayoutC_naviBar.constant = 0;
        self.middleTitleBtn.alpha = 1;
        self.leftSelectBtn.alpha = 1;
        
    }
    
    CGPoint translation = [scrollView.panGestureRecognizer translationInView:scrollView.superview];
    if (translation.y > 30.f) { //触摸向下移动30.f
        self.middleTitleBtn.alpha = 1;
        self.leftSelectBtn.alpha = 1;
        [UIView animateWithDuration:0.35 animations:^{
            self.topLayoutC_naviBar.constant = 0;
        } completion:nil];
    }
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
    [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:UD_lastApiPath];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    self.detailTitleLabel.text = [filePath componentsSeparatedByString:@"/"].lastObject;
    [self loadFrameworkData:filePath];
}
@end
