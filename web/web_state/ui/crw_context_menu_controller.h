// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_WEB_WEB_STATE_UI_CRW_CONTEXT_MENU_CONTROLLER_H_
#define IOS_WEB_WEB_STATE_UI_CRW_CONTEXT_MENU_CONTROLLER_H_

#import <Foundation/Foundation.h>
#import <Webkit/Webkit.h>

#import "ios/web/public/block_types.h"

@protocol CRWContextMenuDelegate;
@protocol CRWJSInjectionEvaluator;

// A controller that will recognise context menu gesture on |webView|. This
// controller will rely on a long press gesture recognizer and JavaScript to
// determine the element on which context menu is triggered.
// The trigger delay is slightly shorter that ths system's one.
@interface CRWContextMenuController : NSObject

// Installs the |CRWContextMenuController| on |webView|.
// - |webView| cannot be nil. |webView| is not retained and caller is
//   responsible for keeping it alive.
// - |injectionEvaluator| can proxy all javascript calls to |webView| to
//   sanitize the eveluated strings. If |injectionEvaluator| is nil, JavaScript
//   is directly executed on |webView|.
// - This class relies on the pre-injection of base.js in webView.
// - This class will perform gesture recognition and JavaScript on every touch
//   event on |webView| and can have performance impact.
// TODO(crbug.com/228179): This class only triggers context menu on mainFrame.
- (instancetype)initWithWebView:(WKWebView*)webView
             injectionEvaluator:(id<CRWJSInjectionEvaluator>)injectionEvaluator
                       delegate:(id<CRWContextMenuDelegate>)delegate
    NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

@end

#endif  // IOS_WEB_WEB_STATE_UI_CRW_CONTEXT_MENU_CONTROLLER_H_
