//
//  Argon2idKdfCipher.m
//  Strongbox
//
//  Created by Strongbox on 13/01/2021.
//  Copyright © 2021 Mark McGuill. All rights reserved.
//

#import "Argon2idKdfCipher.h"

@implementation Argon2idKdfCipher

- (instancetype)initWithDefaults {
    return [super initWithDefaults:YES];
}

- (instancetype)initWithMemory:(uint64_t)memory parallelism:(uint32_t)parallelism iterations:(uint64_t)iterations {
    return [super initWithArgon2id:YES memory:memory parallelism:parallelism iterations:iterations];
}

@end
