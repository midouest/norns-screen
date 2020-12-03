{
  'targets': [
    {
      'target_name': 'norns-screen-native',
      'sources': [ 'src/norns_screen.cc' ],
      'include_dirs': [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/opt/homebrew/include",
        "/opt/homebrew/include/freetype2"
      ],
      "libraries": [
        "/opt/homebrew/lib/libcairo.a",
        "/opt/homebrew/lib/libpixman-1.a",
        "/opt/homebrew/lib/libpng.a",
        "/opt/homebrew/lib/libfreetype.a"
      ],
      'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
        'CLANG_CXX_LIBRARY': 'libc++',
        'MACOSX_DEPLOYMENT_TARGET': '10.7'
      },
      'msvs_settings': {
        'VCCLCompilerTool': { 'ExceptionHandling': 1 },
      }
    }
  ]
}