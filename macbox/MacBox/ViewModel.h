//
//  ViewModel.h
//  MacBox
//
//  Created by Mark on 09/08/2017.
//  Copyright © 2017 Mark McGuill. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Document.h"
#import "Node.h"
#import "CHCSVParser.h"
#import "DatabaseModel.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString* const kModelUpdateNotificationCustomFieldsChanged;
extern NSString* const kModelUpdateNotificationPasswordChanged;
extern NSString* const kModelUpdateNotificationTitleChanged;
extern NSString* const kNotificationUserInfoKeyNode;
extern NSString* const kModelUpdateNotificationUsernameChanged;
extern NSString* const kModelUpdateNotificationEmailChanged;
extern NSString* const kModelUpdateNotificationUrlChanged;
extern NSString* const kModelUpdateNotificationNotesChanged;
extern NSString* const kModelUpdateNotificationIconChanged;
extern NSString* const kModelUpdateNotificationAttachmentsChanged;
extern NSString* const kModelUpdateNotificationTotpChanged;

@interface ViewModel : NSObject

- (instancetype _Nullable )init NS_UNAVAILABLE;
- (instancetype _Nullable )initNewWithSampleData:(Document*)document format:(DatabaseFormat)format password:(nullable NSString*)password keyFileDigest:(nullable NSData*)keyFileDigest;
- (instancetype _Nullable )initWithData:(NSData*)data document:(Document*)document;

- (void)importRecordsFromCsvRows:(NSArray<CHCSVOrderedDictionary*>*)rows;

- (BOOL)lock:(NSError**)error selectedItem:(NSString*_Nullable)selectedItem;
- (BOOL)unlock:(NSString*)password selectedItem:(NSString*_Nullable*_Nonnull)selectedItem error:(NSError**)error;
- (BOOL)unlock:(nullable NSString*)password keyFileDigest:(nullable NSData*)keyFileDigest selectedItem:(NSString*_Nullable*_Nonnull)selectedItem error:(NSError**)error;

- (BOOL)isDereferenceableText:(NSString*)text;
- (NSString*)dereference:(NSString*)text node:(Node*)node;

- (NSData*_Nullable)getPasswordDatabaseAsData:(NSError**)error;

- (BOOL)setItemTitle:(Node* )item title:(NSString* )title;
- (void)setItemUsername:(Node*)item username:(NSString*)username;
- (void)setItemEmail:(Node*)item email:(NSString*)email;
- (void)setItemUrl:(Node*)item url:(NSString*)url;
- (void)setItemPassword:(Node*)item password:(NSString*)password;
- (void)setItemNotes:(Node*)item notes:(NSString*)notes;
- (void)setItemIcon:(Node *)item index:(NSNumber*)index existingCustom:(NSUUID*)existingCustom custom:(NSData* _Nullable)custom;

- (void)deleteHistoryItem:(Node*)item historicalItem:(Node*)historicalItem;
- (void)restoreHistoryItem:(Node*)item historicalItem:(Node*)historicalItem;
    
- (void)removeItemAttachment:(Node*)item atIndex:(NSUInteger)atIndex;
- (void)addItemAttachment:(Node*)item attachment:(UiAttachment*)attachment;

- (void)setCustomField:(Node *)item key:(NSString *)key value:(StringValue *)value;
- (void)removeCustomField:(Node *)item key:(NSString *)key;

- (void)setTotp:(Node *)item otp:(NSString *)otp;
- (void)clearTotp:(Node *)item;

- (BOOL)addNewRecord:(Node *)parentGroup;
- (void)addNewGroup:(Node *)parentGroup;

- (BOOL)deleteItem:(Node *)child;
- (BOOL)deleteWillRecycle:(Node*_Nonnull)child;

- (BOOL)validateChangeParent:(Node *)parent node:(Node *)node;
- (BOOL)changeParent:(Node *)parent node:(Node *)node;

- (Node*_Nullable)getItemFromSerializationId:(NSString*)serializationId;

- (NSString*)generatePassword;

- (BOOL)isTitleMatches:(NSString*)searchText node:(Node*)node dereference:(BOOL)dereference;
- (BOOL)isUsernameMatches:(NSString*)searchText node:(Node*)node dereference:(BOOL)dereference;
- (BOOL)isPasswordMatches:(NSString*)searchText node:(Node*)node dereference:(BOOL)dereference;
- (BOOL)isUrlMatches:(NSString*)searchText node:(Node*)node dereference:(BOOL)dereference;
- (BOOL)isAllFieldsMatches:(NSString*)searchText node:(Node*)node dereference:(BOOL)dereference;
- (NSArray<NSString*>*)getSearchTerms:(NSString *)searchText;

@property (nonatomic, readonly) Document*  document;
@property (nonatomic, readonly) BOOL dirty;
@property (nonatomic, readonly) BOOL locked;
@property (nonatomic, readonly) NSURL*  fileUrl;
@property (nonatomic, readonly) Node*  rootGroup;
@property (nonatomic, readonly) BOOL masterCredentialsSet;
@property (nonatomic, readonly) DatabaseFormat format;
@property (nonatomic, readonly) id<AbstractDatabaseMetadata> metadata;
@property (nonatomic, readonly, nonnull) NSArray<DatabaseAttachment*> *attachments;
@property (nonatomic, readonly, nonnull) NSDictionary<NSUUID*, NSData*>* customIcons;

@property (nonatomic, readonly) NSString* masterPassword;
@property (nonatomic, readonly) NSData* masterKeyFileDigest;
- (void)setMasterCredentials:(NSString *)masterPassword masterKeyFileDigest:(NSData *)masterKeyFileDigest;

@property (readonly) BOOL recycleBinEnabled; // Read-Only until we allow config
@property (readonly) Node* recycleBinNode;
- (void)createNewRecycleBinNode;

// Convenience / Summary

@property (readonly) NSArray<Node*>* activeRecords;

@property (nonatomic, readonly, copy) NSSet<NSString*> * usernameSet;
@property (nonatomic, readonly, copy) NSSet<NSString*> * urlSet;
@property (nonatomic, readonly, copy) NSSet<NSString*> * emailSet;
@property (nonatomic, readonly, copy) NSSet<NSString*> * passwordSet;
@property (nonatomic, readonly) NSString * mostPopularUsername;
@property (nonatomic, readonly) NSString * mostPopularPassword;
@property (nonatomic, readonly) NSInteger numberOfRecords;
@property (nonatomic, readonly) NSInteger numberOfGroups;

@property (nonatomic, copy) void (^onNewItemAdded)(Node* node);
@property (nonatomic, copy) void (^onDeleteItem)(Node* node);
@property (nonatomic, copy) void (^onChangeParent)(Node* node);
@property (nonatomic, copy) void (^onDeleteHistoryItem)(Node* item, Node* historicalItem);
@property (nonatomic, copy) void (^onRestoreHistoryItem)(Node* item, Node* historicalItem);

@end

NS_ASSUME_NONNULL_END
