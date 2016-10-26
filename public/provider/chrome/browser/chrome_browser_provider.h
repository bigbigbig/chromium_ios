// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IOS_PUBLIC_PROVIDER_CHROME_BROWSER_CHROME_BROWSER_PROVIDER_H_
#define IOS_PUBLIC_PROVIDER_CHROME_BROWSER_CHROME_BROWSER_PROVIDER_H_

#include <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>
#include <stddef.h>

#include <memory>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "components/favicon_base/favicon_callback.h"

class AutocompleteProvider;
class GURL;
class InfoBarViewDelegate;
class PrefRegistrySimple;
class PrefService;
class VoiceSearchProvider;

namespace autofill {
class CardUnmaskPromptController;
class CardUnmaskPromptView;
}

namespace net {
class URLRequestContextGetter;
}

namespace web {
class WebState;
}

namespace sync_sessions {
class SyncedWindowDelegatesGetter;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

@protocol AppRatingPrompt;
@protocol InfoBarViewProtocol;
@protocol TextFieldStyling;
@class UITextField;
@class UIView;
typedef UIView<InfoBarViewProtocol>* InfoBarViewPlaceholder;

namespace ios {

class ChromeBrowserProvider;
class ChromeBrowserState;
class ChromeIdentityService;
class GeolocationUpdaterProvider;
class SigninErrorProvider;
class SigninResourcesProvider;
class LiveTabContextProvider;
class UpdatableResourceProvider;

// Setter and getter for the provider. The provider should be set early, before
// any browser code is called.
void SetChromeBrowserProvider(ChromeBrowserProvider* provider);
ChromeBrowserProvider* GetChromeBrowserProvider();

// A class that allows embedding iOS-specific functionality in the
// ios_chrome_browser target.
class ChromeBrowserProvider {
 public:
  ChromeBrowserProvider();
  virtual ~ChromeBrowserProvider();

  // Asserts all iOS-specific |BrowserContextKeyedServiceFactory| are built.
  virtual void AssertBrowserContextKeyedFactoriesBuilt();
  // Registers all prefs that will be used via a PrefService attached to a
  // Profile.
  virtual void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);
  // Returns an UpdatableResourceProvider instance.
  virtual UpdatableResourceProvider* GetUpdatableResourceProvider();
  // Returns an infobar view conforming to the InfoBarViewProtocol. The returned
  // object is retained.
  virtual InfoBarViewPlaceholder CreateInfoBarView(
      CGRect frame,
      InfoBarViewDelegate* delegate) NS_RETURNS_RETAINED;
  // Returns an instance of a signing error provider.
  virtual SigninErrorProvider* GetSigninErrorProvider();
  // Returns an instance of a signin resources provider.
  virtual SigninResourcesProvider* GetSigninResourcesProvider();
  // Sets the current instance of Chrome identity service. Used for testing.
  virtual void SetChromeIdentityServiceForTesting(
      std::unique_ptr<ChromeIdentityService> service);
  // Returns an instance of a Chrome identity service.
  virtual ChromeIdentityService* GetChromeIdentityService();
  // Returns an instance of a LiveTabContextProvider.
  virtual LiveTabContextProvider* GetLiveTabContextProvider();
  virtual GeolocationUpdaterProvider* GetGeolocationUpdaterProvider();
  // Returns "enabled", "disabled", or "default".
  virtual std::string DataReductionProxyAvailability();
  // Returns the distribution brand code.
  virtual std::string GetDistributionBrandCode();
  // Sets the alpha property of an UIView with an animation.
  virtual void SetUIViewAlphaWithAnimation(UIView* view, float alpha);
  // Returns an instance of a CardUnmaskPromptView used to unmask Wallet cards.
  // The view is responsible for its own lifetime.
  virtual autofill::CardUnmaskPromptView* CreateCardUnmaskPromptView(
      autofill::CardUnmaskPromptController* controller);
  // Returns risk data used in Wallet requests.
  virtual std::string GetRiskData();
  // Returns whether there is an Off-The-Record session active.
  virtual bool IsOffTheRecordSessionActive();
  // Get the favicon for |page_url| and run |callback| with result when loaded.
  // Note. |callback| is always run asynchronously.
  virtual void GetFaviconForURL(
      ChromeBrowserState* browser_state,
      const GURL& page_url,
      const std::vector<int>& desired_sizes_in_pixel,
      const favicon_base::FaviconResultsCallback& callback) const;
  // Creates and returns a new styled text field with the given |frame|.
  virtual UITextField<TextFieldStyling>* CreateStyledTextField(
      CGRect frame) const NS_RETURNS_RETAINED;
  // Creates and returns an app ratings prompt object.  Can return nil if app
  // ratings prompts are not supported by the provider.
  virtual id<AppRatingPrompt> CreateAppRatingPrompt() const NS_RETURNS_RETAINED;

  // Initializes the cast service.  Should be called soon after the given
  // |main_tab_model| is created.
  // TODO(rohitrao): Change from |id| to |TabModel*| once TabModel is moved into
  // the Chromium tree.
  virtual void InitializeCastService(id main_tab_model) const;

  // Attaches any embedder-specific tab helpers to the given |web_state|.  The
  // owning |tab| is included for helpers that need access to information that
  // is not yet available through web::WebState.
  // TODO(rohitrao): Change from |id| to |Tab*| once Tab is moved into the
  // Chromium tree.
  virtual void AttachTabHelpers(web::WebState* web_state, id tab) const;

  // Returns whether safe browsing is enabled. See the comment on
  // metrics_services_manager_client.h for details on |on_update_callback|.
  virtual bool IsSafeBrowsingEnabled(const base::Closure& on_update_callback);

  // Returns the list of available voice search languages.
  // TODO(rohitrao): Remove once callers are going through VoiceSearchProvider.
  virtual NSArray* GetAvailableVoiceSearchLanguages() const;

  // Returns an instance of the voice search provider, if one exists.
  virtual VoiceSearchProvider* GetVoiceSearchProvider() const;

  // Returns the SyncedWindowDelegatesGetter implementation.
  virtual std::unique_ptr<sync_sessions::SyncedWindowDelegatesGetter>
  CreateSyncedWindowDelegatesGetter(ios::ChromeBrowserState* browser_state);

  // TODO(rohitrao): This is a temporary method, used to prevent the tree from
  // breaking due to duplicate prefs registration.
  virtual bool ShouldEmbedderRegisterVoiceSearchPrefs() const;
};

}  // namespace ios

#endif  // IOS_PUBLIC_PROVIDER_CHROME_BROWSER_CHROME_BROWSER_PROVIDER_H_
