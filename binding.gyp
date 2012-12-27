{
  'targets': [
    {
      'target_name': 'big_array',
      'sources': [
        'src/big_array.cpp'
      ],
       'include_dirs': [
         'include'
       ],

      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'conditions': [
        ['OS=="mac"', {
          'xcode_settings': {
            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
          }
        }]
      ]
    }
  ]
}
