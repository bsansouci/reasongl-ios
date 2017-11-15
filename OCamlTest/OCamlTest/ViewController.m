//
//  GameViewController.m
//  TestGame
//
//  Created by Benjamin San Soucie on 1/26/17.
//  Copyright © 2017 personal. All rights reserved.
//

#import "ViewController.h"
#import <OpenGLES/ES2/glext.h>


extern void doReasonThingsWithSelf(GameViewController *this);
extern void doUpdate(GameViewController *this);

@interface GameViewController ()

- (void)tearDownGL;

@end

@implementation GameViewController

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.preferredFramesPerSecond = 60;
	
	doReasonThingsWithSelf(self);
}

- (void)dealloc
{
	[self tearDownGL];
	
	if ([EAGLContext currentContext] == self.context) {
		[EAGLContext setCurrentContext:nil];
	}
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
	
	if ([self isViewLoaded] && ([[self view] window] == nil)) {
		self.view = nil;
		
		[self tearDownGL];
		
		if ([EAGLContext currentContext] == self.context) {
			[EAGLContext setCurrentContext:nil];
		}
		self.context = nil;
	}
	
	// Dispose of any resources that can be recreated.
}

- (BOOL)prefersStatusBarHidden {
	return YES;
}

- (void)tearDownGL {
	[EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update {
	doUpdate(self);
}

@end
