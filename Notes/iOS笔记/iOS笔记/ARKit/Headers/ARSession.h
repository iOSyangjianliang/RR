//
//  ARSession.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ARKit/ARConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

@class ARAnchor;
@class ARCamera;
@class ARFrame;
@protocol ARSessionDelegate;

/**
 Set of options for running the session.
 @discussion These options alter the behavior of calling run on a session.
 Providing no options will result in the default behavior of resuming tracking
 from the last known position and keeping all existing anchors.
 运行会话的一组选项。
 这些选项改变了调用在会话上运行的行为。
 不提供任何选项将导致恢复跟踪的默认行为
 从最后一个已知位置开始并保持所有现有的锚。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_OPTIONS(NSUInteger, ARSessionRunOptions) {
    /** The session will reset tracking.
     会话将重置跟踪。 */
    ARSessionRunOptionResetTracking           = (1 << 0),
    
    /** The session will remove existing anchors.
     会议将删除现有的锚点。*/
    ARSessionRunOptionRemoveExistingAnchors   = (1 << 1)
} NS_SWIFT_NAME(ARSession.RunOptions);

/**
 The ARSession class configures and runs different Augmented Reality techniques on a device.
  ARSession类在设备上配置和运行不同的增强现实技术。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSession : NSObject

/**
 A delegate for receiving ARSession updates.
  接收ARSession更新的代表。
 */
@property (nonatomic, weak) id <ARSessionDelegate> delegate;

/**
 The dispatch queue on which the delegate calls are performed.
 @discussion If not provided or nil, delegate calls will be performed on the main queue.
 执行委托调用的调度队列。
  @discussion如果未提供或为nil，将在主队列上执行委托调用。
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 The current frame of the session.
  会话的当前帧。
 */
@property (nonatomic, copy, nullable, readonly) ARFrame *currentFrame;

/**
 The configuration currently being used by the session.
  会话当前使用的配置。
 */
@property (nonatomic, copy, nullable, readonly) ARConfiguration *configuration;

/**
 Runs the session with the provided configuration.
 @discussion Calling run on a session that has already started will
 transition immediately to using the new configuration.
 @param configuration The configuration to use.
 使用提供的配置运行会话。
  @discussion在已经启动的会话上调用运行
  立即转换为使用新配置。
  @param configuration要使用的配置。
 */
- (void)runWithConfiguration:(ARConfiguration *)configuration NS_SWIFT_UNAVAILABLE("Use run(_:options:) instead");

/**
 Runs the session with the provided configuration and options.
 @discussion Calling run on a session that has already started will
 transition immediately to using the new configuration. Options
 can be used to alter the default behavior when transitioning configurations.
 @param configuration The configuration to use.
 @param options The run options to use.
 
  使用提供的配置和选项运行会话。
  @discussion在已经启动的会话上调用run
  立即转换为使用新配置。选项
  可用于在转换配置时更改默认行为。
  @param configuration要使用的配置。
  @param选项要使用的运行选项。
 */
- (void)runWithConfiguration:(ARConfiguration *)configuration options:(ARSessionRunOptions)options NS_SWIFT_NAME(run(_:options:));

/**
 Pauses the session.
 @discussion Once paused, no more updates will be received from the
 session until run is called again.
  暂停会话。
 @discussion暂停后，在再次调用运行之前，不会从会话接收到任何更新。
 */
- (void)pause;

/**
 Adds an anchor to the session.
 @discussion The anchor will be added in the next frame update.
 @param anchor The anchor to add.
 向会话添加锚点。
  @discussion锚将在下一帧更新中添加。
  @param anchor要添加的锚点。
 */
- (void)addAnchor:(ARAnchor *)anchor NS_SWIFT_NAME(add(anchor:));

/**
 Removes an anchor from the session.
 @discussion The anchor will be removed from subsequent frame updates.
 @param anchor The anchor to remove.
 从会话中删除锚点。
  @discussion锚点将从后续帧更新中删除。
  @param anchor要删除的锚点。
 */
- (void)removeAnchor:(ARAnchor *)anchor NS_SWIFT_NAME(remove(anchor:));

/**
 Sets the world origin of the session to be at the position and orientation
 specified by the provided transform.
 @param relativeTransform The rotation, translation and scale from the current world origin
 to the desired world origin.
 将会话的全局原点设置为位置和方向
  由提供的转换指定。
  @param relativeTransform来自当前全局原点的旋转，平移和缩放
  达到理想的全局起源。
 */
- (void)setWorldOrigin:(matrix_float4x4)relativeTransform NS_SWIFT_NAME(setWorldOrigin(relativeTransform:)) API_AVAILABLE(ios(11.3));

@end


#pragma mark - ARSessionObserver

//会话观察者(协议)
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol ARSessionObserver <NSObject>

@optional

/**
 This is called when a session fails.
 
 @discussion On failure the session will be paused.
 @param session The session that failed.
 @param error The error being reported (see ARError.h).
  
  会话失败时调用此方法。
  @discussion失败时，会话将暂停。
  @param session失败的会话。
  @param error报告的错误（请参阅ARError.h）。
 */
- (void)session:(ARSession *)session didFailWithError:(NSError *)error;

/**
 This is called when the camera’s tracking state has changed.
 
 @param session The session being run.
 @param camera The camera that changed tracking states.
 
  当摄像机的跟踪状态发生变化时，会调用此方法。
  @param session正在运行的会话。
  @param camera改变跟踪状态的摄像头。
 */
- (void)session:(ARSession *)session cameraDidChangeTrackingState:(ARCamera *)camera;

/**
 This is called when a session is interrupted.
 
 @discussion A session will be interrupted and no longer able to track when
 it fails to receive required sensor data. This happens when video capture is interrupted,
 for example when the application is sent to the background or when there are
 multiple foreground applications (see AVCaptureSessionInterruptionReason).
 No additional frame updates will be delivered until the interruption has ended.
 @param session The session that was interrupted.
 
  会话中断时调用此方法。
 
  @discussion会话将被中断，不再能够跟踪何时
  它无法接收所需的传感器数据。当视频捕获中断时会发生这种情况，
  例如，当应用程序发送到后台或有时
  多个前台应用程序（请参阅AVCaptureSessionInterruptionReason）。
  在中断结束之前，不会提供额外的帧更新。
  @param session被中断的会话。
 */
- (void)sessionWasInterrupted:(ARSession *)session;

/**
 This is called when a session interruption has ended.
 
 @discussion A session will continue running from the last known state once
 the interruption has ended. If the device has moved, anchors will be misaligned.
 To avoid this, some applications may want to reset tracking (see ARSessionRunOptions)
 or attempt to relocalize (see `-[ARSessionObserver sessionShouldAttemptRelocalization:]`).
 @param session The session that was interrupted.
 
 这在会话中断结束时调用。
 
 会话将从最后一个已知状态继续运行一次
 中断已经结束。如果设备移动了，锚定就会错位。
 为了避免这种情况，一些应用程序可能需要重置跟踪(参见ARSessionRunOptions)
 或者尝试重新本地化(参见' -[ARSessionObserver sessionshould未遂本地化:]])。
 被中断的会话。
 */
- (void)sessionInterruptionEnded:(ARSession *)session;

/**
 This is called after a session resumes from a pause or interruption to determine
 whether or not the session should attempt to relocalize.
 
 @discussion To avoid misaligned anchors, apps may wish to attempt a relocalization after
 a session pause or interruption. If YES is returned: the session will begin relocalizing
 and tracking state will switch to limited with reason relocalizing. If successful, the
 session's tracking state will return to normal. Because relocalization depends on
 the user's location, it can run indefinitely. Apps that wish to give up on relocalization
 may call run with `ARSessionRunOptionResetTracking` at any time.
 @param session The session to relocalize.
 @return Return YES to begin relocalizing.
 
 在会话从暂停或中断恢复以确定之后调用此方法
   会话是否应该尝试重新定位。
  
   @discussion为了避免未对齐的锚点，应用程序可能希望在之后尝试重定位
   会话暂停或中断。 如果返回YES：会话将开始重新定位
   并且跟踪状态将切换到有限的原因重定位。 如果成功的话
   会话的跟踪状态将恢复正常。 因为重定位取决于
   用户的位置，它可以无限期运行。 希望放弃重定位的应用
   可以随时调用`ARSessionRunOptionResetTracking`运行。
   @param session要重新定位的会话。
   @return返回YES开始重定位。
 */
- (BOOL)sessionShouldAttemptRelocalization:(ARSession *)session API_AVAILABLE(ios(11.3));

/**
 This is called when the session outputs a new audio sample buffer.
 
 @param session The session being run.
 @param audioSampleBuffer The captured audio sample buffer.
 
 当会话输出新的音频样本缓冲区时调用此方法。
  
   @param session正在运行的会话。
   @param audioSampleBuffer捕获的音频样本缓冲区。
 */
- (void)session:(ARSession *)session didOutputAudioSampleBuffer:(CMSampleBufferRef)audioSampleBuffer;

@end

#pragma mark - ARSessionDelegate
//会话代理

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol ARSessionDelegate <ARSessionObserver>

@optional

/**
 This is called when a new frame has been updated.
 
 @param session The session being run.
 @param frame The frame that has been updated.
 
 更新新帧时调用此方法。
  
  @param session正在运行的会话。
  @param frame已更新的帧。
 */
- (void)session:(ARSession *)session didUpdateFrame:(ARFrame *)frame;

/**
 This is called when new anchors are added to the session.
 
 @param session The session being run.
 @param anchors An array of added anchors.
 
  将新锚添加到会话时调用此方法。
  
  @param session正在运行的会话。
  @param anchors一组添加的锚点。
 */
- (void)session:(ARSession *)session didAddAnchors:(NSArray<ARAnchor*>*)anchors;

/**
 This is called when anchors are updated.
 
 @param session The session being run.
 @param anchors An array of updated anchors.
 
  更新锚点时调用此方法。
  
  @param session正在运行的会话。
  @param anchors一组更新的锚点。
 */
- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<ARAnchor*>*)anchors;

/**
 This is called when anchors are removed from the session.
 
 @param session The session being run.
 @param anchors An array of removed anchors.
 
  从会话中删除锚点时调用此方法。
  
  @param session正在运行的会话。
  @param anchors一组已移除的锚点。
 */
- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<ARAnchor*>*)anchors;

@end

NS_ASSUME_NONNULL_END
