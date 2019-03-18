#ifndef ILogger_h
#define ILogger_h
//
//  Copyright (c) 2015 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "SchemaStub.h"
#import "ISemanticContext.h"

enum ACTEventPriority
{
    ACTEventPriorityUnspecified   = -1,
    ACTEventPriorityOff           =  0,
    ACTEventPriorityLow           =  1,
    ACTEventPriorityNormal        =  2,
    ACTEventPriorityHigh          =  3,
    ACTEventPriorityImmediate     =  4
};

enum ACTUserState
{
    /// Unknown: user state is unknown
    ACTUserStateUnknown,
    /// Connected: user is connected to a service
    ACTUserStateConnected,
    /// Reachable: user is reachable for a service like push notification
    ACTUserStateReachable,
    /// SignedIn: user is signed in
    ACTUserStateSignedIn,
    /// SignedOut: user is signed out
    ACTUserStateSignedOut
};

enum ACTSessionState
{
    ACTSessionStateStarted = 0,
    ACTSessionStateEnded = 1
};

@interface ACTEventProperties : NSObject

@property (nonatomic, strong, nonnull) NSString* eventName;
@property (nonatomic, assign) enum ACTEventPriority eventPriority;

// Xcode 6.4 doesn't support strongly typed dictionary.
// @property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDictionary<NSString *,NSString *> *properties;
// @property (NS_NONATOMIC_IOSONLY, readonly, copy) NSDictionary<NSString *,NSNumber *> *piiTags;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSDictionary* properties;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSDictionary* piiValues;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSDictionary* piiTags;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSDictionary* stringProperties;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSMutableDictionary* boolProperties;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSMutableDictionary* dateProperties;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSMutableDictionary* longProperties;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSMutableDictionary* doubleProperties;
@property (NS_NONATOMIC_IOSONLY, readonly, copy, nonnull) NSMutableDictionary* UUIDProperties;

-(nonnull instancetype)init;
-(nonnull instancetype)initWithName:(nonnull NSString*)aName;

@property (NS_NONATOMIC_IOSONLY) int64_t timestamp;

-(void)setStringValue:(nonnull NSString*)value forProperty:(nonnull NSString*)aProp;
-(void)setStringValue:(nonnull NSString*)value piiKind:(enum ACTPiiKind)aPiiKind forProperty:(nonnull NSString*)aProp;
-(void)setBoolValue:(BOOL)value forProperty:(nonnull NSString*)aProp;
-(void)setBoolValue:(BOOL)value piiKind:(enum ACTPiiKind)aPiiKind forProperty:(nonnull NSString*)aProp;
-(void)setDateValue:(nonnull NSDate*)value forProperty:(nonnull NSString*)aProp;
-(void)setDateValue:(nonnull NSDate*)value piiKind:(enum ACTPiiKind)aPiiKind forProperty:(nonnull NSString*)aProp;
-(void)setLongValue:(int64_t)value forProperty:(nonnull NSString*)aProp;
-(void)setLongValue:(int64_t)value piiKind:(enum ACTPiiKind)aPiiKind forProperty:(nonnull NSString*)aProp;
-(void)setDoubleValue:(double)value forProperty:(nonnull NSString*)aProp;
-(void)setDoubleValue:(double)value piiKind:(enum ACTPiiKind)aPiiKind forProperty:(nonnull NSString*)aProp;
-(void)setUUIDValue:(nonnull NSUUID*)value forProperty:(nonnull NSString*)aProp;
-(void)setUUIDValue:(nonnull NSUUID*)value piiKind:(enum ACTPiiKind)aPiiKind forProperty:(nonnull NSString*)aProp;

@end


@interface ACTPageActionData : NSObject

@property (nonatomic, strong, nonnull) NSString* pageViewId;
@property (nonatomic, assign) enum ACTActionType actionType;
@property (nonatomic, assign) enum ACTRawActionType rawActionType;
@property (nonatomic, assign) enum ACTInputDeviceType inputDeviceType;
@property (nonatomic, strong, nullable) NSString* targetItemId;
@property (nonatomic, strong, nullable) NSString* targetItemDataSourceName;
@property (nonatomic, strong, nullable) NSString* targetItemDataSourceCategory;
@property (nonatomic, strong, nullable) NSString* targetItemDataSourceCollection;
@property (nonatomic, strong, nullable) NSString* targetItemLayoutContainer;
@property (nonatomic, assign) unsigned short targetItemLayoutRank;
@property (nonatomic, strong, nonnull) NSString* destinationUri;

-(nullable instancetype)initWithPageViewIdentity:(nonnull NSString*)anId actionType:(enum ACTActionType)anAction;

@end


@interface ACTAggregatedMetricData : NSObject

@property (nonatomic, strong, nonnull) NSString* name;
@property (nonatomic, assign) long duration;
@property (nonatomic, assign) long count;
@property (nonatomic, strong, nullable) NSString* units;
@property (nonatomic, strong, nullable) NSString* instanceName;
@property (nonatomic, strong, nullable) NSString* objectClass;
@property (nonatomic, strong, nullable) NSString* objectId;
@property (nonatomic, strong, nullable) NSMutableDictionary* aggregates;
@property (nonatomic, strong, nullable) NSMutableDictionary* buckets;

-(nullable instancetype)initWithName:(nonnull NSString*)aggrName duration:(long)aggrDurationInMicros count:(long)aggrCount;

@end


@protocol ACTILogger <NSObject>

@property (NS_NONATOMIC_IOSONLY, readonly, strong, nonnull) id<ACTISemanticContext> semanticContext;

-(void) setContextWithName:(nonnull NSString*)aName stringValue:(nonnull NSString*)value piiKind:(enum ACTPiiKind)piiKind;
-(void) setContextWithName:(nonnull NSString*)aName stringValue:(nonnull NSString*)value;
-(void) setContextWithName:(nonnull NSString*)aName boolValue:(BOOL)value piiKind:(enum ACTPiiKind)piiKind;
-(void) setContextWithName:(nonnull NSString*)aName boolValue:(BOOL)value;
-(void) setContextWithName:(nonnull NSString*)aName dateValue:(nonnull NSDate*)value piiKind:(enum ACTPiiKind)piiKind;
-(void) setContextWithName:(nonnull NSString*)aName dateValue:(nonnull NSDate*)value;
-(void) setContextWithName:(nonnull NSString*)aName longValue:(int64_t)value piiKind:(enum ACTPiiKind)piiKind;
-(void) setContextWithName:(nonnull NSString*)aName longValue:(int64_t)value;
-(void) setContextWithName:(nonnull NSString*)aName doubleValue:(double)value piiKind:(enum ACTPiiKind)piiKind;
-(void) setContextWithName:(nonnull NSString*)aName doubleValue:(double)value;
-(void) setContextWithName:(nonnull NSString*)aName UUIDValue:(nonnull NSUUID*)value piiKind:(enum ACTPiiKind)piiKind;
-(void) setContextWithName:(nonnull NSString*)aName UUIDValue:(nonnull NSUUID*)value;

-(void) logAppLifecycleWithState:(enum ACTAppLifecycleState)state eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logEventWithName:(nonnull NSString*)aName;
-(void) logEventWithEventProperties:(nonnull ACTEventProperties*)properties;

-(void) logFailureWithSignature:(nonnull NSString*)aSignature
                         detail:(nonnull NSString*)aDetail
                eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logFailureWithSignature:(nonnull NSString*)aSignature
                         detail:(nonnull NSString*)aDetail
                       category:(nonnull NSString*)aCategory
                       identity:(nonnull NSString*)anId
                eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logPageViewWithIdentity:(nonnull NSString*)anId
                       pageName:(nonnull NSString*)aPageName
                eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logPageViewWithIdentity:(nonnull NSString*)anId
                       pageName:(nonnull NSString*)aPageName
                       category:(nonnull NSString*)aCategory
                            uri:(nonnull NSString*)anUri
                    referrerUri:(nonnull NSString*)aReferrerUri
                eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logPageActionWithPageViewIdentity:(nonnull NSString*)anId
                               actionType:(enum ACTActionType)anAction
                          eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logPageActionWithPageActionData:(nonnull ACTPageActionData*)pageActionData
                        eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logSampledMetricWithName:(nonnull NSString*)aName
                     doubleValue:(double)aDouble
                           units:(nonnull NSString*)aUnit
                 eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logSampledMetricWithName:(nonnull NSString*)aName
                     doubleValue:(double)aDouble
                           units:(nonnull NSString*)aUnit
                    instanceName:(nonnull NSString*)anInstanceName
                     objectClass:(nonnull NSString*)anObjectClass
                  objectIdentity:(nonnull NSString*)anId
                 eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logAggregatedMetricWithName:(nonnull NSString*)aName
                           duration:(long)aDurationInMicros
                              count:(long)aCount
                    eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logAggregatedMetricWithMetricData:(nonnull ACTAggregatedMetricData*)metricData
                          eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logTraceWithTraceLevel:(enum ACTTraceLevel)aLevel
                       message:(nonnull NSString*)aMessage
               eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logUserState:(enum ACTUserState)state timeToLiveInMillis:(long)timeToLive eventProperties:(nonnull ACTEventProperties*)properties;

-(void) logSessionWithState:(enum ACTSessionState)state;

-(void) logSessionWithState:(enum ACTSessionState)state
            eventProperties:(nonnull ACTEventProperties*)properties;

-(nullable NSString*) sessionId;

-(void) setAppExperimentIds:(nonnull NSString *)experimentIds;
-(void) setAppExperimentIds:(nonnull NSString *)experimentIds forEvent:(nonnull NSString *)eventName;
-(void) setAppExperimentETag:(nonnull NSString *)eTag;
-(void) setAppExperimentImpressionId:(nonnull NSString*)impressionId;

@end

#endif // ILogger_h

