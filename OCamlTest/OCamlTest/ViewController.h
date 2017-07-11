//
//  ViewController.h
//  OCamlTest
//
//  Created by Wojciech Czekalski on 22.01.2017.
//  Copyright © 2017 wokalski. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

@interface GameViewController : GLKViewController

@property (strong, nonatomic) EAGLContext *context;
@property (strong, nonatomic) GLKBaseEffect *effect;

@property (nonatomic) GLuint program;

@property (nonatomic) GLKMatrix4 modelViewProjectionMatrix;
@property (nonatomic) GLKMatrix3 normalMatrix;
@property (nonatomic) float rotation;

@property (nonatomic) GLuint vertexArray;
@property (nonatomic) GLuint vertexBuffer;

@property (nonatomic) GLint umvp;
@property (nonatomic) GLint unormal;

@end
