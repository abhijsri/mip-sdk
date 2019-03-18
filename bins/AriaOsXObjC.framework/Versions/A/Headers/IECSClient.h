//
//  IECSClient.h
//  ecsObjc
//
//  Created by Admin on 1/27/16.
//  Copyright (c) 2016 Microsoft. All rights reserved.
//

#ifndef IECSClient_h
#define IECSClient_h

#import "ILogger.h"

// classes without methods (basically, fancy structs - in ObjC, should use classes instead of structs if they have
//                                                      reference types as members, like NSString*)
// empty implementations defined in ECSClient.m
@interface ACTEcsClientConfiguration : NSObject

@property (atomic, strong) NSString* clientName;
@property (atomic, strong) NSString* clientVersion;
@property (atomic, strong) NSString* cacheFilePathName;
@property (atomic, assign) unsigned int defaultExpiryTimeInMin;
@property (atomic, strong) NSMutableArray* serverUrls;
@property (atomic, assign) BOOL enableECSClientTelemetry;

@end

@interface ACTEcsClientEventContext : NSObject

@property (atomic, assign) int expireTimeInSec;
@property (atomic, strong) NSString* clientName;
@property (atomic, strong) NSString* clientVersion;
@property (atomic, assign) BOOL configUpdatedFromECS;
@property (atomic, strong) NSString* userId;
@property (atomic, strong) NSString* deviceId;
@property (atomic, strong) NSDictionary* requestParameters;

@end

enum ACTEcsClientEventType
{
    ACTEcsClientEventTypeConfigUpdated = 0,
    ACTEcsClientEventTypeConfigUpdateFailed
};

@protocol ACTIEcsClientCallback <NSObject>

-(void)onECSClientEventType:(enum ACTEcsClientEventType)evtType context:(ACTEcsClientEventContext*)evtContext;

@end

@protocol ACTIEcsClient <NSObject>

-(BOOL)setConfiguration:(ACTEcsClientConfiguration*)config;
-(BOOL)addListener:(id<ACTIEcsClientCallback>)listener;
-(BOOL)removeListener:(id<ACTIEcsClientCallback>)listener;
-(BOOL)registerLogger:(id<ACTILogger>)logger forAgentName:(NSString* const)agentName;
-(BOOL)setUserId:(NSString* const)userId;
-(BOOL)setUserId:(NSString* const)userId userToken:(NSString* const)userToken;
-(BOOL)setDeviceId:(NSString* const)deviceId;
-(void)setRequestParameters:(NSDictionary* const)requestParams;
-(BOOL)start;
-(BOOL)stop;
-(BOOL)suspend;
-(BOOL)resume;
-(NSString*)eTag;
-(NSArray*)keysWithAgentName:(NSString* const)agentName forKeysPath:(NSString* const)keysPath;
-(NSString*)settingWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath stringDefaultValue:(NSString* const)defaultValue;
-(BOOL)settingWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath boolDefaultValue:(BOOL)defaultValue;
-(int)settingWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath intDefaultValue:(int)defaultValue;
-(double)settingWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath doubleDefaultValue:(double)defaultValue;
-(NSArray*)stringSettingsWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath;
-(NSArray*)intSettingsWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath;
-(NSArray*)doubleSettingsWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath;
-(NSString*)JSONSettingsWithAgentName:(NSString* const)agentName forPath:(NSString* const)settingPath;

@end

// implementation in ECSClientBuilder.m
@interface ACTEcsClientBuilder : NSObject

+(id<ACTIEcsClient>)ecsClient;

@end

#endif // IECSClient_h
