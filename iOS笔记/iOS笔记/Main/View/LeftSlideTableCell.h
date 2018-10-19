//
//  LeftSlideTableCell.h
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/17.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
static NSString * const cellReuse = @"cellReuse";
static NSString * const headerReuse = @"headerReuse";

@class LeftSlideTableCell;
@protocol LeftSlideTableCellDelegate <NSObject>
@optional
-(void)leftSlideTableCellDidSelected:(LeftSlideTableCell *)cell apiName:(NSString *)apiName;
@end

@interface LeftSlideTableCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UILabel *ApiGroupLabel;
@property (weak, nonatomic) IBOutlet UITableView *groupTableView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *heightLayout_GroupLab;

@property (strong, nonatomic) NSMutableArray<NSString *> *arrayGroupData;
@property(nonatomic, weak) id<LeftSlideTableCellDelegate>delegate;

@end

NS_ASSUME_NONNULL_END
