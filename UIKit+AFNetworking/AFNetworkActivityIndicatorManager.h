// AFNetworkActivityIndicatorManager.h
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

#import <Foundation/Foundation.h>

#import <TargetConditionals.h>

#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

//NS_ASSUME_NONNULL_BEGIN和NS_ASSUME_NONNULL_END。在这两个宏之间的代码，所有简单指针对象都被假定为nonnull，因此我们只需要去指定那些nullable的指针
NS_ASSUME_NONNULL_BEGIN

/**
 `AFNetworkActivityIndicatorManager` manages the state of the network activity indicator in the status bar. When enabled, it will listen for notifications indicating that a session task has started or finished, and start or stop animating the indicator accordingly. The number of active requests is incremented and decremented much like a stack or a semaphore, and the activity indicator will animate so long as that number is greater than zero.

 You should enable the shared instance of `AFNetworkActivityIndicatorManager` when your application finishes launching. In `AppDelegate application:didFinishLaunchingWithOptions:` you can do so with the following code:

    [[AFNetworkActivityIndicatorManager sharedManager] setEnabled:YES];

 By setting `enabled` to `YES` for `sharedManager`, the network activity indicator will show and hide automatically as requests start and finish. You should not ever need to call `incrementActivityCount` or `decrementActivityCount` yourself.

 See the Apple Human Interface Guidelines section about the Network Activity Indicator for more information:
 http://developer.apple.com/library/iOS/#documentation/UserExperience/Conceptual/MobileHIG/UIElementGuidelines/UIElementGuidelines.html#//apple_ref/doc/uid/TP40006556-CH13-SW44
 
 
 管理状态栏的网络状态指示器 
 
 使用方法:[[AFNetworkActivityIndicatorManager sharedManager] setEnabled:YES];
 */
NS_EXTENSION_UNAVAILABLE_IOS("Use view controller based solutions where appropriate instead.")
@interface AFNetworkActivityIndicatorManager : NSObject

/**
 A Boolean value indicating whether the manager is enabled.

 If YES, the manager will change status bar network activity indicator according to network operation notifications it receives. The default value is NO.
 */
@property (nonatomic, assign, getter = isEnabled) BOOL enabled;

/**
 A Boolean value indicating whether the network activity indicator manager is currently active.
*/
@property (readonly, nonatomic, assign, getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible;

/**
 A time interval indicating the minimum duration of networking activity that should occur before the activity indicator is displayed. The default value 1 second. If the network activity indicator should be displayed immediately when network activity occurs, this value should be set to 0 seconds.
 
 Apple's HIG describes the following:

 > Display the network activity indicator to provide feedback when your app accesses the network for more than a couple of seconds. If the operation finishes sooner than that, you don’t have to show the network activity indicator, because the indicator is likely to disappear before users notice its presence.

 延迟显示时间 默认1秒 如果网络请求很快 那么没必要显示
 */
@property (nonatomic, assign) NSTimeInterval activationDelay;

/**
 A time interval indicating the duration of time of no networking activity required before the activity indicator is disabled. This allows for continuous display of the network activity indicator across multiple requests. The default value is 0.17 seconds.
 
 延迟消失 默认0.17秒
 */

@property (nonatomic, assign) NSTimeInterval completionDelay;

/**
 Returns the shared network activity indicator manager object for the system.

 @return The systemwide network activity indicator manager.
 */
+ (instancetype)sharedManager;

/**
 Increments the number of active network requests. If this number was zero before incrementing, this will start animating the status bar network activity indicator.
 
 指示器根据ActivityCount来显示或者消失
 */
- (void)incrementActivityCount;

/**
 Decrements the number of active network requests. If this number becomes zero after decrementing, this will stop animating the status bar network activity indicator.
 
 指示器根据ActivityCount来显示或者消失
 */
- (void)decrementActivityCount;

/**
 Set the a custom method to be executed when the network activity indicator manager should be hidden/shown. By default, this is null, and the UIApplication Network Activity Indicator will be managed automatically. If this block is set, it is the responsiblity of the caller to manager the network activity indicator going forward.
 
 尽量不用。。。
 
 activity indicator消失或者隐藏之前调用 默认为null
 
 默认使用以下表达式来设置指示器：
 
 [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:networkActivityIndicatorVisible]
 
 如果networkActivityIndicatorVisible不为空则需要用户自己设置指示器的显示和隐藏

 @param block A block to be executed when the network activity indicator status changes.
 */
- (void)setNetworkingActivityActionWithBlock:(nullable void (^)(BOOL networkActivityIndicatorVisible))block;
@end

NS_ASSUME_NONNULL_END

#endif
