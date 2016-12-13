// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_WEB_PUBLIC_WEB_STATE_CRW_WEB_CONTROLLER_OBSERVER_H_
#define IOS_WEB_PUBLIC_WEB_STATE_CRW_WEB_CONTROLLER_OBSERVER_H_

#import <Foundation/Foundation.h>

@class CRWWebController;
@protocol CRWWebViewProxy;

// NOTE: When adding new methods to CRWWebControllerObserver, consider adding
// them to WebStateObserver instead if they need to be surfaced to the public
// API.
@protocol CRWWebControllerObserver<NSObject>

@optional

// Called when the current page is loaded.
// DEPRECATED: Use WebStateObserver instead.
- (void)pageLoaded:(CRWWebController*)webController;

// Called when the web controller is about to close.
- (void)webControllerWillClose:(CRWWebController*)webController;

// Gives CRWWebControllerObservers access to the CRWWebViewProxy.
- (void)setWebViewProxy:(id<CRWWebViewProxy>)webView
             controller:(CRWWebController*)webController;

@end

#endif  // IOS_WEB_PUBLIC_WEB_STATE_CRW_WEB_CONTROLLER_OBSERVER_H_
