Pod::Spec.new do |s|
  s.name         = "PanicARKit"
  s.version      = "2.0.2474"
  s.summary      = "basic classes to setup an app, includes useful categories and custom controls. includes tracking, resources and sharing utilities."
  s.homepage     = "http://github.com/doPanic/Developer"
  s.license      = {
     :type => 'proprietary',
     :text => 'http://dopanic.com/downloads/ar/PanicARLicenseTermsEN.pdf'
  }
  s.author       = { "Andreas Zeitler" => "azeitler@dopanic.com" }
  s.source       = { 
    :git => "git@bitbucket.org:dopanic/panicar-public.git",
    :tag => "#{s.version.to_s}"
  }
  s.platform        = :ios, '5.0'
  s.frameworks      =  'AVFoundation', 'CoreLocation', 'CoreMotion', 'CoreGraphics', 'UIKit', 'Foundation', 'QuartzCore', 'MapKit', 'PanicARKit'
  s.xcconfig        = { 'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/PanicARKit/Framework"' }
  s.preserve_paths  = 'Framework/PanicARKit.framework', 'Framework/PanicARKitResources.bundle'
  s.resources       = 'Framework/PanicARKitResources.bundle'
end
