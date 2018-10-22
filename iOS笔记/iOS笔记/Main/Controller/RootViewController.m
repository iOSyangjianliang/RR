//
//  RootViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2017/8/14.
//  Copyright © 2017年 yangjianliang. All rights reserved.
//

#import "RootViewController.h"
#import "LeftSlideViewController.h"
#import "ColorManager.h"

@interface RootViewController ()<LeftSlideViewControllerDelegate,UITextViewDelegate>
@property (weak, nonatomic) IBOutlet UITextView *mainTextView;
@property (weak, nonatomic) IBOutlet UILabel *detailTitleLabel;

@property (strong, nonatomic) LeftSlideViewController *leftVC;

@property (strong, nonatomic) NSMutableArray *keywordTitles;

@property (strong, nonatomic) NSMutableArray *macroTitles;


@end

static BOOL bo = NO;

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
}
-(void)setData
{
    _keywordTitles = [NSMutableArray array];
    
    [_keywordTitles addObject:@"@protocol"];
    [_keywordTitles addObject:@"@typedef"];
    [_keywordTitles addObject:@"@class"];
    [_keywordTitles addObject:@"@private"];
    [_keywordTitles addObject:@"@interface"];
    [_keywordTitles addObject:@"struct"];
    [_keywordTitles addObject:@"_Nonnull"];
    [_keywordTitles addObject:@"instancetype"];
    [_keywordTitles addObject:@"id"];
    [_keywordTitles addObject:@"nullable"];
    [_keywordTitles addObject:@"BOOL"];
    [_keywordTitles addObject:@"@property"];
    [_keywordTitles addObject:@"getter"];
    [_keywordTitles addObject:@"readonly"];
    [_keywordTitles addObject:@"void"];
    [_keywordTitles addObject:@"readonly"];
    [_keywordTitles addObject:@"copy"];
    [_keywordTitles addObject:@"readonly"];
    [_keywordTitles addObject:@"unsigned"];
    [_keywordTitles addObject:@"float"];
    [_keywordTitles addObject:@"strong"];
    
    _macroTitles = [NSMutableArray array];
    [_macroTitles addObject:@"#"];
    [_macroTitles addObject:@"import"];
    [_macroTitles addObject:@"ifndef"];
    [_macroTitles addObject:@"define"];
    [_macroTitles addObject:@"endif"];
//    [_macroTitles addObject:@"6666"];


    BOOL bo = [self isOKWithText:@" #park   mark" rule:@" *\\#park +mark"];

    NSRange range = [self fistShow:@"*/dsdsds*/123"];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"Frameworks/QuartzCore/Headers/Test.h" ofType:nil];
    [self loadFrameworkData:path];
    self.detailTitleLabel.text = [path componentsSeparatedByString:@"/"].lastObject;
}
-(void)loadFrameworkData:(NSString *)filePath
{
    self.mainTextView.text = @"";
    [self.mainTextView setContentOffset:CGPointZero];

    NSFileHandle *fileHandle = [NSFileHandle fileHandleForReadingAtPath:filePath];
    NSData *data = [fileHandle readDataToEndOfFile];
    NSString *str = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
   
    self.mainTextView.attributedText = [self attributedTextByText:str];;
}

-(NSMutableAttributedString *)attributedTextByText:(NSString *)text
{

    
    NSMutableAttributedString *attributedString = [[NSMutableAttributedString alloc] initWithString:text];
    NSArray *arr = [text componentsSeparatedByString:@"\n"];
    NSUInteger curryLength = 0;
    for (int i =0; i<arr.count; ++i) {
        NSString *str = arr[i];
        
        if (!bo) {
            for (int i= 0; i<_keywordTitles.count; ++i) {
                NSString *key = _keywordTitles[i];
                NSRange range_keyword = [str rangeOfString:key];//@protocol
                if (range_keyword.location != NSNotFound) {
                    NSRange rangeZZ = NSMakeRange(curryLength+range_keyword.location, key.length);
                    UIColor *color = [ColorManager colorWithType:DisplayColor_keyword];
                    [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeZZ];
                }
            }
            
            for (int i= 0; i<_macroTitles.count; ++i) {
                NSString *key = _macroTitles[i];
                NSRange range_keyword = [str rangeOfString:key];//#import
                if (range_keyword.location != NSNotFound) {
                    NSRange rangeZZ = NSMakeRange(curryLength+range_keyword.location, key.length);
                    UIColor *color = [ColorManager colorWithType:DisplayColor_macro];
                    [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeZZ];
                }
            }
            
            if ([self isOKWithText:str rule:@"^ *\\#park +mark.+"]) { //#park mark
                NSRange rangeQQ = NSMakeRange(curryLength, str.length);
                UIColor *color = [ColorManager colorWithType:DisplayColor_macro];
                [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
            }
        }else{
            NSRange range = [str rangeOfString:@"*/"];//首次出现range
            if (range.location != NSNotFound) {
                NSRange rangeQQ = NSMakeRange(curryLength,range.location+2);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
                bo = NO;
            }else{
                NSRange rangeZZ = NSMakeRange(curryLength, str.length);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeZZ];
            }
            
        }
        
        
        NSString *rule = @" *\\/\\*.*";/* 要呈现的文本应该是NSString或NSAttributedString。 默认为nil. */
        if ([self isOKWithText:str rule:rule]) {
            NSRange range_start = [str rangeOfString:@"/*"];

            NSRange range_end = [str rangeOfString:@"*/"];//首次出现range
            if (range_end.location != NSNotFound) {
                NSRange rangeQQ = NSMakeRange(curryLength+range_start.location, range_end.location+2);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
                bo = NO;
            }else{
                NSRange rangeQQ = NSMakeRange(curryLength+range_start.location, str.length-range_start.location);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [attributedString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
                
                bo = YES;
            }
        }
        
       
        if (!bo) {
            NSRange range_ZZ = [str rangeOfString:@"//"];
            if (range_ZZ.location != NSNotFound) {
                NSRange range = NSMakeRange(curryLength+range_ZZ.location, str.length-range_ZZ.location);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [attributedString addAttribute:NSForegroundColorAttributeName value:color range:range];
            }
        }
        curryLength = curryLength + str.length +1;

    }
    

    
    return attributedString;
}
- (BOOL)isOKWithText:(NSString *)text rule:(NSString *)rule
{
//    NSString* rule= @"^ *LCDScale_iphone6_Width *\\( *[0-9]+(\\.[0-9]*(f|F|)|) *\\) *$”;
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",rule];
    BOOL isOk = [predicate evaluateWithObject:text];
    return isOk;
}
-(NSRange)fistShow:(NSString *)text
{
    NSRange range_ZZ = [text rangeOfString:@"*/"];
//    NSRange range = NSMakeRange(<#NSUInteger loc#>, <#NSUInteger len#>)
    return range_ZZ;
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
-(void)scrollViewDidScroll:(UIScrollView *)scrollView
{
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
    self.detailTitleLabel.text = [filePath componentsSeparatedByString:@"/"].lastObject;
    [self loadFrameworkData:filePath];
}
@end
