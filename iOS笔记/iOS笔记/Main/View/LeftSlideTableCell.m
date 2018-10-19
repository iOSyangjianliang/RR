//
//  LeftSlideTableCell.m
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/17.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "LeftSlideTableCell.h"
#import "LeftSlideTableCell.h"

@interface LeftSlideTableCell ()<UITableViewDelegate,UITableViewDataSource>

@end
@implementation LeftSlideTableCell

- (void)awakeFromNib {
    [super awakeFromNib];

    [self initUI];
}
-(void)setArrayGroupData:(NSMutableArray<NSString *> *)arrayGroupData
{
    _arrayGroupData = arrayGroupData;
    [self.groupTableView reloadData];
}
-(void)initUI
{    
    self.groupTableView.rowHeight = 44;
    self.groupTableView.separatorInset = UIEdgeInsetsMake(0, 25, 0, 0);
    self.groupTableView.dataSource = self;
    self.groupTableView.delegate = self;
    self.groupTableView.separatorColor = [UIColor colorWithRed:0.783922 green:0.780392 blue:0.8 alpha:0.65];
    
    [self.groupTableView registerNib:[UINib nibWithNibName:@"LeftSlideTableCell" bundle:nil] forCellReuseIdentifier:cellReuse];
    
    self.groupTableView.scrollEnabled = NO;    
}
-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (self.arrayGroupData) {
        return self.arrayGroupData.count;
    }
    return 0;
}
-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return CGFLOAT_MIN;
}
-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return CGFLOAT_MIN;
}
-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    LeftSlideTableCell *cell = [tableView dequeueReusableCellWithIdentifier:cellReuse forIndexPath:indexPath];
    cell.ApiGroupLabel.text = self.arrayGroupData[indexPath.row];
    if (!cell.groupTableView.hidden) {
        cell.groupTableView.hidden = YES;
        cell.ApiGroupLabel.textColor = [UIColor colorWithRed:117.f/255.f green:117.f/255.f blue:117.f/255.f alpha:1];
    }
    if (indexPath.row == self.arrayGroupData.count-1 ) {
        self.groupTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    }else{
        self.groupTableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    }
    cell.selectionStyle = UITableViewCellSelectionStyleNone;
    return cell;
}
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
{
    if (self.delegate && [self.delegate respondsToSelector:@selector(leftSlideTableCellDidSelected:apiName:)]) {
        NSString *apiName =self.arrayGroupData[indexPath.row];
        [self.delegate leftSlideTableCellDidSelected:self apiName:apiName];
    }
}



- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
