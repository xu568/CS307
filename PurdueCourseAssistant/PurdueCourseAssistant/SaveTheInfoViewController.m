//
//  SaveTheInfoViewController.m
//  PurdueCourseAssistant
//
//  Created by Hao Xu on 3/5/15.
//  Copyright (c) 2015 team_9. All rights reserved.
//

#import "SaveTheInfoViewController.h"
#import "ServerInfo.h"
#import "User.h"
#import "Course.h"

@interface SaveTheInfoViewController ()

//@property(strong, nonatomic) NSString * username;

@end

CFReadStreamRef readStream;
CFWriteStreamRef writeStream;

NSInputStream *inputStream;
NSOutputStream *outputStream;

NSString * s;

@implementation SaveTheInfoViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    [self initNetworkCommunication];
    _email.text = user.email;
    _nickname.text = user.nickname;
    _courselist.text = user.courses;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)save:(id)sender {
    NSString *username = @"Jiaping Qi";
    NSString *nickname = [_nickname text];
    NSString *email = [_email text];
    NSString *courselist = [_courselist text];
    if([_nickname.text length] != 0) {
        NSLog(@"%@", nickname);
        NSString *changen = [NSString stringWithFormat:@"changen|%@|%@", user.user_id, nickname];
        [self sendRequest: changen];
        [self initNetworkCommunication];
    }
    if([_email.text length] != 0) {
        NSLog(@"%@", email);
        user.email = email;
        NSString *changee = [NSString stringWithFormat:@"changee|%@|%@", user.user_id, email];
        [self sendRequest: changee];
        [self initNetworkCommunication];
    }
    if([_courselist.text length] != 0) {
        NSLog(@"%@", courselist);
        NSString *changec = [NSString stringWithFormat:@"changec|%@|%@", user.user_id, courselist];
        [self sendRequest:changec];
    }
}

- (void)initNetworkCommunication {
    ServerInfo * server = [[ServerInfo alloc] init];
    CFStringRef hostAddress = (__bridge CFStringRef)server.hostAddress;
    int port = [server.port intValue];
    NSLog(@"host = %@, port = %d", hostAddress, port);
    CFStreamCreatePairWithSocketToHost(kCFAllocatorDefault, hostAddress, port, &readStream, &writeStream);
    if(!CFWriteStreamOpen(writeStream)) {
        NSLog(@"Error: writeStream");
        return;
    }
    inputStream = (__bridge NSInputStream *)readStream;
    outputStream = (__bridge NSOutputStream *)writeStream;
    [inputStream setDelegate:self];
    [outputStream setDelegate:self];
    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [inputStream open];
    [outputStream open];
    
}

-(void)stream:(NSStream *)stream handleEvent:(NSStreamEvent)eventCode {
    switch (eventCode) {
        case NSStreamEventHasSpaceAvailable: {
            if(stream == outputStream){
                NSLog(@"none\n");
            }
            break;
        }
        case NSStreamEventHasBytesAvailable: {
            if(stream == inputStream) {
                uint8_t buf[1024];
                unsigned int len = 0;
                len = [inputStream read:buf maxLength:1024];
                if(len > 0) {
                    NSMutableData* data=[[NSMutableData alloc] initWithLength:0];
                    [data appendBytes: (const void *)buf length:len];
                    s = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
                    
                    /***************************************************/
                    // Process Server Respond
                    /***************************************************/

                    
                    
                    /***************************************************/
                    // End
                    /***************************************************/
                    
                }
            }
            break;
        }
        case NSStreamEventEndEncountered: {
            NSLog(@"Stream closed\n");
            break;
        }
        default: {
            NSLog(@"Stream is sending an Event: %lu", eventCode);
            break;
        }
    }
}

-(void)sendRequest: (NSString *) request{
    NSString * tmp = [NSString stringWithFormat:@"%@\r\n", request];
    NSData *data = [[NSData alloc] initWithData:[tmp dataUsingEncoding:NSASCIIStringEncoding]];
    [outputStream write:[data bytes] maxLength:[data length]];
    [outputStream close];
}


/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
