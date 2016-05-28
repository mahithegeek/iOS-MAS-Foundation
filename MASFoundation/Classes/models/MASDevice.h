//
//  MASDevice.h
//  MASFoundation
//
//  Copyright (c) 2016 CA, Inc.
//
//  This software may be modified and distributed under the terms
//  of the MIT license. See the LICENSE file for details.
//

#import "MASObject.h"


@class MASAuthenticationProvider;

@protocol MASSessionSharingDelegate;


/**
 * The `MASDevice` class is a local representation of device data.
 */
@interface MASDevice : MASObject



///--------------------------------------
/// @name Properties
///--------------------------------------

# pragma mark - Properties

/**
 * Is the MASDevice registered.
 */
@property (nonatomic, assign, readonly) BOOL isRegistered;


/**
 * The MASDevice identifier.
 */
@property (nonatomic, copy, readonly) NSString *identifier;


/**
 * The MASDevice name.
 */
@property (nonatomic, copy, readonly) NSString *name;


/**
 * The MASDevice status.
 */
@property (nonatomic, copy, readonly) NSString *status;


/**
 *  Boolean indicator of whether the device is being authorized with other devices through session sharing.
 */
@property (assign) BOOL isBeingAuthorized;


/**
 *  The MASDeviceSessionSharingDelegate static property getter
 */
+ (id<MASSessionSharingDelegate>)SessionSharingDelegate;


/**
 *  The MASDeviceSessionSharingDelegate static property setter
 */
+ (void)setSessionSharingDelegate:(id<MASSessionSharingDelegate>)delegate;


///--------------------------------------
/// @name Current Device
///--------------------------------------

# pragma mark - Current Device

/**
 *  The device the application is running on. This is a singleton object.
 *
 *  @return Returns a singleton 'MASDevice' object.
 */
+ (MASDevice *)currentDevice;



/**
 *  Deregister the application resources on this device. This is a two step operation.
 *
 *  It will first attempt to remove the device's registered record in the cloud.  If it fails,
 *  an error is returned and the appropriate notification is sent and it will stop there.
 *
 *  Upon success of the first operation, deregistration in the cloud, it will then attempt to
 *  wipe the device of all credential settings.  If it fails, an error is returned and the appropriate
 *  notification is sent.  It will stop here.
 *
 *  WARNING #1: 
 * 
 *      A call to deregistration in the same session as the device was initially registered will
 *      fail and may leave the device in a strange state.  This call should work post
 *      initial registration and a restart of the application.
 *
 *  WARNING #2: 
 * 
 *      A successful call to deregistration will leave the current application session 
 *      without required credentials and settings.  You must restart the application
 *      to re-register the application and retrieve new credentials.
 *
 *  This should be considered an advanced feature.  If you make this available to end users it 
 *  should not be made too easily accessible and the UI control should be marked and possibly labeled
 *  to accentuate that it will wipe settings both in the cloud and locally on the device.  We
 *  recommend you also provide an additional user confirmation UI component to make it clear to 
 *  the user what will occur and allow them to cancel the operation or proceed.
 *
 *  Although an asynchronous block callback parameter is provided for detecting the response,
 *  optionally you can set that to nil and the caller can observe the lifecycle notifications instead.
 *
 *  The device deregistration notifications are:
 *
 *      MASDeviceWillDeregisterNotification
 *      MASDeviceDidFailToDeregisterInCloudNotification
 *      MASDeviceDidFailToDeregisterOnDeviceNotification
 *      MASDeviceDidDeregisterInCloudNotification
 *      MASDeviceDidDeregisterOnDeviceNotification
 *      MASDeviceDidRegisterNotification
 *
 *  @param completion The MASCompletionErrorBlock (BOOL completed, NSError *error) block that 
 *      receives the results.
 */
- (void)deregisterWithCompletion:(MASCompletionErrorBlock)completion;



/**
 *  Logout the device from the server.  This will revoke the id_token from the server and local by calling log out endpoint
 *  If clearLocal is defined as true, as part of log out process (revoking id_token),
 *  this method will also clear access_token, and refresh_token that are stored in local.
 *
 *  @param clearLocal BOOL boolean to indicate to clear local access_token and refresh_token or not.
 *  @param completion The MASCompletionErrorBlock (BOOL completed, NSError *error) block that
 *      receives the results.
 */
- (void)logOutDeviceAndClearLocal:(BOOL)clearLocal completion:(MASCompletionErrorBlock)completion DEPRECATED_MSG_ATTRIBUTE("Use [[MASUser currentUser] logoutWithCompletion:] instead.");



/**
 *  Reset the application's locally stored data on the device only.  This does NOT call the
 *  Gateway to remove the device record.  You must call deregisterWithCompletion: to do that.
 *
 *  WARNING if you call this all access credentials will be wiped.  You will have to reregister
 *  the application on the device to retrieve new ones.  It may be necessary to talk to the 
 *  administrator of your Gateway if you have issues.
 *
 *  @param completion The MASCompletionErrorBlock (BOOL completed, NSError *error) block that
 *      receives the results.
 */
- (void)resetLocallyWithCompletion:(MASCompletionErrorBlock)completion DEPRECATED_MSG_ATTRIBUTE("Use [[MASDevice currentDevice] resetLocally] instead.");



/**
 *  Reset the application's locally stored data on the device only.  This does NOT call the
 *  backend service to remove the device record.  You must call [[MASDevice currentDevice] deregisterWithCompletion:] to do that.
 *
 *  WARNING: if you call this method, all access credentials and locally stored configuration related to the application will be removed.  
 *  Re-authentication proccess will be triggered whenever you are trying to access the gateway.
 */
- (void)resetLocally;



///--------------------------------------
/// @name Bluetooth Peripheral
///--------------------------------------

# pragma mark - Bluetooth Peripheral

/**
 * Start the device acting as a bluetooth peripheral.
 */
- (void)startAsBluetoothPeripheral;



/**
 * Stop the device acting as a bluetooth peripheral.
 */
- (void)stopAsBluetoothPeripheral;



///--------------------------------------
/// @name Bluetooth Central
///--------------------------------------

# pragma mark - Bluetooth Central


/**
 *  Start the device acting as a bluetooth central.
 */
- (void)startAsBluetoothCentral;



/**
 *  Start the device acting as a bluetooth central with given authentication provider.
 *
 *  @param provider MASAuthenticationProvider to pass authentication information to other devices
 */
- (void)startAsBluetoothCentralWithAuthenticationProvider:(MASAuthenticationProvider *)provider;



/**
 * Stop the device acting as a bluetooth central.
 */
- (void)stopAsBluetoothCentral;

@end