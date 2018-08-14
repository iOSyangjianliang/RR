//
//  ARSKView.h
//  ARKit
//
//  Copyright © 2017 Apple Inc. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>
#import <ARKit/ARSession.h>
#import <ARKit/ARHitTestResult.h>

NS_ASSUME_NONNULL_BEGIN

@class ARSKView;

#pragma mark ARSKViewDelegate

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@protocol ARSKViewDelegate <SKViewDelegate, ARSessionObserver>
@optional

/**
 Implement this to provide a custom node for the given anchor.
 
 @discussion This node will automatically be added to the scene graph.
 If this method is not implemented, a node will be automatically created.
 If nil is returned the anchor will be ignored.
 @param view The view that will render the scene.
 @param anchor The added anchor.
 @return Node that will be mapped to the anchor or nil.
 实现此目的以为给定锚提供自定义节点。
  
   @discussion此节点将自动添加到场景图中。
   如果未实现此方法，将自动创建节点。
   如果返回nil，则将忽略锚点。
   @param视图将呈现场景的视图。
   @param anchor添加的锚点。
   @return将映射到锚点或nil的节点。
 */
- (nullable SKNode *)view:(ARSKView *)view nodeForAnchor:(ARAnchor *)anchor;

/**
 Called when a new node has been mapped to the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that maps to the anchor.
 @param anchor The added anchor.
 在将新节点映射到给定锚点时调用。
  
   @param视图将呈现场景的视图。
   @param node映射到锚点的节点。
   @param anchor添加的锚点。
 */
- (void)view:(ARSKView *)view didAddNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node will be updated with data from the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that will be updated.
 @param anchor The anchor that was updated.
 在使用给定锚点的数据更新节点时调用。
  
   @param视图将呈现场景的视图。
   @param node将更新的节点。
   @param anchor已更新的锚点。
 */
- (void)view:(ARSKView *)view willUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a node has been updated with data from the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that was updated.
 @param anchor The anchor that was updated.
 使用给定锚点的数据更新节点时调用。
  
   @param视图将呈现场景的视图。
   @param node已更新的节点。
   @param anchor已更新的锚点。
 */
- (void)view:(ARSKView *)view didUpdateNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

/**
 Called when a mapped node has been removed from the scene graph for the given anchor.
 
 @param view The view that will render the scene.
 @param node The node that was removed.
 @param anchor The anchor that was removed.
 从已从给定锚点的场景图中删除映射节点时调用。
  
   @param视图将呈现场景的视图。
   @param node已删除的节点。
   @param anchor已删除的锚点。
 */
- (void)view:(ARSKView *)view didRemoveNode:(SKNode *)node forAnchor:(ARAnchor *)anchor;

@end


#pragma mark ARSKView


/**
 A view that integrates ARSession rendering into SpriteKit.
 
 @discussion The view draws the camera background, and projects and maps anchors to nodes.
 将ARSession渲染集成到SpriteKit中的视图。
  
   @discussion视图绘制摄像机背景，并将锚点投影到地图并映射到节点。
 */
API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
@interface ARSKView : SKView

/**
 Specifies the view’s delegate.
 指定视图的代理。
 */
@property (nonatomic, weak, nullable) NSObject <ARSKViewDelegate> *delegate;

/**
 The session that the view uses to update the view.
 视图用于更新视图的会话。
 */
@property (nonatomic, strong) ARSession *session;

/**
 Searches the scene hierarchy for an anchor associated with the provided node.
 @param node A node in the view’s scene.
 在场景层次结构中搜索与提供的节点关联的锚点。
   @param node视图场景中的一个节点。
 */
- (nullable ARAnchor *)anchorForNode:(SKNode *)node;

/**
 Returns the node that has been mapped to a specific anchor.
 @param anchor An anchor with an existing node mapping.
 返回已映射到特定锚点的节点。
   @param anchor具有现有节点映射的锚点。
 */
- (nullable SKNode *)nodeForAnchor:(ARAnchor *)anchor;

/**
 Searches the current frame for objects corresponding to a point in the view.
 
 @discussion A 2D point in the view’s coordinate space can refer to any point along a line segment
 in the 3D coordinate space. Hit-testing is the process of finding objects in the world located along this line segment.
 @param point A point in the view’s coordinate system.
 @param types The types of results to search for.
 @return An array of all hit-test results sorted from nearest to farthest.
 在当前帧中搜索与视图中的点对应的对象。
  
   @discussion视图坐标空间中的2D点可以指向沿线段的任何点
   在3D坐标空间中。 命中测试是在该线段中找到世界中的对象的过程。
   @param point视图坐标系中的一个点。
   @param types要搜索的结果类型。
   @return从最近到最远排序的所有命中测试结果的数组。
 */
- (NSArray<ARHitTestResult *> *)hitTest:(CGPoint)point types:(ARHitTestResultType)types;

@end

NS_ASSUME_NONNULL_END
