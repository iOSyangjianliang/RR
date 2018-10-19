//
//  LeftSlideViewController.m
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/17.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "LeftSlideViewController.h"
#import "LeftSlideTableCell.h"
#import "LeftSlideTableHeadView.h"
#import "FrameworkModel.h"

@interface LeftSlideViewController ()<UITableViewDelegate,UITableViewDataSource,LeftSlideTableCellDelegate>
@property(nonatomic,strong) UIView *stateView;
@property(nonatomic,strong) UITableView *tableView;

@property(nonatomic,strong) UIButton *coverApiGroupBtn;

@property(nonatomic,strong) FrameworkModel *frameworkModel;

@end

static NSString *const frameworks = @"Frameworks";
@implementation LeftSlideViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:1];
   
    [self initData];

    [self initUI];

}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self showMoveAnimated:YES completion:nil];
    
}
-(void)initData
{
    self.frameworkModel = [[FrameworkModel alloc] initWithPath:frameworks];
}
-(void)initUI
{
    self.tableView = [[UITableView alloc] initWithFrame:CGRectMake(0,0, [UIScreen mainScreen].bounds.size.width*0.75 , [UIScreen mainScreen].bounds.size.height) style:UITableViewStylePlain];
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0.1)];
    self.tableView.sectionHeaderHeight = 45;
    self.tableView.separatorInset = UIEdgeInsetsMake(0, 25, 0, 0);
    self.tableView.dataSource = self;
    self.tableView.delegate = self;
    self.tableView.separatorColor = [UIColor colorWithRed:0.783922 green:0.780392 blue:0.8 alpha:0.65];
    self.tableView.backgroundColor = [UIColor colorWithRed:243.f/255.f green:243.f/255.f blue:243.f/255.f alpha:1];
    [self.view addSubview:self.tableView];
    
    [self.tableView registerNib:[UINib nibWithNibName:@"LeftSlideTableCell" bundle:nil] forCellReuseIdentifier:cellReuse];
    [self.tableView registerNib:[UINib nibWithNibName:@"LeftSlideTableHeadView" bundle:nil] forHeaderFooterViewReuseIdentifier:headerReuse];
    
    CGFloat H =  [[UIApplication sharedApplication] statusBarFrame].size.height;
    UIView *headerView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width*0.75, H)];
    headerView.backgroundColor = [UIColor whiteColor];
    self.stateView = headerView;
    [self.view addSubview:self.stateView];
}
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return _frameworkModel.frameworks.count;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    ApiGroupModel *model = _frameworkModel.frameworks[section];
    if (model.isDeveloped) {
        return model.apiGroups.count;
    }
    return 0;
}
-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ApiGroupModel *groupModel = _frameworkModel.frameworks[indexPath.section];
    ApiModel *model = groupModel.apiGroups[indexPath.row];;
    if (model.isDeveloped) {
        if (groupModel.apiGroups.count==1) {
            return model.apiNames.count* 44.f ;
        }
        return model.apiNames.count* 44.f +44.f;
    }
    return 44;
}
- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    LeftSlideTableHeadView *view = [tableView dequeueReusableHeaderFooterViewWithIdentifier:headerReuse];
    ApiGroupModel *groupModel = _frameworkModel.frameworks[section];
    view.apiTitleLabel.text = groupModel.frameworkName;
    view.btn.tag = 100+section;
    [view.btn addTarget:self action:@selector(clickTableHeaderBtn:) forControlEvents:UIControlEventTouchUpInside];
    return view;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LeftSlideTableCell *cell = [tableView dequeueReusableCellWithIdentifier:cellReuse forIndexPath:indexPath];
    ApiGroupModel *groupModel = _frameworkModel.frameworks[indexPath.section];
    ApiModel *model = groupModel.apiGroups[indexPath.row];;
    cell.ApiGroupLabel.text = model.apiGroupName;
    cell.arrayGroupData = model.apiNames;
    cell.groupTableView.hidden = !model.isDeveloped;
    cell.delegate = self;
    cell.heightLayout_GroupLab.constant = groupModel.apiGroups.count==1?0:44.f;
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
{
    ApiGroupModel *groupModel = _frameworkModel.frameworks[indexPath.section];
    ApiModel *model = groupModel.apiGroups[indexPath.row];
    model.isDeveloped = !model.isDeveloped;
    [self.tableView reloadData];
}
-(void)leftSlideTableCellDidSelected:(LeftSlideTableCell *)cell apiName:(NSString *)apiName
{
    if (self.delegate && [self.delegate respondsToSelector:@selector(leftSlideViewControllerDidSelected:filePath:)]) {
        
        NSString *filePath = [[NSBundle mainBundle] pathForResource:frameworks ofType:nil];
        
        NSIndexPath *indexPath = [self.tableView indexPathForCell:cell];
        ApiGroupModel *groupModel = _frameworkModel.frameworks[indexPath.section];
        ApiModel *model = groupModel.apiGroups[indexPath.row];
        
        filePath = [filePath stringByAppendingPathComponent:groupModel.frameworkName];
        filePath = [filePath stringByAppendingPathComponent:model.apiGroupName];
        filePath = [filePath stringByAppendingPathComponent:apiName];

        [self.delegate leftSlideViewControllerDidSelected:self filePath:filePath];
    }
    
    [self dissmissSelf];
}

-(void)clickTableHeaderBtn:(UIButton *)sender
{
    NSInteger section = sender.tag-100;
    ApiGroupModel *groupModel = _frameworkModel.frameworks[section];
    groupModel.isDeveloped = !groupModel.isDeveloped;
    [self.tableView reloadSections:[NSIndexSet indexSetWithIndex:section] withRowAnimation:UITableViewRowAnimationNone];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self dissmissSelf];
}
-(void)dissmissSelf
{
    [self showMoveAnimated:NO completion:^{
        if (self.parentViewController) {
            [self removeFromParentViewController];
        }
        if (self.view.superview) {
            [self.view removeFromSuperview];
        }
    }];
}
-(void)showMoveAnimated:(BOOL)show completion:(void (^ __nullable)(void))completion
{
    CGFloat start_Alpha = show? 0 : 0.35;
    CGFloat end_Alpha = show? 0.35 : 0;
    CGFloat start_Origin_x = show? -CGRectGetWidth(self.tableView.frame) : 0;
    CGFloat end_Origin_x = show? 0 : -CGRectGetWidth(self.tableView.frame);
   
    self.view.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:start_Alpha];
    CGRect frame = self.tableView.frame;
    frame.origin.x = start_Origin_x;
    self.tableView.frame = frame;
    
    CGRect frameS = self.stateView.frame;
    frameS.origin.x = start_Origin_x;
    self.stateView.frame = frameS;
    
    self.view.userInteractionEnabled = NO;
    [UIView animateWithDuration:0.25 animations:^{
        CGRect frame = self.tableView.frame;
        frame.origin.x = end_Origin_x;
        self.tableView.frame = frame;
        
        CGRect frameS = self.stateView.frame;
        frameS.origin.x = end_Origin_x;
        self.stateView.frame = frameS;
        
        self.view.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:end_Alpha];
    } completion:^(BOOL finished) {
        self.view.userInteractionEnabled = YES;
        if (completion) {
            completion();
        }
    }];
}
@end
