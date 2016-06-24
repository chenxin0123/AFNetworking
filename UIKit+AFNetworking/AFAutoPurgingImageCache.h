// AFAutoPurgingImageCache.h
// Copyright (c) 2011–2016 Alamofire Software Foundation ( http://alamofire.org/ )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <TargetConditionals.h>
#import <Foundation/Foundation.h>

#if TARGET_OS_IOS || TARGET_OS_TV
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The `AFImageCache` protocol defines a set of APIs for adding, removing and fetching images from a cache synchronously.
 
 
 定义一些用于清除 设置 查询图片缓存的api
 
 */
@protocol AFImageCache <NSObject>

/**
 Adds the image to the cache with the given identifier.

 @param image The image to cache.
 @param identifier The unique identifier for the image in the cache.
 
 添加缓存
 
 */
- (void)addImage:(UIImage *)image withIdentifier:(NSString *)identifier;

/**
 Removes the image from the cache matching the given identifier.

 @param identifier The unique identifier for the image in the cache.

 @return A BOOL indicating whether or not the image was removed from the cache.
 
 移除缓存
 
 */
- (BOOL)removeImageWithIdentifier:(NSString *)identifier;

/**
 Removes all images from the cache.

 @return A BOOL indicating whether or not all images were removed from the cache.
 
 清空所有缓存
 
 */
- (BOOL)removeAllImages;

/**
 Returns the image in the cache associated with the given identifier.

 @param identifier The unique identifier for the image in the cache.

 @return An image for the matching identifier, or nil.
 
 获取缓存
 
 */
- (nullable UIImage *)imageWithIdentifier:(NSString *)identifier;
@end


/**
 The `ImageRequestCache` protocol extends the `ImageCache` protocol by adding methods for adding, removing and fetching images from a cache given an `NSURLRequest` and additional identifier.
 
 
 在AFImageCache基础上 添加了给一个请求设置图片缓存的api
 
 */
@protocol AFImageRequestCache <AFImageCache>

/**
 Adds the image to the cache using an identifier created from the request and additional identifier.

 @param image The image to cache.
 @param request The unique URL request identifing the image asset.
 @param identifier The additional identifier to apply to the URL request to identify the image.
 
 添加缓存
 
 */
- (void)addImage:(UIImage *)image forRequest:(NSURLRequest *)request withAdditionalIdentifier:(nullable NSString *)identifier;

/**
 Removes the image from the cache using an identifier created from the request and additional identifier.

 @param request The unique URL request identifing the image asset.
 @param identifier The additional identifier to apply to the URL request to identify the image.
 
 @return A BOOL indicating whether or not all images were removed from the cache.
 
 移除缓存
 
 */
- (BOOL)removeImageforRequest:(NSURLRequest *)request withAdditionalIdentifier:(nullable NSString *)identifier;

/**
 Returns the image from the cache associated with an identifier created from the request and additional identifier.

 @param request The unique URL request identifing the image asset.
 @param identifier The additional identifier to apply to the URL request to identify the image.

 @return An image for the matching request and identifier, or nil.
 
 获取缓存
 
 */
- (nullable UIImage *)imageforRequest:(NSURLRequest *)request withAdditionalIdentifier:(nullable NSString *)identifier;

@end

/**
 The `AutoPurgingImageCache` in an in-memory image cache used to store images up to a given memory capacity. When the memory capacity is reached, the image cache is sorted by last access date, then the oldest image is continuously purged until the preferred memory usage after purge is met. Each time an image is accessed through the cache, the internal access date of the image is updated.
 
 按照给定的内存来缓存 当到达缓存瓶颈则清除accessed date最早期的图片
 
 清除任务将持续清除直到内容使用低于preferredMemoryUsageAfterPurge
 
 每当从缓存获取一张图片 该图片的accessed date会被更新
 
 
 遵守AFImageRequestCache协议
 
 */
@interface AFAutoPurgingImageCache : NSObject <AFImageRequestCache>

/**
 The total memory capacity of the cache in bytes.
 
 缓存的容量
 
 */
@property (nonatomic, assign) UInt64 memoryCapacity;

/**
 The preferred memory usage after purge in bytes. During a purge, images will be purged until the memory capacity drops below this limit.
 
 
 
 
 */
@property (nonatomic, assign) UInt64 preferredMemoryUsageAfterPurge;

/**
 The current total memory usage in bytes of all images stored within the cache.
 
 当前内存使用
 
 */
@property (nonatomic, assign, readonly) UInt64 memoryUsage;

/**
 Initialies the `AutoPurgingImageCache` instance with default values for memory capacity and preferred memory usage after purge limit. `memoryCapcity` defaults to `100 MB`. `preferredMemoryUsageAfterPurge` defaults to `60 MB`.

 @return The new `AutoPurgingImageCache` instance.
 
 
 使用默认值来初始化 memoryCapacity为100M preferredMemoryUsageAfterPurge为60M
 
 */
- (instancetype)init;

/**
 Initialies the `AutoPurgingImageCache` instance with the given memory capacity and preferred memory usage
 after purge limit.

 @param memoryCapacity The total memory capacity of the cache in bytes.
 @param preferredMemoryCapacity The preferred memory usage after purge in bytes.

 @return The new `AutoPurgingImageCache` instance.
 
 r
 
 */
- (instancetype)initWithMemoryCapacity:(UInt64)memoryCapacity preferredMemoryCapacity:(UInt64)preferredMemoryCapacity;

@end

NS_ASSUME_NONNULL_END

#endif

