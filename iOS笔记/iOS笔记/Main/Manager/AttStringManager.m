//
//  AttStringManager.m
//  iOS笔记
//
//  Created by 杨建亮 on 2018/10/23.
//  Copyright © 2018年 yangjianliang. All rights reserved.
//

#import "AttStringManager.h"
#import "ColorManager.h"

@interface AttStringManager ()
@property (strong, nonatomic) NSMutableArray *keywordTitles;
@property (strong, nonatomic) NSMutableArray *macroTitles;
@end

static BOOL findTheEndOfComment = NO;
@implementation AttStringManager
- (instancetype)initWithString:(NSString *)str
{
    if (self = [super init]) {
        [self setNoteData];
        [self addAttributesWithText:str];
    }
    return self;
}
-(void)setNoteData
{
    _keywordTitles = [NSMutableArray array];
    [_keywordTitles addObject:@"@"];
    [_keywordTitles addObject:@"protocol"];
    [_keywordTitles addObject:@"typedef"];
    [_keywordTitles addObject:@"class"];
    [_keywordTitles addObject:@"private"];
    [_keywordTitles addObject:@"optional"];
    [_keywordTitles addObject:@"interface"];
    [_keywordTitles addObject:@"end"];
    [_keywordTitles addObject:@"struct"];
    [_keywordTitles addObject:@"instancetype"];
    [_keywordTitles addObject:@"id"];
    [_keywordTitles addObject:@"nullable"];
    [_keywordTitles addObject:@"_Nonnull"];


    [_keywordTitles addObject:@"property"];
    [_keywordTitles addObject:@"nonatomic"];
    [_keywordTitles addObject:@"null_resettable"];
    [_keywordTitles addObject:@"__kindof"];
    [_keywordTitles addObject:@"readwrite"];
    [_keywordTitles addObject:@"strong"];
    [_keywordTitles addObject:@"getter"];
    [_keywordTitles addObject:@"readonly"];
    [_keywordTitles addObject:@"copy"];
    
    [_keywordTitles addObject:@"void"];
    [_keywordTitles addObject:@"unsigned"];
    [_keywordTitles addObject:@"float"];
    [_keywordTitles addObject:@"int"];
    [_keywordTitles addObject:@"BOOL"];

    _macroTitles = [NSMutableArray array];
    [_macroTitles addObject:@"#"];
    [_macroTitles addObject:@"!"];
    [_macroTitles addObject:@"import"];
    [_macroTitles addObject:@"include"];
    [_macroTitles addObject:@"ifndef"];
    [_macroTitles addObject:@"define"];
    [_macroTitles addObject:@"endif"];
    [_macroTitles addObject:@"else"];
    [_macroTitles addObject:@"NS_ASSUME_NONNULL_BEGIN"];
    [_macroTitles addObject:@"NS_ASSUME_NONNULL_END"];
    [_macroTitles addObject:@"NS_AVAILABLE_IOS"];
    [_macroTitles addObject:@"__TVOS_PROHIBITED"];
    [_macroTitles addObject:@"NS_DEPRECATED_IOS"];
    [_macroTitles addObject:@"TARGET_OS_IOS"];
    [_macroTitles addObject:@"UIKIT_EXTERN"];
    [_macroTitles addObject:@"TARGET_OS_MAC"];
    [_macroTitles addObject:@"TARGET_RT_64_BIT"];
    [_macroTitles addObject:@"&&"];
    [_macroTitles addObject:@"CA_EXTERN"];
    [_macroTitles addObject:@"&&"];


    

    
}


-(void)addAttributesWithText:(NSString *)text
{
    _attString = [[NSMutableAttributedString alloc] initWithString:text];
    NSArray *arr = [text componentsSeparatedByString:@"\n"];
    NSUInteger curryLength = 0;
    for (int i =0; i<arr.count; ++i) {
        NSString *str = arr[i];

        if (!findTheEndOfComment) {
            for (int i= 0; i<_keywordTitles.count; ++i) {
                NSString *key = _keywordTitles[i];
                NSRange range_keyword = [str rangeOfString:key];//@protocol
                if (range_keyword.location != NSNotFound) {
                    if ([key isEqualToString:@"@"] || [self isSapce_first_end:str range:range_keyword]) {
                        NSRange rangeZZ = NSMakeRange(curryLength+range_keyword.location, key.length);
                        UIColor *color = [ColorManager colorWithType:DisplayColor_keyword];
                        [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeZZ];
                    }
                }
            }

            for (int i= 0; i<_macroTitles.count; ++i) {
                NSString *key = _macroTitles[i];
                NSRange range_keyword = [str rangeOfString:key];//#import
                if (range_keyword.location != NSNotFound) {
                    if ([key isEqualToString:@"#"] || [self isSapce_first_end:str range:range_keyword]) {
                        NSRange rangeZZ = NSMakeRange(curryLength+range_keyword.location, key.length);
                        UIColor *color = [ColorManager colorWithType:DisplayColor_macro];
                        [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeZZ];
                    }
                }
            }

            if ([self isOK_Text:str rule:@"^ *\\#park +mark.+"]) { //#park mark
                NSRange rangeQQ = NSMakeRange(curryLength, str.length);
                UIColor *color = [ColorManager colorWithType:DisplayColor_macro];
                [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
            }
        }else{
            NSRange range = [str rangeOfString:@"*/"];//首次出现range
            if (range.location != NSNotFound) {
                NSRange rangeQQ = NSMakeRange(curryLength,range.location+2);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
                findTheEndOfComment = NO;
            }else{
                NSRange rangeZZ = NSMakeRange(curryLength, str.length);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeZZ];
            }

        }

        NSString *rule = @" *\\/\\*.*";/* 要呈现的文本应该是NSString或NSAttributedString。 默认为nil. */
        if ([self isOK_Text:str rule:rule]) {
            NSRange range_start = [str rangeOfString:@"/*"];

            NSRange range_end = [str rangeOfString:@"*/"];//首次出现range
            if (range_end.location != NSNotFound) {
                NSRange rangeQQ = NSMakeRange(curryLength+range_start.location, range_end.location+2);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];
                findTheEndOfComment = NO;
            }else{
                NSRange rangeQQ = NSMakeRange(curryLength+range_start.location, str.length-range_start.location);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [_attString addAttribute:NSForegroundColorAttributeName value:color range:rangeQQ];

                findTheEndOfComment = YES;
            }
        }


        if (!findTheEndOfComment) {
            NSRange range_ZZ = [str rangeOfString:@"//"];
            if (range_ZZ.location != NSNotFound) {
                NSRange range = NSMakeRange(curryLength+range_ZZ.location, str.length-range_ZZ.location);
                UIColor *color = [ColorManager colorWithType:DisplayColor_explain];
                [_attString addAttribute:NSForegroundColorAttributeName value:color range:range];
            }
            
            NSString *rule = @".*\\<.+\\>.*";//eg://<Foundation/Foundation.h>
            if ([self isOK_Text:str rule:rule]) {
                if ([str hasPrefix:@"#"]) {
                    NSRange range_start = [str rangeOfString:@"<"];
                    NSRange range_end = [str rangeOfString:@">"];
                    
                    NSRange range = NSMakeRange(curryLength+range_start.location, range_end.location-range_start.location+1);
                    UIColor *color = [ColorManager colorWithType:DisplayColor_framework];
                    [_attString addAttribute:NSForegroundColorAttributeName value:color range:range];
                }
            }
            
        }
        curryLength = curryLength + str.length +1;

    }
}
// a-z：97-122
// A-Z：65-90
//0-9：48-57
- (BOOL)isSapce_first_end:(NSString *)text range:(NSRange)range
{
    NSUInteger len = [text length];
    BOOL first = NO;     BOOL end = NO;
    if (range.location>0) {
        unichar f = [text characterAtIndex:range.location-1];
        if ( (f >= 97 && f <= 122) || (f >= 65 && f <= 90)) {
            //字母
        }else{
            first = YES;
        }
    }else{
        first = YES;
    }
    
    if (range.location+range.length<len) {
        unichar e = [text characterAtIndex:range.location+range.length];
        if ( (e >= 97 && e <= 122) || (e >= 65 && e <= 90)) {
            //字母
        }else{
            end = YES;
        }
    }else{
        end =  YES;
    }
    return first && end;
}
- (BOOL)isOK_Text:(NSString *)text rule:(NSString *)rule
{
    //    NSString* rule= @"^ *LCDScale_iphone6_Width *\\( *[0-9]+(\\.[0-9]*(f|F|)|) *\\) *$”;
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@",rule];
    BOOL isOk = [predicate evaluateWithObject:text];
    return isOk;
}

@end
