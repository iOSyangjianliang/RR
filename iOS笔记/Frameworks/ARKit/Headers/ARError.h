//
//  ARError.h
//  ARKit
//
//  Copyright © 2016-2017 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
FOUNDATION_EXTERN NSString *const ARErrorDomain;

API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, watchos, tvos)
typedef NS_ERROR_ENUM(ARErrorDomain, ARErrorCode) {
    /** Unsupported configuration.
     不支持的配置。 */
    ARErrorCodeUnsupportedConfiguration   = 100,
    
    /** A sensor required to run the session is not available.
     运行会话所需的传感器不可用。*/
    ARErrorCodeSensorUnavailable          = 101,
    
    /** A sensor failed to provide the required input.
     传感器无法提供所需的输入。 */
    ARErrorCodeSensorFailed               = 102,
    
    /** App does not have permission to use the camera. The user may change this in settings.
     应用程序无权使用相机。用户可以在设置中更改此设置。*/
    ARErrorCodeCameraUnauthorized         = 103,
    
    /** World tracking has encountered a fatal error.
     世界追踪遇到致命错误。*/
    ARErrorCodeWorldTrackingFailed        = 200,
    
    /** Invalid reference image
     参考图像无效*/
    ARErrorCodeInvalidReferenceImage        API_AVAILABLE(ios(11.3)) = 300,
};

NS_ASSUME_NONNULL_END
