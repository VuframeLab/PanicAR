Pod::Spec.new do |s|
  s.name         = "PanicAR"
  s.version      = "3.0.3017"
  s.summary      = "Location-based Augmented Reality Framework for point of interest visualization."
  s.homepage     = "http://github.com/Vuframe/PanicAR"
  s.license      = {
     :type => 'proprietary',
     :text => 'http://panicar.vuframe.com/downloads/ar/PanicARLicenseTermsEN.pdf'
  }
  s.author       = { "Andreas Zeitler" => "azeitler@dopanic.com" }
  s.source       = {
    :git => "https://github.com/Vuframe/PanicAR.git",
    :tag => "#{s.version.to_s}"
  }
  s.platform        = :ios, '8.0'
  s.frameworks      =  'AVFoundation', 'CoreLocation', 'CoreMotion', 'CoreVideo', 'CoreMedia', 'CoreGraphics', 'UIKit', 'Foundation', 'QuartzCore', 'MapKit', 'PanicARKit'
  s.xcconfig        = {
    'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/PanicAR/Framework"'
  }
  s.preserve_paths  = 'Framework/PanicARKit.framework', 'Framework/PanicARKitResources.bundle'
  s.resources       = 'Framework/PanicARKitResources.bundle'
end
