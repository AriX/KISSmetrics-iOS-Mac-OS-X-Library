//
//  KISSMetricsAPI.h
//  KISSMetricsAPI
//
//  Created by Einar Vollset on 9/15/11.
//  Copyright 2011 KISSMetrics. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
#import <CoreServices/CoreServices.h>
#endif

@interface KISSMetricsAPI : NSObject


/**
* sharedAPIWithKey:
*
* Initializes the Kissmetrics API. Requires a valid API key.
*
* Parameters:
* - apiKey: The NSString API key obtained from kissmetrics.com
*
* Return Value:
* The singleton KissmetricsAPI. 
* 
* Discussion:
* Calling this method first before any other is required, it is therefore strongly 
* recommended that you call this in applicationDidFinishLaunching: of your app delegate. 
* Calling this method also identifies the current user with whatever identity was last 
* passed to identify:, or with an anonymous identifier if alias: has not been called yet 
* for this install.
*/
+ (KISSMetricsAPI *) sharedAPIWithKey:(NSString *)apiKey;



/**
* sharedAPI
*
* Returns the singleton KissmetricsAPI object previously initialized with sharedAPIWithKey:
* 
* Return Value:
* The singleton KissmetricsAPI object, or nil if sharedAPIWithKey: has not been called. 
* Note, in the latter case an error message will also be displayed on the log.
*/
+ (KISSMetricsAPI *) sharedAPI;




/**
* recordEvent:withProperties:
* 
* Records an event with an optional set of properties.
* 
* Parameters:
* - name: An NSString identifying this event. 
* 
* - properties: An NSDictionary of properties. The keys must all be non-nil, non-empty 
* NSStrings. The values must all be non-nil, non-empty NSStrings or NSNumber. Any key/value 
* pair that does not conform to this will be dropped with a warning message displayed on the log.
* 
* Discussion:
* 
* In theory you can make your event name as long as you like, and send as many properties as you want 
* up to about 8KB, but in practice, as this API makes HTTPS GET calls to KISSMetrics' servers you will 
* eventually hit the maximum URL length allowed by KISSMetrics servers. Anything where the total URL 
* generated by the API is > 2000 characters will generate a warning message on the logs. 
*/
- (void)recordEvent:(NSString *)name withProperties:(NSDictionary *)properties;

/**
* setProperties:properties
* 
* Sets one or more properties on a user.
* 
* 
* Parameters:
* 
* - properties: An NSDictionary of properties. The keys must all be non-nil, non-empty NSStrings. 
* The values must all be non-nil, non-empty NSStrings or NSNumber. Any key/value pair that does 
* not conform to this will be dropped with a warning message displayed on the log.
* 
* 
* Discussion:
* 
* In theory you can send as many properties as you want up to about 8KB, but in practice, as this API 
* makes HTTPS GET calls to KISSMetrics' servers you will eventually hit the maximum URL length allowed by 
* KISSMetrics servers. Anything where the total URL generated by the API is > 2000 characters will 
* generate a warning message on the logs. 
*/
- (void)setProperties:(NSDictionary *)properties;


/**
* identify:
* 
* Associates an identity (such as an email address) with a user.
* 
* 
* Parameters:
* - identity: An NSString identifying the current user. If nil or the empty string, this call is a no-op.
* 
* 
* Discussion:
* You can associate multiple identities with a user; the KISSMetrics website will allow you to view all 
* identities associated with any given user.
* The API will persist the latest identity passed in with identify: between sessions, and use this in 
* sharedAPIWithKey: (see sharedAPIWithKey:  for more details).
*/
- (void)identify:(NSString *)identity;

/**
 * alias:
 * 
 * Associates two identities (such as an email address and a name) with a user.
 * 
 * 
 * Parameters:
 * - firstIdentity: An NSString containing the first identity. If nil or the empty string, this call is a no-op.
 * - secondIdentity: An NSString containing the second identity. If nil or the empty string, this call is a no-op.
 * 
 * Discussion:
 * You can associate multiple identities with a user; the KISSMetrics website will allow you to view all 
 * identities associated with any given user.
 * Unlike identify, this API will NOT persist any identities.
 */
- (void)alias:(NSString *)firstIdentity withIdentity:(NSString *)secondIdentity;


#if TARGET_OS_MAC
/**
 * macVersionNumber
 * 
 * Returns back OS X version number using Gestalt()
 * 
 * 
 * Discussion:
 * You can return back the current version of Mac OS X that you're running.  This will return back a 
 * formatted NSString.  This is included in the logging props and is only defined for Mac OS X.
 */
+ (NSString *)macVersionNumber;
#endif

@end
