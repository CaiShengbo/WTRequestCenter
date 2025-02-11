//
//  WTNetWorkManager.h
//  WTRequestCenter
//
//  Created by SongWentong on 10/26/15.
//  Copyright © 2015 song. All rights reserved.
//  https://github.com/swtlovewtt/WTRequestCenter

@import Foundation;
NS_ASSUME_NONNULL_BEGIN
@interface WTNetWorkManager : NSObject
+(instancetype)sharedKit;

//缓存
+(NSURLCache*)sharedURLcache;
@property (readonly, nonatomic, strong) NSURLSession *session;


@property (nonatomic,strong) NSLock *lock;
-(NSOperationQueue*)operationQueue;



/*!
 根据请求对象生成对应的task,并执行请求
 注意:成功和失败都是分线程回调
 */
-(NSURLSessionDataTask*)taskWithRequest:(NSURLRequest*)request
                               finished:(nullable void(^)(NSData * data, NSURLResponse * response))finish
                                 failed:(nullable void(^)(NSError * error))failed;

/*!
 缓存式请求,只缓存GET,不重复
 */
-(NSURLSessionDataTask*)cachedTaskWithRequest:(NSURLRequest*)request
                    finished:(nullable void(^)(NSData * data, NSURLResponse * response))finish
                      failed:(nullable void(^)(NSError * error))failed;
@end

@interface WTNetWorkManager(CreatRequest)
/*!
 根据请求方法,URL和参数创建一个请求对象
 
 method 传入对应的方法就可以了,比如GET,POST
 URLString 传入你的url
 parameters 参数
 error  错误
 */
- (NSMutableURLRequest *)requestWithMethod:(NSString *)method
                                 URLString:(NSString *)URLString
                                parameters:(nullable NSDictionary*)parameters
                                     error:(NSError *__autoreleasing *)error;


/*!
 根据url,参数和对应的数据来创建一个请求对象
 
 body 中存的是NSDictionary,包含4个内容
 name 是名字
 filename 是文件名
 contentType 是内容类型
 content 是内容
 目前没有做的是同一个name对应多个文件,那个做起来比较复杂,没啥需求,就不做了.
 
 1.name 是服务端对应的key
 
 2.filename是文件名
 如过不传filename,则和name同名
 
 3.contentType
 可为空(默认用application/octet-stream)
 通常有以下几种:
 "text/html", "image/png", "image/gif", "video/mpeg", "text/css", and "audio/basic"
 图片的话可以根据类型,设置成对应的,比方说 "image/jpeg","image/png", "image/gif",
 详情参见百度百科:
 http://baike.baidu.com/link?url=JIKC351CPOldPwZa50dp6lUJRII_VdWelsP3jRSnHRLsa9UOWMpLhsYR3rRYfvuQfq17KQXnKpBMUbZU7UDnnK
 
 4.content是对应的数据读出来的NSData对象
 
 */
-(NSMutableURLRequest*)POSTRequestWithURL:(NSString*)url
                               parameters:(nullable NSDictionary*)parameters
                                     body:(NSArray*)body;
@end


/**
 Posted when an operation begins executing.
 */
extern NSString * const WTNetworkingOperationDidStartNotification;

/**
 Posted when an operation finishes.
 */
extern NSString * const WTNetworkingOperationDidFinishNotification;
NS_ASSUME_NONNULL_END