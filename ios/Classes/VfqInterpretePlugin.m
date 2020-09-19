#import "VfqInterpretePlugin.h"
#if __has_include(<vfq_interprete/vfq_interprete-Swift.h>)
#import <vfq_interprete/vfq_interprete-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "vfq_interprete-Swift.h"
#endif

@implementation VfqInterpretePlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftVfqInterpretePlugin registerWithRegistrar:registrar];
}
@end
