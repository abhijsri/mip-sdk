//
//  IAFDClient.h
//  ObjCSdkDriver
//
//  Created by Admin on 12/19/16.
//  Copyright © 2016 Microsoft. All rights reserved.
//

#ifndef IAFDClient_h
#define IAFDClient_h

#import "ILogger.h"

// classes without methods (basically, fancy structs - in ObjC, should use classes instead of structs if they have
//                                                      reference types as members, like NSString*)
// empty implementations defined in AFDClient.m
@interface ACTAfdClientConfiguration : NSObject

@property (atomic, strong) NSString* clientId;
@property (atomic, strong) NSString* impressionGuid;
@property (atomic, strong) NSString* market;
@property (atomic, assign) int existingUser;
@property (atomic, assign) int corpnet;
@property (atomic, strong) NSString* setflight;
@property (atomic, strong) NSString* clientVersion;
@property (atomic, strong) NSString* cacheFilePathName;
@property (atomic, assign) unsigned int defaultExpiryTimeInMin;
@property (atomic, strong) NSMutableArray<NSString*>* serverUrls;
@property (atomic, assign) BOOL enableAFDClientTelemetry;
@property (atomic, assign) BOOL verbose;

@end

@interface ACTAfdClientEventContext : NSObject

@property (atomic, assign) int expireTimeInSec;
@property (atomic, strong) NSString* clientId;
@property (atomic, strong) NSString* clientVersion;
@property (atomic, assign) BOOL configUpdatedFromAFD;
@property (atomic, strong) NSDictionary<NSString*, NSString*>* requestHeaders;
@property (atomic, strong) NSDictionary<NSString*, NSString*>* requestParameters;
@property (atomic, strong) NSArray<NSString*>* features;
@property (atomic, strong) NSArray<NSString*>* flights;

@end

enum ACTAfdClientEventType
{
    ACTAfdClientEventTypeConfigUpdated = 0,
    ACTAfdClientEventTypeConfigUpdateFailed
};

@protocol ACTIAfdClientCallback <NSObject>

-(void)onAFDClientEventType:(enum ACTAfdClientEventType)evtType context:(ACTAfdClientEventContext*)evtContext;

@end

@protocol ACTIAfdClient <NSObject>

-(BOOL)setConfiguration:(ACTAfdClientConfiguration*)config;
-(BOOL)addListener:(id<ACTIAfdClientCallback>)listener;
-(BOOL)removeListener:(id<ACTIAfdClientCallback>)listener;
-(BOOL)registerLogger:(id<ACTILogger>)logger forAgentName:(NSString* const)agentName;
-(void)setRequestParameters:(NSDictionary<NSString*, NSString*>* const)requestParams;
-(void)setRequestHeaders:(NSDictionary<NSString*, NSString*>* const)requestHeaders;
-(BOOL)start;
-(BOOL)stop;
-(BOOL)suspend;
-(BOOL)resume;
-(NSArray<NSString*>*)flights;
-(NSArray<NSString*>*)features;
-(NSString*)eTag;

@end

// implementation in AFDClientBuilder.m
@interface ACTAfdClientBuilder : NSObject

+(id<ACTIAfdClient>)afdClient;

@end

#endif // IAFDClient_h
